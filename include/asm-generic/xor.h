multiline_comment|/*&n; * include/asm-generic/xor.h&n; *&n; * Generic optimized RAID-5 checksumming functions.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
r_static
r_void
DECL|function|xor_8regs_2
id|xor_8regs_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|p1
(braket
l_int|0
)braket
op_xor_assign
id|p2
(braket
l_int|0
)braket
suffix:semicolon
id|p1
(braket
l_int|1
)braket
op_xor_assign
id|p2
(braket
l_int|1
)braket
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_xor_assign
id|p2
(braket
l_int|2
)braket
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_xor_assign
id|p2
(braket
l_int|3
)braket
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_xor_assign
id|p2
(braket
l_int|4
)braket
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_xor_assign
id|p2
(braket
l_int|5
)braket
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_xor_assign
id|p2
(braket
l_int|6
)braket
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_xor_assign
id|p2
(braket
l_int|7
)braket
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_8regs_3
id|xor_8regs_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|p1
(braket
l_int|0
)braket
op_xor_assign
id|p2
(braket
l_int|0
)braket
op_xor
id|p3
(braket
l_int|0
)braket
suffix:semicolon
id|p1
(braket
l_int|1
)braket
op_xor_assign
id|p2
(braket
l_int|1
)braket
op_xor
id|p3
(braket
l_int|1
)braket
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_xor_assign
id|p2
(braket
l_int|2
)braket
op_xor
id|p3
(braket
l_int|2
)braket
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_xor_assign
id|p2
(braket
l_int|3
)braket
op_xor
id|p3
(braket
l_int|3
)braket
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_xor_assign
id|p2
(braket
l_int|4
)braket
op_xor
id|p3
(braket
l_int|4
)braket
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_xor_assign
id|p2
(braket
l_int|5
)braket
op_xor
id|p3
(braket
l_int|5
)braket
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_xor_assign
id|p2
(braket
l_int|6
)braket
op_xor
id|p3
(braket
l_int|6
)braket
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_xor_assign
id|p2
(braket
l_int|7
)braket
op_xor
id|p3
(braket
l_int|7
)braket
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_8regs_4
id|xor_8regs_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|p1
(braket
l_int|0
)braket
op_xor_assign
id|p2
(braket
l_int|0
)braket
op_xor
id|p3
(braket
l_int|0
)braket
op_xor
id|p4
(braket
l_int|0
)braket
suffix:semicolon
id|p1
(braket
l_int|1
)braket
op_xor_assign
id|p2
(braket
l_int|1
)braket
op_xor
id|p3
(braket
l_int|1
)braket
op_xor
id|p4
(braket
l_int|1
)braket
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_xor_assign
id|p2
(braket
l_int|2
)braket
op_xor
id|p3
(braket
l_int|2
)braket
op_xor
id|p4
(braket
l_int|2
)braket
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_xor_assign
id|p2
(braket
l_int|3
)braket
op_xor
id|p3
(braket
l_int|3
)braket
op_xor
id|p4
(braket
l_int|3
)braket
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_xor_assign
id|p2
(braket
l_int|4
)braket
op_xor
id|p3
(braket
l_int|4
)braket
op_xor
id|p4
(braket
l_int|4
)braket
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_xor_assign
id|p2
(braket
l_int|5
)braket
op_xor
id|p3
(braket
l_int|5
)braket
op_xor
id|p4
(braket
l_int|5
)braket
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_xor_assign
id|p2
(braket
l_int|6
)braket
op_xor
id|p3
(braket
l_int|6
)braket
op_xor
id|p4
(braket
l_int|6
)braket
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_xor_assign
id|p2
(braket
l_int|7
)braket
op_xor
id|p3
(braket
l_int|7
)braket
op_xor
id|p4
(braket
l_int|7
)braket
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
id|p4
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_8regs_5
id|xor_8regs_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
id|p1
(braket
l_int|0
)braket
op_xor_assign
id|p2
(braket
l_int|0
)braket
op_xor
id|p3
(braket
l_int|0
)braket
op_xor
id|p4
(braket
l_int|0
)braket
op_xor
id|p5
(braket
l_int|0
)braket
suffix:semicolon
id|p1
(braket
l_int|1
)braket
op_xor_assign
id|p2
(braket
l_int|1
)braket
op_xor
id|p3
(braket
l_int|1
)braket
op_xor
id|p4
(braket
l_int|1
)braket
op_xor
id|p5
(braket
l_int|1
)braket
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_xor_assign
id|p2
(braket
l_int|2
)braket
op_xor
id|p3
(braket
l_int|2
)braket
op_xor
id|p4
(braket
l_int|2
)braket
op_xor
id|p5
(braket
l_int|2
)braket
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_xor_assign
id|p2
(braket
l_int|3
)braket
op_xor
id|p3
(braket
l_int|3
)braket
op_xor
id|p4
(braket
l_int|3
)braket
op_xor
id|p5
(braket
l_int|3
)braket
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_xor_assign
id|p2
(braket
l_int|4
)braket
op_xor
id|p3
(braket
l_int|4
)braket
op_xor
id|p4
(braket
l_int|4
)braket
op_xor
id|p5
(braket
l_int|4
)braket
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_xor_assign
id|p2
(braket
l_int|5
)braket
op_xor
id|p3
(braket
l_int|5
)braket
op_xor
id|p4
(braket
l_int|5
)braket
op_xor
id|p5
(braket
l_int|5
)braket
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_xor_assign
id|p2
(braket
l_int|6
)braket
op_xor
id|p3
(braket
l_int|6
)braket
op_xor
id|p4
(braket
l_int|6
)braket
op_xor
id|p5
(braket
l_int|6
)braket
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_xor_assign
id|p2
(braket
l_int|7
)braket
op_xor
id|p3
(braket
l_int|7
)braket
op_xor
id|p4
(braket
l_int|7
)braket
op_xor
id|p5
(braket
l_int|7
)braket
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
id|p4
op_add_assign
l_int|8
suffix:semicolon
id|p5
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_32regs_2
id|xor_32regs_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
r_register
r_int
id|d0
comma
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
id|d5
comma
id|d6
comma
id|d7
suffix:semicolon
id|d0
op_assign
id|p1
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Pull the stuff into registers&t;*/
id|d1
op_assign
id|p1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*  ... in bursts, if possible.&t;&t;*/
id|d2
op_assign
id|p1
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_assign
id|p1
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_assign
id|p1
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_assign
id|p1
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_assign
id|p1
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_assign
id|p1
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p2
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p2
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p2
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p2
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p2
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p2
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p2
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p2
(braket
l_int|7
)braket
suffix:semicolon
id|p1
(braket
l_int|0
)braket
op_assign
id|d0
suffix:semicolon
multiline_comment|/* Store the result (in burts)&t;&t;*/
id|p1
(braket
l_int|1
)braket
op_assign
id|d1
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_assign
id|d2
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_assign
id|d3
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_assign
id|d4
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_assign
id|d5
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_assign
id|d6
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_assign
id|d7
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_32regs_3
id|xor_32regs_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
r_register
r_int
id|d0
comma
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
id|d5
comma
id|d6
comma
id|d7
suffix:semicolon
id|d0
op_assign
id|p1
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Pull the stuff into registers&t;*/
id|d1
op_assign
id|p1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*  ... in bursts, if possible.&t;&t;*/
id|d2
op_assign
id|p1
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_assign
id|p1
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_assign
id|p1
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_assign
id|p1
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_assign
id|p1
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_assign
id|p1
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p2
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p2
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p2
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p2
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p2
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p2
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p2
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p2
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p3
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p3
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p3
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p3
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p3
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p3
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p3
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p3
(braket
l_int|7
)braket
suffix:semicolon
id|p1
(braket
l_int|0
)braket
op_assign
id|d0
suffix:semicolon
multiline_comment|/* Store the result (in burts)&t;&t;*/
id|p1
(braket
l_int|1
)braket
op_assign
id|d1
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_assign
id|d2
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_assign
id|d3
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_assign
id|d4
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_assign
id|d5
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_assign
id|d6
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_assign
id|d7
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_32regs_4
id|xor_32regs_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
r_register
r_int
id|d0
comma
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
id|d5
comma
id|d6
comma
id|d7
suffix:semicolon
id|d0
op_assign
id|p1
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Pull the stuff into registers&t;*/
id|d1
op_assign
id|p1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*  ... in bursts, if possible.&t;&t;*/
id|d2
op_assign
id|p1
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_assign
id|p1
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_assign
id|p1
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_assign
id|p1
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_assign
id|p1
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_assign
id|p1
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p2
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p2
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p2
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p2
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p2
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p2
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p2
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p2
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p3
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p3
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p3
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p3
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p3
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p3
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p3
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p3
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p4
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p4
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p4
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p4
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p4
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p4
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p4
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p4
(braket
l_int|7
)braket
suffix:semicolon
id|p1
(braket
l_int|0
)braket
op_assign
id|d0
suffix:semicolon
multiline_comment|/* Store the result (in burts)&t;&t;*/
id|p1
(braket
l_int|1
)braket
op_assign
id|d1
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_assign
id|d2
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_assign
id|d3
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_assign
id|d4
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_assign
id|d5
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_assign
id|d6
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_assign
id|d7
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
id|p4
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_32regs_5
id|xor_32regs_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
id|lines
op_assign
id|bytes
op_div
(paren
r_sizeof
(paren
r_int
)paren
)paren
op_div
l_int|8
suffix:semicolon
r_do
(brace
r_register
r_int
id|d0
comma
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
id|d5
comma
id|d6
comma
id|d7
suffix:semicolon
id|d0
op_assign
id|p1
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Pull the stuff into registers&t;*/
id|d1
op_assign
id|p1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*  ... in bursts, if possible.&t;&t;*/
id|d2
op_assign
id|p1
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_assign
id|p1
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_assign
id|p1
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_assign
id|p1
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_assign
id|p1
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_assign
id|p1
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p2
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p2
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p2
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p2
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p2
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p2
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p2
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p2
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p3
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p3
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p3
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p3
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p3
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p3
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p3
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p3
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p4
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p4
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p4
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p4
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p4
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p4
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p4
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p4
(braket
l_int|7
)braket
suffix:semicolon
id|d0
op_xor_assign
id|p5
(braket
l_int|0
)braket
suffix:semicolon
id|d1
op_xor_assign
id|p5
(braket
l_int|1
)braket
suffix:semicolon
id|d2
op_xor_assign
id|p5
(braket
l_int|2
)braket
suffix:semicolon
id|d3
op_xor_assign
id|p5
(braket
l_int|3
)braket
suffix:semicolon
id|d4
op_xor_assign
id|p5
(braket
l_int|4
)braket
suffix:semicolon
id|d5
op_xor_assign
id|p5
(braket
l_int|5
)braket
suffix:semicolon
id|d6
op_xor_assign
id|p5
(braket
l_int|6
)braket
suffix:semicolon
id|d7
op_xor_assign
id|p5
(braket
l_int|7
)braket
suffix:semicolon
id|p1
(braket
l_int|0
)braket
op_assign
id|d0
suffix:semicolon
multiline_comment|/* Store the result (in burts)&t;&t;*/
id|p1
(braket
l_int|1
)braket
op_assign
id|d1
suffix:semicolon
id|p1
(braket
l_int|2
)braket
op_assign
id|d2
suffix:semicolon
id|p1
(braket
l_int|3
)braket
op_assign
id|d3
suffix:semicolon
id|p1
(braket
l_int|4
)braket
op_assign
id|d4
suffix:semicolon
id|p1
(braket
l_int|5
)braket
op_assign
id|d5
suffix:semicolon
id|p1
(braket
l_int|6
)braket
op_assign
id|d6
suffix:semicolon
id|p1
(braket
l_int|7
)braket
op_assign
id|d7
suffix:semicolon
id|p1
op_add_assign
l_int|8
suffix:semicolon
id|p2
op_add_assign
l_int|8
suffix:semicolon
id|p3
op_add_assign
l_int|8
suffix:semicolon
id|p4
op_add_assign
l_int|8
suffix:semicolon
id|p5
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|lines
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|xor_block_8regs
r_static
r_struct
id|xor_block_template
id|xor_block_8regs
op_assign
(brace
id|name
suffix:colon
l_string|&quot;8regs&quot;
comma
id|do_2
suffix:colon
id|xor_8regs_2
comma
id|do_3
suffix:colon
id|xor_8regs_3
comma
id|do_4
suffix:colon
id|xor_8regs_4
comma
id|do_5
suffix:colon
id|xor_8regs_5
comma
)brace
suffix:semicolon
DECL|variable|xor_block_32regs
r_static
r_struct
id|xor_block_template
id|xor_block_32regs
op_assign
(brace
id|name
suffix:colon
l_string|&quot;32regs&quot;
comma
id|do_2
suffix:colon
id|xor_32regs_2
comma
id|do_3
suffix:colon
id|xor_32regs_3
comma
id|do_4
suffix:colon
id|xor_32regs_4
comma
id|do_5
suffix:colon
id|xor_32regs_5
comma
)brace
suffix:semicolon
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_8regs);&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_32regs);&t;&bslash;&n;&t;} while (0)
eof
