multiline_comment|/*&n; *  linux/drivers/video/fbcon-iplan2p2.c -- Low level frame buffer operations&n; *&t;&t;&t;&t;  for interleaved bitplanes &#xfffd; la Atari (2&n; *&t;&t;&t;&t;  planes, 2 bytes interleave)&n; *&n; *&t;Created 5 Apr 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;fbcon.h&quot;
macro_line|#include &quot;fbcon-iplan2p2.h&quot;
multiline_comment|/*&n;     *  Interleaved bitplanes &#xfffd; la Atari (2 planes, 2 bytes interleave)&n;     */
multiline_comment|/* Increment/decrement 2 plane addresses */
DECL|macro|INC_2P
mdefine_line|#define&t;INC_2P(p)&t;do { if (!((long)(++(p)) &amp; 1)) (p) += 2; } while(0)
DECL|macro|DEC_2P
mdefine_line|#define&t;DEC_2P(p)&t;do { if ((long)(--(p)) &amp; 1) (p) -= 2; } while(0)
multiline_comment|/*  Convert a standard 4 bit color to our 2 bit color assignment:&n;     *  If at least two RGB channels are active, the low bit is turned on;&n;     *  The intensity bit (b3) is shifted into b1.&n;     */
DECL|variable|color_2p
r_static
r_const
id|u8
id|color_2p
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|3
)brace
suffix:semicolon
DECL|macro|COLOR_2P
mdefine_line|#define&t;COLOR_2P(c)&t;color_2p[c]
multiline_comment|/* Perform the m68k movepw operation.  */
DECL|function|movepw
r_static
r_inline
r_void
id|movepw
c_func
(paren
id|u8
op_star
id|d
comma
id|u16
id|val
)paren
(brace
macro_line|#if defined __mc68000__ &amp;&amp; !defined CONFIG_OPTIMIZE_060
id|asm
r_volatile
(paren
l_string|&quot;movepw %1,%0@(0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|d
)paren
comma
l_string|&quot;d&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
macro_line|#else
id|d
(braket
l_int|0
)braket
op_assign
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|d
(braket
l_int|2
)braket
op_assign
id|val
op_amp
l_int|0xff
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Sets the bytes in the visible column at d, height h, to the value&n; * val for a 2 plane screen. The bits of the color in &squot;color&squot; are&n; * moved (8 times) to the respective bytes. This means:&n; *&n; * for(h times; d += bpr)&n; *   *d     = (color &amp; 1) ? 0xff : 0;&n; *   *(d+2) = (color &amp; 2) ? 0xff : 0;&n; */
DECL|function|memclear_2p_col
r_static
id|__inline__
r_void
id|memclear_2p_col
c_func
(paren
r_void
op_star
id|d
comma
r_int
id|h
comma
id|u16
id|val
comma
r_int
id|bpr
)paren
(brace
id|u8
op_star
id|dd
op_assign
id|d
suffix:semicolon
r_do
(brace
id|movepw
c_func
(paren
id|dd
comma
id|val
)paren
suffix:semicolon
id|dd
op_add_assign
id|bpr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|h
)paren
suffix:semicolon
)brace
multiline_comment|/* Sets a 2 plane region from &squot;d&squot;, length &squot;count&squot; bytes, to the color&n; * in val1. &squot;d&squot; has to be an even address and count must be divisible&n; * by 8, because only whole words and all planes are accessed. I.e.:&n; *&n; * for(count/4 times)&n; *   *d     = *(d+1) = (color &amp; 1) ? 0xff : 0;&n; *   *(d+2) = *(d+3) = (color &amp; 2) ? 0xff : 0;&n; */
DECL|function|memset_even_2p
r_static
id|__inline__
r_void
id|memset_even_2p
c_func
(paren
r_void
op_star
id|d
comma
r_int
id|count
comma
id|u32
id|val
)paren
(brace
id|u32
op_star
id|dd
op_assign
id|d
suffix:semicolon
id|count
op_div_assign
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|dd
op_increment
op_assign
id|val
suffix:semicolon
)brace
multiline_comment|/* Copies a 2 plane column from &squot;s&squot;, height &squot;h&squot;, to &squot;d&squot;. */
DECL|function|memmove_2p_col
r_static
id|__inline__
r_void
id|memmove_2p_col
(paren
r_void
op_star
id|d
comma
r_void
op_star
id|s
comma
r_int
id|h
comma
r_int
id|bpr
)paren
(brace
id|u8
op_star
id|dd
op_assign
id|d
comma
op_star
id|ss
op_assign
id|s
suffix:semicolon
r_while
c_loop
(paren
id|h
op_decrement
)paren
(brace
id|dd
(braket
l_int|0
)braket
op_assign
id|ss
(braket
l_int|0
)braket
suffix:semicolon
id|dd
(braket
l_int|2
)braket
op_assign
id|ss
(braket
l_int|2
)braket
suffix:semicolon
id|dd
op_add_assign
id|bpr
suffix:semicolon
id|ss
op_add_assign
id|bpr
suffix:semicolon
)brace
)brace
multiline_comment|/* This expands a 2 bit color into a short for movepw (2 plane) operations. */
DECL|variable|two2byte
r_static
r_const
id|u16
id|two2byte
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0xff00
comma
l_int|0x00ff
comma
l_int|0xffff
)brace
suffix:semicolon
DECL|function|expand2w
r_static
id|__inline__
id|u16
id|expand2w
c_func
(paren
id|u8
id|c
)paren
(brace
r_return
id|two2byte
(braket
id|c
)braket
suffix:semicolon
)brace
multiline_comment|/* This expands a 2 bit color into one long for a movel operation&n; * (2 planes).&n; */
DECL|variable|two2word
r_static
r_const
id|u32
id|two2word
(braket
)braket
op_assign
(brace
macro_line|#ifndef __LITTLE_ENDIAN
l_int|0x00000000
comma
l_int|0xffff0000
comma
l_int|0x0000ffff
comma
l_int|0xffffffff
macro_line|#else
l_int|0x00000000
comma
l_int|0x0000ffff
comma
l_int|0xffff0000
comma
l_int|0xffffffff
macro_line|#endif
)brace
suffix:semicolon
DECL|function|expand2l
r_static
id|__inline__
id|u32
id|expand2l
c_func
(paren
id|u8
id|c
)paren
(brace
r_return
id|two2word
(braket
id|c
)braket
suffix:semicolon
)brace
multiline_comment|/* This duplicates a byte 2 times into a short. */
DECL|function|dup2w
r_static
id|__inline__
id|u16
id|dup2w
c_func
(paren
id|u8
id|c
)paren
(brace
id|u16
id|rv
suffix:semicolon
id|rv
op_assign
id|c
suffix:semicolon
id|rv
op_or_assign
id|c
op_lshift
l_int|8
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|fbcon_iplan2p2_setup
r_void
id|fbcon_iplan2p2_setup
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
id|p-&gt;var.xres_virtual
op_rshift
l_int|2
suffix:semicolon
id|p-&gt;next_plane
op_assign
l_int|2
suffix:semicolon
)brace
DECL|function|fbcon_iplan2p2_bmove
r_void
id|fbcon_iplan2p2_bmove
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
multiline_comment|/*  bmove() has to distinguish two major cases: If both, source and&n;     *  destination, start at even addresses or both are at odd&n;     *  addresses, just the first odd and last even column (if present)&n;     *  require special treatment (memmove_col()). The rest between&n;     *  then can be copied by normal operations, because all adjacent&n;     *  bytes are affected and are to be stored in the same order.&n;     *    The pathological case is when the move should go from an odd&n;     *  address to an even or vice versa. Since the bytes in the plane&n;     *  words must be assembled in new order, it seems wisest to make&n;     *  all movements by memmove_col().&n;     */
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
l_int|2
op_eq
id|p-&gt;next_line
)paren
(brace
multiline_comment|/*  Special (but often used) case: Moving whole lines can be&n;&t; *  done with memmove()&n;&t; */
id|mymemmove
c_func
(paren
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|p-&gt;next_line
op_star
id|p-&gt;fontheight
comma
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;next_line
op_star
id|p-&gt;fontheight
comma
id|p-&gt;next_line
op_star
id|height
op_star
id|p-&gt;fontheight
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|rows
comma
id|cols
suffix:semicolon
id|u8
op_star
id|src
suffix:semicolon
id|u8
op_star
id|dst
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
r_int
id|linesize
op_assign
id|bytes
op_star
id|p-&gt;fontheight
suffix:semicolon
id|u_int
id|colsize
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|u_int
id|upwards
op_assign
(paren
id|dy
OL
id|sy
)paren
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
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sx
op_amp
l_int|1
)paren
op_eq
(paren
id|dx
op_amp
l_int|1
)paren
)paren
(brace
multiline_comment|/* odd-&gt;odd or even-&gt;even */
r_if
c_cond
(paren
id|upwards
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
(paren
id|sx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
op_plus
(paren
id|dx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|dx
op_amp
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_amp
l_int|1
)paren
(brace
id|memmove_2p_col
c_func
(paren
id|dst
comma
id|src
comma
id|colsize
comma
id|bytes
)paren
suffix:semicolon
id|src
op_add_assign
l_int|3
suffix:semicolon
id|dst
op_add_assign
l_int|3
suffix:semicolon
op_decrement
id|width
suffix:semicolon
)brace
r_if
c_cond
(paren
id|width
OG
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|rows
op_assign
id|colsize
suffix:semicolon
id|rows
OG
l_int|0
suffix:semicolon
op_decrement
id|rows
)paren
(brace
id|mymemmove
c_func
(paren
id|dst
comma
id|src
comma
(paren
id|width
op_rshift
l_int|1
)paren
op_star
l_int|4
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
r_if
c_cond
(paren
id|width
op_amp
l_int|1
)paren
(brace
id|src
op_sub_assign
id|colsize
op_star
id|bytes
suffix:semicolon
id|dst
op_sub_assign
id|colsize
op_star
id|bytes
suffix:semicolon
id|memmove_2p_col
c_func
(paren
id|dst
op_plus
(paren
id|width
op_rshift
l_int|1
)paren
op_star
l_int|4
comma
id|src
op_plus
(paren
id|width
op_rshift
l_int|1
)paren
op_star
l_int|4
comma
id|colsize
comma
id|bytes
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|sx
op_plus
id|width
op_minus
l_int|1
)paren
op_amp
l_int|1
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
(paren
(paren
id|sx
op_plus
id|width
op_minus
l_int|1
)paren
op_rshift
l_int|1
)paren
op_star
l_int|4
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
op_plus
(paren
(paren
id|dx
op_plus
id|width
op_minus
l_int|1
)paren
op_rshift
l_int|1
)paren
op_star
l_int|4
suffix:semicolon
id|memmove_2p_col
c_func
(paren
id|dst
comma
id|src
comma
id|colsize
comma
id|bytes
)paren
suffix:semicolon
op_decrement
id|width
suffix:semicolon
)brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|linesize
op_plus
(paren
id|sx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
op_plus
(paren
id|dx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|dx
op_amp
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|width
OG
l_int|1
)paren
(brace
id|src
op_add_assign
id|colsize
op_star
id|bytes
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
op_star
l_int|3
suffix:semicolon
id|dst
op_add_assign
id|colsize
op_star
id|bytes
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
op_star
l_int|3
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|colsize
suffix:semicolon
id|rows
OG
l_int|0
suffix:semicolon
op_decrement
id|rows
)paren
(brace
id|src
op_sub_assign
id|bytes
suffix:semicolon
id|dst
op_sub_assign
id|bytes
suffix:semicolon
id|mymemmove
c_func
(paren
id|dst
comma
id|src
comma
(paren
id|width
op_rshift
l_int|1
)paren
op_star
l_int|4
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|width
op_amp
l_int|1
)paren
id|memmove_2p_col
c_func
(paren
id|dst
op_minus
l_int|3
comma
id|src
op_minus
l_int|3
comma
id|colsize
comma
id|bytes
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* odd-&gt;even or even-&gt;odd */
r_if
c_cond
(paren
id|upwards
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
(paren
id|sx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
op_plus
(paren
id|dx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|dx
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cols
op_assign
id|width
suffix:semicolon
id|cols
OG
l_int|0
suffix:semicolon
op_decrement
id|cols
)paren
(brace
id|memmove_2p_col
c_func
(paren
id|dst
comma
id|src
comma
id|colsize
comma
id|bytes
)paren
suffix:semicolon
id|INC_2P
c_func
(paren
id|src
)paren
suffix:semicolon
id|INC_2P
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|sx
op_add_assign
id|width
op_minus
l_int|1
suffix:semicolon
id|dx
op_add_assign
id|width
op_minus
l_int|1
suffix:semicolon
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|linesize
op_plus
(paren
id|sx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
suffix:semicolon
id|dst
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|linesize
op_plus
(paren
id|dx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|dx
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cols
op_assign
id|width
suffix:semicolon
id|cols
OG
l_int|0
suffix:semicolon
op_decrement
id|cols
)paren
(brace
id|memmove_2p_col
c_func
(paren
id|dst
comma
id|src
comma
id|colsize
comma
id|bytes
)paren
suffix:semicolon
id|DEC_2P
c_func
(paren
id|src
)paren
suffix:semicolon
id|DEC_2P
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
DECL|function|fbcon_iplan2p2_clear
r_void
id|fbcon_iplan2p2_clear
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
id|u32
id|offset
suffix:semicolon
id|u8
op_star
id|start
suffix:semicolon
r_int
id|rows
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
r_int
id|lines
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|u32
id|cval
suffix:semicolon
id|u16
id|pcval
suffix:semicolon
id|cval
op_assign
id|expand2l
(paren
id|COLOR_2P
(paren
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)paren
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
l_int|2
op_eq
id|bytes
)paren
(brace
id|offset
op_assign
id|sy
op_star
id|bytes
op_star
id|p-&gt;fontheight
suffix:semicolon
id|size
op_assign
id|lines
op_star
id|bytes
suffix:semicolon
id|memset_even_2p
c_func
(paren
id|p-&gt;screen_base
op_plus
id|offset
comma
id|size
comma
id|cval
)paren
suffix:semicolon
)brace
r_else
(brace
id|offset
op_assign
(paren
id|sy
op_star
id|bytes
op_star
id|p-&gt;fontheight
)paren
op_plus
(paren
id|sx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|sx
op_amp
l_int|1
)paren
suffix:semicolon
id|start
op_assign
id|p-&gt;screen_base
op_plus
id|offset
suffix:semicolon
id|pcval
op_assign
id|expand2w
c_func
(paren
id|COLOR_2P
c_func
(paren
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*  Clears are split if the region starts at an odd column or&n;&t; *  end at an even column. These extra columns are spread&n;&t; *  across the interleaved planes. All in between can be&n;&t; *  cleared by normal mymemclear_small(), because both bytes of&n;&t; *  the single plane words are affected.&n;&t; */
r_if
c_cond
(paren
id|sx
op_amp
l_int|1
)paren
(brace
id|memclear_2p_col
c_func
(paren
id|start
comma
id|lines
comma
id|pcval
comma
id|bytes
)paren
suffix:semicolon
id|start
op_add_assign
l_int|3
suffix:semicolon
id|width
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|width
op_amp
l_int|1
)paren
(brace
id|memclear_2p_col
c_func
(paren
id|start
op_plus
(paren
id|width
op_rshift
l_int|1
)paren
op_star
l_int|4
comma
id|lines
comma
id|pcval
comma
id|bytes
)paren
suffix:semicolon
id|width
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|width
)paren
(brace
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
id|start
op_add_assign
id|bytes
)paren
id|memset_even_2p
c_func
(paren
id|start
comma
id|width
op_star
l_int|2
comma
id|cval
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fbcon_iplan2p2_putc
r_void
id|fbcon_iplan2p2_putc
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
suffix:semicolon
id|u8
op_star
id|cdat
suffix:semicolon
r_int
id|rows
suffix:semicolon
r_int
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
id|u16
id|eorx
comma
id|fgx
comma
id|bgx
comma
id|fdx
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
(paren
id|xx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|xx
op_amp
l_int|1
)paren
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
id|expand2w
c_func
(paren
id|COLOR_2P
c_func
(paren
id|attr_fgcol
c_func
(paren
id|p
comma
id|c
)paren
)paren
)paren
suffix:semicolon
id|bgx
op_assign
id|expand2w
c_func
(paren
id|COLOR_2P
c_func
(paren
id|attr_bgcol
c_func
(paren
id|p
comma
id|c
)paren
)paren
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
id|fdx
op_assign
id|dup2w
c_func
(paren
op_star
id|cdat
op_increment
)paren
suffix:semicolon
id|movepw
c_func
(paren
id|dest
comma
(paren
id|fdx
op_amp
id|eorx
)paren
op_xor
id|bgx
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_iplan2p2_putcs
r_void
id|fbcon_iplan2p2_putcs
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
id|dest
comma
op_star
id|dest0
suffix:semicolon
id|u8
op_star
id|cdat
comma
id|c
suffix:semicolon
r_int
id|rows
suffix:semicolon
r_int
id|bytes
suffix:semicolon
id|u16
id|eorx
comma
id|fgx
comma
id|bgx
comma
id|fdx
suffix:semicolon
id|bytes
op_assign
id|p-&gt;next_line
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
(paren
id|xx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|xx
op_amp
l_int|1
)paren
suffix:semicolon
id|fgx
op_assign
id|expand2w
c_func
(paren
id|COLOR_2P
c_func
(paren
id|attr_fgcol
c_func
(paren
id|p
comma
op_star
id|s
)paren
)paren
)paren
suffix:semicolon
id|bgx
op_assign
id|expand2w
c_func
(paren
id|COLOR_2P
c_func
(paren
id|attr_bgcol
c_func
(paren
id|p
comma
op_star
id|s
)paren
)paren
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
(paren
id|c
op_star
id|p-&gt;fontheight
)paren
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
id|fdx
op_assign
id|dup2w
c_func
(paren
op_star
id|cdat
op_increment
)paren
suffix:semicolon
id|movepw
c_func
(paren
id|dest
comma
(paren
id|fdx
op_amp
id|eorx
)paren
op_xor
id|bgx
)paren
suffix:semicolon
)brace
id|INC_2P
c_func
(paren
id|dest0
)paren
suffix:semicolon
)brace
)brace
DECL|function|fbcon_iplan2p2_revc
r_void
id|fbcon_iplan2p2_revc
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
id|j
suffix:semicolon
r_int
id|bytes
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
(paren
id|xx
op_rshift
l_int|1
)paren
op_star
l_int|4
op_plus
(paren
id|xx
op_amp
l_int|1
)paren
suffix:semicolon
id|j
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|bytes
op_assign
id|p-&gt;next_line
suffix:semicolon
r_while
c_loop
(paren
id|j
op_decrement
)paren
(brace
multiline_comment|/*  This should really obey the individual character&squot;s&n;&t; *  background and foreground colors instead of simply&n;&t; *  inverting.&n;&t; */
id|dest
(braket
l_int|0
)braket
op_assign
op_complement
id|dest
(braket
l_int|0
)braket
suffix:semicolon
id|dest
(braket
l_int|2
)braket
op_assign
op_complement
id|dest
(braket
l_int|2
)braket
suffix:semicolon
id|dest
op_add_assign
id|bytes
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  `switch&squot; for the low level operations&n;     */
DECL|variable|fbcon_iplan2p2
r_struct
id|display_switch
id|fbcon_iplan2p2
op_assign
(brace
id|fbcon_iplan2p2_setup
comma
id|fbcon_iplan2p2_bmove
comma
id|fbcon_iplan2p2_clear
comma
id|fbcon_iplan2p2_putc
comma
id|fbcon_iplan2p2_putcs
comma
id|fbcon_iplan2p2_revc
comma
l_int|NULL
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
DECL|variable|fbcon_iplan2p2
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2
)paren
suffix:semicolon
DECL|variable|fbcon_iplan2p2_setup
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2_setup
)paren
suffix:semicolon
DECL|variable|fbcon_iplan2p2_bmove
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2_bmove
)paren
suffix:semicolon
DECL|variable|fbcon_iplan2p2_clear
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2_clear
)paren
suffix:semicolon
DECL|variable|fbcon_iplan2p2_putc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2_putc
)paren
suffix:semicolon
DECL|variable|fbcon_iplan2p2_putcs
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2_putcs
)paren
suffix:semicolon
DECL|variable|fbcon_iplan2p2_revc
id|EXPORT_SYMBOL
c_func
(paren
id|fbcon_iplan2p2_revc
)paren
suffix:semicolon
eof
