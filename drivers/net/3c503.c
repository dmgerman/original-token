multiline_comment|/* 3c503.c: A shared-memory NS8390 ethernet driver for linux. */
multiline_comment|/*&n;    Written 1992,1993 by Donald Becker.&n;&n;    Copyright 1993 United States Government as represented by the&n;    Director, National Security Agency.  This software may be used and&n;    distributed according to the terms of the GNU Public License,&n;    incorporated herein by reference.&n;&n;    This driver should work with the 3c503 and 3c503/16.  It should be used&n;    in shared memory mode for best performance, although it may also work&n;    in programmed-I/O mode.&n;&n;    The Author may be reached as becker@super.org or&n;    C/O Supercomputing Research Ctr., 17100 Science Dr., Bowie MD 20715&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;3c503.c:v0.99.13 8/30/93 Donald Becker (becker@super.org)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;dev.h&quot;
macro_line|#include &quot;8390.h&quot;
macro_line|#include &quot;3c503.h&quot;
r_int
id|el2_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|el2_pio_autoprobe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|el2probe1
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
id|el2_open
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
id|el2_close
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
id|el2_reset_8390
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
id|el2_init_card
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
id|el2_block_output
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
id|el2_block_input
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
"&f;"
multiline_comment|/* This routine probes for a memory-mapped 3c503 board by looking for&n;   the &quot;location register&quot; at the end of the jumpered boot PROM space.&n;   This works even if a PROM isn&squot;t there.&n;&n;   If the ethercard isn&squot;t found there is an optional probe for&n;   ethercard jumpered to programmed-I/O mode.&n;   */
DECL|variable|ports
r_static
r_int
id|ports
(braket
)braket
op_assign
(brace
l_int|0x300
comma
l_int|0x310
comma
l_int|0x330
comma
l_int|0x350
comma
l_int|0x250
comma
l_int|0x280
comma
l_int|0x2a0
comma
l_int|0x2e0
comma
l_int|0
)brace
suffix:semicolon
r_int
DECL|function|el2_probe
id|el2_probe
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
id|addr
comma
id|addrs
(braket
)braket
op_assign
(brace
l_int|0xddffe
comma
l_int|0xd9ffe
comma
l_int|0xcdffe
comma
l_int|0xc9ffe
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
l_int|0
)paren
r_return
op_logical_neg
id|el2probe1
c_func
(paren
id|ioaddr
comma
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|addrs
suffix:semicolon
op_star
id|addr
suffix:semicolon
id|addr
op_increment
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|base_bits
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
op_star
id|addr
suffix:semicolon
multiline_comment|/* Find first set bit. */
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
comma
id|base_bits
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|base_bits
op_amp
l_int|0x1
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|base_bits
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
macro_line|#ifdef HAVE_PORTRESERVE
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ports
(braket
id|i
)braket
comma
l_int|16
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|el2probe1
c_func
(paren
id|ports
(braket
id|i
)braket
comma
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef no_probe_nonshared_memory
r_return
id|el2_pio_autoprobe
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#else
r_return
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*  Try all of the locations that aren&squot;t obviously empty.  This touches&n;    a lot of locations, and is much riskier than the code above. */
r_int
DECL|function|el2_pio_autoprobe
id|el2_pio_autoprobe
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
(brace
macro_line|#ifdef HAVE_PORTRESERVE
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ports
(braket
id|i
)braket
comma
l_int|16
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif
multiline_comment|/* Reset and/or avoid any lurking NE2000 */
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ports
(braket
id|i
)braket
op_plus
l_int|0x408
)paren
op_eq
l_int|0xff
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ports
(braket
id|i
)braket
op_plus
l_int|0x403
)paren
op_eq
(paren
l_int|0x80
op_rshift
id|i
)paren
multiline_comment|/* Preliminary check */
op_logical_and
id|el2probe1
c_func
(paren
id|ports
(braket
id|i
)braket
comma
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Probe for the Etherlink II card at I/O port base IOADDR,&n;   returning non-zero on sucess.  If found, set the station&n;   address and memory parameters in DEVICE. */
r_int
DECL|function|el2probe1
id|el2probe1
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
comma
id|iobase_reg
comma
id|membase_reg
comma
id|saved_406
suffix:semicolon
r_int
r_char
op_star
id|station_addr
op_assign
id|dev-&gt;dev_addr
suffix:semicolon
multiline_comment|/* We verify that it&squot;s a 3C503 board by checking the first three octets&n;       of its ethernet address. */
id|printk
c_func
(paren
l_string|&quot;3c503 probe at %#3x:&quot;
comma
id|ioaddr
)paren
suffix:semicolon
id|iobase_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x403
)paren
suffix:semicolon
id|membase_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x404
)paren
suffix:semicolon
multiline_comment|/* Verify ASIC register that should be 0 or have a single bit set. */
r_if
c_cond
(paren
(paren
id|iobase_reg
op_amp
(paren
id|iobase_reg
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|membase_reg
op_amp
(paren
id|membase_reg
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  not found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|saved_406
op_assign
id|inb_p
c_func
(paren
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ECNTRL_RESET
op_or
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
multiline_comment|/* Reset it... */
id|outb_p
c_func
(paren
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
multiline_comment|/* Map the station addr PROM into the lower I/O ports. */
id|outb
c_func
(paren
id|ECNTRL_SAPROM
op_or
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
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
l_string|&quot; %2.2X&quot;
comma
(paren
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
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|station_addr
(braket
l_int|0
)braket
op_ne
l_int|0x02
op_logical_or
id|station_addr
(braket
l_int|1
)braket
op_ne
l_int|0x60
op_logical_or
id|station_addr
(braket
l_int|2
)braket
op_ne
l_int|0x8c
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  3C503 not found.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Restore the register we frobbed. */
id|outb
c_func
(paren
id|saved_406
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef HAVE_PORTRESERVE
id|snarf_region
c_func
(paren
id|ioaddr
comma
l_int|16
)paren
suffix:semicolon
macro_line|#endif
id|ethdev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Map the 8390 back into the window. */
id|outb
c_func
(paren
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
multiline_comment|/* Probe for, turn on and clear the board&squot;s shared memory. */
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
l_string|&quot; memory jumpers %2.2x &quot;
comma
id|membase_reg
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|ioaddr
op_plus
l_int|0x405
)paren
suffix:semicolon
multiline_comment|/* Enable RAM */
multiline_comment|/* This should be probed for (or set via an ioctl()) at run-time.&n;       Right now we use a sleazy hack to pass in the interface number&n;       at boot-time via the low bits of the mem_end field.  That value is&n;       unused, and the low bits would be discarded even if it was used. */
macro_line|#if defined(EI8390_THICK) || defined(EL2_AUI)
id|ei_status.interface_num
op_assign
l_int|1
suffix:semicolon
macro_line|#else
id|ei_status.interface_num
op_assign
id|dev-&gt;mem_end
op_amp
l_int|0xf
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|membase_reg
op_amp
l_int|0xf0
)paren
op_eq
l_int|0
)paren
(brace
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;mem_start
op_assign
(paren
(paren
id|membase_reg
op_amp
l_int|0xc0
)paren
ques
c_cond
l_int|0xD8000
suffix:colon
l_int|0xC8000
)paren
op_plus
(paren
(paren
id|membase_reg
op_amp
l_int|0xA0
)paren
ques
c_cond
l_int|0x4000
suffix:colon
l_int|0
)paren
suffix:semicolon
DECL|macro|EL2_MEMSIZE
mdefine_line|#define EL2_MEMSIZE (EL2SM_STOP_PG - EL2SM_START_PG)*256
macro_line|#ifdef EL2MEMTEST
multiline_comment|/* This has never found an error, but someone might care. */
(brace
multiline_comment|/* Check the card&squot;s memory. */
r_int
op_star
id|mem_base
op_assign
(paren
r_int
op_star
)paren
id|dev-&gt;mem_start
suffix:semicolon
r_int
id|memtest_value
op_assign
l_int|0xbbadf00d
suffix:semicolon
id|mem_base
(braket
l_int|0
)braket
op_assign
l_int|0xba5eba5e
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|EL2_MEMSIZE
op_div
r_sizeof
(paren
id|mem_base
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mem_base
(braket
id|i
)braket
op_assign
id|memtest_value
suffix:semicolon
r_if
c_cond
(paren
id|mem_base
(braket
l_int|0
)braket
op_ne
l_int|0xba5eba5e
op_logical_or
id|mem_base
(braket
id|i
)braket
op_ne
id|memtest_value
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; memory failure or memory address conflict.&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memtest_value
op_add_assign
l_int|0x55555555
suffix:semicolon
id|mem_base
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif  /* EL2MEMTEST */
multiline_comment|/* Divide the on-board memory into a single maximum-sized transmit&n;&t;   (double-sized for ping-pong transmit) buffer at the base, and&n;&t;   use the rest as a receive ring. */
id|dev-&gt;mem_end
op_assign
id|dev-&gt;rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
id|EL2_MEMSIZE
suffix:semicolon
id|dev-&gt;rmem_start
op_assign
id|TX_PAGES
op_star
l_int|256
op_plus
id|dev-&gt;mem_start
suffix:semicolon
)brace
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
l_string|&quot;&bslash;n3c503: memory params start=%#5x rstart=%#5x end=%#5x rend=%#5x.&bslash;n&quot;
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;rmem_start
comma
id|dev-&gt;mem_end
comma
id|dev-&gt;rmem_end
)paren
suffix:semicolon
multiline_comment|/* Finish setting the board&squot;s parameters. */
id|ei_status.name
op_assign
l_string|&quot;3C503&quot;
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|EL2SM_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|EL2SM_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|EL2SM_STOP_PG
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|el2_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|el2_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|el2_block_output
suffix:semicolon
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
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
OG
l_int|5
op_logical_and
id|dev-&gt;irq
op_ne
l_int|9
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n3c503: configured interrupt %d invalid, using autoIRQ.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
)brace
id|ei_status.saved_irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|el2_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|el2_close
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: %s with shared memory at %#6x-%#6x,&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.name
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
l_int|1
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: %s using programmed I/O (REJUMPER for SHARED MEMORY).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.name
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
id|version
)paren
suffix:semicolon
r_return
id|ioaddr
suffix:semicolon
)brace
"&f;"
r_static
r_int
DECL|function|el2_open
id|el2_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
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
l_int|5
comma
l_int|9
comma
l_int|3
comma
l_int|4
comma
l_int|0
)brace
suffix:semicolon
r_int
op_star
id|irqp
op_assign
id|irqlist
suffix:semicolon
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* Enable RAM and interrupts. */
r_do
(brace
r_if
c_cond
(paren
id|request_irq
(paren
op_star
id|irqp
comma
l_int|NULL
)paren
op_ne
op_minus
id|EBUSY
)paren
(brace
multiline_comment|/* Twinkle the interrupt, and check if it&squot;s seen. */
id|autoirq_setup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x04
op_lshift
(paren
(paren
op_star
id|irqp
op_eq
l_int|9
)paren
ques
c_cond
l_int|2
suffix:colon
op_star
id|irqp
)paren
comma
id|E33G_IDCFR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|E33G_IDCFR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|irqp
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
id|dev-&gt;irq
op_assign
op_star
id|irqp
comma
op_amp
id|ei_interrupt
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
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
id|outb
c_func
(paren
id|EGACFR_IRQOFF
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* disable interrupts. */
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|ei_interrupt
)paren
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
)brace
id|el2_init_card
c_func
(paren
id|dev
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
r_int
DECL|function|el2_close
id|el2_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|free_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|ei_status.saved_irq
suffix:semicolon
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|NULL
suffix:semicolon
id|outb
c_func
(paren
id|EGACFR_IRQOFF
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* disable interrupts. */
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
multiline_comment|/* This is called whenever we have a unrecoverable failure:&n;       transmit timeout&n;       Bad ring buffer packet header&n; */
r_static
r_void
DECL|function|el2_reset_8390
id|el2_reset_8390
c_func
(paren
r_struct
id|device
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
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Resetting the 3c503 board...&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%#x=%#02x %#x=%#02x %#x=%#02x...&quot;
comma
id|E33G_IDCFR
comma
id|inb
c_func
(paren
id|E33G_IDCFR
)paren
comma
id|E33G_CNTRL
comma
id|inb
c_func
(paren
id|E33G_CNTRL
)paren
comma
id|E33G_GACFR
comma
id|inb
c_func
(paren
id|E33G_GACFR
)paren
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|ECNTRL_RESET
op_or
id|ECNTRL_THIN
comma
id|E33G_CNTRL
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
id|el2_init_card
c_func
(paren
id|dev
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
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the 3c503 GA registers after a reset. */
r_static
r_void
DECL|function|el2_init_card
id|el2_init_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* Unmap the station PROM and select the DIX or BNC connector. */
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
multiline_comment|/* Set ASIC copy of rx&squot;s first and last+1 buffer pages */
multiline_comment|/* These must be the same as in the 8390. */
id|outb
c_func
(paren
id|ei_status.rx_start_page
comma
id|E33G_STARTPG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ei_status.stop_page
comma
id|E33G_STOPPG
)paren
suffix:semicolon
multiline_comment|/* Point the vector pointer registers somewhere ?harmless?. */
id|outb
c_func
(paren
l_int|0xff
comma
id|E33G_VP2
)paren
suffix:semicolon
multiline_comment|/* Point at the ROM restart location 0xffff0 */
id|outb
c_func
(paren
l_int|0xff
comma
id|E33G_VP1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|E33G_VP0
)paren
suffix:semicolon
multiline_comment|/* Turn off all interrupts until we&squot;re opened. */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Enable IRQs iff started. */
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* Set the interrupt line. */
id|outb_p
c_func
(paren
(paren
l_int|0x04
op_lshift
(paren
id|dev-&gt;irq
op_eq
l_int|9
ques
c_cond
l_int|2
suffix:colon
id|dev-&gt;irq
)paren
)paren
comma
id|E33G_IDCFR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|8
comma
id|E33G_DRQCNT
)paren
suffix:semicolon
multiline_comment|/* Set burst size to 8 */
id|outb_p
c_func
(paren
l_int|0x20
comma
id|E33G_DMAAH
)paren
suffix:semicolon
multiline_comment|/* Put a valid addr in the GA DMA */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|E33G_DMAAL
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* We always succeed */
)brace
multiline_comment|/* Either use the shared memory (if enabled on the board) or put the packet&n;   out through the ASIC FIFO.  The latter is probably much slower. */
r_static
r_void
DECL|function|el2_block_output
id|el2_block_output
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
id|i
suffix:semicolon
multiline_comment|/* Buffer index */
r_int
id|boguscount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* timeout counter */
multiline_comment|/* This should really be set with during an open(). */
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* Enable RAM and interrupts. */
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Shared memory transfer */
r_void
op_star
id|dest_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|start_page
op_minus
id|ei_status.tx_start_page
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dest_addr
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|2
op_logical_and
id|memcmp
c_func
(paren
id|dest_addr
comma
id|buf
comma
id|count
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: 3c503 send_packet() bad memory copy @ %#5x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
)paren
id|dest_addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ei_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: 3c503 send_packet() good memory copy @ %#5x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
)paren
id|dest_addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* No shared memory, put the packet out the slow way. */
multiline_comment|/* Set up then start the internal memory transfer to Tx Start Page */
id|outb
c_func
(paren
l_int|0x00
comma
id|E33G_DMAAL
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|start_page
comma
id|E33G_DMAAH
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|ei_status.interface_num
ques
c_cond
id|ECNTRL_AUI
suffix:colon
id|ECNTRL_THIN
)paren
op_or
id|ECNTRL_OUTPUT
op_or
id|ECNTRL_START
comma
id|E33G_CNTRL
)paren
suffix:semicolon
multiline_comment|/* This is the byte copy loop: it should probably be tuned for&n;       for speed once everything is working.  I think it is possible&n;       to output 8 bytes between each check of the status bit. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_mod
l_int|8
op_eq
l_int|0
)paren
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|E33G_STATUS
)paren
op_amp
id|ESTAT_DPRDY
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
op_increment
id|boguscount
OG
(paren
id|i
op_lshift
l_int|3
)paren
op_plus
l_int|32
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: FIFO blocked in el2_block_output (at %d of %d, bc=%d).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|i
comma
id|count
comma
id|boguscount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb
c_func
(paren
id|buf
(braket
id|i
)braket
comma
id|E33G_FIFOH
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Returns the new ring pointer. */
r_static
r_int
DECL|function|el2_block_input
id|el2_block_input
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
id|boguscount
op_assign
l_int|0
suffix:semicolon
r_int
id|end_of_ring
op_assign
id|dev-&gt;rmem_end
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Maybe enable shared memory just be to be safe... nahh.*/
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Use the shared memory. */
id|ring_offset
op_sub_assign
(paren
id|EL2SM_START_PG
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_plus
id|count
OG
id|end_of_ring
)paren
(brace
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
id|end_of_ring
op_minus
(paren
id|dev-&gt;mem_start
op_plus
id|ring_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: 3c503 block_input() @ %#5x+%x=%5x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;mem_start
comma
id|ring_offset
comma
id|dev-&gt;mem_start
op_plus
id|ring_offset
)paren
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
id|dev-&gt;mem_start
op_plus
id|ring_offset
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
r_if
c_cond
(paren
id|ei_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: 3c503 block_input() @ %#5x+%x=%5x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;mem_start
comma
id|ring_offset
comma
id|dev-&gt;mem_start
op_plus
id|ring_offset
)paren
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
id|dev-&gt;mem_start
op_plus
id|ring_offset
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
multiline_comment|/* No shared memory, use programmed I/O. */
id|outb
c_func
(paren
id|ring_offset
op_amp
l_int|0xff
comma
id|E33G_DMAAL
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|ring_offset
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|E33G_DMAAH
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
)paren
op_or
id|ECNTRL_INPUT
op_or
id|ECNTRL_START
comma
id|E33G_CNTRL
)paren
suffix:semicolon
multiline_comment|/* This is the byte copy loop: it should probably be tuned for&n;       for speed once everything is working. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_mod
l_int|8
op_eq
l_int|0
)paren
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|E33G_STATUS
)paren
op_amp
id|ESTAT_DPRDY
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
op_increment
id|boguscount
OG
(paren
id|i
op_lshift
l_int|3
)paren
op_plus
l_int|32
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: FIFO blocked in el2_block_input() (at %d of %d, bc=%d).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|i
comma
id|count
comma
id|boguscount
)paren
suffix:semicolon
id|boguscount
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|buf
(braket
id|i
)braket
op_assign
id|inb_p
c_func
(paren
id|E33G_FIFOH
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  version-control: t&n; *  kept-new-versions: 5&n; * End:&n; */
eof