DECL|macro|__LIBRARY__
mdefine_line|#define __LIBRARY__
macro_line|#include &lt;unistd.h&gt;
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
l_string|&quot;int $0x80&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;b&quot;
(paren
id|exit_code
)paren
)paren
suffix:semicolon
)brace
eof
