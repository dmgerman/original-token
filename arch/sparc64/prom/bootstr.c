multiline_comment|/* $Id: bootstr.c,v 1.1 1996/12/27 08:49:10 jj Exp $&n; * bootstr.c:  Boot string/argument acquisition from the PROM.&n; *&n; * Copyright(C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright(C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
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
multiline_comment|/* This check saves us from a panic when bootfd patches args. */
r_if
c_cond
(paren
id|fetched
)paren
r_return
id|barg_buf
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_finddevice
(paren
l_string|&quot;/chosen&quot;
)paren
comma
l_string|&quot;bootargs&quot;
comma
id|barg_buf
comma
id|BARG_LEN
)paren
suffix:semicolon
id|fetched
op_assign
l_int|1
suffix:semicolon
r_return
id|barg_buf
suffix:semicolon
)brace
eof
