multiline_comment|/*&n;&t;kmod header&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_KMOD
r_extern
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#else
DECL|macro|request_module
mdefine_line|#define request_module(x) do {} while(0)
macro_line|#endif
eof
