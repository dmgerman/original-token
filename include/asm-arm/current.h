macro_line|#ifndef _ASMARM_CURRENT_H
DECL|macro|_ASMARM_CURRENT_H
mdefine_line|#define _ASMARM_CURRENT_H
multiline_comment|/* Old compilers seem to generate bad code if we allow `current&squot; to be&n;   non volatile.  */
macro_line|#if (__GNUC__ &gt; 2) || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &gt; 90)
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|__const__
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|function|get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|sp
id|asm
(paren
l_string|&quot;sp&quot;
)paren
suffix:semicolon
r_return
(paren
r_struct
id|task_struct
op_star
)paren
(paren
id|sp
op_amp
op_complement
l_int|0x1fff
)paren
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current (get_current())
macro_line|#endif /* _ASMARM_CURRENT_H */
eof
