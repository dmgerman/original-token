multiline_comment|/* sbus.h:  Defines for the Sun SBus.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_SBUS_H
DECL|macro|_SPARC_SBUS_H
mdefine_line|#define _SPARC_SBUS_H
macro_line|#include &lt;asm/openprom.h&gt;  /* For linux_prom_registers and linux_prom_irqs */
multiline_comment|/* We scan which devices are on the SBus using the PROM node device&n; * tree.  SBus devices are described in two different ways.  You can&n; * either get an absolute address at which to access the device, or&n; * you can get a SBus &squot;slot&squot; number and an offset within that slot.&n; */
multiline_comment|/* The base address at which to calculate device OBIO addresses. */
DECL|macro|SUN_SBUS_BVADDR
mdefine_line|#define SUN_SBUS_BVADDR        0xf8000000
DECL|macro|SBUS_OFF_MASK
mdefine_line|#define SBUS_OFF_MASK          0x01ffffff
multiline_comment|/* These routines are used to calculate device address from slot&n; * numbers + offsets, and vice versa.&n; */
DECL|function|sbus_devaddr
r_extern
r_inline
r_int
r_int
id|sbus_devaddr
c_func
(paren
r_int
id|slotnum
comma
r_int
r_int
id|offset
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
id|SUN_SBUS_BVADDR
op_plus
(paren
(paren
id|slotnum
)paren
op_lshift
l_int|25
)paren
op_plus
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|sbus_dev_slot
r_extern
r_inline
r_int
id|sbus_dev_slot
c_func
(paren
r_int
r_int
id|dev_addr
)paren
(brace
r_return
(paren
r_int
)paren
(paren
(paren
(paren
id|dev_addr
)paren
op_minus
id|SUN_SBUS_BVADDR
)paren
op_rshift
l_int|25
)paren
suffix:semicolon
)brace
DECL|function|sbus_dev_offset
r_extern
r_inline
r_int
r_int
id|sbus_dev_offset
c_func
(paren
r_int
r_int
id|dev_addr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
(paren
(paren
id|dev_addr
)paren
op_minus
id|SUN_SBUS_BVADDR
)paren
op_amp
id|SBUS_OFF_MASK
)paren
suffix:semicolon
)brace
multiline_comment|/* Handy macro */
DECL|macro|STRUCT_ALIGN
mdefine_line|#define STRUCT_ALIGN(addr) ((addr+7)&amp;(~7))
multiline_comment|/* Linus SBUS device tables */
DECL|struct|linux_sbus_device
r_struct
id|linux_sbus_device
(brace
DECL|member|next
r_struct
id|linux_sbus_device
op_star
id|next
suffix:semicolon
multiline_comment|/* next device on this SBus or null */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* PROM device tree node for this device */
DECL|member|prom_name
r_char
op_star
id|prom_name
suffix:semicolon
multiline_comment|/* PROM device name */
DECL|member|linux_name
r_char
op_star
id|linux_name
suffix:semicolon
multiline_comment|/* Name used internally by Linux */
multiline_comment|/* device register addresses */
DECL|member|reg_addrs
r_struct
id|linux_prom_registers
id|reg_addrs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_registers
r_int
id|num_registers
suffix:semicolon
multiline_comment|/* List of IRQ&squot;s this device uses. */
DECL|member|irqs
r_struct
id|linux_prom_irqs
id|irqs
(braket
id|PROMINTR_MAX
)braket
suffix:semicolon
DECL|member|num_irqs
r_int
id|num_irqs
suffix:semicolon
DECL|member|sbus_addr
r_int
r_int
id|sbus_addr
suffix:semicolon
multiline_comment|/* Absolute base address for device. */
DECL|member|sbus_vaddrs
r_int
r_int
id|sbus_vaddrs
(braket
id|PROMVADDR_MAX
)braket
suffix:semicolon
DECL|member|num_vaddrs
r_int
r_int
id|num_vaddrs
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* Offset given by PROM */
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* Device slot number */
)brace
suffix:semicolon
multiline_comment|/* This struct describes the SBus-es found on this machine. */
DECL|struct|linux_sbus
r_struct
id|linux_sbus
(brace
DECL|member|next
r_struct
id|linux_sbus
op_star
id|next
suffix:semicolon
multiline_comment|/* next SBus, if more than one SBus */
DECL|member|devices
r_struct
id|linux_sbus_device
op_star
id|devices
suffix:semicolon
multiline_comment|/* Link to devices on this SBus */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* PROM device tree node for this SBus */
DECL|member|prom_name
r_char
op_star
id|prom_name
suffix:semicolon
multiline_comment|/* Usually &quot;sbus&quot; */
DECL|member|clock_freq
r_int
id|clock_freq
suffix:semicolon
multiline_comment|/* Speed of this SBus */
)brace
suffix:semicolon
r_extern
r_struct
id|linux_sbus
id|Linux_SBus
suffix:semicolon
macro_line|#endif /* !(_SPARC_SBUS_H) */
eof
