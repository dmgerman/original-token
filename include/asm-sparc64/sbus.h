multiline_comment|/* $Id: sbus.h,v 1.1 1996/12/26 14:22:36 davem Exp $&n; * sbus.h:  Defines for the Sun SBus.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* XXX This needs to be mostly redone for sun5 SYSIO. */
macro_line|#ifndef _SPARC64_SBUS_H
DECL|macro|_SPARC64_SBUS_H
mdefine_line|#define _SPARC64_SBUS_H
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
multiline_comment|/* We scan which devices are on the SBus using the PROM node device&n; * tree.  SBus devices are described in two different ways.  You can&n; * either get an absolute address at which to access the device, or&n; * you can get a SBus &squot;slot&squot; number and an offset within that slot.&n; */
multiline_comment|/* The base address at which to calculate device OBIO addresses. */
DECL|macro|SUN_SBUS_BVADDR
mdefine_line|#define SUN_SBUS_BVADDR        0xf8000000
DECL|macro|SBUS_OFF_MASK
mdefine_line|#define SBUS_OFF_MASK          0x01ffffff
multiline_comment|/* These routines are used to calculate device address from slot&n; * numbers + offsets, and vice versa.&n; */
DECL|function|sbus_devaddr
r_extern
id|__inline__
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
id|__inline__
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
id|__inline__
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
r_struct
id|linux_sbus
suffix:semicolon
multiline_comment|/* Linux SBUS device tables */
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
DECL|member|child
r_struct
id|linux_sbus_device
op_star
id|child
suffix:semicolon
multiline_comment|/* For ledma and espdma on sun4m */
DECL|member|my_bus
r_struct
id|linux_sbus
op_star
id|my_bus
suffix:semicolon
multiline_comment|/* Back ptr to sbus */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* PROM device tree node for this device */
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* PROM device name */
DECL|member|linux_name
r_char
id|linux_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Name used internally by Linux */
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
)brace
suffix:semicolon
multiline_comment|/* This struct describes the SBus(s) found on this machine. */
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
DECL|member|iommu
r_struct
id|iommu_struct
op_star
id|iommu
suffix:semicolon
multiline_comment|/* IOMMU for this sbus if applicable */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* PROM device tree node for this SBus */
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Usually &quot;sbus&quot; or &quot;sbi&quot; */
DECL|member|clock_freq
r_int
id|clock_freq
suffix:semicolon
DECL|member|sbus_ranges
r_struct
id|linux_prom_ranges
id|sbus_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_sbus_ranges
r_int
id|num_sbus_ranges
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|linux_sbus
op_star
id|SBus_chain
suffix:semicolon
multiline_comment|/* Device probing routines could find these handy */
DECL|macro|for_each_sbus
mdefine_line|#define for_each_sbus(bus) &bslash;&n;        for((bus) = SBus_chain; (bus); (bus)=(bus)-&gt;next)
DECL|macro|for_each_sbusdev
mdefine_line|#define for_each_sbusdev(device, bus) &bslash;&n;        for((device) = (bus)-&gt;devices; (device); (device)=(device)-&gt;next)
DECL|macro|for_all_sbusdev
mdefine_line|#define for_all_sbusdev(device, bus) &bslash;&n;&t;for((bus) = SBus_chain, (device) = (bus)-&gt;devices; (bus); (device)=((device)-&gt;next ? (device)-&gt;next : ((bus) = (bus)-&gt;next, (bus) ? (bus)-&gt;devices : 0)))
multiline_comment|/* XXX This is promlib stuff, what is it doing here? XXX */
multiline_comment|/* Apply promlib probed SBUS ranges to registers. */
r_extern
r_void
id|prom_apply_sbus_ranges
c_func
(paren
r_struct
id|linux_sbus
op_star
id|sbus
comma
r_struct
id|linux_prom_registers
op_star
id|sbusregs
comma
r_int
id|nregs
)paren
suffix:semicolon
macro_line|#endif /* !(_SPARC64_SBUS_H) */
eof
