multiline_comment|/* e2100.c: A Cabletron E2100 series ethernet driver for linux. */
multiline_comment|/*&n;    Written 1993 by Donald Becker.&n;    Copyright 1993 United States Government as represented by the&n;    Director, National Security Agency.  This software may be used and&n;    distributed according to the terms of the GNU Public License,&n;    incorporated herein by reference.&n;&n;    This is a driver for the Cabletron E2100 series ethercards.&n;&n;    The Author may be reached as becker@cesdis.gsfc.nasa.gov, or&n;    C/O Supercomputing Research Ctr., 17100 Science Dr., Bowie MD 20715&n;&n;&t;The E2100 series ethercard is a fairly generic shared memory 8390&n;&t;implementation.  The only unusual aspect is the way the shared memory&n;&t;registers are set: first you do an inb() in what is normally the&n;&t;station address region, and the low four bits of next outb() is used&n;&t;as the write value for that register.  Either someone wasn&squot;t too used&n;&t;to dem bit en bites, or they were trying to obfusicate the programming&n;&t;interface.&n;&n;&t;There is an additional complication when setting the window on the packet&n;&t;buffer.  You must first do a read into the packet buffer region with the&n;&t;low 8 address bits the address setting the page for the start of the packet&n;&t;buffer window, and then do the above operation.  See mem_on() for details.&n;&n;&t;One bug on the chip is that even a hard reset won&squot;t disable the memory&n;&t;window, usually resulting in a hung machine if mem_off() isn&squot;t called.&n;&t;If this happens, you must power down the machine for about 30 seconds.&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;e2100.c:v0.01 11/21/93 Donald Becker (becker@super.org)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifndef PRE_PL13
macro_line|#include &lt;linux/ioport.h&gt;       /* Delete if your kernel doesn&squot;t have it. */
macro_line|#endif
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* Compatibility definitions for earlier kernel versions. */
macro_line|#ifndef HAVE_PORTRESERVE
DECL|macro|check_region
mdefine_line|#define check_region(ioaddr, size)              0
DECL|macro|snarf_region
mdefine_line|#define snarf_region(ioaddr, size);             do ; while (0)
macro_line|#endif
macro_line|#ifndef HAVE_AUTOIRQ
multiline_comment|/* From auto_irq.c, in ioport.h for later versions. */
r_extern
r_void
id|autoirq_setup
c_func
(paren
r_int
id|waittime
)paren
suffix:semicolon
r_extern
r_int
id|autoirq_report
c_func
(paren
r_int
id|waittime
)paren
suffix:semicolon
multiline_comment|/* The map from IRQ number (as passed to the interrupt handler) to&n;   &squot;struct device&squot;. */
r_extern
r_struct
id|device
op_star
id|irq2dev_map
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* Offsets from the base_addr.&n;   Read from the ASIC register, and the low 3(?) bits of the next outb() address&n;   is used to set the cooresponding register. */
DECL|macro|E21_NIC_OFFSET
mdefine_line|#define E21_NIC_OFFSET  0       /* Offset to the 8390 NIC. */
DECL|macro|E21_ASIC
mdefine_line|#define E21_ASIC&t;&t;0x10
DECL|macro|E21_MEM_ENABLE
mdefine_line|#define E21_MEM_ENABLE&t;0x10
DECL|macro|E21_MEM_ON
mdefine_line|#define  E21_MEM_ON&t;&t;0x05&t;/* Enable memory in 16 bit mode. */
DECL|macro|E21_MEM_ON_8
mdefine_line|#define  E21_MEM_ON_8&t;0x07&t;/* Enable memory in  8 bit mode. */
DECL|macro|E21_MEM_BASE
mdefine_line|#define E21_MEM_BASE&t;0x11&t;
DECL|macro|E21_IRQ_LOW
mdefine_line|#define E21_IRQ_LOW&t;&t;0x12&t;/* The low three bits of the IRQ number. */
DECL|macro|E21_IRQ_HIGH
mdefine_line|#define E21_IRQ_HIGH&t;0x14&t;/* The high IRQ bit, and ...  */
DECL|macro|E21_ALT_IFPORT
mdefine_line|#define  E21_ALT_IFPORT 0x02&t;/* Set to use the other (BNC,AUI) port. */
DECL|macro|E21_BIG_MEM
mdefine_line|#define  E21_BIG_MEM&t;0x04&t;/* Use a bigger (64K) buffer (we don&squot;t) */
DECL|macro|E21_SAPROM
mdefine_line|#define E21_SAPROM      0x10    /* Offset to station address data. */
DECL|macro|ETHERCARD_TOTAL_SIZE
mdefine_line|#define ETHERCARD_TOTAL_SIZE    0x20
DECL|function|mem_on
r_extern
r_inline
r_void
id|mem_on
c_func
(paren
r_int
id|port
comma
r_volatile
r_char
op_star
id|mem_base
comma
r_int
r_char
id|start_page
)paren
(brace
multiline_comment|/* This is a little weird: set the shared memory window by doing a&n;&t;   read.  The low address bits specify the starting page. */
id|mem_base
(braket
id|start_page
)braket
suffix:semicolon
id|inb
c_func
(paren
id|port
op_plus
id|E21_MEM_ENABLE
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E21_MEM_ON
comma
id|port
op_plus
id|E21_MEM_ENABLE
op_plus
id|E21_MEM_ON
)paren
suffix:semicolon
)brace
DECL|function|mem_off
r_extern
r_inline
r_void
id|mem_off
c_func
(paren
r_int
id|port
)paren
(brace
id|inb
c_func
(paren
id|port
op_plus
id|E21_MEM_ENABLE
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|port
op_plus
id|E21_MEM_ENABLE
)paren
suffix:semicolon
)brace
multiline_comment|/* In other drivers I put the TX pages first, but the E2100 window circuitry&n;   is designed to have a 4K Tx region last. The windowing circuitry wraps the&n;   window at 0x2fff-&gt;0x0000 so that the packets at e.g. 0x2f00 in the RX ring&n;   appear contiguously in the window. */
DECL|macro|E21_RX_START_PG
mdefine_line|#define E21_RX_START_PG    0x00    /* First page of RX buffer */
DECL|macro|E21_RX_STOP_PG
mdefine_line|#define E21_RX_STOP_PG     0x30    /* Last page +1 of RX ring */
DECL|macro|E21_BIG_RX_STOP_PG
mdefine_line|#define E21_BIG_RX_STOP_PG 0xF0    /* Last page +1 of RX ring */
DECL|macro|E21_TX_START_PG
mdefine_line|#define E21_TX_START_PG  E21_RX_STOP_PG    /* First page of TX buffer */
r_int
id|e2100_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|e21_probe1
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
id|e21_open
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
id|e21_reset_8390
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
id|e21_block_input
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
id|e21_block_output
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
id|e21_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
multiline_comment|/*  Probe for the E2100 series ethercards.  These cards have an 8390 at the&n;&t;base address and the station address at both offset 0x10 and 0x18.  I read&n;&t;the station address from offset 0x18 to avoid the dataport of NE2000&n;&t;ethercards, and look for Ctron&squot;s unique ID (first three octets of the&n;&t;station address).&n; */
DECL|function|e2100_probe
r_int
id|e2100_probe
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
l_int|0x380
comma
l_int|0x220
comma
l_int|0
)brace
suffix:semicolon
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
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
id|e21_probe1
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
id|ushort
id|ioaddr
op_assign
op_star
id|port
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ioaddr
comma
id|ETHERCARD_TOTAL_SIZE
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|0
)paren
op_eq
l_int|0x00
op_logical_and
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|1
)paren
op_eq
l_int|0x00
op_logical_and
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|2
)paren
op_eq
l_int|0x1d
op_logical_and
id|e21_probe1
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
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|e21_probe1
r_int
id|e21_probe1
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
id|status
suffix:semicolon
r_int
r_char
op_star
id|station_addr
op_assign
id|dev-&gt;dev_addr
suffix:semicolon
multiline_comment|/* We&squot;ve already checked the station address prefix, now verify by making&n;&t;   certain that there is a 8390 at the expected location. */
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_STOP
comma
id|ioaddr
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
id|status
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
id|status
op_ne
l_int|0x21
op_logical_and
id|status
op_ne
l_int|0x23
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#ifdef testing_only
id|printk
c_func
(paren
l_string|&quot;%s: E21xx at %#3x (PAXI backwards): &quot;
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02X&quot;
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x1f
op_minus
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Read the station address PROM.  */
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
id|E21_SAPROM
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Grab the region so we can find another board if needed . */
id|snarf_region
c_func
(paren
id|ioaddr
comma
id|ETHERCARD_TOTAL_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: E21xx at %#3x, &quot;
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
l_string|&quot; %02X&quot;
comma
id|station_addr
(braket
id|i
)braket
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
id|irqlist
(braket
)braket
op_assign
(brace
l_int|15
comma
l_int|11
comma
l_int|10
comma
l_int|12
comma
l_int|5
comma
l_int|9
comma
l_int|3
comma
l_int|4
)brace
comma
id|i
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
r_if
c_cond
(paren
id|request_irq
(paren
id|irqlist
(braket
id|i
)braket
comma
l_int|NULL
)paren
op_ne
op_minus
id|EBUSY
)paren
(brace
id|dev-&gt;irq
op_assign
id|irqlist
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
multiline_comment|/* Fixup bogosity: IRQ2 is really IRQ9 */
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* Snarf the interrupt now. */
r_if
c_cond
(paren
id|irqaction
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
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* The 8390 is at the base address. */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|ethdev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;E2100&quot;
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|E21_TX_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|E21_RX_START_PG
suffix:semicolon
id|ei_status.stop_page
op_assign
id|E21_RX_STOP_PG
suffix:semicolon
multiline_comment|/* Check the media port used.  The port can be passed in on the&n;&t;   low mem_end bits. */
r_if
c_cond
(paren
id|dev-&gt;mem_end
op_amp
l_int|15
)paren
id|dev-&gt;if_port
op_assign
id|dev-&gt;mem_end
op_amp
l_int|7
suffix:semicolon
r_else
(brace
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_HIGH
)paren
suffix:semicolon
multiline_comment|/* Select if_port detect. */
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
r_if
c_cond
(paren
id|station_addr
(braket
id|i
)braket
op_ne
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
)paren
)paren
id|dev-&gt;if_port
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Never map in the E21 shared memory unless you are actively using it.&n;&t;   Also, the shared memory has effective only one setting -- spread all&n;&t;   over the 128K region! */
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
id|dev-&gt;mem_start
op_assign
l_int|0xd0000
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* These values are unused.  The E2100 has a 2K window into the packet&n;&t;   buffer.  The window can be set to start on any page boundary. */
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
l_int|2
op_star
l_int|1024
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot; IRQ %d, %s interface,  memory at %#x-%#x.&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|dev-&gt;if_port
ques
c_cond
l_string|&quot;secondary&quot;
suffix:colon
l_string|&quot;primary&quot;
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_start
op_plus
l_int|2
op_star
l_int|1024
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
id|e21_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|e21_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|e21_block_output
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|e21_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|e21_close
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
DECL|function|e21_open
id|e21_open
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
suffix:semicolon
multiline_comment|/* Set the interrupt line and memory base on the hardware. */
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_LOW
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
op_plus
(paren
id|dev-&gt;irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_HIGH
)paren
suffix:semicolon
multiline_comment|/* High IRQ bit, and if_port. */
id|outb_p
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
op_plus
(paren
id|dev-&gt;irq
OG
l_int|7
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_plus
(paren
id|dev-&gt;if_port
ques
c_cond
id|E21_ALT_IFPORT
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|E21_MEM_BASE
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
op_plus
(paren
(paren
id|dev-&gt;mem_start
op_rshift
l_int|17
)paren
op_amp
l_int|7
)paren
)paren
suffix:semicolon
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
DECL|function|e21_reset_8390
id|e21_reset_8390
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
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
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
l_string|&quot;resetting the E2180x3 t=%d...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set up the ASIC registers, just in case something changed them. */
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
multiline_comment|/* Block input and output are easy on shared memory ethercards.  The E21xx makes&n;   block_input() especially easy by wrapping the top ring buffer to the bottom&n;   automatically. */
r_static
r_int
DECL|function|e21_block_input
id|e21_block_input
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_char
op_star
id|shared_mem
op_assign
(paren
r_char
op_star
)paren
id|dev-&gt;mem_start
suffix:semicolon
r_int
id|start_page
op_assign
(paren
id|ring_offset
op_rshift
l_int|8
)paren
suffix:semicolon
id|mem_on
c_func
(paren
id|ioaddr
comma
id|shared_mem
comma
id|start_page
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll always get a 4 byte header read first. */
r_if
c_cond
(paren
id|count
op_eq
l_int|4
)paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|0
)braket
op_assign
(paren
(paren
r_int
op_star
)paren
id|shared_mem
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|buf
comma
id|shared_mem
op_plus
(paren
id|ring_offset
op_amp
l_int|0xff
)paren
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* Turn off memory access: we would need to reprogram the window anyway. */
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|e21_block_output
id|e21_block_output
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_volatile
r_char
op_star
id|shared_mem
op_assign
(paren
r_char
op_star
)paren
id|dev-&gt;mem_start
suffix:semicolon
multiline_comment|/* Set the shared memory window start by doing a read, with the low address&n;&t;   bits specifing the starting page. */
op_star
(paren
id|shared_mem
op_plus
id|start_page
)paren
suffix:semicolon
id|mem_on
c_func
(paren
id|ioaddr
comma
id|shared_mem
comma
id|start_page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|shared_mem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|e21_close
id|e21_close
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
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/net/inet -Wall -Wstrict-prototypes -O6 -m486 -c e2100.c&quot;&n; *  version-control: t&n; *  tab-width: 4&n; *  kept-new-versions: 5&n; * End:&n; */
eof