macro_line|#ifndef __ALPHA_STRING_H__
DECL|macro|__ALPHA_STRING_H__
mdefine_line|#define __ALPHA_STRING_H__
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * GCC of any recent vintage doesn&squot;t do stupid things with bcopy.&n; * EGCS-devel knows all about expanding memcpy inline, others don&squot;t.&n; *&n; * Similarly for a memset with data = 0.&n; */
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
multiline_comment|/* For backward compatibility with modules.  Unused otherwise.  */
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
macro_line|#if __GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 91
DECL|macro|memcpy
mdefine_line|#define memcpy __builtin_memcpy
macro_line|#endif
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
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
macro_line|#if __GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 91
DECL|macro|memset
mdefine_line|#define memset(s, c, n)&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;(__builtin_constant_p(c)&t;&t;&t;&t;&t;&t;    &bslash;&n; ? (__builtin_constant_p(n) &amp;&amp; (c) == 0&t;&t;&t;&t;&t;    &bslash;&n;    ? __builtin_memset((s),0,(n)) &t;&t;&t;&t;&t;    &bslash;&n;    : __constant_c_memset((s),0x0101010101010101UL*(unsigned char)(c),(n))) &bslash;&n; : __memset((s),(c),(n)))
macro_line|#else
DECL|macro|memset
mdefine_line|#define memset(s, c, n)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(__builtin_constant_p(c)&t;&t;&t;&t;&t;&t;&bslash;&n; ? __constant_c_memset((s),0x0101010101010101UL*(unsigned char)(c),(n)) &bslash;&n; : __memset((s),(c),(n)))
macro_line|#endif
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
DECL|macro|__HAVE_ARCH_STRCAT
mdefine_line|#define __HAVE_ARCH_STRCAT
DECL|macro|__HAVE_ARCH_STRNCAT
mdefine_line|#define __HAVE_ARCH_STRNCAT
DECL|macro|__HAVE_ARCH_STRCHR
mdefine_line|#define __HAVE_ARCH_STRCHR
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_STRING_H__ */
eof
