multiline_comment|/* $Id: salone.c,v 1.1 1997/06/06 09:37:20 ralf Exp $&n; * salone.c: Routines to load into memory and execute stand-along&n; *           program images using ARCS PROM firmware.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;asm/sgialib.h&gt;
DECL|function|prom_load
r_int
id|prom_load
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|end
comma
r_int
r_int
op_star
id|pc
comma
r_int
r_int
op_star
id|eaddr
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|load
c_func
(paren
id|name
comma
id|end
comma
id|pc
comma
id|eaddr
)paren
suffix:semicolon
)brace
DECL|function|prom_invoke
r_int
id|prom_invoke
c_func
(paren
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|invoke
c_func
(paren
id|pc
comma
id|sp
comma
id|argc
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
)brace
DECL|function|prom_exec
r_int
id|prom_exec
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|exec
c_func
(paren
id|name
comma
id|argc
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
)brace
eof
