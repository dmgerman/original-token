multiline_comment|/*&n; * This function is used through-out the kernel (includeinh mm and fs)&n; * to indicate a major problem.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
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
