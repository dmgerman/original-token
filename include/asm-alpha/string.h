macro_line|#ifndef __ALPHA_STRING_H
DECL|macro|__ALPHA_STRING_H
mdefine_line|#define __ALPHA_STRING_H
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
DECL|macro|memset
mdefine_line|#define memset(s, c, count) &bslash;&n;(__builtin_constant_p(c) ? &bslash;&n; __constant_c_memset((s),(0x01010101UL*(unsigned char)c),(count)) : &bslash;&n; __memset((s),(c),(count)))
macro_line|#endif
eof
