multiline_comment|/*&n; *&t;HP300 Topcat framebuffer support (derived from macfb of all things)&n; *&t;Phil Blundell &lt;philb@gnu.org&gt; 1998&n; * &n; * Should this be moved to drivers/dio/video/ ? -- Peter Maydell&n; * No! -- Jes&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/dio.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/blinken.h&gt;
macro_line|#include &lt;asm/hwtest.h&gt;
macro_line|#include &quot;fbcon-mfb.h&quot;
macro_line|#include &quot;fbcon-cfb2.h&quot;
macro_line|#include &quot;fbcon-cfb4.h&quot;
macro_line|#include &quot;fbcon-cfb8.h&quot;
DECL|macro|arraysize
mdefine_line|#define arraysize(x)    (sizeof(x)/sizeof(*(x)))
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|fb_start
DECL|variable|fb_size
DECL|variable|fb_line_length
r_int
r_int
id|fb_start
comma
id|fb_size
op_assign
l_int|1024
op_star
l_int|768
comma
id|fb_line_length
op_assign
l_int|1024
suffix:semicolon
DECL|variable|fb_regs
r_int
r_int
id|fb_regs
suffix:semicolon
DECL|variable|fb_bitmask
r_int
r_char
id|fb_bitmask
suffix:semicolon
DECL|macro|TC_WEN
mdefine_line|#define TC_WEN&t;&t;0x4088
DECL|macro|TC_REN
mdefine_line|#define TC_REN&t;&t;0x408c
DECL|macro|TC_FBEN
mdefine_line|#define TC_FBEN&t;&t;0x4090
DECL|macro|TC_NBLANK
mdefine_line|#define TC_NBLANK&t;0x4080
multiline_comment|/* blitter regs */
DECL|macro|BUSY
mdefine_line|#define BUSY&t;&t;0x4044
DECL|macro|WMRR
mdefine_line|#define WMRR&t;&t;0x40ef
DECL|macro|SOURCE_X
mdefine_line|#define SOURCE_X&t;0x40f2
DECL|macro|SOURCE_Y
mdefine_line|#define SOURCE_Y&t;0x40f6
DECL|macro|DEST_X
mdefine_line|#define DEST_X&t;&t;0x40fa
DECL|macro|DEST_Y
mdefine_line|#define DEST_Y&t;&t;0x40fe
DECL|macro|WHEIGHT
mdefine_line|#define WHEIGHT&t;&t;0x4106
DECL|macro|WWIDTH
mdefine_line|#define WWIDTH&t;&t;0x4102
DECL|macro|WMOVE
mdefine_line|#define WMOVE&t;&t;0x409c
DECL|variable|hpfb_defined
r_static
r_struct
id|fb_var_screeninfo
id|hpfb_defined
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* W,H, W, H (virtual) load xres,xres_virtual*/
l_int|0
comma
l_int|0
comma
multiline_comment|/* virtual -&gt; visible no offset */
l_int|0
comma
multiline_comment|/* depth -&gt; load bits_per_pixel */
l_int|0
comma
multiline_comment|/* greyscale ? */
(brace
l_int|0
comma
l_int|2
comma
l_int|0
)brace
comma
multiline_comment|/* R */
(brace
l_int|0
comma
l_int|2
comma
l_int|0
)brace
comma
multiline_comment|/* G */
(brace
l_int|0
comma
l_int|2
comma
l_int|0
)brace
comma
multiline_comment|/* B */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* transparency */
l_int|0
comma
multiline_comment|/* standard pixel format */
id|FB_ACTIVATE_NOW
comma
l_int|274
comma
l_int|195
comma
multiline_comment|/* 14&quot; monitor */
id|FB_ACCEL_NONE
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0
comma
multiline_comment|/* No sync info */
id|FB_VMODE_NONINTERLACED
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|struct|hpfb_par
r_struct
id|hpfb_par
(brace
)brace
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_par
r_struct
id|hpfb_par
id|current_par
suffix:semicolon
DECL|function|hpfb_encode_var
r_static
r_void
id|hpfb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|hpfb_par
op_star
id|par
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|var-&gt;xres
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|768
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
l_int|768
suffix:semicolon
id|var-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
l_int|1
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_assign
l_int|0
suffix:semicolon
id|var-&gt;height
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;width
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|0
suffix:semicolon
id|var-&gt;sync
op_assign
l_int|0
suffix:semicolon
id|var-&gt;left_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;right_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;upper_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;lower_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;hsync_len
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vsync_len
op_assign
l_int|0
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
id|arraysize
c_func
(paren
id|var-&gt;reserved
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|var-&gt;reserved
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|hpfb_get_par
r_static
r_void
id|hpfb_get_par
c_func
(paren
r_struct
id|hpfb_par
op_star
id|par
)paren
(brace
op_star
id|par
op_assign
id|current_par
suffix:semicolon
)brace
DECL|function|fb_update_var
r_static
r_int
id|fb_update_var
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_fb_set_var
r_static
r_int
id|do_fb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|isactive
)paren
(brace
r_struct
id|hpfb_par
id|par
suffix:semicolon
id|hpfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|hpfb_encode_var
c_func
(paren
id|var
comma
op_amp
id|par
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfb_get_cmap
r_static
r_int
id|hpfb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the palette.  This may not work on all boards but only experimentation will tell.&n; * XXX Doesn&squot;t work at all.&n; */
DECL|function|hpfb_set_cmap
r_static
r_int
id|hpfb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
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
id|cmap-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_while
c_loop
(paren
id|readw
c_func
(paren
id|fb_regs
op_plus
l_int|0x6002
)paren
op_amp
l_int|0x4
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0
comma
id|fb_regs
op_plus
l_int|0x60f0
)paren
suffix:semicolon
id|writew
c_func
(paren
id|cmap-&gt;start
op_plus
id|i
comma
id|fb_regs
op_plus
l_int|0x60b8
)paren
suffix:semicolon
id|writew
c_func
(paren
id|cmap-&gt;red
(braket
id|i
)braket
comma
id|fb_regs
op_plus
l_int|0x60b2
)paren
suffix:semicolon
id|writew
c_func
(paren
id|cmap-&gt;green
(braket
id|i
)braket
comma
id|fb_regs
op_plus
l_int|0x60b4
)paren
suffix:semicolon
id|writew
c_func
(paren
id|cmap-&gt;blue
(braket
id|i
)braket
comma
id|fb_regs
op_plus
l_int|0x60b6
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0xff
comma
id|fb_regs
op_plus
l_int|0x60f0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
id|writew
c_func
(paren
l_int|0xffff
comma
id|fb_regs
op_plus
l_int|0x60ba
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfb_get_var
r_static
r_int
id|hpfb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|hpfb_par
id|par
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
(brace
id|hpfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|hpfb_encode_var
c_func
(paren
id|var
comma
op_amp
id|par
)paren
suffix:semicolon
)brace
r_else
op_star
id|var
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfb_set_var
r_static
r_int
id|hpfb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|do_fb_set_var
c_func
(paren
id|var
comma
l_int|1
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfb_encode_fix
r_static
r_void
id|hpfb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|hpfb_par
op_star
id|par
)paren
(brace
id|memset
c_func
(paren
id|fix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;HP300 Topcat&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * X works, but screen wraps ... &n;&t; */
id|fix-&gt;smem_start
op_assign
(paren
r_char
op_star
)paren
id|fb_start
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|fb_size
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|fb_line_length
suffix:semicolon
)brace
DECL|function|hpfb_get_fix
r_static
r_int
id|hpfb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|hpfb_par
id|par
suffix:semicolon
id|hpfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|hpfb_encode_fix
c_func
(paren
id|fix
comma
op_amp
id|par
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|topcat_blit
r_static
r_void
id|topcat_blit
c_func
(paren
r_int
id|x0
comma
r_int
id|y0
comma
r_int
id|x1
comma
r_int
id|y1
comma
r_int
id|w
comma
r_int
id|h
)paren
(brace
r_while
c_loop
(paren
id|readb
c_func
(paren
id|fb_regs
op_plus
id|BUSY
)paren
op_amp
id|fb_bitmask
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x3
comma
id|fb_regs
op_plus
id|WMRR
)paren
suffix:semicolon
id|writew
c_func
(paren
id|x0
comma
id|fb_regs
op_plus
id|SOURCE_X
)paren
suffix:semicolon
id|writew
c_func
(paren
id|y0
comma
id|fb_regs
op_plus
id|SOURCE_Y
)paren
suffix:semicolon
id|writew
c_func
(paren
id|x1
comma
id|fb_regs
op_plus
id|DEST_X
)paren
suffix:semicolon
id|writew
c_func
(paren
id|y1
comma
id|fb_regs
op_plus
id|DEST_Y
)paren
suffix:semicolon
id|writew
c_func
(paren
id|h
comma
id|fb_regs
op_plus
id|WHEIGHT
)paren
suffix:semicolon
id|writew
c_func
(paren
id|w
comma
id|fb_regs
op_plus
id|WWIDTH
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|fb_bitmask
comma
id|fb_regs
op_plus
id|WMOVE
)paren
suffix:semicolon
)brace
DECL|function|hpfb_ioctl
r_static
r_int
id|hpfb_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|hpfb_switch
r_static
r_int
id|hpfb_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|do_fb_set_var
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
l_int|1
)paren
suffix:semicolon
id|currcon
op_assign
id|con
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
DECL|function|hpfb_blank
r_static
r_void
id|hpfb_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* Not supported */
)brace
DECL|function|hpfb_open
r_static
r_int
id|hpfb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
multiline_comment|/*&n;&t; * Nothing, only a usage count for the moment&n;&t; */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfb_set_disp
r_static
r_void
id|hpfb_set_disp
c_func
(paren
r_int
id|con
)paren
(brace
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_struct
id|display
op_star
id|display
suffix:semicolon
r_if
c_cond
(paren
id|con
op_ge
l_int|0
)paren
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
r_else
id|display
op_assign
op_amp
id|disp
suffix:semicolon
multiline_comment|/* used during initialization */
id|hpfb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|con
comma
l_int|0
)paren
suffix:semicolon
id|display-&gt;screen_base
op_assign
id|fix.smem_start
suffix:semicolon
id|display-&gt;visual
op_assign
id|fix.visual
suffix:semicolon
id|display-&gt;type
op_assign
id|fix.type
suffix:semicolon
id|display-&gt;type_aux
op_assign
id|fix.type_aux
suffix:semicolon
id|display-&gt;ypanstep
op_assign
id|fix.ypanstep
suffix:semicolon
id|display-&gt;ywrapstep
op_assign
id|fix.ywrapstep
suffix:semicolon
id|display-&gt;line_length
op_assign
id|fix.line_length
suffix:semicolon
id|display-&gt;next_line
op_assign
id|fix.line_length
suffix:semicolon
id|display-&gt;can_soft_blank
op_assign
l_int|0
suffix:semicolon
id|display-&gt;inverse
op_assign
l_int|0
suffix:semicolon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
)brace
DECL|function|hpfb_release
r_static
r_int
id|hpfb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hpfb_ops
r_static
r_struct
id|fb_ops
id|hpfb_ops
op_assign
(brace
id|hpfb_open
comma
id|hpfb_release
comma
id|hpfb_get_fix
comma
id|hpfb_get_var
comma
id|hpfb_set_var
comma
id|hpfb_get_cmap
comma
id|hpfb_set_cmap
comma
l_int|NULL
comma
id|hpfb_ioctl
)brace
suffix:semicolon
DECL|macro|TOPCAT_FBOMSB
mdefine_line|#define TOPCAT_FBOMSB&t;0x5d
DECL|macro|TOPCAT_FBOLSB
mdefine_line|#define TOPCAT_FBOLSB&t;0x5f
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|hpfb_init_one
c_func
(paren
r_int
r_int
id|base
)paren
)paren
(brace
r_int
r_int
id|fboff
suffix:semicolon
id|fboff
op_assign
(paren
id|readb
c_func
(paren
id|base
op_plus
id|TOPCAT_FBOMSB
)paren
op_lshift
l_int|8
)paren
op_or
id|readb
c_func
(paren
id|base
op_plus
id|TOPCAT_FBOLSB
)paren
suffix:semicolon
id|fb_start
op_assign
l_int|0xf0000000
op_or
(paren
id|readb
c_func
(paren
id|base
op_plus
id|fboff
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|fb_regs
op_assign
id|base
suffix:semicolon
macro_line|#if 0
multiline_comment|/* This is the magic incantation NetBSD uses to make Catseye boards work. */
id|writeb
c_func
(paren
l_int|0
comma
id|base
op_plus
l_int|0x4800
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|base
op_plus
l_int|0x4510
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|base
op_plus
l_int|0x4512
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|base
op_plus
l_int|0x4514
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|base
op_plus
l_int|0x4516
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x90
comma
id|base
op_plus
l_int|0x4206
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Fill in the available video resolution&n;&t; */
id|hpfb_defined.xres
op_assign
l_int|1024
suffix:semicolon
id|hpfb_defined.yres
op_assign
l_int|768
suffix:semicolon
id|hpfb_defined.xres_virtual
op_assign
l_int|1024
suffix:semicolon
id|hpfb_defined.yres_virtual
op_assign
l_int|768
suffix:semicolon
id|hpfb_defined.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* &n;&t; *&t;Give the hardware a bit of a prod and work out how many bits per&n;&t; *&t;pixel are supported.&n;&t; */
id|writeb
c_func
(paren
l_int|0xff
comma
id|base
op_plus
id|TC_WEN
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xff
comma
id|base
op_plus
id|TC_FBEN
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xff
comma
id|fb_start
)paren
suffix:semicolon
id|fb_bitmask
op_assign
id|readb
c_func
(paren
id|fb_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Enable reading/writing of all the planes.&n;&t; */
id|writeb
c_func
(paren
id|fb_bitmask
comma
id|base
op_plus
id|TC_WEN
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|fb_bitmask
comma
id|base
op_plus
id|TC_REN
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|fb_bitmask
comma
id|base
op_plus
id|TC_FBEN
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x1
comma
id|base
op_plus
id|TC_NBLANK
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Let there be consoles..&n;&t; */
id|strcpy
c_func
(paren
id|fb_info.modename
comma
l_string|&quot;Topcat&quot;
)paren
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|hpfb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|hpfb_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|fb_update_var
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|hpfb_blank
suffix:semicolon
id|do_fb_set_var
c_func
(paren
op_amp
id|hpfb_defined
comma
l_int|1
)paren
suffix:semicolon
id|hpfb_get_var
c_func
(paren
op_amp
id|disp.var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
id|hpfb_set_disp
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Check that the secondary ID indicates that we have some hope of working with this&n; * framebuffer.  The catseye boards are pretty much like topcats and we can muddle through.&n; */
DECL|macro|topcat_sid_ok
mdefine_line|#define topcat_sid_ok(x)  (((x) == DIO_ID2_LRCATSEYE) || ((x) == DIO_ID2_HRCCATSEYE)    &bslash;&n;&t;&t;&t;   || ((x) == DIO_ID2_HRMCATSEYE) || ((x) == DIO_ID2_TOPCAT))
multiline_comment|/* &n; * Initialise the framebuffer&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|hpfb_init
c_func
(paren
r_int
r_int
id|mem_start
)paren
)paren
(brace
r_int
r_int
id|sid
suffix:semicolon
multiline_comment|/* Topcats can be on the internal IO bus or real DIO devices.&n;&t; * The internal variant sits at 0xf0560000; it has primary&n;&t; * and secondary ID registers just like the DIO version.&n;&t; * So we merge the two detection routines.&n;&t; *&n;&t; * Perhaps this #define should be in a global header file:&n;&t; * I believe it&squot;s common to all internal fbs, not just topcat.&n;&t; */
DECL|macro|INTFBADDR
mdefine_line|#define INTFBADDR 0xf0560000
r_if
c_cond
(paren
id|hwreg_present
c_func
(paren
(paren
r_void
op_star
)paren
id|INTFBADDR
)paren
op_logical_and
(paren
id|DIO_ID
c_func
(paren
id|INTFBADDR
)paren
op_eq
id|DIO_ID_FBUFFER
)paren
op_logical_and
id|topcat_sid_ok
c_func
(paren
id|sid
op_assign
id|DIO_SECID
c_func
(paren
id|INTFBADDR
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Internal Topcat found (secondary id %02x)&bslash;n&quot;
comma
id|sid
)paren
suffix:semicolon
id|hpfb_init_one
c_func
(paren
id|INTFBADDR
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|sc
op_assign
id|dio_find
c_func
(paren
id|DIO_ID_FBUFFER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sc
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|dio_scodetoviraddr
c_func
(paren
id|sc
)paren
suffix:semicolon
r_int
r_int
id|sid
op_assign
id|DIO_SECID
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|topcat_sid_ok
c_func
(paren
id|sid
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Topcat found at DIO select code %02x &quot;
l_string|&quot;(secondary id %02x)&bslash;n&quot;
comma
id|sc
comma
id|sid
)paren
suffix:semicolon
id|hpfb_init_one
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|mem_start
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|hpfb_setup
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|ints
)paren
)paren
(brace
)brace
eof