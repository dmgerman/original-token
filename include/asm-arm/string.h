macro_line|#ifndef __ASM_ARM_STRING_H
DECL|macro|__ASM_ARM_STRING_H
mdefine_line|#define __ASM_ARM_STRING_H
multiline_comment|/*&n; * inline versions, hmm...&n; */
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR
r_extern
r_char
op_star
id|strrchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_STRCHR
mdefine_line|#define __HAVE_ARCH_STRCHR
r_extern
r_char
op_star
id|strchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|__HAVE_ARCH_MEMZERO
mdefine_line|#define __HAVE_ARCH_MEMZERO
r_extern
r_void
id|memzero
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|memsetl
(paren
r_int
r_int
op_star
comma
r_int
r_int
comma
r_int
id|n
)paren
suffix:semicolon
macro_line|#endif
eof
