multiline_comment|/* $Id: cgthreefb.c,v 1.3 1998/09/04 15:43:43 jj Exp $&n; * cgthreefb.c: CGthree frame buffer driver&n; *&n; * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * Copyright (C) 1997 Eddie C. Dost (ecd@skynet.be)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;video/sbusfb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
multiline_comment|/* Control Register Constants */
DECL|macro|CG3_CR_ENABLE_INTS
mdefine_line|#define CG3_CR_ENABLE_INTS      0x80
DECL|macro|CG3_CR_ENABLE_VIDEO
mdefine_line|#define CG3_CR_ENABLE_VIDEO     0x40
DECL|macro|CG3_CR_ENABLE_TIMING
mdefine_line|#define CG3_CR_ENABLE_TIMING    0x20
DECL|macro|CG3_CR_ENABLE_CURCMP
mdefine_line|#define CG3_CR_ENABLE_CURCMP    0x10
DECL|macro|CG3_CR_XTAL_MASK
mdefine_line|#define CG3_CR_XTAL_MASK        0x0c
DECL|macro|CG3_CR_DIVISOR_MASK
mdefine_line|#define CG3_CR_DIVISOR_MASK     0x03
multiline_comment|/* Status Register Constants */
DECL|macro|CG3_SR_PENDING_INT
mdefine_line|#define CG3_SR_PENDING_INT      0x80
DECL|macro|CG3_SR_RES_MASK
mdefine_line|#define CG3_SR_RES_MASK         0x70
DECL|macro|CG3_SR_1152_900_76_A
mdefine_line|#define CG3_SR_1152_900_76_A    0x40
DECL|macro|CG3_SR_1152_900_76_B
mdefine_line|#define CG3_SR_1152_900_76_B    0x60
DECL|macro|CG3_SR_ID_MASK
mdefine_line|#define CG3_SR_ID_MASK          0x0f
DECL|macro|CG3_SR_ID_COLOR
mdefine_line|#define CG3_SR_ID_COLOR         0x01
DECL|macro|CG3_SR_ID_MONO
mdefine_line|#define CG3_SR_ID_MONO          0x02
DECL|macro|CG3_SR_ID_MONO_ECL
mdefine_line|#define CG3_SR_ID_MONO_ECL      0x03
DECL|enum|cg3_type
r_enum
id|cg3_type
(brace
DECL|enumerator|CG3_AT_66HZ
id|CG3_AT_66HZ
op_assign
l_int|0
comma
DECL|enumerator|CG3_AT_76HZ
id|CG3_AT_76HZ
comma
DECL|enumerator|CG3_RDI
id|CG3_RDI
)brace
suffix:semicolon
DECL|struct|cg3_regs
r_struct
id|cg3_regs
(brace
DECL|member|cmap
r_struct
id|bt_regs
id|cmap
suffix:semicolon
DECL|member|control
r_volatile
id|u8
id|control
suffix:semicolon
DECL|member|status
r_volatile
id|u8
id|status
suffix:semicolon
DECL|member|cursor_start
r_volatile
id|u8
id|cursor_start
suffix:semicolon
DECL|member|cursor_end
r_volatile
id|u8
id|cursor_end
suffix:semicolon
DECL|member|h_blank_start
r_volatile
id|u8
id|h_blank_start
suffix:semicolon
DECL|member|h_blank_end
r_volatile
id|u8
id|h_blank_end
suffix:semicolon
DECL|member|h_sync_start
r_volatile
id|u8
id|h_sync_start
suffix:semicolon
DECL|member|h_sync_end
r_volatile
id|u8
id|h_sync_end
suffix:semicolon
DECL|member|comp_sync_end
r_volatile
id|u8
id|comp_sync_end
suffix:semicolon
DECL|member|v_blank_start_high
r_volatile
id|u8
id|v_blank_start_high
suffix:semicolon
DECL|member|v_blank_start_low
r_volatile
id|u8
id|v_blank_start_low
suffix:semicolon
DECL|member|v_blank_end
r_volatile
id|u8
id|v_blank_end
suffix:semicolon
DECL|member|v_sync_start
r_volatile
id|u8
id|v_sync_start
suffix:semicolon
DECL|member|v_sync_end
r_volatile
id|u8
id|v_sync_end
suffix:semicolon
DECL|member|xfer_holdoff_start
r_volatile
id|u8
id|xfer_holdoff_start
suffix:semicolon
DECL|member|xfer_holdoff_end
r_volatile
id|u8
id|xfer_holdoff_end
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Offset of interesting structures in the OBIO space */
DECL|macro|CG3_REGS_OFFSET
mdefine_line|#define CG3_REGS_OFFSET&t;     0x400000
DECL|macro|CG3_RAM_OFFSET
mdefine_line|#define CG3_RAM_OFFSET&t;     0x800000
DECL|variable|cg3_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|cg3_mmap_map
(braket
)braket
op_assign
(brace
(brace
id|CG3_MMAP_OFFSET
comma
id|CG3_RAM_OFFSET
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The cg3 palette is loaded with 4 color values at each time  */
multiline_comment|/* so you end up with: (rgb)(r), (gb)(rg), (b)(rgb), and so on */
DECL|macro|D4M3
mdefine_line|#define D4M3(x) ((((x)&gt;&gt;2)&lt;&lt;1) + ((x)&gt;&gt;2))      /* (x/4)*3 */
DECL|macro|D4M4
mdefine_line|#define D4M4(x) ((x)&amp;~0x3)                      /* (x/4)*4 */
DECL|function|cg3_loadcmap
r_static
r_void
id|cg3_loadcmap
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|index
comma
r_int
id|count
)paren
(brace
r_struct
id|bt_regs
op_star
id|bt
op_assign
op_amp
id|fb-&gt;s.cg3.regs-&gt;cmap
suffix:semicolon
id|u32
op_star
id|i
suffix:semicolon
r_int
id|steps
suffix:semicolon
id|i
op_assign
(paren
(paren
(paren
id|u32
op_star
)paren
id|fb-&gt;color_map
)paren
op_plus
id|D4M3
c_func
(paren
id|index
)paren
)paren
suffix:semicolon
id|steps
op_assign
id|D4M3
c_func
(paren
id|index
op_plus
id|count
op_minus
l_int|1
)paren
op_minus
id|D4M3
c_func
(paren
id|index
)paren
op_plus
l_int|3
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|bt-&gt;addr
op_assign
(paren
id|u8
)paren
id|D4M4
c_func
(paren
id|index
)paren
suffix:semicolon
r_while
c_loop
(paren
id|steps
op_decrement
)paren
id|bt-&gt;color_map
op_assign
op_star
id|i
op_increment
suffix:semicolon
)brace
DECL|function|cg3_blank
r_static
r_void
id|cg3_blank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
id|fb-&gt;s.cg3.regs-&gt;control
op_and_assign
op_complement
id|CG3_CR_ENABLE_VIDEO
suffix:semicolon
)brace
DECL|function|cg3_unblank
r_static
r_void
id|cg3_unblank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
id|fb-&gt;s.cg3.regs-&gt;control
op_or_assign
id|CG3_CR_ENABLE_VIDEO
suffix:semicolon
)brace
DECL|function|cg3_margins
r_static
r_void
id|cg3_margins
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|x_margin
comma
r_int
id|y_margin
)paren
(brace
id|p-&gt;screen_base
op_add_assign
(paren
id|y_margin
op_minus
id|fb-&gt;y_margin
)paren
op_star
id|p-&gt;line_length
op_plus
(paren
id|x_margin
op_minus
id|fb-&gt;x_margin
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
id|u8
id|cg3regvals_66hz
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* 1152 x 900, 66 Hz */
l_int|0x14
comma
l_int|0xbb
comma
l_int|0x15
comma
l_int|0x2b
comma
l_int|0x16
comma
l_int|0x04
comma
l_int|0x17
comma
l_int|0x14
comma
l_int|0x18
comma
l_int|0xae
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xa8
comma
l_int|0x1b
comma
l_int|0x24
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x05
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|cg3regvals_76hz
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* 1152 x 900, 76 Hz */
l_int|0x14
comma
l_int|0xb7
comma
l_int|0x15
comma
l_int|0x27
comma
l_int|0x16
comma
l_int|0x03
comma
l_int|0x17
comma
l_int|0x0f
comma
l_int|0x18
comma
l_int|0xae
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xae
comma
l_int|0x1b
comma
l_int|0x2a
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x09
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x24
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|cg3regvals_rdi
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* 640 x 480, cgRDI */
l_int|0x14
comma
l_int|0x70
comma
l_int|0x15
comma
l_int|0x20
comma
l_int|0x16
comma
l_int|0x08
comma
l_int|0x17
comma
l_int|0x10
comma
l_int|0x18
comma
l_int|0x06
comma
l_int|0x19
comma
l_int|0x02
comma
l_int|0x1a
comma
l_int|0x31
comma
l_int|0x1b
comma
l_int|0x51
comma
l_int|0x1c
comma
l_int|0x06
comma
l_int|0x1d
comma
l_int|0x0c
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x22
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
op_star
id|cg3_regvals
(braket
)braket
id|__initdata
op_assign
(brace
id|cg3regvals_66hz
comma
id|cg3regvals_76hz
comma
id|cg3regvals_rdi
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|cg3_dacvals
(braket
)braket
id|__initdata
op_assign
(brace
l_int|4
comma
l_int|0xff
comma
l_int|5
comma
l_int|0x00
comma
l_int|6
comma
l_int|0x70
comma
l_int|7
comma
l_int|0x00
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|idstring
(braket
l_int|60
)braket
id|__initdata
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_char
op_star
id|cgthreefb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
)paren
(brace
r_struct
id|fb_fix_screeninfo
op_star
id|fix
op_assign
op_amp
id|fb-&gt;fix
suffix:semicolon
r_struct
id|display
op_star
id|disp
op_assign
op_amp
id|fb-&gt;disp
suffix:semicolon
r_struct
id|fbtype
op_star
id|type
op_assign
op_amp
id|fb-&gt;type
suffix:semicolon
r_int
r_int
id|phys
op_assign
id|fb-&gt;sbdp-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
r_int
id|cgRDI
op_assign
id|strstr
c_func
(paren
id|fb-&gt;sbdp-&gt;prom_name
comma
l_string|&quot;cgRDI&quot;
)paren
op_ne
l_int|NULL
suffix:semicolon
macro_line|#ifndef FBCON_HAS_CFB8
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;s.cg3.regs
)paren
(brace
id|fb-&gt;s.cg3.regs
op_assign
(paren
r_struct
id|cg3_regs
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|phys
op_plus
id|CG3_REGS_OFFSET
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cg3_regs
)paren
comma
l_string|&quot;cg3_regs&quot;
comma
id|fb-&gt;iospace
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cgRDI
)paren
(brace
r_char
id|buffer
(braket
l_int|40
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|ww
comma
id|hh
suffix:semicolon
op_star
id|buffer
op_assign
l_int|0
suffix:semicolon
id|prom_getstring
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;params&quot;
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buffer
)paren
(brace
id|ww
op_assign
id|simple_strtoul
(paren
id|buffer
comma
op_amp
id|p
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ww
op_logical_and
op_star
id|p
op_eq
l_char|&squot;x&squot;
)paren
(brace
id|hh
op_assign
id|simple_strtoul
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hh
op_logical_and
op_star
id|p
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|type-&gt;fb_width
op_ne
id|ww
op_logical_or
id|type-&gt;fb_height
op_ne
id|hh
)paren
(brace
id|type-&gt;fb_width
op_assign
id|ww
suffix:semicolon
id|type-&gt;fb_height
op_assign
id|hh
suffix:semicolon
r_return
id|SBUSFBINIT_SIZECHANGE
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
)brace
id|strcpy
c_func
(paren
id|fb-&gt;info.modename
comma
l_string|&quot;CGthree&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;CGthree&quot;
)paren
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|fb-&gt;var.xres_virtual
suffix:semicolon
id|disp-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disp-&gt;screen_base
)paren
id|disp-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|phys
op_plus
id|CG3_RAM_OFFSET
comma
l_int|0
comma
id|type-&gt;fb_size
comma
l_string|&quot;cg3_ram&quot;
comma
id|fb-&gt;iospace
comma
l_int|0
)paren
suffix:semicolon
id|disp-&gt;screen_base
op_add_assign
id|fix-&gt;line_length
op_star
id|fb-&gt;y_margin
op_plus
id|fb-&gt;x_margin
suffix:semicolon
id|fb-&gt;dispsw
op_assign
id|fbcon_cfb8
suffix:semicolon
id|fb-&gt;margins
op_assign
id|cg3_margins
suffix:semicolon
id|fb-&gt;loadcmap
op_assign
id|cg3_loadcmap
suffix:semicolon
id|fb-&gt;blank
op_assign
id|cg3_blank
suffix:semicolon
id|fb-&gt;unblank
op_assign
id|cg3_unblank
suffix:semicolon
id|fb-&gt;physbase
op_assign
id|phys
suffix:semicolon
id|fb-&gt;mmap_map
op_assign
id|cg3_mmap_map
suffix:semicolon
macro_line|#ifdef __sparc_v9__&t;
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;%s at %016lx&quot;
comma
id|cgRDI
ques
c_cond
l_string|&quot;cgRDI&quot;
suffix:colon
l_string|&quot;cgthree&quot;
comma
id|phys
)paren
suffix:semicolon
macro_line|#else
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;%s at %x.%08lx&quot;
comma
id|cgRDI
ques
c_cond
l_string|&quot;cgRDI&quot;
suffix:colon
l_string|&quot;cgthree&quot;
comma
id|fb-&gt;iospace
comma
id|phys
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|prom_getbool
c_func
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;width&quot;
)paren
)paren
(brace
multiline_comment|/* Ugh, broken PROM didn&squot;t initialize us.&n;&t;&t; * Let&squot;s deal with this ourselves.&n;&t;&t; */
r_enum
id|cg3_type
id|type
suffix:semicolon
id|u8
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|cgRDI
)paren
id|type
op_assign
id|CG3_RDI
suffix:semicolon
r_else
(brace
id|u8
id|status
op_assign
id|fb-&gt;s.cg3.regs-&gt;status
comma
id|mon
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|CG3_SR_ID_MASK
)paren
op_eq
id|CG3_SR_ID_COLOR
)paren
(brace
id|mon
op_assign
id|status
op_amp
id|CG3_SR_RES_MASK
suffix:semicolon
r_if
c_cond
(paren
id|mon
op_eq
id|CG3_SR_1152_900_76_A
op_logical_or
id|mon
op_eq
id|CG3_SR_1152_900_76_B
)paren
id|type
op_assign
id|CG3_AT_76HZ
suffix:semicolon
r_else
id|type
op_assign
id|CG3_AT_66HZ
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;cgthree: can&squot;t handle SR %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* fool gcc. */
)brace
)brace
r_for
c_loop
(paren
id|p
op_assign
id|cg3_regvals
(braket
id|type
)braket
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_add_assign
l_int|2
)paren
(paren
(paren
id|u8
op_star
)paren
id|fb-&gt;s.cg3.regs
)paren
(braket
id|p
(braket
l_int|0
)braket
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|cg3_dacvals
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_add_assign
l_int|2
)paren
(brace
op_star
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|fb-&gt;s.cg3.regs-&gt;cmap.addr
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|fb-&gt;s.cg3.regs-&gt;cmap.control
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
)brace
)brace
r_return
id|idstring
suffix:semicolon
)brace
eof
