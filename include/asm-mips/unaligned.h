multiline_comment|/*&n; * Inline functions to do unaligned accesses.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_UNALIGNED_H
DECL|macro|__ASM_MIPS_UNALIGNED_H
mdefine_line|#define __ASM_MIPS_UNALIGNED_H
macro_line|#include &lt;asm/string.h&gt;
multiline_comment|/*&n; * Load quad unaligned.&n; */
DECL|function|ldq_u
r_extern
id|__inline__
r_int
r_int
id|ldq_u
c_func
(paren
r_int
r_int
r_int
op_star
id|__addr
)paren
(brace
r_int
r_int
r_int
id|__res
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;uld&bslash;t%0,(%1)&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__addr
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/*&n; * Load long unaligned.&n; */
DECL|function|ldl_u
r_extern
id|__inline__
r_int
r_int
id|ldl_u
c_func
(paren
r_int
r_int
op_star
id|__addr
)paren
(brace
r_int
r_int
id|__res
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;ulw&bslash;t%0,(%1)&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__addr
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/*&n; * Load word unaligned.&n; */
DECL|function|ldw_u
r_extern
id|__inline__
r_int
r_int
id|ldw_u
c_func
(paren
r_int
r_int
op_star
id|__addr
)paren
(brace
r_int
r_int
id|__res
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;ulh&bslash;t%0,(%1)&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__addr
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/*&n; * Store quad ununaligned.&n; */
DECL|function|stq_u
r_extern
id|__inline__
r_void
id|stq_u
c_func
(paren
r_int
r_int
id|__val
comma
r_int
r_int
r_int
op_star
id|__addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;usd&bslash;t%0,(%1)&quot;
suffix:colon
multiline_comment|/* No results */
suffix:colon
l_string|&quot;r&quot;
(paren
id|__val
)paren
comma
l_string|&quot;r&quot;
(paren
id|__addr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Store long ununaligned.&n; */
DECL|function|stl_u
r_extern
id|__inline__
r_void
id|stl_u
c_func
(paren
r_int
r_int
id|__val
comma
r_int
r_int
op_star
id|__addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;usw&bslash;t%0,(%1)&quot;
suffix:colon
multiline_comment|/* No results */
suffix:colon
l_string|&quot;r&quot;
(paren
id|__val
)paren
comma
l_string|&quot;r&quot;
(paren
id|__addr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Store word ununaligned.&n; */
DECL|function|stw_u
r_extern
id|__inline__
r_void
id|stw_u
c_func
(paren
r_int
r_int
id|__val
comma
r_int
r_int
op_star
id|__addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ush&bslash;t%0,(%1)&quot;
suffix:colon
multiline_comment|/* No results */
suffix:colon
l_string|&quot;r&quot;
(paren
id|__val
)paren
comma
l_string|&quot;r&quot;
(paren
id|__addr
)paren
)paren
suffix:semicolon
)brace
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memcpy(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memcpy((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
macro_line|#endif /* __ASM_MIPS_UNALIGNED_H */
eof
