macro_line|#ifndef _PPC_STRING_H_
DECL|macro|_PPC_STRING_H_
mdefine_line|#define _PPC_STRING_H_
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP
DECL|macro|__HAVE_ARCH_STRCAT
mdefine_line|#define __HAVE_ARCH_STRCAT
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
DECL|macro|__HAVE_ARCH_MEMCMP
mdefine_line|#define __HAVE_ARCH_MEMCMP
DECL|macro|__HAVE_ARCH_MEMCHR
mdefine_line|#define __HAVE_ARCH_MEMCHR
multiline_comment|/*#define bzero(addr,size) memset((addr),(int)(0),(size))*/
DECL|function|memchr
r_extern
r_inline
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
id|cs
comma
r_int
id|c
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ne
id|i
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
)paren
id|c
op_eq
op_star
(paren
r_char
op_star
)paren
(paren
id|cs
op_plus
id|i
)paren
)paren
r_return
(paren
r_void
op_star
)paren
(paren
id|cs
op_plus
id|i
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
