macro_line|#ifndef _ASM_MMX_H
DECL|macro|_ASM_MMX_H
mdefine_line|#define _ASM_MMX_H
multiline_comment|/*&n; *&t;MMX 3Dnow! helper operations&n; */
macro_line|#include &lt;linux/types.h&gt;
r_extern
r_void
op_star
id|_mmx_memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|mmx_clear_page
c_func
(paren
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|mmx_copy_page
c_func
(paren
r_int
id|to
comma
r_int
id|from
)paren
suffix:semicolon
macro_line|#endif
eof
