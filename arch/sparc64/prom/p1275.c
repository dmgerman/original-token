multiline_comment|/* $Id: p1275.c,v 1.10 1997/06/27 04:18:30 davem Exp $&n; * p1275.c: Sun IEEE 1275 PROM low level interface routines&n; *&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/pstate.h&gt;
r_struct
(brace
DECL|member|prom_sync_routine
r_int
id|prom_sync_routine
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|prom_cif_handler
r_void
(paren
op_star
id|prom_cif_handler
)paren
(paren
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|prom_cif_stack
r_int
r_int
id|prom_cif_stack
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|prom_args
r_int
r_int
id|prom_args
(braket
l_int|23
)braket
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|prom_buffer
r_char
id|prom_buffer
(braket
l_int|3000
)braket
suffix:semicolon
DECL|variable|p1275buf
)brace
id|p1275buf
suffix:semicolon
DECL|function|prom_cif_interface
r_void
id|prom_cif_interface
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
"&quot;"
id|mov
op_mod
l_int|0
comma
op_mod
op_mod
id|o0
id|ldx
(braket
op_mod
op_mod
id|o0
op_plus
l_int|0x010
)braket
comma
op_mod
op_mod
id|o1
op_logical_neg
id|prom_cif_stack
id|save
op_mod
op_mod
id|o1
comma
op_minus
l_int|0xc0
comma
op_mod
op_mod
id|sp
id|ldx
(braket
op_mod
op_mod
id|i0
op_plus
l_int|0x008
)braket
comma
op_mod
op_mod
id|l2
op_logical_neg
id|prom_cif_handler
id|rdpr
op_mod
op_mod
id|pstate
comma
op_mod
op_mod
id|l4
id|mov
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|l0
id|mov
op_mod
op_mod
id|g6
comma
op_mod
op_mod
id|l1
id|wrpr
op_mod
op_mod
id|l4
comma
op_mod
l_int|1
comma
op_mod
op_mod
id|pstate
op_logical_neg
id|turn
id|on
id|address
id|masking
id|call
op_mod
op_mod
id|l2
id|add
op_mod
op_mod
id|i0
comma
l_int|0x018
comma
op_mod
op_mod
id|o0
op_logical_neg
id|prom_args
id|wrpr
op_mod
op_mod
id|l4
comma
l_int|0
comma
op_mod
op_mod
id|pstate
op_logical_neg
id|put
id|pstate
id|back
id|mov
op_mod
op_mod
id|l0
comma
op_mod
op_mod
id|g4
id|ret
id|restore
op_mod
op_mod
id|l1
comma
l_int|0
comma
op_mod
op_mod
id|g6
id|save
op_mod
op_mod
id|sp
comma
op_minus
l_int|0xc0
comma
op_mod
op_mod
id|sp
op_logical_neg
id|If
id|you
id|change
id|the
id|offset
id|of
id|the
id|save
id|rdpr
op_mod
op_mod
id|pstate
comma
op_mod
op_mod
id|l4
op_logical_neg
id|here
comma
id|please
id|change
id|the
l_int|0x8038
id|andn
op_mod
op_mod
id|l4
comma
op_mod
l_int|1
comma
op_mod
op_mod
id|l3
op_logical_neg
id|constant
id|below
id|as
id|well
id|wrpr
op_mod
op_mod
id|l3
comma
op_mod
op_mod
id|pstate
id|ldx
(braket
op_mod
op_mod
id|o0
op_plus
l_int|0x000
)braket
comma
op_mod
op_mod
id|l2
id|call
op_mod
op_mod
id|l2
id|nop
id|wrpr
op_mod
op_mod
id|l4
comma
l_int|0
comma
op_mod
op_mod
id|pstate
id|ret
id|restore
l_string|&quot; : : &quot;
id|r
l_string|&quot; (&amp;p1275buf), &quot;
id|i
"&quot;"
(paren
l_int|0
multiline_comment|/* PSTATE_AM */
)paren
)paren
suffix:semicolon
)brace
DECL|function|p1275_cmd
r_int
id|p1275_cmd
(paren
r_char
op_star
id|service
comma
r_int
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|nargs
comma
id|nrets
comma
id|i
suffix:semicolon
id|va_list
id|list
suffix:semicolon
r_int
id|attrs
comma
id|x
suffix:semicolon
r_int
id|ctx
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|p1275buf.prom_buffer
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ctx
op_assign
id|spitfire_get_primary_context
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx
)paren
(brace
id|flushw_user
(paren
)paren
suffix:semicolon
id|spitfire_set_primary_context
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|p1275buf.prom_args
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
multiline_comment|/* service */
id|strcpy
(paren
id|p
comma
id|service
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|strchr
(paren
id|p
comma
l_int|0
)paren
op_plus
l_int|8
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
l_int|1
)braket
op_assign
id|nargs
op_assign
(paren
id|fmt
op_amp
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* nargs */
id|p1275buf.prom_args
(braket
l_int|2
)braket
op_assign
id|nrets
op_assign
(paren
(paren
id|fmt
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* nrets */
id|attrs
op_assign
id|fmt
op_rshift
l_int|8
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|fmt
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
id|nargs
suffix:semicolon
id|i
op_increment
comma
id|attrs
op_rshift_assign
l_int|3
)paren
(brace
r_switch
c_cond
(paren
id|attrs
op_amp
l_int|0x7
)paren
(brace
r_case
id|P1275_ARG_NUMBER
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_STRING
suffix:colon
id|strcpy
(paren
id|p
comma
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|strchr
(paren
id|p
comma
l_int|0
)paren
op_plus
l_int|8
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_BUF
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|p
op_plus
(paren
r_int
)paren
id|x
op_plus
l_int|7
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_BUF
suffix:colon
id|q
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
id|memcpy
(paren
id|p
comma
id|q
comma
(paren
r_int
)paren
id|x
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|p
op_plus
(paren
r_int
)paren
id|x
op_plus
l_int|7
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_32B
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p
op_add_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_FUNCTION
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|prom_cif_interface
op_plus
l_int|0x38
suffix:semicolon
id|p1275buf.prom_sync_routine
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|prom_cif_interface
c_func
(paren
)paren
suffix:semicolon
id|attrs
op_assign
id|fmt
op_rshift
l_int|8
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|fmt
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
id|nargs
suffix:semicolon
id|i
op_increment
comma
id|attrs
op_rshift_assign
l_int|3
)paren
(brace
r_switch
c_cond
(paren
id|attrs
op_amp
l_int|0x7
)paren
(brace
r_case
id|P1275_ARG_NUMBER
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_STRING
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_FUNCTION
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_BUF
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_BUF
suffix:colon
id|p
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|memcpy
(paren
id|p
comma
(paren
r_char
op_star
)paren
(paren
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
)paren
comma
(paren
r_int
)paren
id|x
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_32B
suffix:colon
id|p
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|memcpy
(paren
id|p
comma
(paren
r_char
op_star
)paren
(paren
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
)paren
comma
l_int|32
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|x
op_assign
id|p1275buf.prom_args
(braket
id|nargs
op_plus
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ctx
)paren
id|spitfire_set_primary_context
(paren
id|ctx
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|function|prom_cif_init
r_void
id|prom_cif_init
c_func
(paren
r_void
op_star
id|cif_handler
comma
r_void
op_star
id|cif_stack
)paren
(brace
id|p1275buf.prom_cif_handler
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_int
op_star
)paren
)paren
id|cif_handler
suffix:semicolon
id|p1275buf.prom_cif_stack
op_assign
(paren
r_int
r_int
)paren
id|cif_stack
suffix:semicolon
)brace
eof
