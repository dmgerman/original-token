multiline_comment|/*&n; *  linux/lib/open.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdarg.h&gt;
DECL|function|open
r_int
id|open
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|flag
comma
dot
dot
dot
)paren
(brace
r_register
r_int
id|res
suffix:semicolon
id|va_list
id|arg
suffix:semicolon
id|va_start
c_func
(paren
id|arg
comma
id|flag
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %2,%%ebx&bslash;n&bslash;t&quot;
l_string|&quot;int $0x80&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__NR_open
)paren
comma
l_string|&quot;g&quot;
(paren
(paren
r_int
)paren
(paren
id|filename
)paren
)paren
comma
l_string|&quot;c&quot;
(paren
id|flag
)paren
comma
l_string|&quot;d&quot;
(paren
id|va_arg
c_func
(paren
id|arg
comma
r_int
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ge
l_int|0
)paren
r_return
id|res
suffix:semicolon
id|errno
op_assign
op_minus
id|res
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof
