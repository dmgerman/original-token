multiline_comment|/* $Id: newport_con.c,v 1.3 1998/09/01 21:43:18 tsbogend Exp $&n; *&n; * newport_con.c: Abscon for newport hardware&n; * &n; * (C) 1998 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; * &n; * This driver is based on sgicons.c and cons_newport.&n; * &n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/newport.h&gt;
DECL|variable|npregs
r_struct
id|newport_regs
op_star
id|npregs
suffix:semicolon
DECL|variable|newport_num_lines
r_int
id|newport_num_lines
suffix:semicolon
DECL|variable|newport_num_columns
r_int
id|newport_num_columns
suffix:semicolon
DECL|variable|topscan
r_int
id|topscan
suffix:semicolon
r_extern
r_int
r_char
id|vga_font
(braket
)braket
suffix:semicolon
DECL|macro|BMASK
mdefine_line|#define BMASK(c) (c &lt;&lt; 24)
DECL|macro|RENDER
mdefine_line|#define RENDER(regs, cp) do { &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0x0]); (regs)-&gt;go.zpattern = BMASK((cp)[0x1]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0x2]); (regs)-&gt;go.zpattern = BMASK((cp)[0x3]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0x4]); (regs)-&gt;go.zpattern = BMASK((cp)[0x5]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0x6]); (regs)-&gt;go.zpattern = BMASK((cp)[0x7]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0x8]); (regs)-&gt;go.zpattern = BMASK((cp)[0x9]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0xa]); (regs)-&gt;go.zpattern = BMASK((cp)[0xb]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0xc]); (regs)-&gt;go.zpattern = BMASK((cp)[0xd]); &bslash;&n;(regs)-&gt;go.zpattern = BMASK((cp)[0xe]); (regs)-&gt;go.zpattern = BMASK((cp)[0xf]); &bslash;&n;} while(0)
DECL|macro|TESTVAL
mdefine_line|#define TESTVAL 0xdeadbeef
DECL|macro|XSTI_TO_FXSTART
mdefine_line|#define XSTI_TO_FXSTART(val) (((val) &amp; 0xffff) &lt;&lt; 11)
DECL|function|newport_render_background
r_static
r_inline
r_void
id|newport_render_background
c_func
(paren
r_int
id|xpos
comma
r_int
id|ypos
comma
r_int
id|ci
)paren
(brace
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
id|npregs-&gt;set.wrmask
op_assign
l_int|0xffffffff
suffix:semicolon
id|npregs-&gt;set.drawmode0
op_assign
(paren
id|NPORT_DMODE0_DRAW
op_or
id|NPORT_DMODE0_BLOCK
op_or
id|NPORT_DMODE0_DOSETUP
op_or
id|NPORT_DMODE0_STOPX
op_or
id|NPORT_DMODE0_STOPY
)paren
suffix:semicolon
id|npregs-&gt;set.colori
op_assign
id|ci
suffix:semicolon
id|npregs-&gt;set.xystarti
op_assign
(paren
id|xpos
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|ypos
op_plus
id|topscan
)paren
op_amp
l_int|0x3ff
)paren
suffix:semicolon
id|npregs-&gt;go.xyendi
op_assign
(paren
(paren
id|xpos
op_plus
l_int|7
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|ypos
op_plus
id|topscan
op_plus
l_int|15
)paren
op_amp
l_int|0x3ff
)paren
suffix:semicolon
)brace
DECL|function|newport_init_cmap
r_static
r_inline
r_void
id|newport_init_cmap
c_func
(paren
r_void
)paren
(brace
r_int
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|newport_bfwait
c_func
(paren
)paren
suffix:semicolon
id|newport_cmap_setaddr
c_func
(paren
id|npregs
comma
id|color_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|newport_cmap_setrgb
c_func
(paren
id|npregs
comma
id|default_red
(braket
id|i
)braket
comma
id|default_grn
(braket
id|i
)braket
comma
id|default_blu
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|newport_clear_screen
r_static
r_inline
r_void
id|newport_clear_screen
c_func
(paren
r_int
id|xstart
comma
r_int
id|ystart
comma
r_int
id|xend
comma
r_int
id|yend
)paren
(brace
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
id|npregs-&gt;set.wrmask
op_assign
l_int|0xffffffff
suffix:semicolon
id|npregs-&gt;set.drawmode0
op_assign
(paren
id|NPORT_DMODE0_DRAW
op_or
id|NPORT_DMODE0_BLOCK
op_or
id|NPORT_DMODE0_DOSETUP
op_or
id|NPORT_DMODE0_STOPX
op_or
id|NPORT_DMODE0_STOPY
)paren
suffix:semicolon
id|npregs-&gt;set.colori
op_assign
l_int|0
suffix:semicolon
id|npregs-&gt;set.xystarti
op_assign
(paren
id|xstart
op_lshift
l_int|16
)paren
op_or
id|ystart
suffix:semicolon
id|npregs-&gt;go.xyendi
op_assign
(paren
id|xend
op_lshift
l_int|16
)paren
op_or
id|yend
suffix:semicolon
)brace
DECL|function|newport_clear_lines
r_static
r_inline
r_void
id|newport_clear_lines
c_func
(paren
r_int
id|ystart
comma
r_int
id|yend
)paren
(brace
id|ystart
op_assign
(paren
(paren
id|ystart
op_lshift
l_int|4
)paren
op_plus
id|topscan
)paren
op_amp
l_int|0x3ff
suffix:semicolon
id|yend
op_assign
(paren
(paren
id|yend
op_lshift
l_int|4
)paren
op_plus
id|topscan
op_plus
l_int|15
)paren
op_amp
l_int|0x3ff
suffix:semicolon
id|newport_clear_screen
(paren
l_int|0
comma
id|ystart
comma
l_int|1279
comma
id|yend
)paren
suffix:semicolon
)brace
DECL|function|newport_reset
r_void
id|newport_reset
(paren
r_void
)paren
(brace
r_int
r_int
id|treg
suffix:semicolon
r_int
id|i
suffix:semicolon
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
id|treg
op_assign
id|newport_vc2_get
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
comma
(paren
id|treg
op_or
id|VC2_CTRL_EVIDEO
)paren
)paren
suffix:semicolon
id|treg
op_assign
id|newport_vc2_get
c_func
(paren
id|npregs
comma
id|VC2_IREG_CENTRY
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_RADDR
comma
id|treg
)paren
suffix:semicolon
id|npregs-&gt;set.dcbmode
op_assign
(paren
id|NPORT_DMODE_AVC2
op_or
id|VC2_REGADDR_RAM
op_or
id|NPORT_DMODE_W2
op_or
id|VC2_PROTOCOL
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
(brace
id|newport_bfwait
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|92
op_logical_or
id|i
op_eq
l_int|94
)paren
id|npregs-&gt;set.dcbdata0.hwords.s1
op_assign
l_int|0xff00
suffix:semicolon
r_else
id|npregs-&gt;set.dcbdata0.hwords.s1
op_assign
l_int|0x0000
suffix:semicolon
)brace
id|newport_init_cmap
c_func
(paren
)paren
suffix:semicolon
id|npregs-&gt;cset.topscan
op_assign
id|topscan
op_assign
l_int|0
suffix:semicolon
id|npregs-&gt;cset.xywin
op_assign
(paren
l_int|4096
op_lshift
l_int|16
)paren
op_or
l_int|4096
suffix:semicolon
multiline_comment|/* Clear the screen. */
id|newport_clear_screen
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|1280
op_plus
l_int|63
comma
l_int|1024
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_const
r_char
op_star
id|newport_startup
c_func
(paren
r_void
)paren
)paren
(brace
r_struct
id|newport_regs
op_star
id|p
suffix:semicolon
id|npregs
op_assign
(paren
r_struct
id|newport_regs
op_star
)paren
(paren
id|KSEG1
op_plus
l_int|0x1f0f0000
)paren
suffix:semicolon
id|p
op_assign
id|npregs
suffix:semicolon
id|p-&gt;cset.config
op_assign
id|NPORT_CFG_GD0
suffix:semicolon
r_if
c_cond
(paren
id|newport_wait
c_func
(paren
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|p-&gt;set.xstarti
op_assign
id|TESTVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;set._xstart.i
op_ne
id|XSTI_TO_FXSTART
c_func
(paren
id|TESTVAL
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|newport_reset
(paren
)paren
suffix:semicolon
singleline_comment|// gfx_init (display_desc);
id|newport_num_lines
op_assign
id|ORIG_VIDEO_LINES
suffix:semicolon
id|newport_num_columns
op_assign
id|ORIG_VIDEO_COLS
suffix:semicolon
r_return
l_string|&quot;SGI Newport&quot;
suffix:semicolon
)brace
DECL|function|newport_init
r_static
r_void
id|newport_init
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|init
)paren
(brace
id|vc-&gt;vc_cols
op_assign
id|newport_num_columns
suffix:semicolon
id|vc-&gt;vc_rows
op_assign
id|newport_num_lines
suffix:semicolon
id|vc-&gt;vc_can_do_color
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|newport_clear
r_static
r_void
id|newport_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_int
id|xend
op_assign
(paren
(paren
id|sx
op_plus
id|width
)paren
op_lshift
l_int|3
)paren
op_minus
l_int|1
suffix:semicolon
r_int
id|ystart
op_assign
(paren
(paren
id|sy
op_lshift
l_int|4
)paren
op_plus
id|topscan
)paren
op_amp
l_int|0x3ff
suffix:semicolon
r_int
id|yend
op_assign
(paren
(paren
(paren
id|sy
op_plus
id|height
)paren
op_lshift
l_int|4
)paren
op_plus
id|topscan
op_minus
l_int|1
)paren
op_amp
l_int|0x3ff
suffix:semicolon
r_if
c_cond
(paren
id|ystart
OL
id|yend
)paren
(brace
id|newport_clear_screen
c_func
(paren
id|sx
op_lshift
l_int|3
comma
id|ystart
comma
id|xend
comma
id|yend
)paren
suffix:semicolon
)brace
r_else
(brace
id|newport_clear_screen
c_func
(paren
id|sx
op_lshift
l_int|3
comma
id|ystart
comma
id|xend
comma
l_int|1023
)paren
suffix:semicolon
id|newport_clear_screen
c_func
(paren
id|sx
op_lshift
l_int|3
comma
l_int|0
comma
id|xend
comma
id|yend
)paren
suffix:semicolon
)brace
)brace
DECL|function|newport_putc
r_static
r_void
id|newport_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|charattr
comma
r_int
id|ypos
comma
r_int
id|xpos
)paren
(brace
r_int
r_char
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|vga_font
(braket
(paren
id|charattr
op_amp
l_int|0xff
)paren
op_lshift
l_int|4
)braket
suffix:semicolon
id|charattr
op_assign
(paren
id|charattr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|xpos
op_lshift_assign
l_int|3
suffix:semicolon
id|ypos
op_lshift_assign
l_int|4
suffix:semicolon
id|newport_render_background
c_func
(paren
id|xpos
comma
id|ypos
comma
(paren
id|charattr
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Set the color and drawing mode. */
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
id|npregs-&gt;set.colori
op_assign
id|charattr
op_amp
l_int|0xf
suffix:semicolon
id|npregs-&gt;set.drawmode0
op_assign
(paren
id|NPORT_DMODE0_DRAW
op_or
id|NPORT_DMODE0_BLOCK
op_or
id|NPORT_DMODE0_STOPX
op_or
id|NPORT_DMODE0_ZPENAB
op_or
id|NPORT_DMODE0_L32
)paren
suffix:semicolon
multiline_comment|/* Set coordinates for bitmap operation. */
id|npregs-&gt;set.xystarti
op_assign
(paren
id|xpos
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|ypos
op_plus
id|topscan
)paren
op_amp
l_int|0x3ff
)paren
suffix:semicolon
id|npregs-&gt;set.xyendi
op_assign
(paren
(paren
id|xpos
op_plus
l_int|7
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Go, baby, go... */
id|RENDER
c_func
(paren
id|npregs
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|newport_putcs
r_static
r_void
id|newport_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|ypos
comma
r_int
id|xpos
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|newport_putc
(paren
id|vc
comma
op_star
id|s
op_increment
comma
id|ypos
comma
id|xpos
op_increment
)paren
suffix:semicolon
)brace
DECL|function|newport_cursor
r_static
r_void
id|newport_cursor
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|treg
suffix:semicolon
r_int
id|xcurs
comma
id|ycurs
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
id|treg
op_assign
id|newport_vc2_get
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
comma
(paren
id|treg
op_amp
op_complement
(paren
id|VC2_CTRL_ECDISP
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CM_MOVE
suffix:colon
r_case
id|CM_DRAW
suffix:colon
id|treg
op_assign
id|newport_vc2_get
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
comma
(paren
id|treg
op_or
id|VC2_CTRL_ECDISP
)paren
)paren
suffix:semicolon
id|xcurs
op_assign
(paren
id|vc-&gt;vc_pos
op_minus
id|vc-&gt;vc_visible_origin
)paren
op_div
l_int|2
suffix:semicolon
id|ycurs
op_assign
(paren
(paren
id|xcurs
op_div
id|vc-&gt;vc_cols
)paren
op_lshift
l_int|4
)paren
op_plus
l_int|31
suffix:semicolon
id|xcurs
op_assign
(paren
(paren
id|xcurs
op_mod
id|vc-&gt;vc_cols
)paren
op_lshift
l_int|3
)paren
op_plus
l_int|21
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CURSX
comma
id|xcurs
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CURSY
comma
id|ycurs
)paren
suffix:semicolon
)brace
)brace
DECL|function|newport_switch
r_static
r_int
id|newport_switch
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
)paren
(brace
id|npregs-&gt;cset.topscan
op_assign
id|topscan
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|newport_blank
r_static
r_int
id|newport_blank
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|blank
)paren
(brace
r_int
r_int
id|treg
suffix:semicolon
r_if
c_cond
(paren
id|blank
op_eq
l_int|0
)paren
(brace
multiline_comment|/* unblank console */
id|treg
op_assign
id|newport_vc2_get
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
comma
(paren
id|treg
op_or
id|VC2_CTRL_EDISP
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* blank console */
id|treg
op_assign
id|newport_vc2_get
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
)paren
suffix:semicolon
id|newport_vc2_set
c_func
(paren
id|npregs
comma
id|VC2_IREG_CONTROL
comma
(paren
id|treg
op_amp
op_complement
(paren
id|VC2_CTRL_EDISP
)paren
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|newport_font_op
r_static
r_int
id|newport_font_op
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_struct
id|console_font_op
op_star
id|f
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|newport_set_palette
r_static
r_int
id|newport_set_palette
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
r_char
op_star
id|table
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|newport_scrolldelta
r_static
r_int
id|newport_scrolldelta
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|lines
)paren
(brace
multiline_comment|/* there is (nearly) no off-screen memory, so we can&squot;t scroll back */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|newport_scroll
r_static
r_int
id|newport_scroll
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|t
comma
r_int
id|b
comma
r_int
id|dir
comma
r_int
id|lines
)paren
(brace
r_int
id|count
comma
id|x
comma
id|y
suffix:semicolon
r_int
r_int
op_star
id|s
comma
op_star
id|d
suffix:semicolon
r_int
r_int
id|chattr
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
l_int|0
op_logical_and
id|b
op_eq
id|vc-&gt;vc_rows
)paren
(brace
r_if
c_cond
(paren
id|dir
op_eq
id|SM_UP
)paren
(brace
id|npregs-&gt;cset.topscan
op_assign
id|topscan
op_assign
(paren
id|topscan
op_plus
(paren
id|lines
op_lshift
l_int|4
)paren
)paren
op_amp
l_int|0x3ff
suffix:semicolon
id|newport_clear_lines
(paren
id|vc-&gt;vc_rows
op_minus
id|lines
comma
id|vc-&gt;vc_rows
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|npregs-&gt;cset.topscan
op_assign
id|topscan
op_assign
(paren
id|topscan
op_plus
(paren
op_minus
id|lines
op_lshift
l_int|4
)paren
)paren
op_amp
l_int|0x3ff
suffix:semicolon
id|newport_clear_lines
(paren
l_int|0
comma
id|lines
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|count
op_assign
(paren
id|b
op_minus
id|t
op_minus
id|lines
)paren
op_star
id|vc-&gt;vc_cols
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_eq
id|SM_UP
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
id|y
op_assign
id|t
suffix:semicolon
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|vc-&gt;vc_origin
op_plus
id|vc-&gt;vc_size_row
op_star
(paren
id|t
op_plus
id|lines
)paren
)paren
suffix:semicolon
id|d
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|vc-&gt;vc_origin
op_plus
id|vc-&gt;vc_size_row
op_star
id|t
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|chattr
op_assign
id|scr_readw
(paren
id|s
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chattr
op_ne
id|scr_readw
c_func
(paren
id|d
)paren
)paren
(brace
id|newport_putc
(paren
id|vc
comma
id|chattr
comma
id|y
comma
id|x
)paren
suffix:semicolon
id|scr_writew
(paren
id|chattr
comma
id|d
)paren
suffix:semicolon
)brace
id|d
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_eq
id|vc-&gt;vc_cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
id|y
op_increment
suffix:semicolon
)brace
)brace
id|d
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|vc-&gt;vc_origin
op_plus
id|vc-&gt;vc_size_row
op_star
(paren
id|b
op_minus
id|lines
)paren
)paren
suffix:semicolon
id|x
op_assign
l_int|0
suffix:semicolon
id|y
op_assign
id|b
op_minus
id|lines
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
(paren
id|lines
op_star
id|vc-&gt;vc_cols
)paren
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
id|scr_readw
c_func
(paren
id|d
)paren
op_ne
id|vc-&gt;vc_video_erase_char
)paren
(brace
id|newport_putc
(paren
id|vc
comma
id|chattr
comma
id|y
comma
id|x
)paren
suffix:semicolon
id|scr_writew
(paren
id|vc-&gt;vc_video_erase_char
comma
id|d
)paren
suffix:semicolon
)brace
id|d
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_eq
id|vc-&gt;vc_cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
id|y
op_increment
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|x
op_assign
id|vc-&gt;vc_cols
op_minus
l_int|1
suffix:semicolon
id|y
op_assign
id|b
op_minus
l_int|1
suffix:semicolon
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|vc-&gt;vc_origin
op_plus
id|vc-&gt;vc_size_row
op_star
(paren
id|b
op_minus
id|lines
)paren
op_minus
l_int|2
)paren
suffix:semicolon
id|d
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|vc-&gt;vc_origin
op_plus
id|vc-&gt;vc_size_row
op_star
id|b
op_minus
l_int|2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|chattr
op_assign
id|scr_readw
(paren
id|s
op_decrement
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chattr
op_ne
id|scr_readw
c_func
(paren
id|d
)paren
)paren
(brace
id|newport_putc
(paren
id|vc
comma
id|chattr
comma
id|y
comma
id|x
)paren
suffix:semicolon
id|scr_writew
(paren
id|chattr
comma
id|d
)paren
suffix:semicolon
)brace
id|d
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|x
op_decrement
op_eq
l_int|0
)paren
(brace
id|x
op_assign
id|vc-&gt;vc_cols
op_minus
l_int|1
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
id|d
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|vc-&gt;vc_origin
op_plus
id|vc-&gt;vc_size_row
op_star
id|t
)paren
suffix:semicolon
id|x
op_assign
l_int|0
suffix:semicolon
id|y
op_assign
id|t
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
(paren
id|lines
op_star
id|vc-&gt;vc_cols
)paren
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
id|scr_readw
c_func
(paren
id|d
)paren
op_ne
id|vc-&gt;vc_video_erase_char
)paren
(brace
id|newport_putc
(paren
id|vc
comma
id|vc-&gt;vc_video_erase_char
comma
id|y
comma
id|x
)paren
suffix:semicolon
id|scr_writew
(paren
id|vc-&gt;vc_video_erase_char
comma
id|d
)paren
suffix:semicolon
)brace
id|d
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_eq
id|vc-&gt;vc_cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
id|y
op_increment
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|newport_bmove
r_static
r_void
id|newport_bmove
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|h
comma
r_int
id|w
)paren
(brace
r_int
id|xs
comma
id|ys
comma
id|xe
comma
id|ye
comma
id|xoffs
comma
id|yoffs
comma
id|tmp
suffix:semicolon
id|xs
op_assign
id|sx
op_lshift
l_int|3
suffix:semicolon
id|xe
op_assign
(paren
(paren
id|sx
op_plus
id|w
)paren
op_lshift
l_int|3
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * as bmove is only used to move stuff around in the same line&n;     * (h == 1), we don&squot;t care about wrap arounds caused by topscan != 0&n;     */
id|ys
op_assign
(paren
(paren
id|sy
op_lshift
l_int|4
)paren
op_plus
id|topscan
)paren
op_amp
l_int|0x3ff
suffix:semicolon
id|ye
op_assign
(paren
(paren
(paren
id|sy
op_plus
id|h
)paren
op_lshift
l_int|4
)paren
op_minus
l_int|1
op_plus
id|topscan
)paren
op_amp
l_int|0x3ff
suffix:semicolon
id|xoffs
op_assign
(paren
id|dx
op_minus
id|sx
)paren
op_lshift
l_int|3
suffix:semicolon
id|yoffs
op_assign
(paren
id|dy
op_minus
id|sy
)paren
op_lshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|xoffs
OG
l_int|0
)paren
(brace
multiline_comment|/* move to the right, exchange starting points */
id|tmp
op_assign
id|xe
suffix:semicolon
id|xe
op_assign
id|xs
suffix:semicolon
id|xs
op_assign
id|tmp
suffix:semicolon
)brace
id|newport_wait
c_func
(paren
)paren
suffix:semicolon
id|npregs-&gt;set.drawmode0
op_assign
(paren
id|NPORT_DMODE0_S2S
op_or
id|NPORT_DMODE0_BLOCK
op_or
id|NPORT_DMODE0_DOSETUP
op_or
id|NPORT_DMODE0_STOPX
op_or
id|NPORT_DMODE0_STOPY
)paren
suffix:semicolon
id|npregs-&gt;set.xystarti
op_assign
(paren
id|xs
op_lshift
l_int|16
)paren
op_or
id|ys
suffix:semicolon
id|npregs-&gt;set.xyendi
op_assign
(paren
id|xe
op_lshift
l_int|16
)paren
op_or
id|ye
suffix:semicolon
id|npregs-&gt;go.xymove
op_assign
(paren
id|xoffs
op_lshift
l_int|16
)paren
op_or
id|yoffs
suffix:semicolon
)brace
DECL|function|newport_dummy
r_static
r_int
id|newport_dummy
c_func
(paren
r_struct
id|vc_data
op_star
id|c
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DUMMY
mdefine_line|#define DUMMY (void *) newport_dummy
DECL|variable|newport_con
r_struct
id|consw
id|newport_con
op_assign
(brace
id|newport_startup
comma
id|newport_init
comma
id|DUMMY
comma
multiline_comment|/* con_deinit */
id|newport_clear
comma
id|newport_putc
comma
id|newport_putcs
comma
id|newport_cursor
comma
id|newport_scroll
comma
id|newport_bmove
comma
id|newport_switch
comma
id|newport_blank
comma
id|newport_font_op
comma
id|newport_set_palette
comma
id|newport_scrolldelta
comma
id|DUMMY
comma
multiline_comment|/* newport_set_origin, */
id|DUMMY
comma
multiline_comment|/* newport_save_screen */
l_int|NULL
comma
multiline_comment|/* newport_build_attr */
l_int|NULL
multiline_comment|/* newport_invert_region */
)brace
suffix:semicolon
eof