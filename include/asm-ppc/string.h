macro_line|#ifndef _PPC_STRING_H_
DECL|macro|_PPC_STRING_H_
mdefine_line|#define _PPC_STRING_H_
multiline_comment|/*&n; * keep things happy, the compile became unhappy since memset is&n; * in include/linux/string.h and lib/string.c with different prototypes&n; *                          -- Cort&n; */
macro_line|#if 1
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define  __HAVE_ARCH_MEMSET
DECL|function|memset
r_extern
id|__inline__
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|c
comma
id|__kernel_size_t
id|count
)paren
(brace
r_char
op_star
id|xs
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|xs
op_increment
op_assign
id|c
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|bzero
mdefine_line|#define bzero(addr,size) memset((addr),(int)(0),(size))
macro_line|#endif
eof
