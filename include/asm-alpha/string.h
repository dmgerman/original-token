macro_line|#ifndef __ALPHA_STRING_H__
DECL|macro|__ALPHA_STRING_H__
mdefine_line|#define __ALPHA_STRING_H__
macro_line|#ifdef __KERNEL__
r_extern
r_void
op_star
id|__constant_c_memset
c_func
(paren
r_void
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memset
c_func
(paren
r_void
op_star
comma
r_char
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Ugh. Gcc uses &quot;bcopy()&quot; internally for structure assignments.&n; */
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY
multiline_comment|/*&n; * Define &quot;memcpy()&quot; to something else, otherwise gcc will&n; * corrupt that too into a &quot;bcopy&quot;.  Also, some day we might&n; * want to do a separate inlined constant-size memcpy (for 8&n; * and 16 byte user&lt;-&gt;kernel structure copying).&n; */
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
r_extern
r_void
op_star
id|__memcpy
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|memcpy
mdefine_line|#define memcpy __memcpy
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|memset
mdefine_line|#define memset(s, c, count) &bslash;&n;(__builtin_constant_p(c) ? &bslash;&n; __constant_c_memset((s),(0x0101010101010101UL*(unsigned char)c),(count)) : &bslash;&n; __memset((s),(c),(count)))
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_STRING_H__ */
eof
