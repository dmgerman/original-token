multiline_comment|/* printf.c:  Internal prom library printf facility.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* This routine is internal to the prom library, no one else should know&n; * about or use it!  It&squot;s simple and smelly anyway....&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|variable|hexstring
r_char
id|hexstring
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
r_void
DECL|function|prom_printf
id|prom_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
r_int
id|ui_val
suffix:semicolon
r_int
id|i_val
comma
id|n_ctr
suffix:semicolon
r_char
id|c_val
suffix:semicolon
r_char
id|nstr_buf
(braket
l_int|32
)braket
suffix:semicolon
r_char
op_star
id|s_val
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|fmt
)paren
(brace
r_if
c_cond
(paren
op_star
id|fmt
op_ne
l_char|&squot;%&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|prom_putchar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
id|prom_putchar
c_func
(paren
op_star
id|fmt
op_increment
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fmt
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|fmt
)paren
(brace
r_break
suffix:semicolon
)brace
id|n_ctr
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
id|c_val
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c_val
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|prom_putchar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
id|prom_putchar
c_func
(paren
id|c_val
)paren
suffix:semicolon
id|fmt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|s_val
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s_val
op_ne
l_int|0
)paren
(brace
id|prom_putchar
c_func
(paren
op_star
id|s_val
)paren
suffix:semicolon
id|s_val
op_increment
suffix:semicolon
)brace
id|fmt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
multiline_comment|/* Base 10 */
id|i_val
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i_val
op_eq
l_int|0x0
)paren
(brace
id|prom_putchar
c_func
(paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
id|i_val
op_ne
l_int|0x0
)paren
(brace
id|nstr_buf
(braket
id|n_ctr
)braket
op_assign
id|hexstring
(braket
id|i_val
op_mod
l_int|0xa
)braket
suffix:semicolon
id|i_val
op_assign
(paren
(paren
r_int
r_int
)paren
id|i_val
)paren
op_div
(paren
r_int
)paren
l_int|0xa
suffix:semicolon
id|n_ctr
op_increment
suffix:semicolon
)brace
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|n_ctr
op_ge
l_int|0
)paren
(brace
id|prom_putchar
c_func
(paren
id|nstr_buf
(braket
id|n_ctr
)braket
)paren
suffix:semicolon
)brace
id|fmt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
multiline_comment|/* Base 16 */
id|ui_val
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ui_val
op_eq
l_int|0x0
)paren
(brace
id|prom_putchar
c_func
(paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
id|ui_val
op_ne
l_int|0x0
)paren
(brace
id|nstr_buf
(braket
id|n_ctr
)braket
op_assign
id|hexstring
(braket
id|ui_val
op_mod
l_int|0x10
)braket
suffix:semicolon
id|ui_val
op_assign
(paren
(paren
r_int
r_int
)paren
id|ui_val
)paren
op_div
(paren
r_int
)paren
l_int|0x10
suffix:semicolon
id|n_ctr
op_increment
suffix:semicolon
)brace
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|n_ctr
op_ge
l_int|0
)paren
(brace
id|prom_putchar
c_func
(paren
id|nstr_buf
(braket
id|n_ctr
)braket
)paren
suffix:semicolon
)brace
id|fmt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;o&squot;
suffix:colon
multiline_comment|/* Base 8 */
id|ui_val
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ui_val
op_eq
l_int|0x0
)paren
(brace
id|prom_putchar
c_func
(paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
id|ui_val
op_ne
l_int|0x0
)paren
(brace
id|nstr_buf
(braket
id|n_ctr
)braket
op_assign
id|hexstring
(braket
id|ui_val
op_mod
l_int|0x8
)braket
suffix:semicolon
id|ui_val
op_assign
(paren
(paren
r_int
r_int
)paren
id|ui_val
)paren
op_div
(paren
r_int
)paren
l_int|0x8
suffix:semicolon
)brace
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|n_ctr
op_ge
l_int|0
)paren
(brace
id|prom_putchar
c_func
(paren
id|nstr_buf
(braket
id|n_ctr
)braket
)paren
suffix:semicolon
)brace
id|fmt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Uh oh, something we can&squot;t handle... skip it */
id|fmt
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* We are done... */
r_return
suffix:semicolon
)brace
eof