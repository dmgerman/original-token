multiline_comment|/* at1700.c: A network device driver for  the Allied Telesis AT1700.&n;&n;&t;Written 1993-94 by Donald Becker.&n;&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;&t;Center of Excellence in Space Data and Information Sciences&n;&t;   Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;&t;This is a device driver for the Allied Telesis AT1700, which is a&n;&t;straight-forward Fujitsu MB86965 implementation.&n;&n;  Sources:&n;    The Fujitsu MB86695 datasheet.&n;&n;&t;After the initial version of this driver was written Gerry Sockins of&n;&t;ATI provided their EEPROM configuration code header file.&n;    Thanks to NIIBE Yutaka &lt;gniibe@mri.co.jp&gt; for bug fixes.&n;&n;  Bugs:&n;&t;The MB86695 has a design flaw that makes all probes unreliable.  Not&n;&t;only is it difficult to detect, it also moves around in I/O space in&n;&t;response to inb()s from other device probes!&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;at1700.c:v1.10 9/24/94  Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
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
multiline_comment|/* This unusual address order is used to verify the CONFIG register. */
DECL|variable|at1700_probe_list
r_static
r_int
id|at1700_probe_list
(braket
)braket
op_assign
(brace
l_int|0x260
comma
l_int|0x280
comma
l_int|0x2a0
comma
l_int|0x240
comma
l_int|0x340
comma
l_int|0x320
comma
l_int|0x380
comma
l_int|0x300
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 1
macro_line|#endif
DECL|variable|net_debug
r_static
r_int
r_int
id|net_debug
op_assign
id|NET_DEBUG
suffix:semicolon
DECL|typedef|uchar
r_typedef
r_int
r_char
id|uchar
suffix:semicolon
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
DECL|member|open_time
r_int
id|open_time
suffix:semicolon
multiline_comment|/* Useless example local info. */
DECL|member|tx_started
id|uint
id|tx_started
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Number of packet on the Tx queue. */
DECL|member|tx_queue
id|uchar
id|tx_queue
suffix:semicolon
multiline_comment|/* Number of packet on the Tx queue. */
DECL|member|tx_queue_len
id|ushort
id|tx_queue_len
suffix:semicolon
multiline_comment|/* Current length of the Tx queue. */
)brace
suffix:semicolon
multiline_comment|/* Offsets from the base address. */
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;&t;0
DECL|macro|TX_STATUS
mdefine_line|#define TX_STATUS&t;&t;0
DECL|macro|RX_STATUS
mdefine_line|#define RX_STATUS&t;&t;1
DECL|macro|TX_INTR
mdefine_line|#define TX_INTR&t;&t;&t;2&t;&t;/* Bit-mapped interrupt enable registers. */
DECL|macro|RX_INTR
mdefine_line|#define RX_INTR&t;&t;&t;3
DECL|macro|TX_MODE
mdefine_line|#define TX_MODE&t;&t;&t;4
DECL|macro|RX_MODE
mdefine_line|#define RX_MODE&t;&t;&t;5
DECL|macro|CONFIG_0
mdefine_line|#define CONFIG_0&t;&t;6&t;&t;/* Misc. configuration settings. */
DECL|macro|CONFIG_1
mdefine_line|#define CONFIG_1&t;&t;7
multiline_comment|/* Run-time register bank 2 definitions. */
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT&t;&t;8&t;&t;/* Word-wide DMA or programmed-I/O dataport. */
DECL|macro|TX_START
mdefine_line|#define TX_START&t;&t;10
DECL|macro|MODE13
mdefine_line|#define MODE13&t;&t;&t;13
DECL|macro|EEPROM_Ctrl
mdefine_line|#define EEPROM_Ctrl &t;16
DECL|macro|EEPROM_Data
mdefine_line|#define EEPROM_Data &t;17
DECL|macro|IOCONFIG
mdefine_line|#define IOCONFIG&t;&t;19
DECL|macro|RESET
mdefine_line|#define RESET&t;&t;&t;31&t;&t;/* Write to reset some parts of the chip. */
DECL|macro|AT1700_IO_EXTENT
mdefine_line|#define AT1700_IO_EXTENT&t;32
multiline_comment|/*  EEPROM_Ctrl bits. */
DECL|macro|EE_SHIFT_CLK
mdefine_line|#define EE_SHIFT_CLK&t;0x40&t;/* EEPROM shift clock, in reg. 16. */
DECL|macro|EE_CS
mdefine_line|#define EE_CS&t;&t;&t;0x20&t;/* EEPROM chip select, in reg. 16. */
DECL|macro|EE_DATA_WRITE
mdefine_line|#define EE_DATA_WRITE&t;0x80&t;/* EEPROM chip data in, in reg. 17. */
DECL|macro|EE_DATA_READ
mdefine_line|#define EE_DATA_READ&t;0x80&t;/* EEPROM chip data out, in reg. 17. */
multiline_comment|/* Delay between EEPROM clock transitions. */
DECL|macro|eeprom_delay
mdefine_line|#define eeprom_delay()&t;do { int _i = 40; while (--_i &gt; 0) { __SLOW_DOWN_IO; }} while (0)
multiline_comment|/* The EEPROM commands include the alway-set leading bit. */
DECL|macro|EE_WRITE_CMD
mdefine_line|#define EE_WRITE_CMD&t;(5 &lt;&lt; 6)
DECL|macro|EE_READ_CMD
mdefine_line|#define EE_READ_CMD&t;&t;(6 &lt;&lt; 6)
DECL|macro|EE_ERASE_CMD
mdefine_line|#define EE_ERASE_CMD&t;(7 &lt;&lt; 6)
multiline_comment|/* Index to functions, as function prototypes. */
r_extern
r_int
id|at1700_probe
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
id|at1700_probe1
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
id|read_eeprom
c_func
(paren
r_int
id|ioaddr
comma
r_int
id|location
)paren
suffix:semicolon
r_static
r_int
id|net_open
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
id|net_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|net_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
suffix:semicolon
r_static
r_void
id|net_rx
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
id|net_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|enet_statistics
op_star
id|net_get_stats
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
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
)paren
suffix:semicolon
"&f;"
multiline_comment|/* Check for a network adaptor of this type, and return &squot;0&squot; iff one exists.&n;   If dev-&gt;base_addr == 0, probe all likely locations.&n;   If dev-&gt;base_addr == 1, always return failure.&n;   If dev-&gt;base_addr == 2, allocate space for the device and return success&n;   (detachable devices only).&n;   */
macro_line|#ifdef HAVE_DEVLIST
multiline_comment|/* Support for a alternate probe manager, which will eliminate the&n;   boilerplate below. */
DECL|variable|at1700_drv
r_struct
id|netdev_entry
id|at1700_drv
op_assign
(brace
l_string|&quot;at1700&quot;
comma
id|at1700_probe1
comma
id|AT1700_IO_EXTENT
comma
id|at1700_probe_list
)brace
suffix:semicolon
macro_line|#else
r_int
DECL|function|at1700_probe
id|at1700_probe
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
id|at1700_probe1
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
id|at1700_probe_list
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
id|at1700_probe_list
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
id|AT1700_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|at1700_probe1
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
multiline_comment|/* The Fujitsu datasheet suggests that the NIC be probed for by checking its&n;   &quot;signature&quot;, the default bit pattern after a reset.  This *doesn&squot;t* work --&n;   there is no way to reset the bus interface without a complete power-cycle!&n;&n;   It turns out that ATI came to the same conclusion I did: the only thing&n;   that can be done is checking a few bits and then diving right into an&n;   EEPROM read. */
DECL|function|at1700_probe1
r_int
id|at1700_probe1
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
r_char
id|irqmap
(braket
l_int|8
)braket
op_assign
(brace
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|14
comma
l_int|15
)brace
suffix:semicolon
r_int
r_int
id|i
comma
id|irq
suffix:semicolon
multiline_comment|/* Resetting the chip doesn&squot;t reset the ISA interface, so don&squot;t bother.&n;&t;   That means we have to be careful with the register values we probe for.&n;&t;   */
macro_line|#ifdef notdef
id|printk
c_func
(paren
l_string|&quot;at1700 probe at %#x, eeprom is %4.4x %4.4x %4.4x ctrl %4.4x.&bslash;n&quot;
comma
id|ioaddr
comma
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|4
)paren
comma
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|5
)paren
comma
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|6
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
id|EEPROM_Ctrl
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|at1700_probe_list
(braket
id|inb
c_func
(paren
id|ioaddr
op_plus
id|IOCONFIG
)paren
op_amp
l_int|0x07
)braket
op_ne
id|ioaddr
op_logical_or
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|4
)paren
op_ne
l_int|0x0000
op_logical_or
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|5
)paren
op_amp
l_int|0xff00
op_ne
l_int|0xF400
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Reset the internal state machines. */
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|RESET
)paren
suffix:semicolon
id|irq
op_assign
id|irqmap
(braket
(paren
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|12
)paren
op_amp
l_int|0x04
)paren
op_or
(paren
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|0
)paren
op_rshift
l_int|14
)paren
)braket
suffix:semicolon
multiline_comment|/* Snarf the interrupt vector now. */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
op_amp
id|net_interrupt
comma
l_int|0
comma
l_string|&quot;at1700&quot;
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;AT1700 found at %#3x, but it&squot;s unusable due to a conflict on&quot;
l_string|&quot;IRQ %d.&bslash;n&quot;
comma
id|ioaddr
comma
id|irq
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/* Allocate a new &squot;dev&squot; if needed. */
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
id|net_local
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Grab the region so that we can find another board if the IRQ request&n;&t;   fails. */
id|register_iomem
c_func
(paren
id|ioaddr
comma
id|AT1700_IO_EXTENT
comma
l_string|&quot;at1700&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: AT1700 found at %#3x, IRQ %d, address &quot;
comma
id|dev-&gt;name
comma
id|ioaddr
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|irq2dev_map
(braket
id|irq
)braket
op_assign
id|dev
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
r_int
r_int
id|eeprom_val
op_assign
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|4
op_plus
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%04x&quot;
comma
id|eeprom_val
)paren
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|dev-&gt;dev_addr
)paren
(braket
id|i
)braket
op_assign
id|ntohs
c_func
(paren
id|eeprom_val
)paren
suffix:semicolon
)brace
multiline_comment|/* The EEPROM word 12 bit 0x0400 means use regular 100 ohm 10baseT signals,&n;&t;   rather than 150 ohm shielded twisted pair compensation.&n;&t;   0x0000 == auto-sense the interface&n;&t;   0x0800 == use TP interface&n;&t;   0x1800 == use coax interface&n;&t;   */
(brace
r_char
op_star
id|porttype
(braket
)braket
op_assign
(brace
l_string|&quot;auto-sense&quot;
comma
l_string|&quot;10baseT&quot;
comma
l_string|&quot;auto-sense&quot;
comma
l_string|&quot;10base2&quot;
)brace
suffix:semicolon
id|ushort
id|setup_value
op_assign
id|read_eeprom
c_func
(paren
id|ioaddr
comma
l_int|12
)paren
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|setup_value
op_rshift
l_int|8
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %s interface.&bslash;n&quot;
comma
id|porttype
(braket
(paren
id|dev-&gt;if_port
op_rshift
l_int|3
)paren
op_amp
l_int|3
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the station address in bank zero. */
id|outb
c_func
(paren
l_int|0xe0
comma
id|ioaddr
op_plus
l_int|7
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
id|outb
c_func
(paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
comma
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Switch to bank 1 and set the multicast table to accept none. */
id|outb
c_func
(paren
l_int|0xe4
comma
id|ioaddr
op_plus
l_int|7
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
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Set the configuration register 0 to 32K 100ns. byte-wide memory, 16 bit&n;&t;   bus access, two 4K Tx queues, and disabled Tx and Rx. */
id|outb
c_func
(paren
l_int|0xda
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Switch to bank 2 and lock our I/O address. */
id|outb
c_func
(paren
l_int|0xe8
comma
id|ioaddr
op_plus
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|dev-&gt;if_port
comma
id|MODE13
)paren
suffix:semicolon
multiline_comment|/* Power-down the chip.  Aren&squot;t we green! */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
)paren
id|printk
c_func
(paren
id|version
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
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_local
)paren
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|net_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|net_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|net_send_packet
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|net_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
op_amp
id|set_multicast_list
suffix:semicolon
multiline_comment|/* Fill in the fields of &squot;dev&squot; with ethernet-generic values. */
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
DECL|function|read_eeprom
r_static
r_int
id|read_eeprom
c_func
(paren
r_int
id|ioaddr
comma
r_int
id|location
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|ee_addr
op_assign
id|ioaddr
op_plus
id|EEPROM_Ctrl
suffix:semicolon
r_int
id|ee_daddr
op_assign
id|ioaddr
op_plus
id|EEPROM_Data
suffix:semicolon
r_int
id|read_cmd
op_assign
id|location
op_or
id|EE_READ_CMD
suffix:semicolon
r_int
id|ctrl_val
op_assign
id|EE_CS
suffix:semicolon
id|outb
c_func
(paren
id|ctrl_val
comma
id|ee_addr
)paren
suffix:semicolon
multiline_comment|/* Shift the read command bits out. */
r_for
c_loop
(paren
id|i
op_assign
l_int|9
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_int
id|dataval
op_assign
(paren
id|read_cmd
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|EE_DATA_WRITE
suffix:colon
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|dataval
comma
id|ee_daddr
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EE_CS
op_or
id|EE_SHIFT_CLK
comma
id|ee_addr
)paren
suffix:semicolon
multiline_comment|/* EEPROM clock tick. */
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EE_CS
comma
id|ee_addr
)paren
suffix:semicolon
multiline_comment|/* Finish EEPROM a clock tick. */
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|EE_CS
comma
id|ee_addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|outb
c_func
(paren
id|EE_CS
op_or
id|EE_SHIFT_CLK
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|retval
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|inb
c_func
(paren
id|ee_daddr
)paren
op_amp
id|EE_DATA_READ
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EE_CS
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Terminate the EEPROM access. */
id|ctrl_val
op_and_assign
op_complement
id|EE_CS
suffix:semicolon
id|outb
c_func
(paren
id|ctrl_val
op_or
id|EE_SHIFT_CLK
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ctrl_val
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
"&f;"
DECL|function|net_open
r_static
r_int
id|net_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Powerup the chip, initialize config register 1, and select bank 0. */
id|outb
c_func
(paren
l_int|0xe0
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
multiline_comment|/* Set the station address in bank zero. */
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
id|outb
c_func
(paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
comma
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Switch to bank 1 and set the multicast table to accept none. */
id|outb
c_func
(paren
l_int|0xe4
comma
id|ioaddr
op_plus
l_int|7
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
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Set the configuration register 0 to 32K 100ns. byte-wide memory, 16 bit&n;&t;   bus access, and two 4K Tx queues. */
id|outb
c_func
(paren
l_int|0xda
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Same config 0, except enable the Rx and Tx. */
id|outb
c_func
(paren
l_int|0x5a
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Switch to register bank 2 for the run-time registers. */
id|outb
c_func
(paren
l_int|0xe8
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
multiline_comment|/* Turn on Rx interrupts, leave Tx interrupts off until packet Tx. */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|TX_INTR
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x81
comma
id|ioaddr
op_plus
id|RX_INTR
)paren
suffix:semicolon
id|lp-&gt;open_time
op_assign
id|jiffies
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|net_send_packet
id|net_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tbusy
)paren
(brace
multiline_comment|/* If we get here, some higher level has decided we are broken.&n;&t;&t;   There should really be a &quot;kick me&quot; function call instead. */
r_int
id|tickssofar
op_assign
id|jiffies
op_minus
id|dev-&gt;trans_start
suffix:semicolon
r_if
c_cond
(paren
id|tickssofar
OL
l_int|10
)paren
r_return
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: transmit timed out with status %04x, %s?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
id|STATUS
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|TX_STATUS
)paren
op_amp
l_int|0x80
ques
c_cond
l_string|&quot;IRQ conflict&quot;
suffix:colon
l_string|&quot;network cable problem&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: timeout registers: %04x %04x %04x %04x %04x %04x %04x %04x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|0
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|2
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|6
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|8
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|10
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|12
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|14
)paren
)paren
suffix:semicolon
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
multiline_comment|/* ToDo: We should try to restart the adaptor... */
id|outw
c_func
(paren
l_int|0xffff
comma
id|ioaddr
op_plus
l_int|24
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0xffff
comma
id|ioaddr
op_plus
id|TX_STATUS
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0xe85a
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0x8100
comma
id|ioaddr
op_plus
id|TX_INTR
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
multiline_comment|/* If some higher layer thinks we&squot;ve missed an tx-done interrupt&n;&t;   we are passed NULL. Caution: dev_tint() handles the cli()/sti()&n;&t;   itself. */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|dev_tint
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Block a timer-based transmit from overlapping.  This could better be&n;&t;   done with atomic_swap(1, dev-&gt;tbusy), but set_bit() works as well. */
r_if
c_cond
(paren
id|set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|dev-&gt;tbusy
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Transmitter access conflict.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_else
(brace
r_int
id|length
op_assign
id|ETH_ZLEN
OL
id|skb-&gt;len
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ETH_ZLEN
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* Turn off the possible Tx interrupts. */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|TX_INTR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|length
comma
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
id|outsw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
comma
id|buf
comma
(paren
id|length
op_plus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|lp-&gt;tx_queue
op_increment
suffix:semicolon
id|lp-&gt;tx_queue_len
op_add_assign
id|length
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;tx_started
op_eq
l_int|0
)paren
(brace
multiline_comment|/* If the Tx is idle, always trigger a transmit. */
id|outb
c_func
(paren
l_int|0x80
op_or
id|lp-&gt;tx_queue
comma
id|ioaddr
op_plus
id|TX_START
)paren
suffix:semicolon
id|lp-&gt;tx_queue
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|lp-&gt;tx_started
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lp-&gt;tx_queue_len
OL
l_int|4096
op_minus
l_int|1502
)paren
multiline_comment|/* Yes, there is room for one more packet. */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Turn on Tx interrupts back on. */
id|outb
c_func
(paren
l_int|0x82
comma
id|ioaddr
op_plus
id|TX_INTR
)paren
suffix:semicolon
)brace
id|dev_kfree_skb
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/* The typical workload of the driver:&n;   Handle the network interface interrupts. */
r_static
r_void
DECL|function|net_interrupt
id|net_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
(brace
r_int
id|irq
op_assign
op_minus
(paren
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|reg_ptr
)paren
op_member_access_from_pointer
id|orig_eax
op_plus
l_int|2
)paren
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
(paren
id|irq2dev_map
(braket
id|irq
)braket
)paren
suffix:semicolon
r_struct
id|net_local
op_star
id|lp
suffix:semicolon
r_int
id|ioaddr
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;at1700_interrupt(): irq %d for unknown device.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|status
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|TX_STATUS
)paren
suffix:semicolon
id|outw
c_func
(paren
id|status
comma
id|ioaddr
op_plus
id|TX_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Interrupt with status %04x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0xff00
op_logical_or
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Got a packet(s). */
id|net_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x00ff
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x80
)paren
(brace
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;tx_queue
)paren
(brace
id|outb
c_func
(paren
l_int|0x80
op_or
id|lp-&gt;tx_queue
comma
id|ioaddr
op_plus
id|TX_START
)paren
suffix:semicolon
id|lp-&gt;tx_queue
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
multiline_comment|/* Inform upper layers. */
)brace
r_else
(brace
id|lp-&gt;tx_started
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Turn on Tx interrupts off. */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|TX_INTR
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
multiline_comment|/* Inform upper layers. */
)brace
)brace
)brace
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We have a good packet(s), get it/them out of the buffers. */
r_static
r_void
DECL|function|net_rx
id|net_rx
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|5
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
id|ushort
id|status
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Rxing packet mode %02x status %04x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
comma
id|status
)paren
suffix:semicolon
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0xF0
)paren
op_ne
l_int|0x20
)paren
(brace
multiline_comment|/* There was an error. */
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x08
)paren
id|lp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x04
)paren
id|lp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x02
)paren
id|lp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x01
)paren
id|lp-&gt;stats.rx_over_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
id|ushort
id|pkt_len
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
multiline_comment|/* Malloc up new buffer. */
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
OG
l_int|1550
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: The AT1700 claimed a very large packet, size %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Memory squeeze, dropping packet (len %d).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb-&gt;len
op_assign
id|pkt_len
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|insw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
comma
id|skb-&gt;data
comma
(paren
id|pkt_len
op_plus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|5
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Rxed packet of length %d: &quot;
comma
id|dev-&gt;name
comma
id|pkt_len
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
l_int|14
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|skb-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|lp-&gt;stats.rx_packets
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|boguscount
op_le
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* If any worth-while packets have been received, dev_rint()&n;&t;   has done a mark_bh(NET_BH) for us and will work on them&n;&t;   when we get to the bottom-half routine. */
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0x40
)paren
r_break
suffix:semicolon
id|inw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
multiline_comment|/* dummy status read */
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|net_debug
OG
l_int|5
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Exint Rx packet with mode %02x after %d ticks.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
comma
id|i
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* The inverse routine to net_open(). */
DECL|function|net_close
r_static
r_int
id|net_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|lp-&gt;open_time
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set configuration register 0 to disable Tx and Rx. */
id|outb
c_func
(paren
l_int|0xda
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Update the statistics -- ToDo. */
multiline_comment|/* Power-down the chip.  Green, green, green! */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the current statistics.&t;This may be called with the card open or&n;   closed. */
r_static
r_struct
id|enet_statistics
op_star
DECL|function|net_get_stats
id|net_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ToDo: Update the statistics from the device registers. */
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
multiline_comment|/* Set or clear the multicast filter for this adaptor.&n;   num_addrs == -1&t;Promiscuous mode, receive all packets&n;   num_addrs == 0&t;Normal mode, clear multicast list&n;   num_addrs &gt; 0&t;Multicast mode, receive normal and MC packets, and do&n;&t;&t;&t;best-effort filtering.&n; */
r_static
r_void
DECL|function|set_multicast_list
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
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
id|num_addrs
)paren
(brace
id|outb
c_func
(paren
l_int|3
comma
id|ioaddr
op_plus
id|RX_MODE
)paren
suffix:semicolon
multiline_comment|/* Enable promiscuous mode */
)brace
r_else
id|outb
c_func
(paren
l_int|2
comma
id|ioaddr
op_plus
id|RX_MODE
)paren
suffix:semicolon
multiline_comment|/* Disable promiscuous, use normal mode */
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/net/inet -Wall -Wstrict-prototypes -O6 -m486 -c at1700.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  tab-width: 4&n; *  c-indent-level: 4&n; * End:&n; */
eof
