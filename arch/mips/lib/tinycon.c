multiline_comment|/*&n; * arch/mips/lib/console.c&n; *&n; * Copyright (C) 1994 by Waldorf Electronic,&n; * written by Ralf Baechle and Andreas Busse&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive for&n; * more details.&n; *&n; * FIXME: This file is hacked to be hardwired for the Deskstation&n; *        Only thought as a debugging console output.  It&squot;s as inefficient&n; *        as a piece of code can be but probably a good piece of code to&n; *        implement a preliminary console for a new target.&n; */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|variable|size_x
r_static
r_int
r_int
id|size_x
suffix:semicolon
DECL|variable|size_y
r_static
r_int
r_int
id|size_y
suffix:semicolon
DECL|variable|cursor_x
r_static
r_int
r_int
id|cursor_x
suffix:semicolon
DECL|variable|cursor_y
r_static
r_int
r_int
id|cursor_y
suffix:semicolon
DECL|variable|vram_addr
r_static
r_volatile
r_int
r_int
op_star
id|vram_addr
suffix:semicolon
DECL|variable|console_needs_init
r_static
r_int
id|console_needs_init
op_assign
l_int|1
suffix:semicolon
r_extern
r_struct
id|screen_info
id|screen_info
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------&n; * init_console()&n; * ---------------------------------------------------------------------- */
DECL|function|init_console
r_void
id|init_console
c_func
(paren
r_void
)paren
(brace
id|size_x
op_assign
l_int|80
suffix:semicolon
id|size_y
op_assign
l_int|25
suffix:semicolon
id|cursor_x
op_assign
l_int|0
suffix:semicolon
id|cursor_y
op_assign
l_int|0
suffix:semicolon
id|vram_addr
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xb00b8000
suffix:semicolon
id|console_needs_init
op_assign
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|set_size_x
id|set_size_x
c_func
(paren
r_int
r_int
id|x
)paren
(brace
id|size_x
op_assign
id|x
suffix:semicolon
)brace
r_void
DECL|function|set_size_y
id|set_size_y
c_func
(paren
r_int
r_int
id|y
)paren
(brace
id|size_y
op_assign
id|y
suffix:semicolon
)brace
r_void
DECL|function|set_vram
id|set_vram
c_func
(paren
r_int
r_int
op_star
id|vram
)paren
(brace
id|vram_addr
op_assign
id|vram
suffix:semicolon
)brace
r_void
DECL|function|set_crsr
id|set_crsr
c_func
(paren
r_int
r_int
id|x
comma
r_int
r_int
id|y
)paren
(brace
id|cursor_x
op_assign
id|x
suffix:semicolon
id|cursor_y
op_assign
id|y
suffix:semicolon
)brace
r_void
DECL|function|print_char
id|print_char
c_func
(paren
r_int
r_int
id|x
comma
r_int
r_int
id|y
comma
r_int
r_char
id|c
)paren
(brace
r_volatile
r_int
r_int
op_star
id|caddr
suffix:semicolon
id|caddr
op_assign
id|vram_addr
op_plus
(paren
id|y
op_star
id|size_x
)paren
op_plus
id|x
suffix:semicolon
op_star
id|caddr
op_assign
(paren
op_star
id|caddr
op_amp
l_int|0xff00
)paren
op_or
l_int|0x0f00
op_or
(paren
r_int
r_int
)paren
id|c
suffix:semicolon
)brace
r_static
r_void
DECL|function|scroll
id|scroll
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|caddr
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
id|caddr
op_assign
id|vram_addr
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
id|size_x
op_star
(paren
id|size_y
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
(paren
id|caddr
op_increment
)paren
op_assign
op_star
(paren
id|caddr
op_plus
id|size_x
)paren
suffix:semicolon
)brace
multiline_comment|/* blank last line */
id|caddr
op_assign
id|vram_addr
op_plus
(paren
id|size_x
op_star
(paren
id|size_y
op_minus
l_int|1
)paren
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
id|size_x
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
(paren
id|caddr
op_increment
)paren
op_assign
(paren
op_star
id|caddr
op_amp
l_int|0xff00
)paren
op_or
(paren
r_int
r_int
)paren
l_char|&squot; &squot;
suffix:semicolon
)brace
)brace
DECL|function|print_string
r_void
id|print_string
c_func
(paren
r_const
r_int
r_char
op_star
id|str
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|console_needs_init
)paren
id|init_console
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|str
op_increment
)paren
)paren
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|cursor_x
op_assign
l_int|0
suffix:semicolon
id|cursor_y
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cursor_y
op_eq
id|size_y
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|cursor_y
op_assign
id|size_y
op_minus
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|print_char
c_func
(paren
id|cursor_x
comma
id|cursor_y
comma
id|c
)paren
suffix:semicolon
id|cursor_x
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cursor_x
op_eq
id|size_x
)paren
(brace
id|cursor_x
op_assign
l_int|0
suffix:semicolon
id|cursor_y
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cursor_y
op_eq
id|size_y
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|cursor_y
op_assign
id|size_y
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* end of file */
eof
