multiline_comment|/*&n; *  linux/drivers/video/cfb24.c -- Low level frame buffer operations for 24 bpp&n; *&t;&t;&t;&t;   truecolor packed pixels&n; *&n; *&t;Created 7 Mar 1998 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &quot;fbcon.h&quot;
macro_line|#include &quot;fbcon-cfb24.h&quot;
multiline_comment|/*&n;     *  24 bpp packed pixels&n;     */
DECL|variable|fbcon_cfb24_cmap
id|u32
id|fbcon_cfb24_cmap
(braket
l_int|16
)braket
suffix:semicolon
DECL|function|fbcon_cfb24_setup
r_void
id|fbcon_cfb24_setup
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
op_star
l_int|3
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_cfb24_bmove
r_void
id|fbcon_cfb24_bmove
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
id|p-&gt;fontheight
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
l_int|24
op_eq
id|bytes
)paren
id|mymemmove
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
r_else
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
op_star
l_int|24
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
op_star
l_int|24
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
id|dst
comma
id|src
comma
id|width
op_star
l_int|24
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
op_star
l_int|24
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
op_star
l_int|24
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
id|dst
comma
id|src
comma
id|width
op_star
l_int|24
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
DECL|function|fbcon_cfb24_clear
r_void
id|fbcon_cfb24_clear
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
id|dest0
comma
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
id|p-&gt;fontheight
comma
id|rows
comma
id|i
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
id|p-&gt;fontheight
op_star
id|bytes
op_plus
id|sx
op_star
l_int|24
suffix:semicolon
id|bgx
op_assign
id|fbcon_cfb24_cmap
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
id|sx
op_eq
l_int|0
op_logical_and
id|width
op_star
l_int|24
op_eq
id|bytes
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lines
op_star
id|width
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|0
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|1
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|2
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|3
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|4
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|5
)braket
op_assign
id|bgx
suffix:semicolon
id|dest
op_add_assign
l_int|24
suffix:semicolon
)brace
r_else
(brace
id|dest0
op_assign
id|dest
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|lines
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest0
op_add_assign
id|bytes
)paren
(brace
id|dest
op_assign
id|dest0
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
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|0
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|1
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|2
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|3
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|4
)braket
op_assign
id|bgx
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|5
)braket
op_assign
id|bgx
suffix:semicolon
id|dest
op_add_assign
l_int|24
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|store4pixels
r_static
r_inline
r_void
id|store4pixels
c_func
(paren
id|u32
id|d1
comma
id|u32
id|d2
comma
id|u32
id|d3
comma
id|u32
id|d4
comma
id|u32
op_star
id|dest
)paren
(brace
macro_line|#if defined(__BIG_ENDIAN)
op_star
id|dest
op_increment
op_assign
(paren
id|d1
op_lshift
l_int|8
)paren
op_or
(paren
id|d2
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dest
op_increment
op_assign
(paren
id|d2
op_lshift
l_int|16
)paren
op_or
(paren
id|d3
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|dest
op_increment
op_assign
(paren
id|d3
op_lshift
l_int|24
)paren
op_or
id|d4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN)
op_star
id|dest
op_increment
op_assign
(paren
id|d1
op_lshift
l_int|8
)paren
op_or
(paren
id|d2
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dest
op_increment
op_assign
(paren
id|d2
op_lshift
l_int|16
)paren
op_or
(paren
id|d3
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|dest
op_increment
op_assign
(paren
id|d3
op_lshift
l_int|24
)paren
op_or
id|d4
suffix:semicolon
macro_line|#else
macro_line|#error FIXME: No endianness??
macro_line|#endif
)brace
DECL|function|fbcon_cfb24_putc
r_void
id|fbcon_cfb24_putc
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
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|bytes
op_plus
id|xx
op_star
l_int|24
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
(paren
id|c
op_amp
l_int|0xff
)paren
op_star
id|p-&gt;fontheight
suffix:semicolon
id|fgx
op_assign
id|fbcon_cfb24_cmap
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
id|fbcon_cfb24_cmap
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
id|u8
id|bits
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|u32
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
suffix:semicolon
id|d1
op_assign
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
suffix:semicolon
id|d2
op_assign
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
suffix:semicolon
id|d3
op_assign
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
suffix:semicolon
id|d4
op_assign
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
suffix:semicolon
id|store4pixels
c_func
(paren
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
(paren
id|u32
op_star
)paren
id|dest
)paren
suffix:semicolon
id|d1
op_assign
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
suffix:semicolon
id|d2
op_assign
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
suffix:semicolon
id|d3
op_assign
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
suffix:semicolon
id|d4
op_assign
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
suffix:semicolon
id|store4pixels
c_func
(paren
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
(paren
id|u32
op_star
)paren
(paren
id|dest
op_plus
l_int|12
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb24_putcs
r_void
id|fbcon_cfb24_putcs
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
id|c
comma
op_star
id|dest
comma
op_star
id|dest0
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
suffix:semicolon
id|dest0
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|bytes
op_plus
id|xx
op_star
l_int|24
suffix:semicolon
id|fgx
op_assign
id|fbcon_cfb24_cmap
(braket
id|attr_fgcol
c_func
(paren
id|p
comma
op_star
id|s
)paren
)braket
suffix:semicolon
id|bgx
op_assign
id|fbcon_cfb24_cmap
(braket
id|attr_bgcol
c_func
(paren
id|p
comma
op_star
id|s
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
op_star
id|s
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
id|u8
id|bits
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|u32
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
suffix:semicolon
id|d1
op_assign
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
suffix:semicolon
id|d2
op_assign
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
suffix:semicolon
id|d3
op_assign
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
suffix:semicolon
id|d4
op_assign
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
suffix:semicolon
id|store4pixels
c_func
(paren
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
(paren
id|u32
op_star
)paren
id|dest
)paren
suffix:semicolon
id|d1
op_assign
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
suffix:semicolon
id|d2
op_assign
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
suffix:semicolon
id|d3
op_assign
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
suffix:semicolon
id|d4
op_assign
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
suffix:semicolon
id|store4pixels
c_func
(paren
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
(paren
id|u32
op_star
)paren
(paren
id|dest
op_plus
l_int|12
)paren
)paren
suffix:semicolon
)brace
id|dest0
op_add_assign
l_int|24
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb24_revc
r_void
id|fbcon_cfb24_revc
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
id|p-&gt;fontheight
op_star
id|bytes
op_plus
id|xx
op_star
l_int|24
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
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|0
)braket
op_xor_assign
l_int|0xffffffff
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|1
)braket
op_xor_assign
l_int|0xffffffff
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|2
)braket
op_xor_assign
l_int|0xffffffff
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|3
)braket
op_xor_assign
l_int|0xffffffff
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|4
)braket
op_xor_assign
l_int|0xffffffff
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|dest
)paren
(braket
l_int|5
)braket
op_xor_assign
l_int|0xffffffff
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_cfb24
r_struct
id|display_switch
id|fbcon_cfb24
op_assign
(brace
id|fbcon_cfb24_setup
comma
id|fbcon_cfb24_bmove
comma
id|fbcon_cfb24_clear
comma
id|fbcon_cfb24_putc
comma
id|fbcon_cfb24_putcs
comma
id|fbcon_cfb24_revc
comma
l_int|NULL
comma
l_int|NULL
comma
id|FONTWIDTH
c_func
(paren
l_int|8
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
DECL|variable|fbcon_cfb24
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_setup
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_clear
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_putc
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_revc
)paren
suffix:semicolon
DECL|variable|fbcon_cfb24_cmap
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb24_cmap
)paren
suffix:semicolon
eof
