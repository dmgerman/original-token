multiline_comment|/* $Id: cgfourteenfb.c,v 1.3 1998/09/04 15:43:41 jj Exp $&n; * cgfourteenfb.c: CGfourteen frame buffer driver&n; *&n; * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; */
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
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
DECL|macro|CG14_MCR_INTENABLE_SHIFT
mdefine_line|#define CG14_MCR_INTENABLE_SHIFT&t;7
DECL|macro|CG14_MCR_INTENABLE_MASK
mdefine_line|#define CG14_MCR_INTENABLE_MASK&t;&t;0x80
DECL|macro|CG14_MCR_VIDENABLE_SHIFT
mdefine_line|#define CG14_MCR_VIDENABLE_SHIFT&t;6
DECL|macro|CG14_MCR_VIDENABLE_MASK
mdefine_line|#define CG14_MCR_VIDENABLE_MASK&t;&t;0x40
DECL|macro|CG14_MCR_PIXMODE_SHIFT
mdefine_line|#define CG14_MCR_PIXMODE_SHIFT&t;&t;4
DECL|macro|CG14_MCR_PIXMODE_MASK
mdefine_line|#define CG14_MCR_PIXMODE_MASK&t;&t;0x30
DECL|macro|CG14_MCR_TMR_SHIFT
mdefine_line|#define CG14_MCR_TMR_SHIFT&t;&t;2
DECL|macro|CG14_MCR_TMR_MASK
mdefine_line|#define CG14_MCR_TMR_MASK&t;&t;0x0c
DECL|macro|CG14_MCR_TMENABLE_SHIFT
mdefine_line|#define CG14_MCR_TMENABLE_SHIFT&t;&t;1
DECL|macro|CG14_MCR_TMENABLE_MASK
mdefine_line|#define CG14_MCR_TMENABLE_MASK&t;&t;0x02
DECL|macro|CG14_MCR_RESET_SHIFT
mdefine_line|#define CG14_MCR_RESET_SHIFT&t;&t;0
DECL|macro|CG14_MCR_RESET_MASK
mdefine_line|#define CG14_MCR_RESET_MASK&t;&t;0x01
DECL|macro|CG14_REV_REVISION_SHIFT
mdefine_line|#define CG14_REV_REVISION_SHIFT&t;&t;4
DECL|macro|CG14_REV_REVISION_MASK
mdefine_line|#define CG14_REV_REVISION_MASK&t;&t;0xf0
DECL|macro|CG14_REV_IMPL_SHIFT
mdefine_line|#define CG14_REV_IMPL_SHIFT&t;&t;0
DECL|macro|CG14_REV_IMPL_MASK
mdefine_line|#define CG14_REV_IMPL_MASK&t;&t;0x0f
DECL|macro|CG14_VBR_FRAMEBASE_SHIFT
mdefine_line|#define CG14_VBR_FRAMEBASE_SHIFT&t;12
DECL|macro|CG14_VBR_FRAMEBASE_MASK
mdefine_line|#define CG14_VBR_FRAMEBASE_MASK&t;&t;0x00fff000
DECL|macro|CG14_VMCR1_SETUP_SHIFT
mdefine_line|#define CG14_VMCR1_SETUP_SHIFT&t;&t;0
DECL|macro|CG14_VMCR1_SETUP_MASK
mdefine_line|#define CG14_VMCR1_SETUP_MASK&t;&t;0x000001ff
DECL|macro|CG14_VMCR1_VCONFIG_SHIFT
mdefine_line|#define CG14_VMCR1_VCONFIG_SHIFT&t;9
DECL|macro|CG14_VMCR1_VCONFIG_MASK
mdefine_line|#define CG14_VMCR1_VCONFIG_MASK&t;&t;0x00000e00
DECL|macro|CG14_VMCR2_REFRESH_SHIFT
mdefine_line|#define CG14_VMCR2_REFRESH_SHIFT&t;0
DECL|macro|CG14_VMCR2_REFRESH_MASK
mdefine_line|#define CG14_VMCR2_REFRESH_MASK&t;&t;0x00000001
DECL|macro|CG14_VMCR2_TESTROWCNT_SHIFT
mdefine_line|#define CG14_VMCR2_TESTROWCNT_SHIFT&t;1
DECL|macro|CG14_VMCR2_TESTROWCNT_MASK
mdefine_line|#define CG14_VMCR2_TESTROWCNT_MASK&t;0x00000002
DECL|macro|CG14_VMCR2_FBCONFIG_SHIFT
mdefine_line|#define CG14_VMCR2_FBCONFIG_SHIFT&t;2
DECL|macro|CG14_VMCR2_FBCONFIG_MASK
mdefine_line|#define CG14_VMCR2_FBCONFIG_MASK&t;0x0000000c
DECL|macro|CG14_VCR_REFRESHREQ_SHIFT
mdefine_line|#define CG14_VCR_REFRESHREQ_SHIFT&t;0
DECL|macro|CG14_VCR_REFRESHREQ_MASK
mdefine_line|#define CG14_VCR_REFRESHREQ_MASK&t;0x000003ff
DECL|macro|CG14_VCR1_REFRESHENA_SHIFT
mdefine_line|#define CG14_VCR1_REFRESHENA_SHIFT&t;10
DECL|macro|CG14_VCR1_REFRESHENA_MASK
mdefine_line|#define CG14_VCR1_REFRESHENA_MASK&t;0x00000400
DECL|macro|CG14_VCA_CAD_SHIFT
mdefine_line|#define CG14_VCA_CAD_SHIFT&t;&t;0
DECL|macro|CG14_VCA_CAD_MASK
mdefine_line|#define CG14_VCA_CAD_MASK&t;&t;0x000003ff
DECL|macro|CG14_VCA_VERS_SHIFT
mdefine_line|#define CG14_VCA_VERS_SHIFT&t;&t;10
DECL|macro|CG14_VCA_VERS_MASK
mdefine_line|#define CG14_VCA_VERS_MASK&t;&t;0x00000c00
DECL|macro|CG14_VCA_RAMSPEED_SHIFT
mdefine_line|#define CG14_VCA_RAMSPEED_SHIFT&t;&t;12
DECL|macro|CG14_VCA_RAMSPEED_MASK
mdefine_line|#define CG14_VCA_RAMSPEED_MASK&t;&t;0x00001000
DECL|macro|CG14_VCA_8MB_SHIFT
mdefine_line|#define CG14_VCA_8MB_SHIFT&t;&t;13
DECL|macro|CG14_VCA_8MB_MASK
mdefine_line|#define CG14_VCA_8MB_MASK&t;&t;0x00002000
DECL|macro|CG14_MCR_PIXMODE_8
mdefine_line|#define CG14_MCR_PIXMODE_8&t;&t;0
DECL|macro|CG14_MCR_PIXMODE_16
mdefine_line|#define CG14_MCR_PIXMODE_16&t;&t;2
DECL|macro|CG14_MCR_PIXMODE_32
mdefine_line|#define CG14_MCR_PIXMODE_32&t;&t;3
DECL|struct|cg14_regs
r_struct
id|cg14_regs
(brace
DECL|member|mcr
r_volatile
id|u8
id|mcr
suffix:semicolon
multiline_comment|/* Master Control Reg */
DECL|member|ppr
r_volatile
id|u8
id|ppr
suffix:semicolon
multiline_comment|/* Packed Pixel Reg */
DECL|member|tms
r_volatile
id|u8
id|tms
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Test Mode Status Regs */
DECL|member|msr
r_volatile
id|u8
id|msr
suffix:semicolon
multiline_comment|/* Master Status Reg */
DECL|member|fsr
r_volatile
id|u8
id|fsr
suffix:semicolon
multiline_comment|/* Fault Status Reg */
DECL|member|rev
r_volatile
id|u8
id|rev
suffix:semicolon
multiline_comment|/* Revision &amp; Impl */
DECL|member|ccr
r_volatile
id|u8
id|ccr
suffix:semicolon
multiline_comment|/* Clock Control Reg */
DECL|member|tmr
r_volatile
id|u32
id|tmr
suffix:semicolon
multiline_comment|/* Test Mode Read Back */
DECL|member|mod
r_volatile
id|u8
id|mod
suffix:semicolon
multiline_comment|/* Monitor Operation Data Reg */
DECL|member|acr
r_volatile
id|u8
id|acr
suffix:semicolon
multiline_comment|/* Aux Control */
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|hct
r_volatile
id|u16
id|hct
suffix:semicolon
multiline_comment|/* Hor Counter */
DECL|member|vct
r_volatile
id|u16
id|vct
suffix:semicolon
multiline_comment|/* Vert Counter */
DECL|member|hbs
r_volatile
id|u16
id|hbs
suffix:semicolon
multiline_comment|/* Hor Blank Start */
DECL|member|hbc
r_volatile
id|u16
id|hbc
suffix:semicolon
multiline_comment|/* Hor Blank Clear */
DECL|member|hss
r_volatile
id|u16
id|hss
suffix:semicolon
multiline_comment|/* Hor Sync Start */
DECL|member|hsc
r_volatile
id|u16
id|hsc
suffix:semicolon
multiline_comment|/* Hor Sync Clear */
DECL|member|csc
r_volatile
id|u16
id|csc
suffix:semicolon
multiline_comment|/* Composite Sync Clear */
DECL|member|vbs
r_volatile
id|u16
id|vbs
suffix:semicolon
multiline_comment|/* Vert Blank Start */
DECL|member|vbc
r_volatile
id|u16
id|vbc
suffix:semicolon
multiline_comment|/* Vert Blank Clear */
DECL|member|vss
r_volatile
id|u16
id|vss
suffix:semicolon
multiline_comment|/* Vert Sync Start */
DECL|member|vsc
r_volatile
id|u16
id|vsc
suffix:semicolon
multiline_comment|/* Vert Sync Clear */
DECL|member|xcs
r_volatile
id|u16
id|xcs
suffix:semicolon
DECL|member|xcc
r_volatile
id|u16
id|xcc
suffix:semicolon
DECL|member|fsa
r_volatile
id|u16
id|fsa
suffix:semicolon
multiline_comment|/* Fault Status Address */
DECL|member|adr
r_volatile
id|u16
id|adr
suffix:semicolon
multiline_comment|/* Address Registers */
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|0xce
)braket
suffix:semicolon
DECL|member|pcg
r_volatile
id|u8
id|pcg
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* Pixel Clock Generator */
DECL|member|vbr
r_volatile
id|u32
id|vbr
suffix:semicolon
multiline_comment|/* Frame Base Row */
DECL|member|vmcr
r_volatile
id|u32
id|vmcr
suffix:semicolon
multiline_comment|/* VBC Master Control */
DECL|member|vcr
r_volatile
id|u32
id|vcr
suffix:semicolon
multiline_comment|/* VBC refresh */
DECL|member|vca
r_volatile
id|u32
id|vca
suffix:semicolon
multiline_comment|/* VBC Config */
)brace
suffix:semicolon
DECL|macro|CG14_CCR_ENABLE
mdefine_line|#define CG14_CCR_ENABLE&t;0x04
DECL|macro|CG14_CCR_SELECT
mdefine_line|#define CG14_CCR_SELECT 0x02&t;/* HW/Full screen */
DECL|struct|cg14_cursor
r_struct
id|cg14_cursor
(brace
DECL|member|cpl0
r_volatile
id|u32
id|cpl0
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Enable plane 0 */
DECL|member|cpl1
r_volatile
id|u32
id|cpl1
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Color selection plane */
DECL|member|ccr
r_volatile
id|u8
id|ccr
suffix:semicolon
multiline_comment|/* Cursor Control Reg */
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cursx
r_volatile
id|u16
id|cursx
suffix:semicolon
multiline_comment|/* Cursor x,y position */
DECL|member|cursy
r_volatile
id|u16
id|cursy
suffix:semicolon
multiline_comment|/* Cursor x,y position */
DECL|member|color0
r_volatile
id|u32
id|color0
suffix:semicolon
DECL|member|color1
r_volatile
id|u32
id|color1
suffix:semicolon
DECL|member|xxx1
id|u32
id|xxx1
(braket
l_int|0x1bc
)braket
suffix:semicolon
DECL|member|cpl0i
r_volatile
id|u32
id|cpl0i
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Enable plane 0 autoinc */
DECL|member|cpl1i
r_volatile
id|u32
id|cpl1i
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Color selection autoinc */
)brace
suffix:semicolon
DECL|struct|cg14_dac
r_struct
id|cg14_dac
(brace
DECL|member|addr
r_volatile
id|u8
id|addr
suffix:semicolon
multiline_comment|/* Address Register */
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|glut
r_volatile
id|u8
id|glut
suffix:semicolon
multiline_comment|/* Gamma table */
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|select
r_volatile
id|u8
id|select
suffix:semicolon
multiline_comment|/* Register Select */
DECL|member|xxx2
id|u8
id|xxx2
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|mode
r_volatile
id|u8
id|mode
suffix:semicolon
multiline_comment|/* Mode Register */
)brace
suffix:semicolon
DECL|struct|cg14_xlut
r_struct
id|cg14_xlut
(brace
DECL|member|x_xlut
r_volatile
id|u8
id|x_xlut
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|x_xlutd
r_volatile
id|u8
id|x_xlutd
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|0x600
)braket
suffix:semicolon
DECL|member|x_xlut_inc
r_volatile
id|u8
id|x_xlut_inc
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|x_xlutd_inc
r_volatile
id|u8
id|x_xlutd_inc
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Color look up table (clut) */
multiline_comment|/* Each one of these arrays hold the color lookup table (for 256&n; * colors) for each MDI page (I assume then there should be 4 MDI&n; * pages, I still wonder what they are.  I have seen NeXTStep split&n; * the screen in four parts, while operating in 24 bits mode.  Each&n; * integer holds 4 values: alpha value (transparency channel, thanks&n; * go to John Stone (johns@umr.edu) from OpenBSD), red, green and blue&n; *&n; * I currently use the clut instead of the Xlut&n; */
DECL|struct|cg14_clut
r_struct
id|cg14_clut
(brace
DECL|member|c_clut
r_int
r_int
id|c_clut
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|c_clutd
r_int
r_int
id|c_clutd
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* i wonder what the &squot;d&squot; is for */
DECL|member|c_clut_inc
r_int
r_int
id|c_clut_inc
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|c_clutd_inc
r_int
r_int
id|c_clutd_inc
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sbus_mmap_map
id|cg14_mmap_map
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|CG14_REGS
comma
l_int|0x80000000
comma
l_int|0x1000
)brace
comma
(brace
id|CG14_XLUT
comma
l_int|0x80003000
comma
l_int|0x1000
)brace
comma
(brace
id|CG14_CLUT1
comma
l_int|0x80004000
comma
l_int|0x1000
)brace
comma
(brace
id|CG14_CLUT2
comma
l_int|0x80005000
comma
l_int|0x1000
)brace
comma
(brace
id|CG14_CLUT3
comma
l_int|0x80006000
comma
l_int|0x1000
)brace
comma
(brace
id|CG3_MMAP_OFFSET
op_minus
l_int|0x7000
comma
l_int|0x80000000
comma
l_int|0x7000
)brace
comma
(brace
id|CG3_MMAP_OFFSET
comma
l_int|0x00000000
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
(brace
id|MDI_CURSOR_MAP
comma
l_int|0x80001000
comma
l_int|0x1000
)brace
comma
(brace
id|MDI_CHUNKY_BGR_MAP
comma
l_int|0x01000000
comma
l_int|0x400000
)brace
comma
(brace
id|MDI_PLANAR_X16_MAP
comma
l_int|0x02000000
comma
l_int|0x200000
)brace
comma
(brace
id|MDI_PLANAR_C16_MAP
comma
l_int|0x02800000
comma
l_int|0x200000
)brace
comma
(brace
id|MDI_PLANAR_X32_MAP
comma
l_int|0x03000000
comma
l_int|0x100000
)brace
comma
(brace
id|MDI_PLANAR_B32_MAP
comma
l_int|0x03400000
comma
l_int|0x100000
)brace
comma
(brace
id|MDI_PLANAR_G32_MAP
comma
l_int|0x03800000
comma
l_int|0x100000
)brace
comma
(brace
id|MDI_PLANAR_R32_MAP
comma
l_int|0x03c00000
comma
l_int|0x100000
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
DECL|function|cg14_loadcmap
r_static
r_void
id|cg14_loadcmap
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
id|cg14_clut
op_star
id|clut
op_assign
id|fb-&gt;s.cg14.clut
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|index
op_increment
)paren
id|clut-&gt;c_clut
(braket
id|index
)braket
op_assign
(paren
id|fb-&gt;color_map
id|CM
c_func
(paren
id|index
comma
l_int|2
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|fb-&gt;color_map
id|CM
c_func
(paren
id|index
comma
l_int|1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|fb-&gt;color_map
id|CM
c_func
(paren
id|index
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|cg14_margins
r_static
r_void
id|cg14_margins
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
DECL|function|cg14_setcursormap
r_static
r_void
id|cg14_setcursormap
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
id|cg14_cursor
op_star
id|cur
op_assign
id|fb-&gt;s.cg14.cursor
suffix:semicolon
id|cur-&gt;color0
op_assign
(paren
(paren
id|red
(braket
l_int|0
)braket
)paren
op_or
(paren
id|green
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|blue
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|cur-&gt;color1
op_assign
(paren
(paren
id|red
(braket
l_int|1
)braket
)paren
op_or
(paren
id|green
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|blue
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set cursor shape */
DECL|function|cg14_setcurshape
r_static
r_void
id|cg14_setcurshape
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_struct
id|cg14_cursor
op_star
id|cur
op_assign
id|fb-&gt;s.cg14.cursor
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
id|cur-&gt;cpl0
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
id|cur-&gt;cpl1
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
DECL|function|cg14_setcursor
r_static
r_void
id|cg14_setcursor
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_struct
id|cg_cursor
op_star
id|c
op_assign
op_amp
id|fb-&gt;cursor
suffix:semicolon
r_struct
id|cg14_cursor
op_star
id|cur
op_assign
id|fb-&gt;s.cg14.cursor
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;enable
)paren
id|cur-&gt;ccr
op_or_assign
id|CG14_CCR_ENABLE
suffix:semicolon
id|cur-&gt;cursx
op_assign
(paren
(paren
id|c-&gt;cpos.fbx
op_minus
id|c-&gt;chot.fbx
)paren
op_amp
l_int|0xfff
)paren
suffix:semicolon
id|cur-&gt;cursy
op_assign
(paren
(paren
id|c-&gt;cpos.fby
op_minus
id|c-&gt;chot.fby
)paren
op_amp
l_int|0xfff
)paren
suffix:semicolon
)brace
DECL|function|cg14_switch_from_graph
r_static
r_void
id|cg14_switch_from_graph
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
multiline_comment|/* Set the 8-bpp mode */
r_if
c_cond
(paren
id|fb-&gt;open
op_logical_and
id|fb-&gt;mmaped
)paren
(brace
r_volatile
r_char
op_star
id|mcr
op_assign
op_amp
id|fb-&gt;s.cg14.regs-&gt;mcr
suffix:semicolon
id|fb-&gt;s.cg14.mode
op_assign
l_int|8
suffix:semicolon
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
(paren
id|CG14_MCR_PIXMODE_MASK
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|cg14_reset
r_static
r_void
id|cg14_reset
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_volatile
r_char
op_star
id|mcr
op_assign
op_amp
id|fb-&gt;s.cg14.regs-&gt;mcr
suffix:semicolon
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
(paren
id|CG14_MCR_PIXMODE_MASK
)paren
)paren
suffix:semicolon
)brace
DECL|function|cg14_ioctl
r_static
r_int
id|cg14_ioctl
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_volatile
r_char
op_star
id|mcr
op_assign
op_amp
id|fb-&gt;s.cg14.regs-&gt;mcr
suffix:semicolon
r_struct
id|mdi_cfginfo
op_star
id|mdii
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MDI_RESET
suffix:colon
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
id|CG14_MCR_PIXMODE_MASK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_GET_CFGINFO
suffix:colon
id|mdii
op_assign
(paren
r_struct
id|mdi_cfginfo
op_star
)paren
id|arg
suffix:semicolon
id|put_user_ret
c_func
(paren
id|FBTYPE_MDICOLOR
comma
op_amp
id|mdii-&gt;mdi_type
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
id|__put_user_ret
c_func
(paren
id|fb-&gt;type.fb_height
comma
op_amp
id|mdii-&gt;mdi_height
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
id|__put_user_ret
c_func
(paren
id|fb-&gt;type.fb_width
comma
op_amp
id|mdii-&gt;mdi_width
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
id|__put_user_ret
c_func
(paren
id|fb-&gt;s.cg14.mode
comma
op_amp
id|mdii-&gt;mdi_mode
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
id|__put_user_ret
c_func
(paren
l_int|72
comma
op_amp
id|mdii-&gt;mdi_pixfreq
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* FIXME */
id|__put_user_ret
c_func
(paren
id|fb-&gt;s.cg14.ramsize
comma
op_amp
id|mdii-&gt;mdi_size
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_SET_PIXELMODE
suffix:colon
id|get_user_ret
c_func
(paren
id|mode
comma
(paren
r_int
op_star
)paren
id|arg
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|MDI_32_PIX
suffix:colon
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
id|CG14_MCR_PIXMODE_MASK
)paren
op_or
(paren
id|CG14_MCR_PIXMODE_32
op_lshift
id|CG14_MCR_PIXMODE_SHIFT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_16_PIX
suffix:colon
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
id|CG14_MCR_PIXMODE_MASK
)paren
op_or
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_8_PIX
suffix:colon
op_star
id|mcr
op_assign
(paren
op_star
id|mcr
op_amp
op_complement
id|CG14_MCR_PIXMODE_MASK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
id|fb-&gt;s.cg14.mode
op_assign
id|mode
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_int
r_int
id|get_phys
c_func
(paren
r_int
r_int
id|addr
)paren
)paren
(brace
r_return
id|__get_phys
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_int
id|get_iospace
c_func
(paren
r_int
r_int
id|addr
)paren
)paren
(brace
r_return
id|__get_iospace
c_func
(paren
id|addr
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
id|cgfourteenfb_init
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
id|rphys
comma
id|phys
suffix:semicolon
id|u32
id|bases
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|is_8mb
comma
id|i
suffix:semicolon
macro_line|#ifndef FBCON_HAS_CFB8
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
id|prom_getproperty
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;address&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|bases
(braket
l_int|0
)braket
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bases
(braket
l_int|0
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cg14 not mmaped&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_iospace
c_func
(paren
id|bases
(braket
l_int|0
)braket
)paren
op_ne
id|get_iospace
c_func
(paren
id|bases
(braket
l_int|1
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ugh. cg14 iospaces don&squot;t match&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|fb-&gt;physbase
op_assign
id|phys
op_assign
id|get_phys
c_func
(paren
id|bases
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|rphys
op_assign
id|get_phys
c_func
(paren
id|bases
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|fb-&gt;iospace
op_assign
id|get_iospace
c_func
(paren
id|bases
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|fb-&gt;s.cg14.regs
op_assign
(paren
r_struct
id|cg14_regs
op_star
)paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|0
)braket
suffix:semicolon
id|fb-&gt;s.cg14.clut
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|0
)braket
op_plus
id|CG14_CLUT1
)paren
suffix:semicolon
id|fb-&gt;s.cg14.cursor
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|0
)braket
op_plus
id|CG14_CURSORREGS
)paren
suffix:semicolon
id|disp-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|bases
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* CG14_VCA_8MB_MASK is not correctly set on the 501-2482&n;&t; * VSIMM, so we read the memory size from the PROM&n;&t; */
id|prom_getproperty
c_func
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|bases
(braket
l_int|0
)braket
comma
l_int|24
)paren
suffix:semicolon
id|is_8mb
op_assign
id|bases
(braket
l_int|5
)braket
op_eq
l_int|0x800000
suffix:semicolon
id|fb-&gt;mmap_map
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|cg14_mmap_map
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;mmap_map
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fb-&gt;mmap_map
(braket
id|i
)braket
dot
id|voff
op_assign
id|cg14_mmap_map
(braket
id|i
)braket
dot
id|voff
suffix:semicolon
id|fb-&gt;mmap_map
(braket
id|i
)braket
dot
id|poff
op_assign
(paren
id|cg14_mmap_map
(braket
id|i
)braket
dot
id|poff
op_amp
l_int|0x80000000
)paren
ques
c_cond
(paren
id|cg14_mmap_map
(braket
id|i
)braket
dot
id|poff
op_amp
l_int|0x7fffffff
)paren
op_plus
id|rphys
op_minus
id|phys
suffix:colon
id|cg14_mmap_map
(braket
id|i
)braket
dot
id|poff
suffix:semicolon
id|fb-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
op_assign
id|cg14_mmap_map
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|is_8mb
op_logical_and
id|fb-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
op_ge
l_int|0x100000
op_logical_and
id|fb-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
op_le
l_int|0x400000
)paren
id|fb-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cg14_mmap_map
(braket
id|i
)braket
dot
id|size
)paren
r_break
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|fb-&gt;info.modename
comma
l_string|&quot;CGfourteen&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;CGfourteen&quot;
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
id|type-&gt;fb_depth
op_assign
l_int|24
suffix:semicolon
id|fb-&gt;emulations
(braket
l_int|1
)braket
op_assign
id|FBTYPE_SUN3COLOR
suffix:semicolon
id|fb-&gt;margins
op_assign
id|cg14_margins
suffix:semicolon
id|fb-&gt;loadcmap
op_assign
id|cg14_loadcmap
suffix:semicolon
id|fb-&gt;setcursor
op_assign
id|cg14_setcursor
suffix:semicolon
id|fb-&gt;setcursormap
op_assign
id|cg14_setcursormap
suffix:semicolon
id|fb-&gt;setcurshape
op_assign
id|cg14_setcurshape
suffix:semicolon
id|fb-&gt;reset
op_assign
id|cg14_reset
suffix:semicolon
id|fb-&gt;switch_from_graph
op_assign
id|cg14_switch_from_graph
suffix:semicolon
id|fb-&gt;ioctl
op_assign
id|cg14_ioctl
suffix:semicolon
id|fb-&gt;s.cg14.mode
op_assign
l_int|8
suffix:semicolon
id|fb-&gt;s.cg14.ramsize
op_assign
(paren
id|is_8mb
)paren
ques
c_cond
l_int|0x800000
suffix:colon
l_int|0x400000
suffix:semicolon
id|cg14_reset
c_func
(paren
id|fb
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;cgfourteen at %x.%08lx, %dMB, rev=%d, impl=%d&quot;
comma
id|fb-&gt;iospace
comma
id|phys
comma
id|is_8mb
ques
c_cond
l_int|8
suffix:colon
l_int|4
comma
id|fb-&gt;s.cg14.regs-&gt;rev
op_rshift
l_int|4
comma
id|fb-&gt;s.cg14.regs-&gt;rev
op_amp
l_int|0xf
)paren
suffix:semicolon
r_return
id|idstring
suffix:semicolon
)brace
eof
