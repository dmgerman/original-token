macro_line|#ifndef _LINUX_MALLOC_H
DECL|macro|_LINUX_MALLOC_H
mdefine_line|#define _LINUX_MALLOC_H
macro_line|#include &lt;linux/mm.h&gt;
r_void
op_star
id|kmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|kfree
c_func
(paren
r_void
op_star
id|obj
)paren
suffix:semicolon
DECL|macro|kfree_s
mdefine_line|#define kfree_s(a,b) kfree(a)
macro_line|#endif /* _LINUX_MALLOC_H */
eof
