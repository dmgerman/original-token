multiline_comment|/*&n; *  linux/drivers/video/cfb8.c -- Low level frame buffer operations for 8 bpp&n; *&t;&t;&t;&t;  packed pixels&n; *&n; *&t;Created 5 Apr 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &quot;fbcon.h&quot;
macro_line|#include &quot;fbcon-cfb8.h&quot;
multiline_comment|/*&n;     *  8 bpp packed pixels&n;     */
DECL|variable|nibbletab_cfb8
r_static
id|u32
id|nibbletab_cfb8
(braket
)braket
op_assign
(brace
macro_line|#if defined(__BIG_ENDIAN)
l_int|0x00000000
comma
l_int|0x000000ff
comma
l_int|0x0000ff00
comma
l_int|0x0000ffff
comma
l_int|0x00ff0000
comma
l_int|0x00ff00ff
comma
l_int|0x00ffff00
comma
l_int|0x00ffffff
comma
l_int|0xff000000
comma
l_int|0xff0000ff
comma
l_int|0xff00ff00
comma
l_int|0xff00ffff
comma
l_int|0xffff0000
comma
l_int|0xffff00ff
comma
l_int|0xffffff00
comma
l_int|0xffffffff
macro_line|#elif defined(__LITTLE_ENDIAN)
l_int|0x00000000
comma
l_int|0xff000000
comma
l_int|0x00ff0000
comma
l_int|0xffff0000
comma
l_int|0x0000ff00
comma
l_int|0xff00ff00
comma
l_int|0x00ffff00
comma
l_int|0xffffff00
comma
l_int|0x000000ff
comma
l_int|0xff0000ff
comma
l_int|0x00ff00ff
comma
l_int|0xffff00ff
comma
l_int|0x0000ffff
comma
l_int|0xff00ffff
comma
l_int|0x00ffffff
comma
l_int|0xffffffff
macro_line|#else
macro_line|#error FIXME: No endianness??
macro_line|#endif
)brace
suffix:semicolon
DECL|function|fbcon_cfb8_setup
r_void
id|fbcon_cfb8_setup
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
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|fbcon_cfb8_bmove
r_void
id|fbcon_cfb8_bmove
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
l_int|8
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
l_int|8
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
l_int|8
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
l_int|8
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
l_int|8
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
l_int|8
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
l_int|8
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
DECL|function|fbcon_cfb8_clear
r_void
id|fbcon_cfb8_clear
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
l_int|8
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|8
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|16
)paren
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
l_int|8
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
id|dest
op_add_assign
l_int|8
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
id|dest
op_add_assign
l_int|8
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|fbcon_cfb8_putc
r_void
id|fbcon_cfb8_putc
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
id|bytes
op_plus
id|xx
op_star
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
id|fgx
op_assign
id|attr_fgcol
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|8
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|16
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|8
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|16
)paren
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
(paren
id|nibbletab_cfb8
(braket
op_star
id|cdat
op_rshift
l_int|4
)braket
op_amp
id|eorx
)paren
op_xor
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
(paren
id|nibbletab_cfb8
(braket
op_star
id|cdat
op_increment
op_amp
l_int|0xf
)braket
op_amp
id|eorx
)paren
op_xor
id|bgx
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb8_putcs
r_void
id|fbcon_cfb8_putcs
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
l_int|8
suffix:semicolon
id|fgx
op_assign
id|attr_fgcol
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|bgx
op_assign
id|attr_bgcol
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|8
)paren
suffix:semicolon
id|fgx
op_or_assign
(paren
id|fgx
op_lshift
l_int|16
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|8
)paren
suffix:semicolon
id|bgx
op_or_assign
(paren
id|bgx
op_lshift
l_int|16
)paren
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
(paren
id|nibbletab_cfb8
(braket
op_star
id|cdat
op_rshift
l_int|4
)braket
op_amp
id|eorx
)paren
op_xor
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
(paren
id|nibbletab_cfb8
(braket
op_star
id|cdat
op_increment
op_amp
l_int|0xf
)braket
op_amp
id|eorx
)paren
op_xor
id|bgx
suffix:semicolon
)brace
id|dest0
op_add_assign
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|fbcon_cfb8_revc
r_void
id|fbcon_cfb8_revc
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
l_int|8
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
l_int|0x0f0f0f0f
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
l_int|0x0f0f0f0f
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_cfb8
r_struct
id|display_switch
id|fbcon_cfb8
op_assign
(brace
id|fbcon_cfb8_setup
comma
id|fbcon_cfb8_bmove
comma
id|fbcon_cfb8_clear
comma
id|fbcon_cfb8_putc
comma
id|fbcon_cfb8_putcs
comma
id|fbcon_cfb8_revc
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Visible symbols for modules&n;     */
DECL|variable|fbcon_cfb8
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8
)paren
suffix:semicolon
DECL|variable|fbcon_cfb8_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8_setup
)paren
suffix:semicolon
DECL|variable|fbcon_cfb8_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_cfb8_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8_clear
)paren
suffix:semicolon
DECL|variable|fbcon_cfb8_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8_putc
)paren
suffix:semicolon
DECL|variable|fbcon_cfb8_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_cfb8_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_cfb8_revc
)paren
suffix:semicolon
eof
