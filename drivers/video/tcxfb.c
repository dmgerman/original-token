multiline_comment|/* $Id: tcxfb.c,v 1.1 1998/07/21 14:50:44 jj Exp $&n; * tcxfb.c: TCX 24/8bit frame buffer driver&n; *&n; * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)&n; */
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
macro_line|#include &quot;sbusfb.h&quot;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;fbcon-cfb8.h&quot;
multiline_comment|/* THC definitions */
DECL|macro|TCX_THC_MISC_REV_SHIFT
mdefine_line|#define TCX_THC_MISC_REV_SHIFT       16
DECL|macro|TCX_THC_MISC_REV_MASK
mdefine_line|#define TCX_THC_MISC_REV_MASK        15
DECL|macro|TCX_THC_MISC_VSYNC_DIS
mdefine_line|#define TCX_THC_MISC_VSYNC_DIS       (1 &lt;&lt; 25)
DECL|macro|TCX_THC_MISC_HSYNC_DIS
mdefine_line|#define TCX_THC_MISC_HSYNC_DIS       (1 &lt;&lt; 24)
DECL|macro|TCX_THC_MISC_RESET
mdefine_line|#define TCX_THC_MISC_RESET           (1 &lt;&lt; 12)
DECL|macro|TCX_THC_MISC_VIDEO
mdefine_line|#define TCX_THC_MISC_VIDEO           (1 &lt;&lt; 10)
DECL|macro|TCX_THC_MISC_SYNC
mdefine_line|#define TCX_THC_MISC_SYNC            (1 &lt;&lt; 9)
DECL|macro|TCX_THC_MISC_VSYNC
mdefine_line|#define TCX_THC_MISC_VSYNC           (1 &lt;&lt; 8)
DECL|macro|TCX_THC_MISC_SYNC_ENAB
mdefine_line|#define TCX_THC_MISC_SYNC_ENAB       (1 &lt;&lt; 7)
DECL|macro|TCX_THC_MISC_CURS_RES
mdefine_line|#define TCX_THC_MISC_CURS_RES        (1 &lt;&lt; 6)
DECL|macro|TCX_THC_MISC_INT_ENAB
mdefine_line|#define TCX_THC_MISC_INT_ENAB        (1 &lt;&lt; 5)
DECL|macro|TCX_THC_MISC_INT
mdefine_line|#define TCX_THC_MISC_INT             (1 &lt;&lt; 4)
DECL|macro|TCX_THC_MISC_INIT
mdefine_line|#define TCX_THC_MISC_INIT            0x9f
DECL|macro|TCX_THC_REV_REV_SHIFT
mdefine_line|#define TCX_THC_REV_REV_SHIFT        20
DECL|macro|TCX_THC_REV_REV_MASK
mdefine_line|#define TCX_THC_REV_REV_MASK         15
DECL|macro|TCX_THC_REV_MINREV_SHIFT
mdefine_line|#define TCX_THC_REV_MINREV_SHIFT     28
DECL|macro|TCX_THC_REV_MINREV_MASK
mdefine_line|#define TCX_THC_REV_MINREV_MASK      15
multiline_comment|/* The contents are unknown */
DECL|struct|tcx_tec
r_struct
id|tcx_tec
(brace
DECL|member|tec_matrix
r_volatile
id|u32
id|tec_matrix
suffix:semicolon
DECL|member|tec_clip
r_volatile
id|u32
id|tec_clip
suffix:semicolon
DECL|member|tec_vdc
r_volatile
id|u32
id|tec_vdc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcx_thc
r_struct
id|tcx_thc
(brace
DECL|member|thc_rev
r_volatile
id|u32
id|thc_rev
suffix:semicolon
DECL|member|thc_pad0
id|u32
id|thc_pad0
(braket
l_int|511
)braket
suffix:semicolon
DECL|member|thc_hs
r_volatile
id|u32
id|thc_hs
suffix:semicolon
multiline_comment|/* hsync timing */
DECL|member|thc_hsdvs
r_volatile
id|u32
id|thc_hsdvs
suffix:semicolon
DECL|member|thc_hd
r_volatile
id|u32
id|thc_hd
suffix:semicolon
DECL|member|thc_vs
r_volatile
id|u32
id|thc_vs
suffix:semicolon
multiline_comment|/* vsync timing */
DECL|member|thc_vd
r_volatile
id|u32
id|thc_vd
suffix:semicolon
DECL|member|thc_refresh
r_volatile
id|u32
id|thc_refresh
suffix:semicolon
DECL|member|thc_misc
r_volatile
id|u32
id|thc_misc
suffix:semicolon
DECL|member|thc_pad1
id|u32
id|thc_pad1
(braket
l_int|56
)braket
suffix:semicolon
DECL|member|thc_cursxy
r_volatile
id|u32
id|thc_cursxy
suffix:semicolon
multiline_comment|/* cursor x,y position (16 bits each) */
DECL|member|thc_cursmask
r_volatile
id|u32
id|thc_cursmask
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* cursor mask bits */
DECL|member|thc_cursbits
r_volatile
id|u32
id|thc_cursbits
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* what to show where mask enabled */
)brace
suffix:semicolon
DECL|variable|tcx_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|tcx_mmap_map
(braket
)braket
op_assign
(brace
(brace
id|TCX_RAM8BIT
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
(brace
id|TCX_RAM24BIT
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|4
)paren
)brace
comma
(brace
id|TCX_UNK3
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_UNK4
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_CONTROLPLANE
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|4
)paren
)brace
comma
(brace
id|TCX_UNK6
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_UNK7
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_TEC
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_BTREGS
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_THC
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_DHC
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_ALT
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_UNK2
comma
l_int|0
comma
l_int|0x20000
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
DECL|function|tcx_set_control_plane
r_static
r_void
id|tcx_set_control_plane
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
id|u32
op_star
id|p
comma
op_star
id|pend
suffix:semicolon
id|p
op_assign
id|fb-&gt;s.tcx.cplane
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|pend
op_assign
id|p
op_plus
id|fb-&gt;type.fb_size
suffix:semicolon
id|p
OL
id|pend
suffix:semicolon
id|p
op_increment
)paren
op_star
id|p
op_and_assign
l_int|0xffffff
suffix:semicolon
)brace
DECL|function|tcx_switch_from_graph
r_static
r_void
id|tcx_switch_from_graph
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
multiline_comment|/* Reset control plane to 8bit mode if necessary */
r_if
c_cond
(paren
id|fb-&gt;open
op_logical_and
id|fb-&gt;mmaped
)paren
id|tcx_set_control_plane
(paren
id|fb
)paren
suffix:semicolon
)brace
DECL|function|tcx_loadcmap
r_static
r_void
id|tcx_loadcmap
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
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
id|fb-&gt;s.tcx.bt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bt-&gt;addr
op_assign
id|index
op_lshift
l_int|24
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|index
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bt-&gt;color_map
op_assign
id|fb-&gt;color_map
id|CM
c_func
(paren
id|i
comma
l_int|0
)paren
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;color_map
op_assign
id|fb-&gt;color_map
id|CM
c_func
(paren
id|i
comma
l_int|1
)paren
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;color_map
op_assign
id|fb-&gt;color_map
id|CM
c_func
(paren
id|i
comma
l_int|2
)paren
op_lshift
l_int|24
suffix:semicolon
)brace
)brace
DECL|function|tcx_restore_palette
r_static
r_void
id|tcx_restore_palette
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_struct
id|bt_regs
op_star
id|bt
op_assign
id|fb-&gt;s.tcx.bt
suffix:semicolon
id|bt-&gt;addr
op_assign
l_int|0
suffix:semicolon
id|bt-&gt;color_map
op_assign
l_int|0xffffffff
suffix:semicolon
id|bt-&gt;color_map
op_assign
l_int|0xffffffff
suffix:semicolon
id|bt-&gt;color_map
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
DECL|function|tcx_setcursormap
r_static
r_void
id|tcx_setcursormap
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
id|u8
op_star
id|red
comma
id|u8
op_star
id|green
comma
id|u8
op_star
id|blue
)paren
(brace
r_struct
id|bt_regs
op_star
id|bt
op_assign
id|fb-&gt;s.tcx.bt
suffix:semicolon
multiline_comment|/* Note the 2 &lt;&lt; 24 is different from cg6&squot;s 1 &lt;&lt; 24 */
id|bt-&gt;addr
op_assign
l_int|2
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;cursor
op_assign
id|red
(braket
l_int|0
)braket
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;cursor
op_assign
id|green
(braket
l_int|0
)braket
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;cursor
op_assign
id|blue
(braket
l_int|0
)braket
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;addr
op_assign
l_int|3
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;cursor
op_assign
id|red
(braket
l_int|1
)braket
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;cursor
op_assign
id|green
(braket
l_int|1
)braket
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;cursor
op_assign
id|blue
(braket
l_int|1
)braket
op_lshift
l_int|24
suffix:semicolon
id|bt-&gt;addr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set cursor shape */
DECL|function|tcx_setcurshape
r_static
r_void
id|tcx_setcurshape
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_struct
id|tcx_thc
op_star
id|thc
op_assign
id|fb-&gt;s.tcx.thc
suffix:semicolon
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|thc-&gt;thc_cursmask
(braket
id|i
)braket
op_assign
id|fb-&gt;cursor.bits
(braket
l_int|0
)braket
(braket
id|i
)braket
suffix:semicolon
id|thc-&gt;thc_cursbits
(braket
id|i
)braket
op_assign
id|fb-&gt;cursor.bits
(braket
l_int|1
)braket
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/* Load cursor information */
DECL|function|tcx_setcursor
r_static
r_void
id|tcx_setcursor
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_struct
id|cg_cursor
op_star
id|c
op_assign
op_amp
id|fb-&gt;cursor
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;enable
)paren
id|v
op_assign
(paren
(paren
id|c-&gt;cpos.fbx
op_minus
id|c-&gt;chot.fbx
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|c-&gt;cpos.fby
op_minus
id|c-&gt;chot.fby
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_else
multiline_comment|/* Magic constant to turn off the cursor */
id|v
op_assign
(paren
(paren
l_int|65536
op_minus
l_int|32
)paren
op_lshift
l_int|16
)paren
op_or
(paren
l_int|65536
op_minus
l_int|32
)paren
suffix:semicolon
id|fb-&gt;s.tcx.thc-&gt;thc_cursxy
op_assign
id|v
suffix:semicolon
)brace
DECL|function|tcx_blank
r_static
r_void
id|tcx_blank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
id|fb-&gt;s.tcx.thc-&gt;thc_misc
op_and_assign
op_complement
id|TCX_THC_MISC_VIDEO
suffix:semicolon
multiline_comment|/* This should put us in power-save */
id|fb-&gt;s.tcx.thc-&gt;thc_misc
op_or_assign
id|TCX_THC_MISC_VSYNC_DIS
suffix:semicolon
id|fb-&gt;s.tcx.thc-&gt;thc_misc
op_or_assign
id|TCX_THC_MISC_HSYNC_DIS
suffix:semicolon
)brace
DECL|function|tcx_unblank
r_static
r_void
id|tcx_unblank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
id|fb-&gt;s.tcx.thc-&gt;thc_misc
op_and_assign
op_complement
id|TCX_THC_MISC_VSYNC_DIS
suffix:semicolon
id|fb-&gt;s.tcx.thc-&gt;thc_misc
op_and_assign
op_complement
id|TCX_THC_MISC_HSYNC_DIS
suffix:semicolon
id|fb-&gt;s.tcx.thc-&gt;thc_misc
op_or_assign
id|TCX_THC_MISC_VIDEO
suffix:semicolon
)brace
DECL|function|tcx_reset
r_static
r_void
id|tcx_reset
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_if
c_cond
(paren
id|fb-&gt;open
op_logical_and
id|fb-&gt;mmaped
)paren
id|tcx_set_control_plane
c_func
(paren
id|fb
)paren
suffix:semicolon
multiline_comment|/* Turn off stuff in the Transform Engine. */
id|fb-&gt;s.tcx.tec-&gt;tec_matrix
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;s.tcx.tec-&gt;tec_clip
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;s.tcx.tec-&gt;tec_vdc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Enable cursor in Brooktree DAC. */
id|fb-&gt;s.tcx.bt-&gt;addr
op_assign
l_int|0x06
op_lshift
l_int|24
suffix:semicolon
id|fb-&gt;s.tcx.bt-&gt;control
op_or_assign
l_int|0x03
op_lshift
l_int|24
suffix:semicolon
)brace
DECL|function|tcx_margins
r_static
r_void
id|tcx_margins
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
id|tcxfb_init
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
id|lowdepth
suffix:semicolon
macro_line|#ifndef FBCON_HAS_CFB8
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
id|lowdepth
op_assign
id|prom_getbool
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;tcx-8-bit&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lowdepth
)paren
(brace
id|strcpy
c_func
(paren
id|fb-&gt;info.modename
comma
l_string|&quot;TCX8&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;TCX8&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|fb-&gt;info.modename
comma
l_string|&quot;TCX24&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;TCX24&quot;
)paren
suffix:semicolon
)brace
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
comma
l_int|0
comma
id|type-&gt;fb_size
comma
l_string|&quot;tcx_ram&quot;
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
id|fb-&gt;s.tcx.tec
op_assign
(paren
r_struct
id|tcx_tec
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|fb-&gt;sbdp-&gt;reg_addrs
(braket
l_int|7
)braket
dot
id|phys_addr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tcx_tec
)paren
comma
l_string|&quot;tcx_tec&quot;
comma
id|fb-&gt;iospace
comma
l_int|0
)paren
suffix:semicolon
id|fb-&gt;s.tcx.thc
op_assign
(paren
r_struct
id|tcx_thc
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|fb-&gt;sbdp-&gt;reg_addrs
(braket
l_int|9
)braket
dot
id|phys_addr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tcx_thc
)paren
comma
l_string|&quot;tcx_thc&quot;
comma
id|fb-&gt;iospace
comma
l_int|0
)paren
suffix:semicolon
id|fb-&gt;s.tcx.bt
op_assign
(paren
r_struct
id|bt_regs
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|fb-&gt;sbdp-&gt;reg_addrs
(braket
l_int|8
)braket
dot
id|phys_addr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|bt_regs
)paren
comma
l_string|&quot;tcx_dac&quot;
comma
id|fb-&gt;iospace
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lowdepth
)paren
(brace
id|fb-&gt;s.tcx.cplane
op_assign
(paren
id|u32
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|fb-&gt;sbdp-&gt;reg_addrs
(braket
l_int|4
)braket
dot
id|phys_addr
comma
l_int|0
comma
id|type-&gt;fb_size
op_star
l_int|4
comma
l_string|&quot;tcx_cplane&quot;
comma
id|fb-&gt;iospace
comma
l_int|0
)paren
suffix:semicolon
id|type-&gt;fb_depth
op_assign
l_int|24
suffix:semicolon
id|fb-&gt;switch_from_graph
op_assign
id|tcx_switch_from_graph
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* As there can be one tcx in a machine only, we can write directly into&n;&t;&t;   tcx_mmap_map */
id|tcx_mmap_map
(braket
l_int|1
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
id|tcx_mmap_map
(braket
l_int|4
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
id|tcx_mmap_map
(braket
l_int|5
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
id|tcx_mmap_map
(braket
l_int|6
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
)brace
id|fb-&gt;dispsw
op_assign
id|fbcon_cfb8
suffix:semicolon
id|fb-&gt;margins
op_assign
id|tcx_margins
suffix:semicolon
id|fb-&gt;loadcmap
op_assign
id|tcx_loadcmap
suffix:semicolon
r_if
c_cond
(paren
id|prom_getbool
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;hw-cursor&quot;
)paren
)paren
(brace
id|fb-&gt;setcursor
op_assign
id|tcx_setcursor
suffix:semicolon
id|fb-&gt;setcursormap
op_assign
id|tcx_setcursormap
suffix:semicolon
id|fb-&gt;setcurshape
op_assign
id|tcx_setcurshape
suffix:semicolon
)brace
id|fb-&gt;restore_palette
op_assign
id|tcx_restore_palette
suffix:semicolon
id|fb-&gt;blank
op_assign
id|tcx_blank
suffix:semicolon
id|fb-&gt;unblank
op_assign
id|tcx_unblank
suffix:semicolon
id|fb-&gt;reset
op_assign
id|tcx_reset
suffix:semicolon
id|fb-&gt;physbase
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;mmap_map
op_assign
id|tcx_mmap_map
suffix:semicolon
multiline_comment|/* Initialize Brooktree DAC */
id|fb-&gt;s.tcx.bt-&gt;addr
op_assign
l_int|0x04
op_lshift
l_int|24
suffix:semicolon
multiline_comment|/* color planes */
id|fb-&gt;s.tcx.bt-&gt;control
op_assign
l_int|0xff
op_lshift
l_int|24
suffix:semicolon
id|fb-&gt;s.tcx.bt-&gt;addr
op_assign
l_int|0x05
op_lshift
l_int|24
suffix:semicolon
id|fb-&gt;s.tcx.bt-&gt;control
op_assign
l_int|0x00
op_lshift
l_int|24
suffix:semicolon
id|fb-&gt;s.tcx.bt-&gt;addr
op_assign
l_int|0x06
op_lshift
l_int|24
suffix:semicolon
multiline_comment|/* overlay plane */
id|fb-&gt;s.tcx.bt-&gt;control
op_assign
l_int|0x73
op_lshift
l_int|24
suffix:semicolon
id|fb-&gt;s.tcx.bt-&gt;addr
op_assign
l_int|0x07
op_lshift
l_int|24
suffix:semicolon
id|fb-&gt;s.tcx.bt-&gt;control
op_assign
l_int|0x00
op_lshift
l_int|24
suffix:semicolon
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;tcx at %x.%08lx Rev %d.%d %s&quot;
comma
id|fb-&gt;iospace
comma
id|phys
comma
(paren
id|fb-&gt;s.tcx.thc-&gt;thc_rev
op_rshift
id|TCX_THC_REV_REV_SHIFT
)paren
op_amp
id|TCX_THC_REV_REV_MASK
comma
(paren
id|fb-&gt;s.tcx.thc-&gt;thc_rev
op_rshift
id|TCX_THC_REV_MINREV_SHIFT
)paren
op_amp
id|TCX_THC_REV_MINREV_MASK
comma
id|lowdepth
ques
c_cond
l_string|&quot;8-bit only&quot;
suffix:colon
l_string|&quot;24-bit depth&quot;
)paren
suffix:semicolon
id|tcx_reset
c_func
(paren
id|fb
)paren
suffix:semicolon
r_return
id|idstring
suffix:semicolon
)brace
eof