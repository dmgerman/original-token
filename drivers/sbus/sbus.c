multiline_comment|/* sbus.c:  SBus support routines.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* This file has been written to be more dynamic and a bit cleaner,&n; * but it still needs some spring cleaning.&n; */
DECL|variable|SBus_chain
r_struct
id|linux_sbus
op_star
id|SBus_chain
suffix:semicolon
DECL|variable|lbuf
r_static
r_char
id|lbuf
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Perhaps when I figure out more about the iommu we&squot;ll put a&n; * device registration routine here that probe_sbus() calls to&n; * setup the iommu for each Sbus.&n; */
multiline_comment|/* We call this for each SBus device, and fill the structure based&n; * upon the prom device tree.  We return the start of memory after&n; * the things we have allocated.&n; */
multiline_comment|/* #define DEBUG_FILL */
r_void
DECL|function|fill_sbus_device
id|fill_sbus_device
c_func
(paren
r_int
id|nd
comma
r_struct
id|linux_sbus_device
op_star
id|sbus_dev
)paren
(brace
r_int
id|grrr
comma
id|len
suffix:semicolon
r_int
r_int
id|dev_base_addr
comma
id|base
suffix:semicolon
id|sbus_dev-&gt;prom_node
op_assign
id|nd
suffix:semicolon
id|prom_getstring
c_func
(paren
id|nd
comma
l_string|&quot;name&quot;
comma
id|lbuf
comma
r_sizeof
(paren
id|lbuf
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sbus_dev-&gt;prom_name
comma
id|lbuf
)paren
suffix:semicolon
id|dev_base_addr
op_assign
id|prom_getint
c_func
(paren
id|nd
comma
l_string|&quot;address&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_base_addr
op_ne
op_minus
l_int|1
)paren
(brace
id|sbus_dev-&gt;sbus_addr
op_assign
id|dev_base_addr
suffix:semicolon
)brace
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|nd
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|sbus_dev-&gt;reg_addrs
comma
r_sizeof
(paren
id|sbus_dev-&gt;reg_addrs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_mod
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;WHOOPS:  proplen for %s was %d, need multiple of %d&bslash;n&quot;
comma
id|sbus_dev-&gt;prom_name
comma
id|len
comma
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;fill_sbus_device&quot;
)paren
suffix:semicolon
)brace
id|sbus_dev-&gt;num_registers
op_assign
(paren
id|len
op_div
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
id|base
op_assign
(paren
r_int
r_int
)paren
id|sbus_dev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ge
id|SUN_SBUS_BVADDR
op_logical_or
id|sparc_cpu_model
op_eq
id|sun4m
)paren
(brace
multiline_comment|/* Ahh, we can determine the slot and offset */
id|sbus_dev-&gt;slot
op_assign
id|sbus_dev_slot
c_func
(paren
id|base
)paren
suffix:semicolon
id|sbus_dev-&gt;offset
op_assign
id|sbus_dev_offset
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Grrr, gotta do calculations to fix things up */
id|sbus_dev-&gt;slot
op_assign
id|sbus_dev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
id|sbus_dev-&gt;offset
op_assign
id|base
suffix:semicolon
id|sbus_dev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
op_assign
(paren
r_char
op_star
)paren
id|sbus_devaddr
c_func
(paren
id|sbus_dev-&gt;slot
comma
id|base
)paren
suffix:semicolon
r_for
c_loop
(paren
id|grrr
op_assign
l_int|1
suffix:semicolon
id|grrr
OL
id|sbus_dev-&gt;num_registers
suffix:semicolon
id|grrr
op_increment
)paren
(brace
id|base
op_assign
(paren
r_int
r_int
)paren
id|sbus_dev-&gt;reg_addrs
(braket
id|grrr
)braket
dot
id|phys_addr
suffix:semicolon
id|sbus_dev-&gt;reg_addrs
(braket
id|grrr
)braket
dot
id|phys_addr
op_assign
(paren
r_char
op_star
)paren
id|sbus_devaddr
c_func
(paren
id|sbus_dev-&gt;slot
comma
id|base
)paren
suffix:semicolon
)brace
multiline_comment|/* That surely sucked */
)brace
id|sbus_dev-&gt;sbus_addr
op_assign
(paren
r_int
r_int
)paren
id|sbus_dev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
(paren
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
op_star
id|PROMREG_MAX
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;WHOOPS:  I got too many register addresses for %s  len=%d&bslash;n&quot;
comma
id|sbus_dev-&gt;prom_name
comma
id|len
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;sbus device register overflow&quot;
)paren
suffix:semicolon
)brace
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|nd
comma
l_string|&quot;address&quot;
comma
(paren
r_void
op_star
)paren
id|sbus_dev-&gt;sbus_vaddrs
comma
r_sizeof
(paren
id|sbus_dev-&gt;sbus_vaddrs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_amp
l_int|3
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Grrr, I didn&squot;t get a multiple of 4 proplen &quot;
l_string|&quot;for device %s got %d&bslash;n&quot;
comma
id|sbus_dev-&gt;prom_name
comma
id|len
)paren
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
id|sbus_dev-&gt;num_vaddrs
op_assign
(paren
id|len
op_div
l_int|4
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|nd
comma
l_string|&quot;intr&quot;
comma
(paren
r_void
op_star
)paren
id|sbus_dev-&gt;irqs
comma
r_sizeof
(paren
id|sbus_dev-&gt;irqs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
l_int|7
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Grrr, I didn&squot;t get a multiple of 8 proplen for &quot;
l_string|&quot;device %s got %d&bslash;n&quot;
comma
id|sbus_dev-&gt;prom_name
comma
id|len
)paren
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
id|sbus_dev-&gt;num_irqs
op_assign
(paren
id|len
op_div
l_int|8
)paren
suffix:semicolon
macro_line|#if OLD_STYLE_IRQ
multiline_comment|/* Grrr, V3 prom tries to be efficient */
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|sbus_dev-&gt;num_irqs
suffix:semicolon
id|len
op_increment
)paren
(brace
id|sbus_dev-&gt;irqs
(braket
id|len
)braket
dot
id|pri
op_and_assign
l_int|0xf
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|sbus_dev-&gt;num_irqs
op_eq
l_int|0
)paren
(brace
id|sbus_dev-&gt;irqs
(braket
l_int|0
)braket
dot
id|pri
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_FILL
id|prom_printf
c_func
(paren
l_string|&quot;Found %s at SBUS slot %x offset %08lx irq-level %d&bslash;n&quot;
comma
id|sbus_dev-&gt;prom_name
comma
id|sbus_dev-&gt;slot
comma
id|sbus_dev-&gt;offset
comma
id|sbus_dev-&gt;irqs
(braket
l_int|0
)braket
dot
id|pri
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Base address %08lx&bslash;n&quot;
comma
id|sbus_dev-&gt;sbus_addr
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;REGISTERS: Probed %d register(s)&bslash;n&quot;
comma
id|sbus_dev-&gt;num_registers
)paren
suffix:semicolon
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|sbus_dev-&gt;num_registers
suffix:semicolon
id|len
op_increment
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Regs&lt;%d&gt; at address&lt;%08lx&gt; IO-space&lt;%d&gt; size&lt;%d &quot;
l_string|&quot;bytes, %d words&gt;&bslash;n&quot;
comma
(paren
r_int
)paren
id|len
comma
(paren
r_int
r_int
)paren
id|sbus_dev-&gt;reg_addrs
(braket
id|len
)braket
dot
id|phys_addr
comma
id|sbus_dev-&gt;reg_addrs
(braket
id|len
)braket
dot
id|which_io
comma
id|sbus_dev-&gt;reg_addrs
(braket
id|len
)braket
dot
id|reg_size
comma
(paren
id|sbus_dev-&gt;reg_addrs
(braket
id|len
)braket
dot
id|reg_size
op_div
l_int|4
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/* This routine gets called from whoever needs the sbus first, to scan&n; * the SBus device tree.  Currently it just prints out the devices&n; * found on the bus and builds trees of SBUS structs and attached&n; * devices.&n; */
r_extern
r_void
id|sun_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|iommu_init
c_func
(paren
r_int
id|iommu_node
comma
r_int
r_int
id|memstart
comma
r_int
r_int
id|memend
comma
r_struct
id|linux_sbus
op_star
id|sbus
)paren
suffix:semicolon
r_int
r_int
DECL|function|sbus_init
id|sbus_init
c_func
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
(brace
r_register
r_int
id|nd
comma
id|this_sbus
comma
id|sbus_devs
comma
id|topnd
comma
id|iommund
suffix:semicolon
r_int
r_int
id|sbus_clock
suffix:semicolon
r_struct
id|linux_sbus
op_star
id|sbus
suffix:semicolon
r_struct
id|linux_sbus_device
op_star
id|this_dev
suffix:semicolon
r_int
id|num_sbus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* How many did we find? */
id|memory_start
op_assign
(paren
(paren
id|memory_start
op_plus
l_int|7
)paren
op_amp
(paren
op_complement
l_int|7
)paren
)paren
suffix:semicolon
id|topnd
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
multiline_comment|/* Finding the first sbus is a special case... */
id|iommund
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;sbus&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|iommund
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;iommu&quot;
)paren
)paren
op_eq
l_int|0
op_logical_or
(paren
id|nd
op_assign
id|prom_getchild
c_func
(paren
id|iommund
)paren
)paren
op_eq
l_int|0
op_logical_or
(paren
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|nd
comma
l_string|&quot;sbus&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* No reason to run further - the data access trap will occur. */
id|panic
c_func
(paren
l_string|&quot;sbus not found&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Ok, we&squot;ve found the first one, allocate first SBus struct&n;&t; * and place in chain.&n;&t; */
id|sbus
op_assign
id|SBus_chain
op_assign
(paren
r_struct
id|linux_sbus
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
r_sizeof
(paren
r_struct
id|linux_sbus
)paren
suffix:semicolon
id|sbus-&gt;next
op_assign
l_int|0
suffix:semicolon
id|this_sbus
op_assign
id|nd
suffix:semicolon
multiline_comment|/* Have IOMMU will travel. XXX grrr - this should be per sbus... */
r_if
c_cond
(paren
id|iommund
)paren
(brace
id|memory_start
op_assign
id|iommu_init
c_func
(paren
id|iommund
comma
id|memory_start
comma
id|memory_end
comma
id|sbus
)paren
suffix:semicolon
)brace
multiline_comment|/* Loop until we find no more SBUS&squot;s */
r_while
c_loop
(paren
id|this_sbus
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus%d: &quot;
comma
id|num_sbus
)paren
suffix:semicolon
id|sbus_clock
op_assign
id|prom_getint
c_func
(paren
id|this_sbus
comma
l_string|&quot;clock-frequency&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbus_clock
op_eq
op_minus
l_int|1
)paren
(brace
id|sbus_clock
op_assign
(paren
l_int|25
op_star
l_int|1000
op_star
l_int|1000
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Clock %d.%d MHz&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
(paren
id|sbus_clock
op_div
l_int|1000
)paren
op_div
l_int|1000
)paren
comma
(paren
r_int
)paren
(paren
(paren
(paren
id|sbus_clock
op_div
l_int|1000
)paren
op_mod
l_int|1000
op_ne
l_int|0
)paren
ques
c_cond
(paren
(paren
(paren
id|sbus_clock
op_div
l_int|1000
)paren
op_mod
l_int|1000
)paren
op_plus
l_int|1000
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|prom_getstring
c_func
(paren
id|this_sbus
comma
l_string|&quot;name&quot;
comma
id|lbuf
comma
r_sizeof
(paren
id|lbuf
)paren
)paren
suffix:semicolon
id|sbus-&gt;prom_node
op_assign
id|this_sbus
suffix:semicolon
id|strcpy
c_func
(paren
id|sbus-&gt;prom_name
comma
id|lbuf
)paren
suffix:semicolon
id|sbus-&gt;clock_freq
op_assign
id|sbus_clock
suffix:semicolon
id|sbus_devs
op_assign
id|prom_getchild
c_func
(paren
id|this_sbus
)paren
suffix:semicolon
id|sbus-&gt;devices
op_assign
(paren
r_struct
id|linux_sbus_device
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
r_sizeof
(paren
r_struct
id|linux_sbus_device
)paren
suffix:semicolon
id|this_dev
op_assign
id|sbus-&gt;devices
suffix:semicolon
id|this_dev-&gt;next
op_assign
l_int|0
suffix:semicolon
id|fill_sbus_device
c_func
(paren
id|sbus_devs
comma
id|this_dev
)paren
suffix:semicolon
id|this_dev-&gt;my_bus
op_assign
id|sbus
suffix:semicolon
multiline_comment|/* Should we traverse for children? */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|this_dev-&gt;prom_name
comma
l_string|&quot;espdma&quot;
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|this_dev-&gt;prom_name
comma
l_string|&quot;ledma&quot;
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Allocate device node */
id|this_dev-&gt;child
op_assign
(paren
r_struct
id|linux_sbus_device
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
r_sizeof
(paren
r_struct
id|linux_sbus_device
)paren
suffix:semicolon
multiline_comment|/* Fill it */
id|fill_sbus_device
c_func
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
comma
id|this_dev-&gt;child
)paren
suffix:semicolon
id|this_dev-&gt;child-&gt;my_bus
op_assign
id|sbus
suffix:semicolon
)brace
r_else
(brace
id|this_dev-&gt;child
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|sbus_devs
op_assign
id|prom_getsibling
c_func
(paren
id|sbus_devs
)paren
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Allocate device node */
id|this_dev-&gt;next
op_assign
(paren
r_struct
id|linux_sbus_device
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
r_sizeof
(paren
r_struct
id|linux_sbus_device
)paren
suffix:semicolon
id|this_dev
op_assign
id|this_dev-&gt;next
suffix:semicolon
id|this_dev-&gt;next
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Fill it */
id|fill_sbus_device
c_func
(paren
id|sbus_devs
comma
id|this_dev
)paren
suffix:semicolon
id|this_dev-&gt;my_bus
op_assign
id|sbus
suffix:semicolon
multiline_comment|/* Is there a child node hanging off of us? */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|this_dev-&gt;prom_name
comma
l_string|&quot;espdma&quot;
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|this_dev-&gt;prom_name
comma
l_string|&quot;ledma&quot;
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Get new device struct */
id|this_dev-&gt;child
op_assign
(paren
r_struct
id|linux_sbus_device
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
r_sizeof
(paren
r_struct
id|linux_sbus_device
)paren
suffix:semicolon
multiline_comment|/* Fill it */
id|fill_sbus_device
c_func
(paren
id|prom_getchild
c_func
(paren
id|sbus_devs
)paren
comma
id|this_dev-&gt;child
)paren
suffix:semicolon
id|this_dev-&gt;child-&gt;my_bus
op_assign
id|sbus
suffix:semicolon
)brace
r_else
(brace
id|this_dev-&gt;child
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|memory_start
op_assign
id|dvma_init
c_func
(paren
id|sbus
comma
id|memory_start
)paren
suffix:semicolon
id|num_sbus
op_increment
suffix:semicolon
id|this_sbus
op_assign
id|prom_getsibling
c_func
(paren
id|this_sbus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_sbus
)paren
(brace
r_break
suffix:semicolon
)brace
id|this_sbus
op_assign
id|prom_searchsiblings
c_func
(paren
id|this_sbus
comma
l_string|&quot;sbus&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this_sbus
)paren
(brace
id|sbus-&gt;next
op_assign
(paren
r_struct
id|linux_sbus
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
r_sizeof
(paren
r_struct
id|linux_sbus
)paren
suffix:semicolon
id|sbus
op_assign
id|sbus-&gt;next
suffix:semicolon
id|sbus-&gt;next
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* while(this_sbus) */
id|sun_console_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* whee... */
r_return
id|memory_start
suffix:semicolon
)brace
eof