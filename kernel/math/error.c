multiline_comment|/*&n; * linux/kernel/math/error.c&n; *&n; * (C) 1991 Linus Torvalds&n; */
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|function|math_error
r_void
id|math_error
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
)paren
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|last_task_used_math
comma
l_int|1
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fnclex&quot;
)paren
suffix:semicolon
)brace
eof
