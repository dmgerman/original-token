multiline_comment|/*&n; *  linux/drivers/video/retz3.c -- Low level frame buffer operations for the&n; *&t;&t;&t;&t;   RetinaZ3 (accelerated)&n; *&n; *&t;Created 5 Apr 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &quot;fbcon.h&quot;
multiline_comment|/*&n; *  Prototypes&n; */
r_static
r_int
id|open_retz3
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
r_static
r_void
id|release_retz3
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|bmove_retz3
c_func
(paren
r_struct
id|display
op_star
id|p
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
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_static
r_void
id|clear_retz3
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
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
suffix:semicolon
r_static
r_void
id|putc_retz3
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|ypos
comma
r_int
id|xpos
)paren
suffix:semicolon
r_static
r_void
id|putcs_retz3
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_const
r_char
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
suffix:semicolon
r_static
r_void
id|rev_char_retz3
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xpos
comma
r_int
id|ypos
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Acceleration functions in retz3fb.c&n;     */
r_extern
r_void
id|retz3_bitblt
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|scr
comma
r_int
r_int
id|srcx
comma
r_int
r_int
id|srcy
comma
r_int
r_int
id|destx
comma
r_int
r_int
id|desty
comma
r_int
r_int
id|width
comma
r_int
r_int
id|height
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|mask
)paren
suffix:semicolon
DECL|macro|Z3BLTcopy
mdefine_line|#define Z3BLTcopy&t;&t;0xc0
DECL|macro|Z3BLTset
mdefine_line|#define Z3BLTset&t;&t;0xf0
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|dispsw_retz3
r_static
r_struct
id|display_switch
id|dispsw_retz3
op_assign
(brace
id|open_retz3
comma
id|release_retz3
comma
id|bmove_retz3
comma
id|clear_retz3
comma
id|putc_retz3
comma
id|putcs_retz3
comma
id|rev_char_retz3
)brace
suffix:semicolon
multiline_comment|/*&n;     *  RetinaZ3 (accelerated)&n;     */
DECL|function|open_retz3
r_static
r_int
id|open_retz3
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;type
op_ne
id|FB_TYPE_PACKED_PIXELS
op_logical_or
id|p-&gt;var.accel
op_ne
id|FB_ACCEL_RETINAZ3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;next_line
op_assign
id|p-&gt;var.xres_virtual
op_star
id|p-&gt;var.bits_per_pixel
op_rshift
l_int|3
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_retz3
r_static
r_void
id|release_retz3
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|bmove_retz3
r_static
r_void
id|bmove_retz3
c_func
(paren
r_struct
id|display
op_star
id|p
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
id|height
comma
r_int
id|width
)paren
(brace
r_int
id|fontwidth
op_assign
id|p-&gt;fontwidth
suffix:semicolon
id|sx
op_mul_assign
id|fontwidth
suffix:semicolon
id|dx
op_mul_assign
id|fontwidth
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
suffix:semicolon
id|retz3_bitblt
c_func
(paren
op_amp
id|p-&gt;var
comma
(paren
r_int
r_int
)paren
id|sx
comma
(paren
r_int
r_int
)paren
(paren
id|sy
op_star
id|p-&gt;fontheight
)paren
comma
(paren
r_int
r_int
)paren
id|dx
comma
(paren
r_int
r_int
)paren
(paren
id|dy
op_star
id|p-&gt;fontheight
)paren
comma
(paren
r_int
r_int
)paren
id|width
comma
(paren
r_int
r_int
)paren
(paren
id|height
op_star
id|p-&gt;fontheight
)paren
comma
id|Z3BLTcopy
comma
l_int|0xffff
)paren
suffix:semicolon
)brace
DECL|function|clear_retz3
r_static
r_void
id|clear_retz3
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
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
r_int
id|col
suffix:semicolon
r_int
id|fontwidth
op_assign
id|p-&gt;fontwidth
suffix:semicolon
id|sx
op_mul_assign
id|fontwidth
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
suffix:semicolon
id|col
op_assign
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|col
op_and_assign
l_int|0xff
suffix:semicolon
id|col
op_or_assign
(paren
id|col
op_lshift
l_int|8
)paren
suffix:semicolon
id|retz3_bitblt
c_func
(paren
op_amp
id|p-&gt;var
comma
(paren
r_int
r_int
)paren
id|sx
comma
(paren
r_int
r_int
)paren
(paren
id|sy
op_star
id|p-&gt;fontheight
)paren
comma
(paren
r_int
r_int
)paren
id|sx
comma
(paren
r_int
r_int
)paren
(paren
id|sy
op_star
id|p-&gt;fontheight
)paren
comma
(paren
r_int
r_int
)paren
id|width
comma
(paren
r_int
r_int
)paren
(paren
id|height
op_star
id|p-&gt;fontheight
)paren
comma
id|Z3BLTset
comma
id|col
)paren
suffix:semicolon
)brace
DECL|function|putc_retz3
r_static
r_void
id|putc_retz3
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
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
id|dest
comma
op_star
id|cdat
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|rows
comma
id|revs
comma
id|underl
suffix:semicolon
r_int
r_char
id|d
suffix:semicolon
r_int
r_char
id|fg
comma
id|bg
suffix:semicolon
id|c
op_and_assign
l_int|0xff
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|ypos
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xpos
op_star
id|p-&gt;fontwidth
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|p-&gt;fontheight
suffix:semicolon
id|fg
op_assign
id|p-&gt;fgcol
suffix:semicolon
id|bg
op_assign
id|p-&gt;bgcol
suffix:semicolon
id|revs
op_assign
id|conp-&gt;vc_reverse
suffix:semicolon
id|underl
op_assign
id|conp-&gt;vc_underline
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|underl
op_logical_and
op_logical_neg
id|rows
)paren
id|d
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|revs
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|d
op_amp
l_int|0x80
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|24
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x40
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|16
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x20
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|8
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x10
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|dest
)paren
op_assign
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|d
op_amp
l_int|0x8
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|24
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x4
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|16
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x2
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|8
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x1
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|dest
op_plus
l_int|1
)paren
op_assign
id|tmp
suffix:semicolon
)brace
)brace
DECL|function|putcs_retz3
r_static
r_void
id|putcs_retz3
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_const
r_char
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
r_int
r_char
op_star
id|dest
comma
op_star
id|dest0
comma
op_star
id|cdat
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|rows
comma
id|revs
comma
id|underl
suffix:semicolon
r_int
r_char
id|c
comma
id|d
suffix:semicolon
r_int
r_char
id|fg
comma
id|bg
suffix:semicolon
id|dest0
op_assign
id|p-&gt;screen_base
op_plus
id|ypos
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xpos
op_star
id|p-&gt;fontwidth
suffix:semicolon
id|fg
op_assign
id|p-&gt;fgcol
suffix:semicolon
id|bg
op_assign
id|p-&gt;bgcol
suffix:semicolon
id|revs
op_assign
id|conp-&gt;vc_reverse
suffix:semicolon
id|underl
op_assign
id|conp-&gt;vc_underline
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|s
op_increment
suffix:semicolon
id|dest
op_assign
id|dest0
suffix:semicolon
id|dest0
op_add_assign
l_int|8
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|p-&gt;fontheight
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|underl
op_logical_and
op_logical_neg
id|rows
)paren
id|d
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|revs
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|d
op_amp
l_int|0x80
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|24
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x40
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|16
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x20
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|8
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x10
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|dest
)paren
op_assign
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|d
op_amp
l_int|0x8
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|24
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x4
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|16
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x2
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
op_lshift
l_int|8
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|d
op_amp
l_int|0x1
)paren
ques
c_cond
id|fg
suffix:colon
id|bg
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|dest
op_plus
l_int|1
)paren
op_assign
id|tmp
suffix:semicolon
)brace
)brace
)brace
DECL|function|rev_char_retz3
r_static
r_void
id|rev_char_retz3
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xpos
comma
r_int
id|ypos
)paren
(brace
r_int
r_char
op_star
id|dest
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
comma
id|rows
suffix:semicolon
r_int
r_int
id|bpp
comma
id|mask
suffix:semicolon
id|bpp
op_assign
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_switch
c_cond
(paren
id|bpp
)paren
(brace
r_case
l_int|8
suffix:colon
id|mask
op_assign
l_int|0x0f0f0f0f
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|mask
op_assign
l_int|0xffffffff
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|mask
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* ??? */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;illegal depth for rev_char_retz3(), bpp = %i&bslash;n&quot;
comma
id|bpp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|ypos
op_star
id|p-&gt;fontheight
op_star
id|bytes
op_plus
id|xpos
op_star
id|p-&gt;fontwidth
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|bytes
)paren
(brace
(paren
(paren
r_int
r_int
op_star
)paren
id|dest
)paren
(braket
l_int|0
)braket
op_xor_assign
id|mask
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|dest
)paren
(braket
l_int|1
)braket
op_xor_assign
id|mask
suffix:semicolon
)brace
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
r_int
id|fbcon_init_retz3
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_return
id|fbcon_register_driver
c_func
(paren
op_amp
id|dispsw_retz3
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|fbcon_unregister_driver
c_func
(paren
op_amp
id|dispsw_retz3
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
