multiline_comment|/*&n; *  linux/drivers/video/mfb.c -- Low level frame buffer operations for&n; *&t;&t;&t;&t; monochrome&n; *&n; *&t;Created 5 Apr 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &quot;fbcon.h&quot;
multiline_comment|/*&n;     *  Prototypes&n;     */
r_static
r_int
id|open_mfb
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
id|release_mfb
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|bmove_mfb
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
id|clear_mfb
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
id|putc_mfb
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
id|yy
comma
r_int
id|xx
)paren
suffix:semicolon
r_static
r_void
id|putcs_mfb
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
id|yy
comma
r_int
id|xx
)paren
suffix:semicolon
r_static
r_void
id|rev_char_mfb
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
suffix:semicolon
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|dispsw_mfb
r_static
r_struct
id|display_switch
id|dispsw_mfb
op_assign
(brace
id|open_mfb
comma
id|release_mfb
comma
id|bmove_mfb
comma
id|clear_mfb
comma
id|putc_mfb
comma
id|putcs_mfb
comma
id|rev_char_mfb
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Monochrome&n;     */
DECL|function|open_mfb
r_static
r_int
id|open_mfb
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
id|p-&gt;var.bits_per_pixel
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;line_length
)paren
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
suffix:semicolon
r_else
id|p-&gt;next_line
op_assign
id|p-&gt;var.xres_virtual
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
DECL|function|release_mfb
r_static
r_void
id|release_mfb
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|bmove_mfb
r_static
r_void
id|bmove_mfb
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
id|u_char
op_star
id|src
comma
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|dx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;fontheight
op_star
id|width
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|p-&gt;fontheight
op_star
id|width
suffix:semicolon
id|mymemmove
c_func
(paren
id|dest
comma
id|src
comma
id|height
op_star
id|p-&gt;fontheight
op_star
id|width
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dy
op_le
id|sy
)paren
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|mymemmove
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_add_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
)brace
r_else
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
(paren
(paren
id|sy
op_plus
id|height
)paren
op_star
id|p-&gt;fontheight
op_minus
l_int|1
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
(paren
(paren
id|dy
op_plus
id|height
)paren
op_star
id|p-&gt;fontheight
op_minus
l_int|1
)paren
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|mymemmove
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
)brace
)brace
)brace
DECL|function|clear_mfb
r_static
r_void
id|clear_mfb
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
id|u_char
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
(brace
r_if
c_cond
(paren
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
)paren
id|mymemset
c_func
(paren
id|dest
comma
id|height
op_star
id|p-&gt;fontheight
op_star
id|width
)paren
suffix:semicolon
r_else
id|mymemclear
c_func
(paren
id|dest
comma
id|height
op_star
id|p-&gt;fontheight
op_star
id|width
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
r_if
c_cond
(paren
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
)paren
id|mymemset
c_func
(paren
id|dest
comma
id|width
)paren
suffix:semicolon
r_else
id|mymemclear_small
c_func
(paren
id|dest
comma
id|width
)paren
suffix:semicolon
)brace
DECL|function|putc_mfb
r_static
r_void
id|putc_mfb
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
id|yy
comma
r_int
id|xx
)paren
(brace
id|u_char
op_star
id|dest
comma
op_star
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|revs
comma
id|underl
suffix:semicolon
id|u_char
id|d
suffix:semicolon
id|c
op_and_assign
l_int|0xff
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|p-&gt;fontheight
suffix:semicolon
id|bold
op_assign
id|attr_bold
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|revs
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|underl
op_assign
id|attr_underline
c_func
(paren
id|p
comma
id|conp
)paren
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
r_else
r_if
c_cond
(paren
id|bold
)paren
id|d
op_or_assign
id|d
op_rshift
l_int|1
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
op_star
id|dest
op_assign
id|d
suffix:semicolon
)brace
)brace
DECL|function|putcs_mfb
r_static
r_void
id|putcs_mfb
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
id|yy
comma
r_int
id|xx
)paren
(brace
id|u_char
op_star
id|dest
comma
op_star
id|dest0
comma
op_star
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|revs
comma
id|underl
suffix:semicolon
id|u_char
id|c
comma
id|d
suffix:semicolon
id|dest0
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|bold
op_assign
id|attr_bold
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|revs
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|underl
op_assign
id|attr_underline
c_func
(paren
id|p
comma
id|conp
)paren
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
op_increment
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
r_else
r_if
c_cond
(paren
id|bold
)paren
id|d
op_or_assign
id|d
op_rshift
l_int|1
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
op_star
id|dest
op_assign
id|d
suffix:semicolon
)brace
)brace
)brace
DECL|function|rev_char_mfb
r_static
r_void
id|rev_char_mfb
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
(brace
id|u_char
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xx
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
op_star
id|dest
op_assign
op_complement
op_star
id|dest
suffix:semicolon
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
id|fbcon_init_mfb
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
id|dispsw_mfb
comma
l_int|0
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
id|dispsw_mfb
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
