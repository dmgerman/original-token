multiline_comment|/*&n; *  linux/include/asm-ppc/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the ppc architecture specific IDE code.&n; */
macro_line|#ifndef __ASMPPC_IDE_H
DECL|macro|__ASMPPC_IDE_H
mdefine_line|#define __ASMPPC_IDE_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4
macro_line|#endif
macro_line|#include &lt;asm/hdreg.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_int
id|pmac_ide_ports_known
suffix:semicolon
r_extern
id|ide_ioreg_t
id|pmac_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
r_extern
r_int
id|pmac_ide_irq
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
r_extern
r_void
id|pmac_ide_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|chrp_ide_ports_known
suffix:semicolon
r_extern
id|ide_ioreg_t
id|chrp_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
r_extern
id|ide_ioreg_t
id|chrp_idedma_regbase
suffix:semicolon
multiline_comment|/* one for both channels */
r_extern
r_int
r_int
id|chrp_ide_irq
suffix:semicolon
r_extern
r_void
id|chrp_ide_probe
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|struct|ide_machdep_calls
r_struct
id|ide_machdep_calls
(brace
DECL|member|insw
r_void
(paren
op_star
id|insw
)paren
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
DECL|member|outsw
r_void
(paren
op_star
id|outsw
)paren
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
DECL|member|default_irq
r_int
(paren
op_star
id|default_irq
)paren
(paren
id|ide_ioreg_t
id|base
)paren
suffix:semicolon
DECL|member|default_io_base
id|ide_ioreg_t
(paren
op_star
id|default_io_base
)paren
(paren
r_int
id|index
)paren
suffix:semicolon
DECL|member|check_region
r_int
(paren
op_star
id|check_region
)paren
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
suffix:semicolon
DECL|member|request_region
r_void
(paren
op_star
id|request_region
)paren
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
DECL|member|release_region
r_void
(paren
op_star
id|release_region
)paren
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
suffix:semicolon
DECL|member|fix_driveid
r_void
(paren
op_star
id|fix_driveid
)paren
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
suffix:semicolon
DECL|member|ide_init_hwif
r_void
(paren
op_star
id|ide_init_hwif
)paren
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
DECL|member|io_base
r_int
id|io_base
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ide_machdep_calls
id|ppc_ide_md
suffix:semicolon
r_void
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|ide_insw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_void
id|ide_outsw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_void
id|ppc_generic_ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
suffix:semicolon
DECL|macro|insw
macro_line|#undef insw
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns) &t;do {&t;&t;&t;&t;&bslash;&n;&t;ppc_ide_md.insw((port), (buf), (ns));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|outsw
macro_line|#undef outsw
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns) &t;do {&t;&t;&t;&t;&bslash;&n;&t;ppc_ide_md.outsw((port), (buf), (ns));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef&t;SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define&t;SUPPORT_SLOW_DATA_PORTS&t;0
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef&t;SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC&t;0
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;__sti()
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.default_irq
)paren
r_return
id|ppc_ide_md
dot
id|default_irq
c_func
(paren
id|base
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
id|ide_ioreg_t
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.default_io_base
)paren
r_return
id|ppc_ide_md
dot
id|default_io_base
c_func
(paren
id|index
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ide_init_default_hwifs
r_static
id|__inline__
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef __DO_I_NEED_THIS
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_HWIFS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hw
comma
id|ide_default_io_base
c_func
(paren
id|index
)paren
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|ide_default_irq
c_func
(paren
id|ide_default_io_base
c_func
(paren
id|index
)paren
)paren
suffix:semicolon
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif /* __DO_I_NEED_THIS */
)brace
DECL|function|ide_check_region
r_static
id|__inline__
r_int
id|ide_check_region
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.check_region
)paren
r_return
id|ppc_ide_md
dot
id|check_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ide_request_region
r_static
id|__inline__
r_void
id|ide_request_region
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.request_region
)paren
id|ppc_ide_md
dot
id|request_region
c_func
(paren
id|from
comma
id|extent
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|ide_release_region
r_static
id|__inline__
r_void
id|ide_release_region
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.release_region
)paren
id|ppc_ide_md
dot
id|release_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
)brace
DECL|function|ide_fix_driveid
r_static
id|__inline__
r_void
id|ide_fix_driveid
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.fix_driveid
)paren
id|ppc_ide_md
dot
id|fix_driveid
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inb
mdefine_line|#define inb(port)&t;in_8((unsigned char *)((port) + ppc_ide_md.io_base))
DECL|macro|inb_p
macro_line|#undef inb_p
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;inb(port)
DECL|macro|outb
macro_line|#undef outb
DECL|macro|outb
mdefine_line|#define outb(val, port)&t;&bslash;&n;&t;out_8((unsigned char *)((port) + ppc_ide_md.io_base), (val) )
DECL|macro|outb_p
macro_line|#undef outb_p
DECL|macro|outb_p
mdefine_line|#define outb_p(val, port)&t;outb(val, port)
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0/1 */
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
DECL|macro|ide_request_irq
mdefine_line|#define ide_request_irq(irq,hand,flg,dev,id)&t;request_irq((irq),(hand),(flg),(dev),(id))
DECL|macro|ide_free_irq
mdefine_line|#define ide_free_irq(irq,dev_id)&t;&t;free_irq((irq), (dev_id))
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMPPC_IDE_H */
eof
