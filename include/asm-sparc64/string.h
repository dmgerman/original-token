multiline_comment|/* $Id: string.h,v 1.5 1997/05/18 04:16:57 davem Exp $&n; * string.h: External definitions for optimized assembly string&n; *           routines for the Linux Kernel.&n; *&n; * Copyright (C) 1995,1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef __SPARC64_STRING_H__
DECL|macro|__SPARC64_STRING_H__
mdefine_line|#define __SPARC64_STRING_H__
multiline_comment|/* Really, userland/ksyms should not see any of this stuff. */
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|__memmove
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
id|__kernel_size_t
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
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
id|__kernel_size_t
id|__memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#ifndef EXPORT_SYMTAB
multiline_comment|/* First the mem*() things. */
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
DECL|macro|memmove
macro_line|#undef memmove
DECL|macro|memmove
mdefine_line|#define memmove(_to, _from, _n) &bslash;&n;({ &bslash;&n;&t;void *_t = (_to); &bslash;&n;&t;__memmove(_t, (_from), (_n)); &bslash;&n;&t;_t; &bslash;&n;})
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
DECL|function|__constant_memcpy
r_extern
r_inline
r_void
op_star
id|__constant_memcpy
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
id|__kernel_size_t
id|n
)paren
(brace
r_extern
r_void
id|__copy_1page
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
r_if
c_cond
(paren
id|n
op_le
l_int|32
)paren
(brace
id|__builtin_memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if 0
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|8192
suffix:colon
id|__copy_1page
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#endif
id|__memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
macro_line|#if 0
r_break
suffix:semicolon
)brace
macro_line|#endif
)brace
)brace
r_return
id|to
suffix:semicolon
)brace
DECL|function|__nonconstant_memcpy
r_extern
r_inline
r_void
op_star
id|__nonconstant_memcpy
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
id|__kernel_size_t
id|n
)paren
(brace
id|__memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
id|to
suffix:semicolon
)brace
DECL|macro|memcpy
macro_line|#undef memcpy
DECL|macro|memcpy
mdefine_line|#define memcpy(t, f, n) &bslash;&n;(__builtin_constant_p(n) ? &bslash;&n; __constant_memcpy((t),(f),(n)) : &bslash;&n; __nonconstant_memcpy((t),(f),(n)))
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|function|__constant_c_and_count_memset
r_extern
r_inline
r_void
op_star
id|__constant_c_and_count_memset
c_func
(paren
r_void
op_star
id|s
comma
r_char
id|c
comma
id|__kernel_size_t
id|count
)paren
(brace
r_extern
r_void
op_star
id|bzero_1page
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
id|__kernel_size_t
id|__bzero
c_func
(paren
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|count
op_eq
l_int|8192
)paren
(brace
id|bzero_1page
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|__bzero
c_func
(paren
id|s
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
id|__memset
c_func
(paren
id|s
comma
id|c
comma
id|count
)paren
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|__constant_c_memset
r_extern
r_inline
r_void
op_star
id|__constant_c_memset
c_func
(paren
r_void
op_star
id|s
comma
r_char
id|c
comma
id|__kernel_size_t
id|count
)paren
(brace
r_extern
id|__kernel_size_t
id|__bzero
c_func
(paren
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|__bzero
c_func
(paren
id|s
comma
id|count
)paren
suffix:semicolon
)brace
r_else
id|__memset
c_func
(paren
id|s
comma
id|c
comma
id|count
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|__nonconstant_memset
r_extern
r_inline
r_void
op_star
id|__nonconstant_memset
c_func
(paren
r_void
op_star
id|s
comma
r_char
id|c
comma
id|__kernel_size_t
id|count
)paren
(brace
id|__memset
c_func
(paren
id|s
comma
id|c
comma
id|count
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|macro|memset
macro_line|#undef memset
DECL|macro|memset
mdefine_line|#define memset(s, c, count) &bslash;&n;(__builtin_constant_p(c) ? (__builtin_constant_p(count) ? &bslash;&n;                            __constant_c_and_count_memset((s), (c), (count)) : &bslash;&n;                            __constant_c_memset((s), (c), (count))) &bslash;&n;                          : __nonconstant_memset((s), (c), (count)))
DECL|macro|__HAVE_ARCH_MEMSCAN
mdefine_line|#define __HAVE_ARCH_MEMSCAN
DECL|macro|memscan
macro_line|#undef memscan
DECL|macro|memscan
mdefine_line|#define memscan(__arg0, __char, __arg2)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern void *__memscan_zero(void *, size_t);&t;&t;&t;&t;&bslash;&n;&t;extern void *__memscan_generic(void *, int, size_t);&t;&t;&t;&bslash;&n;&t;void *__retval, *__addr = (__arg0);&t;&t;&t;&t;&t;&bslash;&n;&t;size_t __size = (__arg2);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(__builtin_constant_p(__char) &amp;&amp; !(__char))&t;&t;&t;&t;&bslash;&n;&t;&t;__retval = __memscan_zero(__addr, __size);&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__retval = __memscan_generic(__addr, (__char), __size);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__retval;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__HAVE_ARCH_MEMCMP
mdefine_line|#define __HAVE_ARCH_MEMCMP
multiline_comment|/* Now the str*() stuff... */
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
DECL|macro|__HAVE_ARCH_STRNCMP
mdefine_line|#define __HAVE_ARCH_STRNCMP
r_extern
r_int
id|__strncmp
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|function|__constant_strncmp
r_extern
r_inline
r_int
id|__constant_strncmp
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_const
r_char
op_star
id|dest
comma
id|__kernel_size_t
id|count
)paren
(brace
r_register
r_int
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|count
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
(paren
id|src
(braket
l_int|0
)braket
op_minus
id|dest
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
id|retval
op_assign
(paren
id|src
(braket
l_int|0
)braket
op_minus
id|dest
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|0
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|1
)braket
op_minus
id|dest
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
r_case
l_int|3
suffix:colon
id|retval
op_assign
(paren
id|src
(braket
l_int|0
)braket
op_minus
id|dest
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|0
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|1
)braket
op_minus
id|dest
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|1
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|2
)braket
op_minus
id|dest
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
r_case
l_int|4
suffix:colon
id|retval
op_assign
(paren
id|src
(braket
l_int|0
)braket
op_minus
id|dest
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|0
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|1
)braket
op_minus
id|dest
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|1
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|2
)braket
op_minus
id|dest
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|2
)braket
)paren
id|retval
op_assign
(paren
id|src
(braket
l_int|3
)braket
op_minus
id|dest
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
r_case
l_int|5
suffix:colon
id|retval
op_assign
(paren
id|src
(braket
l_int|0
)braket
op_minus
id|dest
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|0
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|1
)braket
op_minus
id|dest
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|1
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|2
)braket
op_minus
id|dest
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|2
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|3
)braket
op_minus
id|dest
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|3
)braket
)paren
id|retval
op_assign
(paren
id|src
(braket
l_int|4
)braket
op_minus
id|dest
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
(paren
id|src
(braket
l_int|0
)braket
op_minus
id|dest
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|0
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|1
)braket
op_minus
id|dest
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|1
)braket
)paren
(brace
id|retval
op_assign
(paren
id|src
(braket
l_int|2
)braket
op_minus
id|dest
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|src
(braket
l_int|2
)braket
)paren
(brace
id|retval
op_assign
id|__strncmp
c_func
(paren
id|src
op_plus
l_int|3
comma
id|dest
op_plus
l_int|3
comma
id|count
op_minus
l_int|3
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
)brace
DECL|macro|strncmp
macro_line|#undef strncmp
DECL|macro|strncmp
mdefine_line|#define strncmp(__arg0, __arg1, __arg2)&t;&bslash;&n;(__builtin_constant_p(__arg2) ?&t;&bslash;&n; __constant_strncmp(__arg0, __arg1, __arg2) : &bslash;&n; __strncmp(__arg0, __arg1, __arg2))
macro_line|#endif /* !EXPORT_SYMTAB */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(__SPARC64_STRING_H__) */
eof