multiline_comment|/* $Id: bootstr.c,v 1.11 1996/07/27 05:02:06 zaitcev Exp $&n; * bootstr.c:  Boot string/argument acquisition from the PROM.&n; *&n; * Copyright(C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|macro|BARG_LEN
mdefine_line|#define BARG_LEN  256
DECL|variable|barg_buf
r_static
r_char
id|barg_buf
(braket
id|BARG_LEN
)braket
suffix:semicolon
DECL|variable|fetched
r_static
r_char
id|fetched
op_assign
l_int|0
suffix:semicolon
r_char
op_star
DECL|function|prom_getbootargs
id|prom_getbootargs
c_func
(paren
r_void
)paren
(brace
r_int
id|iter
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|arg
suffix:semicolon
multiline_comment|/* This check saves us from a panic when bootfd patches args. */
r_if
c_cond
(paren
id|fetched
)paren
(brace
r_return
id|barg_buf
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
id|cp
op_assign
id|barg_buf
suffix:semicolon
multiline_comment|/* Start from 1 and go over fd(0,0,0)kernel */
r_for
c_loop
(paren
id|iter
op_assign
l_int|1
suffix:semicolon
id|iter
OL
l_int|8
suffix:semicolon
id|iter
op_increment
)paren
(brace
id|arg
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v0bootargs
)paren
)paren
op_member_access_from_pointer
id|argv
(braket
id|iter
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|arg
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Leave place for space and null. */
r_if
c_cond
(paren
id|cp
op_ge
id|barg_buf
op_plus
id|BARG_LEN
op_minus
l_int|2
)paren
(brace
multiline_comment|/* We might issue a warning here. */
r_break
suffix:semicolon
)brace
op_star
id|cp
op_increment
op_assign
op_star
id|arg
op_increment
suffix:semicolon
)brace
op_star
id|cp
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
multiline_comment|/*&n;&t;&t; * V3 PROM cannot supply as with more than 128 bytes&n;&t;&t; * of an argument. But a smart bootstrap loader can.&n;&t;&t; */
id|strncpy
c_func
(paren
id|barg_buf
comma
op_star
id|romvec-&gt;pv_v2bootargs.bootargs
comma
id|BARG_LEN
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_AP1000
suffix:colon
multiline_comment|/*&n;&t;   * Get message from host boot process.&n;&t;   */
macro_line|#if CONFIG_AP1000
id|ap_getbootargs
c_func
(paren
id|barg_buf
comma
id|BARG_LEN
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|fetched
op_assign
l_int|1
suffix:semicolon
r_return
id|barg_buf
suffix:semicolon
)brace
eof
