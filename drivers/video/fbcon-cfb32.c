multiline_comment|/*&n; *  linux/drivers/video/cfb32.c -- Low level frame buffer operations for 32 bpp&n; *&t;&t;&t;&t;   truecolor packed pixels&n; *&n; *&t;Created 28 Dec 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
multiline_comment|/*&n;     *  32 bpp packed pixels&n;     */
DECL|function|fbcon_cfb32_setup
r_void
id|fbcon_cfb32_setup
c_func
(paren
r_struct
id|display
op_star
id|p
)paren
(brace
id|p-&gt;next_line
op_assign
id|p-&gt;line_length
ques
c_cond
id|p-&gt;line_length
suffix:colon
id|p-&gt;var.xres_virtual
op_lshift
l_int|2
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_cfb32_bmove
r_void
id|fbcon_cfb32_bmove
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
id|bytes
op_assign
id|p-&gt;next_line
comma
id|linesize
op_assign
id|bytes
op_star
id|fontheight
c_func
(paren
id|p
)paren
comma
id|rows
suffix:semicolon
id|u8
op_star
id|src
comma
op_star
id|dst
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
op_star
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
op_eq
id|bytes
)paren
(brace
id|fb_memmove
c_func
(paren
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
comma
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|linesize
comma
id|height
op_star
id|linesize
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fontwidthlog
c_func
(paren
id|p
)paren
)paren
(brace
id|sx
op_lshift_assign
id|fontwidthlog
c_func
(paren
id|p
)paren
op_plus
l_int|2
suffix:semicolon
id|dx
op_lshift_assign
id|fontwidthlog
c_func
(paren
id|p
)paren
op_plus
l_int|2
suffix:semicolon
id|width
op_lshift_assign
id|fontwidthlog
c_func
(paren
id|p
)paren
op_plus
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|sx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
id|dx
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dy
OL
id|sy
op_logical_or
(paren
id|dy
op_eq
id|sy
op_logical_and
id|dx
OL
id|sx
)paren
)paren
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|linesize
op_plus
id|sx
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
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
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|fb_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_add_assign
id|bytes
suffix:semicolon
id|dst
op_add_assign
id|bytes
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
id|sy
op_plus
id|height
)paren
op_star
id|linesize
op_plus
id|sx
op_minus
id|bytes
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|dy
op_plus
id|height
)paren
op_star
id|linesize
op_plus
id|dx
op_minus
id|bytes
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|fb_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_sub_assign
id|bytes
suffix:semicolon
id|dst
op_sub_assign
id|bytes
suffix:semicolon
)brace
)brace
)brace
DECL|function|rectfill
r_static
r_inline
r_void
id|rectfill
c_func
(paren
id|u8
op_star
id|dest
comma
r_int
id|width
comma
r_int
id|height
comma
id|u32
id|data
comma
r_int
id|linesize
)paren
(brace
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
id|height
op_decrement
OG
l_int|0
)paren
(brace
id|u32
op_star
id|p
op_assign
(paren
id|u32
op_star
)paren
id|dest
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
id|width
op_div
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|width
op_amp
l_int|2
)paren
(brace
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|width
op_amp
l_int|1
)paren
id|fb_writel
c_func
(paren
id|data
comma
id|p
op_increment
)paren
suffix:semicolon
id|dest
op_add_assign
id|linesize
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb32_clear
r_void
id|fbcon_cfb32_clear
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
id|u8
op_star
id|dest
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
comma
id|lines
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|u32
id|bgx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|sx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)braket
suffix:semicolon
id|width
op_mul_assign
id|fontwidth
c_func
(paren
id|p
)paren
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|width
op_star
l_int|16
op_eq
id|bytes
)paren
id|rectfill
c_func
(paren
id|dest
comma
id|lines
op_star
id|width
op_star
l_int|4
comma
l_int|1
comma
id|bgx
comma
id|bytes
)paren
suffix:semicolon
r_else
id|rectfill
c_func
(paren
id|dest
comma
id|width
op_star
l_int|4
comma
id|lines
comma
id|bgx
comma
id|bytes
)paren
suffix:semicolon
)brace
DECL|function|fbcon_cfb32_putc
r_void
id|fbcon_cfb32_putc
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
id|u8
op_star
id|dest
comma
op_star
id|cdat
comma
id|bits
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
comma
id|rows
suffix:semicolon
id|u32
id|eorx
comma
id|fgx
comma
id|bgx
comma
op_star
id|pt
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|xx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
op_le
l_int|8
)paren
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
id|c
op_amp
id|p-&gt;charmask
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_else
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
(paren
id|c
op_amp
id|p-&gt;charmask
)paren
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|fgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
)braket
suffix:semicolon
id|eorx
op_assign
id|fgx
op_xor
id|bgx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|bytes
)paren
(brace
id|bits
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|pt
op_assign
(paren
id|u32
op_star
)paren
id|dest
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|7
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|6
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|5
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|4
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
OL
l_int|8
)paren
r_continue
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|3
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|2
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|1
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
OL
l_int|12
)paren
r_continue
suffix:semicolon
id|bits
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|7
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|6
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|5
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|4
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
OL
l_int|16
)paren
r_continue
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|3
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|2
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|1
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb32_putcs
r_void
id|fbcon_cfb32_putcs
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
r_int
r_int
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
id|u8
op_star
id|cdat
comma
op_star
id|dest
comma
op_star
id|dest0
comma
id|bits
suffix:semicolon
id|u16
id|c
suffix:semicolon
r_int
id|rows
comma
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
id|u32
id|eorx
comma
id|fgx
comma
id|bgx
comma
op_star
id|pt
suffix:semicolon
id|dest0
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|xx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
id|fgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
id|scr_readw
c_func
(paren
id|s
)paren
)paren
)braket
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
id|scr_readw
c_func
(paren
id|s
)paren
)paren
)braket
suffix:semicolon
id|eorx
op_assign
id|fgx
op_xor
id|bgx
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
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
op_amp
id|p-&gt;charmask
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
op_le
l_int|8
)paren
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_else
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
id|c
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|fontheight
c_func
(paren
id|p
)paren
comma
id|dest
op_assign
id|dest0
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|bytes
)paren
(brace
id|bits
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|pt
op_assign
(paren
id|u32
op_star
)paren
id|dest
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|7
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|6
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|5
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|4
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
OL
l_int|8
)paren
r_continue
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|3
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|2
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|1
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
OL
l_int|12
)paren
r_continue
suffix:semicolon
id|bits
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|7
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|6
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|5
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|4
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
OL
l_int|16
)paren
r_continue
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|3
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|2
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_rshift
l_int|1
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
(paren
op_minus
(paren
id|bits
op_amp
l_int|1
)paren
op_amp
id|eorx
)paren
op_xor
id|bgx
comma
id|pt
op_increment
)paren
suffix:semicolon
)brace
id|dest0
op_add_assign
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb32_revc
r_void
id|fbcon_cfb32_revc
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
id|u8
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
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|fontheight
c_func
(paren
id|p
)paren
op_star
id|bytes
op_plus
id|xx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
op_star
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|bytes
)paren
(brace
r_switch
c_cond
(paren
id|fontwidth
c_func
(paren
id|p
)paren
)paren
(brace
r_case
l_int|16
suffix:colon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|12
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|12
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|13
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|13
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|14
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|14
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|15
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|15
)paren
)paren
suffix:semicolon
multiline_comment|/* FALL THROUGH */
r_case
l_int|12
suffix:colon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|8
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|8
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|9
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|9
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|10
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|10
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|11
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|11
)paren
)paren
suffix:semicolon
multiline_comment|/* FALL THROUGH */
r_case
l_int|8
suffix:colon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|4
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|5
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|5
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|6
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|6
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|7
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|7
)paren
)paren
suffix:semicolon
multiline_comment|/* FALL THROUGH */
r_case
l_int|4
suffix:colon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|0
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|0
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|1
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|1
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|2
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|dest
op_plus
(paren
l_int|4
op_star
l_int|3
)paren
)paren
op_xor
l_int|0xffffffff
comma
id|dest
op_plus
(paren
l_int|4
op_star
l_int|3
)paren
)paren
suffix:semicolon
multiline_comment|/* FALL THROUGH */
)brace
)brace
)brace
DECL|function|fbcon_cfb32_clear_margins
r_void
id|fbcon_cfb32_clear_margins
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
id|bottom_only
)paren
(brace
r_int
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
id|u32
id|bgx
suffix:semicolon
r_int
r_int
id|right_start
op_assign
id|conp-&gt;vc_cols
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
r_int
id|bottom_start
op_assign
id|conp-&gt;vc_rows
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
r_int
id|right_width
comma
id|bottom_width
suffix:semicolon
id|bgx
op_assign
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;dispsw_data
)paren
(braket
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bottom_only
op_logical_and
(paren
id|right_width
op_assign
id|p-&gt;var.xres
op_minus
id|right_start
)paren
)paren
id|rectfill
c_func
(paren
id|p-&gt;screen_base
op_plus
id|right_start
op_star
l_int|4
comma
id|right_width
comma
id|p-&gt;var.yres_virtual
comma
id|bgx
comma
id|bytes
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bottom_width
op_assign
id|p-&gt;var.yres
op_minus
id|bottom_start
)paren
)paren
id|rectfill
c_func
(paren
id|p-&gt;screen_base
op_plus
(paren
id|p-&gt;var.yoffset
op_plus
id|bottom_start
)paren
op_star
id|bytes
comma
id|right_start
comma
id|bottom_width
comma
id|bgx
comma
id|bytes
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_cfb32
r_struct
id|display_switch
id|fbcon_cfb32
op_assign
(brace
id|fbcon_cfb32_setup
comma
id|fbcon_cfb32_bmove
comma
id|fbcon_cfb32_clear
comma
id|fbcon_cfb32_putc
comma
id|fbcon_cfb32_putcs
comma
id|fbcon_cfb32_revc
comma
l_int|NULL
comma
l_int|NULL
comma
id|fbcon_cfb32_clear_margins
comma
id|FONTWIDTH
c_func
(paren
l_int|4
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|8
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|12
)paren
op_or
id|FONTWIDTH
c_func
(paren
l_int|16
)paren
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n;     *  Visible symbols for modules&n;     */
DECL|variable|fbcon_cfb32
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_setup
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_clear
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_putc
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_revc
)paren
suffix:semicolon
DECL|variable|fbcon_cfb32_clear_margins
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb32_clear_margins
)paren
suffix:semicolon
eof
