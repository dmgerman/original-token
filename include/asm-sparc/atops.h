multiline_comment|/* atops.h: Atomic SPARC operations.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ATOPS_H
DECL|macro|_SPARC_ATOPS_H
mdefine_line|#define _SPARC_ATOPS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
DECL|function|ldstub
r_extern
id|__inline__
id|__volatile__
r_int
r_char
id|ldstub
c_func
(paren
r_volatile
r_int
r_char
op_star
id|lock
)paren
(brace
r_volatile
r_int
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldstub [%1], %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|lock
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
