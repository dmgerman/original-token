multiline_comment|/*&n; * When in kernel-mode, we cannot use printf, as fs is liable to&n; * point to &squot;interesting&squot; things. Make a printf with fs-saving, and&n; * all is well.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|variable|buf
r_static
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|printk
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;push %%fs&bslash;n&bslash;t&quot;
l_string|&quot;push %%ds&bslash;n&bslash;t&quot;
l_string|&quot;pop %%fs&bslash;n&bslash;t&quot;
l_string|&quot;pushl %0&bslash;n&bslash;t&quot;
l_string|&quot;pushl $_buf&bslash;n&bslash;t&quot;
l_string|&quot;pushl $0&bslash;n&bslash;t&quot;
l_string|&quot;call _tty_write&bslash;n&bslash;t&quot;
l_string|&quot;addl $8,%%esp&bslash;n&bslash;t&quot;
l_string|&quot;popl %0&bslash;n&bslash;t&quot;
l_string|&quot;pop %%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
