multiline_comment|/*&n; *  linux/lib/_exit.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
macro_line|#include &lt;linux/unistd.h&gt;
DECL|function|_exit
r_volatile
r_void
id|_exit
c_func
(paren
r_int
id|exit_code
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;movl %1,%%ebx&bslash;n&bslash;t&quot;
l_string|&quot;int $0x80&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;g&quot;
(paren
id|exit_code
)paren
)paren
suffix:semicolon
)brace
eof
