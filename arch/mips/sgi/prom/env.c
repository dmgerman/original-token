multiline_comment|/* $Id: env.c,v 1.1 1997/06/06 09:36:59 ralf Exp $&n; * env.c: ARCS environment variable routines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
DECL|function|prom_getenv
r_char
op_star
id|prom_getenv
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|get_evar
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
DECL|function|prom_setenv
r_int
id|prom_setenv
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|value
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|set_evar
c_func
(paren
id|name
comma
id|value
)paren
suffix:semicolon
)brace
eof
