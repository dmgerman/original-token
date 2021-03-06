multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_UNALIGNED_H
DECL|macro|_ASM_UNALIGNED_H
mdefine_line|#define _ASM_UNALIGNED_H
r_extern
r_void
id|__get_unaligned_bad_length
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_unaligned_bad_length
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Load quad unaligned.&n; */
DECL|function|__ldq_u
r_extern
r_inline
r_int
r_int
id|__ldq_u
c_func
(paren
r_const
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
l_string|&quot;uld&bslash;t%0,%1&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__addr
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/*&n; * Load long unaligned.&n; */
DECL|function|__ldl_u
r_extern
r_inline
r_int
r_int
id|__ldl_u
c_func
(paren
r_const
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
l_string|&quot;ulw&bslash;t%0,%1&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__addr
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/*&n; * Load word unaligned.&n; */
DECL|function|__ldw_u
r_extern
r_inline
r_int
r_int
id|__ldw_u
c_func
(paren
r_const
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
l_string|&quot;ulh&bslash;t%0,%1&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__addr
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
multiline_comment|/*&n; * Store quad ununaligned.&n; */
DECL|function|__stq_u
r_extern
r_inline
r_void
id|__stq_u
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
c_func
(paren
l_string|&quot;usd&bslash;t%1, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|__addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Store long ununaligned.&n; */
DECL|function|__stl_u
r_extern
r_inline
r_void
id|__stl_u
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
c_func
(paren
l_string|&quot;usw&bslash;t%1, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|__addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Store word ununaligned.&n; */
DECL|function|__stw_u
r_extern
r_inline
r_void
id|__stw_u
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
c_func
(paren
l_string|&quot;ush&bslash;t%1, %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|__addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * The main single-value unaligned transfer routines.&n; */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __val;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val = *(const unsigned char *)(ptr);&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val = __ldw_u((const unsigned short *)(ptr));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val = __ldl_u((const unsigned int *)(ptr));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val = __ldq_u((const unsigned long long *)(ptr));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_unaligned_bad_length();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__val;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val,ptr)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (sizeof(*(ptr))) {&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*(unsigned char *)(ptr) = (val);&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__stw_u((val), (unsigned short *)(ptr));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 4:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__stl_u((val), (unsigned int *)(ptr));&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 8:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__stq_u((val), (unsigned long long *)(ptr));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__put_unaligned_bad_length();&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#endif /* _ASM_UNALIGNED_H */
eof
