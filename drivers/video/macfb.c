multiline_comment|/*&n; *&t;We&squot;ve been given MAC frame buffer info by the booter. Now go set it up&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/nubus.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
multiline_comment|/* conditionalize these ?? */
macro_line|#include &lt;video/fbcon-mfb.h&gt;
macro_line|#include &lt;video/fbcon-cfb2.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
DECL|macro|arraysize
mdefine_line|#define arraysize(x)    (sizeof(x)/sizeof(*(x)))
DECL|variable|macfb_defined
r_static
r_struct
id|fb_var_screeninfo
id|macfb_defined
op_assign
initialization_block
suffix:semicolon
DECL|macro|NUM_TOTAL_MODES
mdefine_line|#define NUM_TOTAL_MODES&t;&t;1
DECL|macro|NUM_PREDEF_MODES
mdefine_line|#define NUM_PREDEF_MODES&t;1
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
DECL|variable|inverse
r_static
r_int
id|inverse
op_assign
l_int|0
suffix:semicolon
DECL|struct|macfb_par
r_struct
id|macfb_par
(brace
DECL|member|unused
r_void
op_star
id|unused
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_par_valid
r_static
r_int
id|current_par_valid
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_par
r_struct
id|macfb_par
id|current_par
suffix:semicolon
DECL|variable|mac_xres
DECL|variable|mac_yres
DECL|variable|mac_depth
DECL|variable|mac_xbytes
DECL|variable|mac_vxres
r_static
r_int
id|mac_xres
comma
id|mac_yres
comma
id|mac_depth
comma
id|mac_xbytes
comma
id|mac_vxres
suffix:semicolon
DECL|variable|mac_videobase
r_static
r_int
r_int
id|mac_videobase
suffix:semicolon
DECL|variable|mac_videosize
r_static
r_int
r_int
id|mac_videosize
suffix:semicolon
multiline_comment|/*&n;&t; * Open/Release the frame buffer device&n;&t; */
DECL|function|macfb_open
r_static
r_int
id|macfb_open
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
DECL|function|macfb_release
r_static
r_int
id|macfb_release
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
DECL|function|macfb_encode_var
r_static
r_void
id|macfb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|macfb_par
op_star
id|par
)paren
(brace
id|memset
c_func
(paren
id|var
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
id|var-&gt;xres
op_assign
id|mac_xres
suffix:semicolon
id|var-&gt;yres
op_assign
id|mac_yres
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|mac_vxres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
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
id|mac_depth
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
r_return
suffix:semicolon
)brace
DECL|function|macfb_get_par
r_static
r_void
id|macfb_get_par
c_func
(paren
r_struct
id|macfb_par
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
DECL|function|macfb_set_par
r_static
r_void
id|macfb_set_par
c_func
(paren
r_struct
id|macfb_par
op_star
id|par
)paren
(brace
id|current_par_valid
op_assign
l_int|1
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
id|macfb_par
id|par
suffix:semicolon
id|macfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|macfb_encode_var
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
r_extern
r_int
id|console_loglevel
suffix:semicolon
DECL|function|macfb_encode_fix
r_static
r_void
id|macfb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|macfb_par
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
l_string|&quot;Macintosh&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * fbmem.c accepts non page aligned mappings now!&n;&t; */
id|fix-&gt;smem_start
op_assign
(paren
r_char
op_star
)paren
id|mac_videobase
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|mac_videosize
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
r_if
c_cond
(paren
id|mac_depth
op_eq
l_int|1
)paren
id|fix-&gt;visual
op_assign
id|FB_VISUAL_MONO01
suffix:semicolon
r_else
id|fix-&gt;visual
op_assign
id|FB_VISUAL_STATIC_PSEUDOCOLOR
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
id|mac_xbytes
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|macfb_get_fix
r_static
r_int
id|macfb_get_fix
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
id|macfb_par
id|par
suffix:semicolon
id|macfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|macfb_encode_fix
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
DECL|function|macfb_get_var
r_static
r_int
id|macfb_get_var
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
id|macfb_par
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
id|macfb_get_par
c_func
(paren
op_amp
id|par
)paren
suffix:semicolon
id|macfb_encode_var
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
DECL|function|macfb_set_disp
r_static
r_void
id|macfb_set_disp
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
id|macfb_get_fix
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
(paren
id|fix.visual
op_eq
id|FB_VISUAL_MONO01
ques
c_cond
op_logical_neg
id|inverse
suffix:colon
id|inverse
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mac_depth
)paren
(brace
macro_line|#ifdef FBCON_HAS_MFB
r_case
l_int|1
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_mfb
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB2
r_case
l_int|2
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb2
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB4
r_case
l_int|4
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb4
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB8
r_case
l_int|8
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|display-&gt;dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|macfb_set_var
r_static
r_int
id|macfb_set_var
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
multiline_comment|/*&n; * Color map handling - hardcoded maps!! &n; *&n; * 2.0 color map primitives, copied from atafb.c&n; */
multiline_comment|/*&n; * should be kmalloc&squot;ed on request&n; */
DECL|variable|red256
DECL|variable|green256
DECL|variable|blue256
r_static
r_int
id|red256
(braket
l_int|256
)braket
comma
id|green256
(braket
l_int|256
)braket
comma
id|blue256
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|red16
r_static
r_int
id|red16
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x8080
comma
l_int|0x8080
comma
l_int|0xc0c0
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|green16
r_static
r_int
id|green16
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0xc0c0
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|blue16
r_static
r_int
id|blue16
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0xc0c0
comma
l_int|0x8080
comma
l_int|0xffff
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_int|0x0000
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|red4
r_static
r_int
id|red4
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0xffff
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|green4
r_static
r_int
id|green4
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|blue4
r_static
r_int
id|blue4
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x8080
comma
l_int|0x0000
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|red2
r_static
r_int
id|red2
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|green2
r_static
r_int
id|green2
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|blue2
r_static
r_int
id|blue2
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|variable|default_256_colors
r_struct
id|fb_cmap
id|default_256_colors
op_assign
(brace
l_int|0
comma
l_int|256
comma
id|red256
comma
id|green256
comma
id|blue256
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|default_16_colors
r_struct
id|fb_cmap
id|default_16_colors
op_assign
(brace
l_int|0
comma
l_int|16
comma
id|red16
comma
id|green16
comma
id|blue16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|default_4_colors
r_struct
id|fb_cmap
id|default_4_colors
op_assign
(brace
l_int|0
comma
l_int|4
comma
id|red4
comma
id|green4
comma
id|blue4
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|default_2_colors
r_struct
id|fb_cmap
id|default_2_colors
op_assign
(brace
l_int|0
comma
l_int|2
comma
id|red2
comma
id|green2
comma
id|blue2
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|mac_set_cmap256
r_static
r_int
id|mac_set_cmap256
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
)paren
(brace
r_int
id|i
comma
id|start
suffix:semicolon
r_int
r_int
op_star
id|red
comma
op_star
id|green
comma
op_star
id|blue
suffix:semicolon
r_int
r_int
id|cval
(braket
)braket
op_assign
(brace
l_int|0xffff
comma
l_int|0xcccc
comma
l_int|0x9999
comma
l_int|0x6666
comma
l_int|0x3333
comma
l_int|0x0000
)brace
suffix:semicolon
r_int
r_int
id|gval
(braket
)braket
op_assign
(brace
l_int|0x0a0a
comma
l_int|0x1414
comma
l_int|0x1e1e
comma
l_int|0x2828
comma
l_int|0x3232
comma
l_int|0x3c3c
comma
l_int|0x4646
comma
l_int|0x5050
comma
l_int|0x5a5a
comma
l_int|0x6464
comma
l_int|0x6e6e
comma
l_int|0x7878
comma
l_int|0x8282
comma
l_int|0x8c8c
comma
l_int|0x9696
comma
l_int|0xa0a0
comma
l_int|0xaaaa
comma
l_int|0xb4b4
comma
l_int|0xbebe
comma
l_int|0xc8c8
comma
l_int|0xd2d2
comma
l_int|0xdcdc
comma
l_int|0xe6e6
comma
l_int|0xf0f0
)brace
suffix:semicolon
id|red
op_assign
id|cmap-&gt;red
suffix:semicolon
id|green
op_assign
id|cmap-&gt;green
suffix:semicolon
id|blue
op_assign
id|cmap-&gt;blue
suffix:semicolon
id|start
op_assign
id|cmap-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|cmap-&gt;len
OL
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* 16 ANSI colors */
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
op_star
id|red
op_increment
op_assign
id|red16
(braket
id|i
)braket
suffix:semicolon
op_star
id|green
op_increment
op_assign
id|green16
(braket
id|i
)braket
suffix:semicolon
op_star
id|blue
op_increment
op_assign
id|blue16
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* 216 colors (6x6x6) map) */
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|232
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|red
op_increment
op_assign
id|cval
(braket
(paren
id|i
op_minus
l_int|16
)paren
op_div
l_int|36
)braket
suffix:semicolon
op_star
id|green
op_increment
op_assign
id|cval
(braket
(paren
(paren
id|i
op_minus
l_int|16
)paren
op_div
l_int|6
)paren
op_mod
l_int|6
)braket
suffix:semicolon
op_star
id|blue
op_increment
op_assign
id|cval
(braket
(paren
id|i
op_minus
l_int|16
)paren
op_mod
l_int|6
)braket
suffix:semicolon
)brace
multiline_comment|/* 24 grays */
r_for
c_loop
(paren
id|i
op_assign
l_int|232
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|red
op_assign
op_star
id|green
op_assign
op_star
id|blue
op_assign
id|gval
(braket
id|i
op_minus
l_int|232
)braket
suffix:semicolon
id|red
op_increment
suffix:semicolon
id|green
op_increment
suffix:semicolon
id|blue
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mac_get_default_cmap
r_static
r_struct
id|fb_cmap
op_star
id|mac_get_default_cmap
c_func
(paren
r_int
id|bpp
)paren
(brace
r_if
c_cond
(paren
id|bpp
op_eq
l_int|1
)paren
r_return
op_amp
id|default_2_colors
suffix:semicolon
r_if
c_cond
(paren
id|bpp
op_eq
l_int|2
)paren
r_return
op_amp
id|default_4_colors
suffix:semicolon
r_if
c_cond
(paren
id|bpp
op_eq
l_int|4
)paren
r_return
op_amp
id|default_16_colors
suffix:semicolon
r_return
op_amp
id|default_256_colors
suffix:semicolon
)brace
DECL|function|memcpy_fs
r_static
r_void
id|memcpy_fs
c_func
(paren
r_int
id|fsfromto
comma
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
id|len
)paren
(brace
r_switch
c_cond
(paren
id|fsfromto
)paren
(brace
r_case
l_int|0
suffix:colon
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
id|copy_from_user
c_func
(paren
id|to
comma
id|from
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
id|copy_to_user
c_func
(paren
id|to
comma
id|from
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|copy_cmap
r_static
r_void
id|copy_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|from
comma
r_struct
id|fb_cmap
op_star
id|to
comma
r_int
id|fsfromto
)paren
(brace
r_int
id|size
suffix:semicolon
r_int
id|tooff
op_assign
l_int|0
comma
id|fromoff
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|to-&gt;start
OG
id|from-&gt;start
)paren
id|fromoff
op_assign
id|to-&gt;start
op_minus
id|from-&gt;start
suffix:semicolon
r_else
id|tooff
op_assign
id|from-&gt;start
op_minus
id|to-&gt;start
suffix:semicolon
id|size
op_assign
id|to-&gt;len
op_minus
id|tooff
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|from-&gt;len
op_minus
id|fromoff
)paren
id|size
op_assign
id|from-&gt;len
op_minus
id|fromoff
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
r_return
suffix:semicolon
id|size
op_mul_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|memcpy_fs
c_func
(paren
id|fsfromto
comma
id|to-&gt;red
op_plus
id|tooff
comma
id|from-&gt;red
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|memcpy_fs
c_func
(paren
id|fsfromto
comma
id|to-&gt;green
op_plus
id|tooff
comma
id|from-&gt;green
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
id|memcpy_fs
c_func
(paren
id|fsfromto
comma
id|to-&gt;blue
op_plus
id|tooff
comma
id|from-&gt;blue
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;transp
op_logical_and
id|to-&gt;transp
)paren
id|memcpy_fs
c_func
(paren
id|fsfromto
comma
id|to-&gt;transp
op_plus
id|tooff
comma
id|from-&gt;transp
op_plus
id|fromoff
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|macfb_get_cmap
r_static
r_int
id|macfb_get_cmap
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
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;macfb_get_cmap: not supported!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* interferes with X11 */
r_if
c_cond
(paren
id|console_loglevel
OL
l_int|7
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
l_int|0
multiline_comment|/*offb_getcolreg*/
comma
id|info
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
multiline_comment|/* non default colormap? */
id|fb_copy_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
macro_line|#endif
id|copy_cmap
c_func
(paren
id|mac_get_default_cmap
c_func
(paren
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|macfb_set_cmap
r_static
r_int
id|macfb_set_cmap
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
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;macfb_set_cmap: not supported!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|console_loglevel
OL
l_int|7
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
(brace
multiline_comment|/* no colormap allocated? */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_set_cmap
c_func
(paren
id|cmap
comma
id|kspc
comma
l_int|1
multiline_comment|/*offb_setcolreg*/
comma
id|info
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|macfb_pan_display
r_static
r_int
id|macfb_pan_display
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
multiline_comment|/* no panning */
id|printk
c_func
(paren
l_string|&quot;macfb_pan: not supported!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|macfb_ioctl
r_static
r_int
id|macfb_ioctl
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
id|printk
c_func
(paren
l_string|&quot;macfb_ioctl: not supported!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|macfb_ops
r_static
r_struct
id|fb_ops
id|macfb_ops
op_assign
(brace
id|macfb_open
comma
id|macfb_release
comma
id|macfb_get_fix
comma
id|macfb_get_var
comma
id|macfb_set_var
comma
id|macfb_get_cmap
comma
id|macfb_set_cmap
comma
id|macfb_pan_display
comma
id|macfb_ioctl
)brace
suffix:semicolon
DECL|function|macfb_setup
r_void
id|macfb_setup
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
(brace
r_char
op_star
id|this_opt
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|this_opt
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this_opt
suffix:semicolon
id|this_opt
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_opt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;inverse&quot;
)paren
)paren
id|inverse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;font:&quot;
comma
l_int|5
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|fb_info.fontname
comma
id|this_opt
op_plus
l_int|5
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;macfb_setup: option %s&bslash;n&quot;
comma
id|this_opt
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|macfb_switch
r_static
r_int
id|macfb_switch
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
DECL|function|macfb_blank
r_static
r_void
id|macfb_blank
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
multiline_comment|/*&n; *&t;Nubus call back. This will give us our board identity and also&n; *&t;other useful info we need later&n; */
DECL|function|nubus_video_card
r_static
r_int
id|nubus_video_card
c_func
(paren
r_struct
id|nubus_device_specifier
op_star
id|ns
comma
r_int
id|slot
comma
r_struct
id|nubus_type
op_star
id|nt
)paren
(brace
r_if
c_cond
(paren
id|nt-&gt;category
op_eq
id|NUBUS_CAT_DISPLAY
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Claim all video cards. We don&squot;t yet do driver specifics though. */
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|nb_video
r_static
r_struct
id|nubus_device_specifier
id|nb_video
op_assign
initialization_block
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|macfb_init
c_func
(paren
r_void
)paren
)paren
(brace
multiline_comment|/* nubus_remap the video .. */
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
r_return
suffix:semicolon
id|mac_xres
op_assign
id|mac_bi_data.dimensions
op_amp
l_int|0xFFFF
suffix:semicolon
id|mac_yres
op_assign
(paren
id|mac_bi_data.dimensions
op_amp
l_int|0xFFFF0000
)paren
op_rshift
l_int|16
suffix:semicolon
id|mac_depth
op_assign
id|mac_bi_data.videodepth
suffix:semicolon
id|mac_xbytes
op_assign
id|mac_bi_data.videorow
suffix:semicolon
id|mac_vxres
op_assign
(paren
id|mac_xbytes
op_div
id|mac_depth
)paren
op_star
l_int|8
suffix:semicolon
id|mac_videosize
op_assign
id|mac_xbytes
op_star
id|mac_yres
suffix:semicolon
id|mac_videobase
op_assign
id|mac_bi_data.videoaddr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;macfb_init: xres %d yres %d bpp %d addr %lx size %ld &bslash;n&quot;
comma
id|mac_xres
comma
id|mac_yres
comma
id|mac_depth
comma
id|mac_videobase
comma
id|mac_videosize
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fill in the available video resolution&n;&t; */
id|macfb_defined.xres
op_assign
id|mac_xres
suffix:semicolon
id|macfb_defined.yres
op_assign
id|mac_yres
suffix:semicolon
id|macfb_defined.xres_virtual
op_assign
id|mac_vxres
suffix:semicolon
id|macfb_defined.yres_virtual
op_assign
id|mac_yres
suffix:semicolon
id|macfb_defined.bits_per_pixel
op_assign
id|mac_depth
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Let there be consoles..&n;&t; */
id|strcpy
c_func
(paren
id|fb_info.modename
comma
l_string|&quot;Macintosh Builtin &quot;
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
id|macfb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|macfb_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|fb_update_var
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|macfb_blank
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|do_fb_set_var
c_func
(paren
op_amp
id|macfb_defined
comma
l_int|1
)paren
suffix:semicolon
id|macfb_get_var
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
id|macfb_set_disp
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fill in the 8 bit color table if required&n;&t; */
r_if
c_cond
(paren
id|mac_depth
op_eq
l_int|8
)paren
id|mac_set_cmap256
c_func
(paren
op_amp
id|default_256_colors
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Register the nubus hook&n;&t; */
id|register_nubus_device
c_func
(paren
op_amp
id|nb_video
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
(brace
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;fb%d: %s frame buffer device using %ldK of video memory&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|fb_info.modename
comma
id|mac_videosize
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/*&n; * These two auxiliary debug functions should go away ASAP. Only usage: &n; * before the console output is up (after head.S come some other crucial&n; * setup routines :-) &n; *&n; * Now in debug.c ...&n; */
macro_line|#endif
eof
