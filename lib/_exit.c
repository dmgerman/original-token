multiline_comment|/*&n; *  linux/lib/_exit.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
macro_line|#include &lt;linux/unistd.h&gt;
DECL|macro|exit
mdefine_line|#define exit __sys_exit
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
m_exit
)paren
DECL|macro|exit
macro_line|#undef exit
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
id|fake_volatile
suffix:colon
id|__sys_exit
c_func
(paren
)paren
suffix:semicolon
r_goto
id|fake_volatile
suffix:semicolon
)brace
eof
