multiline_comment|/*&n; *  linux/kernel/panic.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * This function is used through-out the kernel (includeinh mm and fs)&n; * to indicate a major problem.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
r_void
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* it&squot;s really int */
DECL|function|panic
r_volatile
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Kernel panic: %s&bslash;n&bslash;r&quot;
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current
op_eq
id|task
(braket
l_int|0
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;In swapper task - not syncing&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_else
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
eof
