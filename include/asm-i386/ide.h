multiline_comment|/*&n; *  linux/include/asm-i386/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the i386 architecture specific IDE code.&n; */
macro_line|#ifndef __ASMi386_IDE_H
DECL|macro|__ASMi386_IDE_H
mdefine_line|#define __ASMi386_IDE_H
macro_line|#ifdef __KERNEL__
DECL|typedef|ide_ioreg_t
r_typedef
r_int
r_int
id|ide_ioreg_t
suffix:semicolon
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4
macro_line|#endif
DECL|macro|ide_sti
mdefine_line|#define ide_sti()&t;sti()
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
r_switch
c_cond
(paren
id|base
)paren
(brace
r_case
l_int|0x1f0
suffix:colon
r_return
l_int|14
suffix:semicolon
r_case
l_int|0x170
suffix:colon
r_return
l_int|15
suffix:semicolon
r_case
l_int|0x1e8
suffix:colon
r_return
l_int|11
suffix:semicolon
r_case
l_int|0x168
suffix:colon
r_return
l_int|10
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|index
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0x1f0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|0x170
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
l_int|0x1e8
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_int|0x168
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|ide_init_hwif_ports
r_static
id|__inline__
r_void
id|ide_init_hwif_ports
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|port
op_assign
id|base
suffix:semicolon
r_int
id|i
op_assign
l_int|8
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
op_star
id|p
op_increment
op_assign
id|port
op_increment
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|base
op_plus
l_int|0x206
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
)brace
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
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|bit5
r_int
id|bit5
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
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
DECL|function|ide_request_irq
r_static
id|__inline__
r_int
id|ide_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|device
comma
r_void
op_star
id|dev_id
)paren
(brace
r_return
id|request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|flags
comma
id|device
comma
id|dev_id
)paren
suffix:semicolon
)brace
DECL|function|ide_free_irq
r_static
id|__inline__
r_void
id|ide_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
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
r_return
id|check_region
c_func
(paren
id|from
comma
id|extent
)paren
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
id|release_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|function|ide_ack_intr
r_static
id|__inline__
r_int
id|ide_ack_intr
(paren
id|ide_ioreg_t
id|base_port
comma
id|ide_ioreg_t
id|irq_port
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ide_fix_driveid
r_static
id|__inline__
r_void
id|ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
)brace
DECL|function|ide_release_lock
r_static
id|__inline__
r_void
id|ide_release_lock
(paren
r_int
op_star
id|ide_lock
)paren
(brace
)brace
DECL|function|ide_get_lock
r_static
id|__inline__
r_void
id|ide_get_lock
(paren
r_int
op_star
id|ide_lock
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMi386_IDE_H */
eof
