multiline_comment|/*&n; *  linux/lib/write.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/types.h&gt;
id|_syscall3
c_func
(paren
r_int
comma
id|write
comma
r_int
comma
id|fd
comma
r_const
r_char
op_star
comma
id|buf
comma
id|off_t
comma
id|count
)paren
eof
