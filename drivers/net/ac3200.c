multiline_comment|/* ac3200.c: A driver for the Ansel Communications EISA ethernet adaptor. */
multiline_comment|/*&n;&t;Written 1993, 1994 by Donald Becker.&n;&t;Copyright 1993 United States Government as represented by the Director,&n;&t;National Security Agency.  This software may only be used and distributed&n;&t;according to the terms of the GNU Public License as modified by SRC,&n;&t;incorporated herein by reference.&n;&n;&t;The author may be reached as becker@cesdis.gsfc.nasa.gov, or&n;    C/O Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;&t;This is driver for the Ansel Communications Model 3200 EISA Ethernet LAN&n;&t;Adapter.  The programming information is from the users manual, as related&n;&t;by glee@ardnassak.math.clemson.edu.&n;  */
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;ac3200.c:v1.01 7/1/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* Offsets from the base address. */
DECL|macro|AC_NIC_BASE
mdefine_line|#define AC_NIC_BASE&t;&t;0x00
DECL|macro|AC_SA_PROM
mdefine_line|#define AC_SA_PROM&t;&t;0x16&t;&t;&t;/* The station address PROM. */
DECL|macro|AC_ADDR0
mdefine_line|#define  AC_ADDR0&t;&t; 0x00&t;&t;&t;/* Prefix station address values. */
DECL|macro|AC_ADDR1
mdefine_line|#define  AC_ADDR1&t;&t; 0x40&t;&t;&t;/* !!!!These are just guesses!!!! */
DECL|macro|AC_ADDR2
mdefine_line|#define  AC_ADDR2&t;&t; 0x90
DECL|macro|AC_ID_PORT
mdefine_line|#define AC_ID_PORT&t;&t;0xC80
DECL|macro|AC_EISA_ID
mdefine_line|#define AC_EISA_ID&t;&t; 0x0110d305
DECL|macro|AC_RESET_PORT
mdefine_line|#define AC_RESET_PORT&t;0xC84
DECL|macro|AC_RESET
mdefine_line|#define  AC_RESET&t;&t; 0x00
DECL|macro|AC_ENABLE
mdefine_line|#define  AC_ENABLE&t;&t; 0x01
DECL|macro|AC_CONFIG
mdefine_line|#define AC_CONFIG&t;&t;0xC90&t;/* The configuration port. */
multiline_comment|/* Decoding of the configuration register. */
DECL|variable|config2irqmap
r_static
r_int
r_char
id|config2irqmap
(braket
l_int|8
)braket
op_assign
(brace
l_int|15
comma
l_int|12
comma
l_int|11
comma
l_int|10
comma
l_int|9
comma
l_int|7
comma
l_int|5
comma
l_int|3
)brace
suffix:semicolon
DECL|variable|addrmap
r_static
r_int
id|addrmap
(braket
l_int|8
)braket
op_assign
(brace
l_int|0xFF0000
comma
l_int|0xFE0000
comma
l_int|0xFD0000
comma
l_int|0xFFF0000
comma
l_int|0xFFE0000
comma
l_int|0xFFC0000
comma
l_int|0xD0000
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|port_name
r_static
r_char
op_star
id|port_name
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;10baseT&quot;
comma
l_string|&quot;invalid&quot;
comma
l_string|&quot;AUI&quot;
comma
l_string|&quot;10base2&quot;
)brace
suffix:semicolon
DECL|macro|config2irq
mdefine_line|#define config2irq(configval)&t;config2irqmap[((configval) &gt;&gt; 3) &amp; 7]
DECL|macro|config2mem
mdefine_line|#define config2mem(configval)&t;addrmap[(configval) &amp; 7]
DECL|macro|config2name
mdefine_line|#define config2name(configval)&t;port_name[((configval) &gt;&gt; 6) &amp; 3]
multiline_comment|/* First and last 8390 pages. */
DECL|macro|AC_START_PG
mdefine_line|#define AC_START_PG&t;&t;0x00&t;/* First page of 8390 TX buffer */
DECL|macro|AC_STOP_PG
mdefine_line|#define AC_STOP_PG&t;&t;0x80&t;/* Last page +1 of the 8390 RX ring */
r_int
id|ac3200_probe
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
id|ac_probe1
c_func
(paren
r_int
id|ioaddr
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ac_open
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
id|ac_reset_8390
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
id|ac_block_input
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
id|ac_block_output
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
r_static
r_int
id|ac_close_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&t;Probe for the AC3200.&n;&n;&t;The AC3200 can be identified by either the EISA configuration registers,&n;&t;or the unique value in the station address PROM.&n;&t;*/
DECL|function|ac3200_probe
r_int
id|ac3200_probe
c_func
(paren
r_struct
id|device
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
id|ac_probe1
c_func
(paren
id|ioaddr
comma
id|dev
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
multiline_comment|/* If you have a pre-pl15 machine you should delete this line. */
r_if
c_cond
(paren
op_logical_neg
id|EISA_bus
)paren
r_return
id|ENXIO
suffix:semicolon
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
r_if
c_cond
(paren
id|ac_probe1
c_func
(paren
id|ioaddr
comma
id|dev
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
)brace
DECL|function|ac_probe1
r_static
r_int
id|ac_probe1
c_func
(paren
r_int
id|ioaddr
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifndef final_version
id|printk
c_func
(paren
l_string|&quot;AC3200 ethercard probe at %#3x:&quot;
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
id|AC_SA_PROM
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* !!!!The values of AC_ADDRn (see above) should be corrected when we&n;&t;   find out the correct station address prefix!!!! */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
l_int|0
)paren
op_ne
id|AC_ADDR0
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
l_int|1
)paren
op_ne
id|AC_ADDR1
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
l_int|2
)paren
op_ne
id|AC_ADDR2
)paren
(brace
macro_line|#ifndef final_version
id|printk
c_func
(paren
l_string|&quot; not found (invalid prefix).&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* The correct probe method is to check the EISA ID. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
)paren
op_ne
id|AC_EISA_ID
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;EISA ID mismatch, %8x vs %8x.&bslash;n&quot;
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|AC_EISA_ID
)paren
comma
id|AC_EISA_ID
)paren
suffix:semicolon
r_return
id|ENODEV
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
id|AC_SA_PROM
op_plus
id|i
)paren
suffix:semicolon
)brace
macro_line|#ifndef final_version
id|printk
c_func
(paren
l_string|&quot;&bslash;nAC3200 ethercard configuration register is %#02x,&quot;
l_string|&quot; EISA ID %02x %02x %02x %02x.&bslash;n&quot;
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|0
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|1
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|2
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|3
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Assign and snarf the interrupt now. */
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|0
)paren
id|dev-&gt;irq
op_assign
id|config2irq
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
)paren
suffix:semicolon
r_else
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
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
l_string|&quot;ac3200&quot;
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
l_int|0
suffix:semicolon
)brace
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
macro_line|#ifdef notyet
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Override the value from the board. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|addrmap
(braket
id|i
)braket
op_eq
id|dev-&gt;mem_start
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|7
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
op_amp
op_complement
l_int|7
)paren
op_or
id|i
comma
id|ioaddr
op_plus
id|AC_CONFIG
)paren
suffix:semicolon
)brace
macro_line|#endif
id|dev-&gt;if_port
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
op_rshift
l_int|6
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|config2mem
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
)paren
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
id|AC_STOP_PG
op_minus
id|AC_START_PG
)paren
op_star
l_int|256
suffix:semicolon
id|ethdev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;AC3200&quot;
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|AC_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|AC_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|AC_STOP_PG
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: AC3200 at %#x, IRQ %d, %s port, shared memory %#lx-%#lx.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ioaddr
comma
id|dev-&gt;irq
comma
id|port_name
(braket
id|dev-&gt;if_port
)braket
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
id|ac_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ac_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ac_block_output
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ac_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ac_close_card
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
DECL|function|ac_open
r_static
r_int
id|ac_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
macro_line|#ifdef notyet
multiline_comment|/* Someday we may enable the IRQ and shared memory here. */
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
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
l_int|0
comma
l_string|&quot;ac3200&quot;
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
macro_line|#endif
r_return
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|ac_reset_8390
r_static
r_void
id|ac_reset_8390
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|ushort
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
id|AC_RESET
comma
id|ioaddr
op_plus
id|AC_RESET_PORT
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
l_string|&quot;resetting AC3200, t=%ld...&quot;
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
id|AC_ENABLE
comma
id|ioaddr
op_plus
id|AC_RESET_PORT
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
multiline_comment|/*  Block input and output are easy on shared memory ethercards, the only&n;&t;complication is when the ring buffer wraps. */
DECL|function|ac_block_input
r_static
r_int
id|ac_block_input
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
id|xfer_start
op_assign
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_minus
(paren
id|AC_START_PG
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
id|memcpy
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
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
(paren
r_char
op_star
)paren
id|xfer_start
comma
id|count
)paren
suffix:semicolon
r_return
id|ring_offset
op_plus
id|count
suffix:semicolon
)brace
DECL|function|ac_block_output
r_static
r_void
id|ac_block_output
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
id|shmem
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|start_page
op_minus
id|AC_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|shmem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|ac_close_card
r_static
r_int
id|ac_close_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
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
macro_line|#ifdef notyet
multiline_comment|/* We should someday disable shared memory and interrupts. */
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
macro_line|#endif
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
"&f;"
multiline_comment|/*&n; * Local variables:&n; * compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/net/inet -Wall -Wstrict-prototypes -O6 -m486 -c ac3200.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  tab-width: 4&n; * End:&n; */
eof
