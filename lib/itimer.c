multiline_comment|/*&n; *  linux/lib/itimer.c&n; *&n; *  (C) 1992  Darren Senn&n; */
DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;sys/time.h&gt;
id|_syscall2
c_func
(paren
r_int
comma
id|getitimer
comma
r_int
comma
id|which
comma
r_struct
id|itimerval
op_star
comma
id|value
)paren
id|_syscall3
c_func
(paren
r_int
comma
id|setitimer
comma
r_int
comma
id|which
comma
r_struct
id|itimerval
op_star
comma
id|value
comma
r_struct
id|itimerval
op_star
comma
id|ovalue
)paren
eof
