multiline_comment|/* hp.c: A HP LAN ethernet driver for linux. */
multiline_comment|/*&n;&t;Written 1993 by Donald Becker.&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.&t; This software may be used and&n;&t;distributed according to the terms of the GNU Public License,&n;&t;incorporated herein by reference.&n;&n;&t;This is a driver for the HP LAN adaptors.&n;&n;&t;The Author may be reached as becker@super.org or&n;&t;C/O Supercomputing Research Ctr., 17100 Science Dr., Bowie MD 20715&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;hp.c:v0.99.15k 3/3/94 Donald Becker (becker@super.org)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
macro_line|#ifndef HAVE_PORTRESERVE
DECL|macro|check_region
mdefine_line|#define check_region(ioaddr, size)&t;&t;&t;&t;0
DECL|macro|snarf_region
mdefine_line|#define snarf_region(ioaddr, size);&t;&t;&t;&t;do ; while (0)
macro_line|#endif
DECL|macro|HP_IO_EXTENT
mdefine_line|#define HP_IO_EXTENT&t;32
DECL|macro|HP_DATAPORT
mdefine_line|#define HP_DATAPORT&t;&t;0x0c&t;/* &quot;Remote DMA&quot; data port. */
DECL|macro|HP_ID
mdefine_line|#define HP_ID&t;&t;&t;0x07
DECL|macro|HP_CONFIGURE
mdefine_line|#define HP_CONFIGURE&t;0x08&t;/* Configuration register. */
DECL|macro|HP_RUN
mdefine_line|#define&t; HP_RUN&t;&t;&t;0x01&t;/* 1 == Run, 0 == reset. */
DECL|macro|HP_IRQ
mdefine_line|#define&t; HP_IRQ&t;&t;&t;0x0E&t;/* Mask for software-configured IRQ line. */
DECL|macro|HP_DATAON
mdefine_line|#define&t; HP_DATAON&t;&t;0x10&t;/* Turn on dataport */
DECL|macro|NIC_OFFSET
mdefine_line|#define NIC_OFFSET&t;&t;0x10&t;/* Offset the 8390 registers. */
DECL|macro|HP_START_PG
mdefine_line|#define HP_START_PG&t;&t;0x00&t;/* First page of TX buffer */
DECL|macro|HP_8BSTOP_PG
mdefine_line|#define HP_8BSTOP_PG&t;0x80&t;/* Last page +1 of RX ring */
DECL|macro|HP_16BSTOP_PG
mdefine_line|#define HP_16BSTOP_PG&t;0xFF&t;/* Same, for 16 bit cards. */
r_int
id|hp_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|hpprobe1
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
r_void
id|hp_reset_8390
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
id|hp_block_input
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
id|hp_block_output
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
r_void
id|hp_init_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* The map from IRQ number to HP_CONFIGURE register setting. */
multiline_comment|/* My default is IRQ5&t;   0  1&t; 2  3  4  5  6&t;7  8  9 10 11 */
DECL|variable|irqmap
r_static
r_char
id|irqmap
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|10
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|4
comma
l_int|2
comma
l_int|12
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
"&f;"
multiline_comment|/*&t;Probe for an HP LAN adaptor.&n;&t;Also initialize the card and fill in STATION_ADDR with the station&n;&t;address. */
DECL|function|hp_probe
r_int
id|hp_probe
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
l_int|0x320
comma
l_int|0x340
comma
l_int|0x280
comma
l_int|0x2C0
comma
l_int|0x200
comma
l_int|0x240
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
OG
l_int|0x1ff
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|hpprobe1
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
r_if
c_cond
(paren
id|check_region
c_func
(paren
op_star
id|port
comma
id|HP_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|hpprobe1
c_func
(paren
id|dev
comma
op_star
id|port
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|ENODEV
suffix:semicolon
)brace
DECL|function|hpprobe1
r_int
id|hpprobe1
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
comma
id|board_id
comma
id|wordmode
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
r_char
op_star
id|station_addr
op_assign
id|dev-&gt;dev_addr
suffix:semicolon
multiline_comment|/* Check for the HP physical address, 08 00 09 xx xx xx. */
multiline_comment|/* This really isn&squot;t good enough: we may pick up HP LANCE boards&n;&t;   also!  Avoid the lance 0x5757 signature. */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
)paren
op_ne
l_int|0x08
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_ne
l_int|0x00
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|2
)paren
op_ne
l_int|0x09
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|14
)paren
op_eq
l_int|0x57
)paren
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* Set up the parameters based on the board ID.&n;&t;   If you have additional mappings, please mail them to becker@super.org. */
r_if
c_cond
(paren
(paren
id|board_id
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|HP_ID
)paren
)paren
op_amp
l_int|0x80
)paren
(brace
id|name
op_assign
l_string|&quot;HP27247&quot;
suffix:semicolon
id|wordmode
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|name
op_assign
l_string|&quot;HP27250&quot;
suffix:semicolon
id|wordmode
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Grab the region so we can find another board if something fails. */
id|snarf_region
c_func
(paren
id|ioaddr
comma
id|HP_IO_EXTENT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s (ID %02x) at %#3x,&quot;
comma
id|dev-&gt;name
comma
id|name
comma
id|board_id
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
l_string|&quot; %2.2x&quot;
comma
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
id|i
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Snarf the interrupt now.  Someday this could be moved to open(). */
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|2
)paren
(brace
r_int
id|irq_16list
(braket
)braket
op_assign
(brace
l_int|11
comma
l_int|10
comma
l_int|5
comma
l_int|3
comma
l_int|4
comma
l_int|7
comma
l_int|9
comma
l_int|0
)brace
suffix:semicolon
r_int
id|irq_8list
(braket
)braket
op_assign
(brace
l_int|7
comma
l_int|5
comma
l_int|3
comma
l_int|4
comma
l_int|9
comma
l_int|0
)brace
suffix:semicolon
r_int
op_star
id|irqp
op_assign
id|wordmode
ques
c_cond
id|irq_16list
suffix:colon
id|irq_8list
suffix:semicolon
r_do
(brace
r_int
id|irq
op_assign
op_star
id|irqp
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
(paren
id|irq
comma
l_int|NULL
)paren
op_ne
op_minus
id|EBUSY
)paren
(brace
id|autoirq_setup
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Twinkle the interrupt, and check if it&squot;s seen. */
id|outb_p
c_func
(paren
id|irqmap
(braket
id|irq
)braket
op_or
id|HP_RUN
comma
id|ioaddr
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
op_or
id|HP_RUN
comma
id|ioaddr
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|autoirq_report
c_func
(paren
l_int|0
)paren
multiline_comment|/* It&squot;s a good IRQ line! */
op_logical_and
id|request_irq
(paren
id|irq
comma
op_amp
id|ei_interrupt
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; selecting IRQ %d.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
op_star
id|irqp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
op_star
op_increment
id|irqp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|irqp
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; no free IRQ lines.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|EBUSY
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|irqaction
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|ei_sigaction
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
id|EBUSY
suffix:semicolon
)brace
)brace
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
id|version
)paren
suffix:semicolon
multiline_comment|/* Set the base address to point to the NIC, not the &quot;real&quot; base! */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|NIC_OFFSET
suffix:semicolon
id|ethdev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ei_status.name
op_assign
id|name
suffix:semicolon
id|ei_status.word16
op_assign
id|wordmode
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|HP_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|HP_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|wordmode
ques
c_cond
id|HP_16BSTOP_PG
suffix:colon
id|HP_8BSTOP_PG
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|hp_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|hp_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|hp_block_output
suffix:semicolon
id|hp_init_card
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|hp_reset_8390
id|hp_reset_8390
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|hp_base
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|saved_config
op_assign
id|inb_p
c_func
(paren
id|hp_base
op_plus
id|HP_CONFIGURE
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
l_string|&quot;resetting the 8390 time=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|hp_base
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Pause just a few cycles for the hardware reset to take place. */
id|SLOW_DOWN_IO
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
id|outb_p
c_func
(paren
id|saved_config
comma
id|hp_base
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|hp_base
op_plus
id|NIC_OFFSET
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: hp_reset_8390() did not complete.&bslash;n&quot;
comma
id|dev-&gt;name
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
l_string|&quot;8390 reset done (%ld).&quot;
comma
id|jiffies
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver.&t; If you&n;   porting to a new ethercard look at the packet driver source for hints.&n;   The HP LAN doesn&squot;t use shared memory -- we put the packet&n;   out through the &quot;remote DMA&quot; dataport. */
r_static
r_int
DECL|function|hp_block_input
id|hp_block_input
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
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|saved_config
op_assign
id|inb_p
c_func
(paren
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
r_int
id|xfer_count
op_assign
id|count
suffix:semicolon
id|outb_p
c_func
(paren
id|saved_config
op_or
id|HP_DATAON
comma
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
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
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_DATAPORT
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
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_DATAPORT
)paren
comma
id|xfer_count
op_increment
suffix:semicolon
)brace
r_else
(brace
id|insb
c_func
(paren
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_DATAPORT
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* This is for the ALPHA version only, remove for later releases. */
r_if
c_cond
(paren
id|ei_debug
OG
l_int|0
)paren
(brace
multiline_comment|/* DMA termination address check... */
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
r_int
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
multiline_comment|/* Check only the lower 8 bits so we can ignore ring wrap. */
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
op_ne
(paren
id|addr
op_amp
l_int|0xff
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: RX transfer address mismatch, %#4.4x vs. %#4.4x (actual).&bslash;n&quot;
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
id|outb_p
c_func
(paren
id|saved_config
op_amp
(paren
op_complement
id|HP_DATAON
)paren
comma
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
r_return
id|ring_offset
op_plus
id|count
suffix:semicolon
)brace
r_static
r_void
DECL|function|hp_block_output
id|hp_block_output
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
(brace
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|saved_config
op_assign
id|inb_p
c_func
(paren
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|saved_config
op_or
id|HP_DATAON
comma
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
multiline_comment|/* Round the count up for word writes.&t;Do we need to do this?&n;&t;   What effect will an odd byte count have on the 8390?&n;&t;   I should check someday. */
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
)paren
suffix:semicolon
macro_line|#ifdef ei8390_bug
multiline_comment|/* Handle the read-before-write bug the same way as the&n;&t;   Crynwr packet driver -- the NatSemi method doesn&squot;t work. */
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
id|EN_CMD
)paren
suffix:semicolon
multiline_comment|/* Make certain that the dummy read has occured. */
id|inb_p
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
id|inb_p
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
macro_line|#endif
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
multiline_comment|/* Use the &squot;rep&squot; sequence for 16 bit boards. */
id|outsw
c_func
(paren
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_DATAPORT
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
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_DATAPORT
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* DON&squot;T check for &squot;inb_p(EN0_ISR) &amp; ENISR_RDC&squot; here -- it&squot;s broken! */
multiline_comment|/* This is for the ALPHA version only, remove for later releases. */
r_if
c_cond
(paren
id|ei_debug
OG
l_int|0
)paren
(brace
multiline_comment|/* DMA termination address check... */
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
r_int
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
op_ne
id|addr
)paren
id|printk
c_func
(paren
l_string|&quot;%s: TX Transfer address mismatch, %#4.4x vs. %#4.4x.&bslash;n&quot;
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
)brace
id|outb_p
c_func
(paren
id|saved_config
op_amp
(paren
op_complement
id|HP_DATAON
)paren
comma
id|nic_base
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This function resets the ethercard if something screws up. */
r_static
r_void
DECL|function|hp_init_card
id|hp_init_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|irqmap
(braket
id|irq
op_amp
l_int|0x0f
)braket
op_or
id|HP_RUN
comma
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
op_plus
id|HP_CONFIGURE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; * compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/net/inet -Wall -Wstrict-prototypes -O6 -m486 -c hp.c&quot;&n; * version-control: t&n; * kept-new-versions: 5&n; * tab-width: 4&n; * c-indent-level: 4&n; * End:&n; */
eof
