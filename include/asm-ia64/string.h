macro_line|#ifndef _ASM_IA64_STRING_H
DECL|macro|_ASM_IA64_STRING_H
mdefine_line|#define _ASM_IA64_STRING_H
multiline_comment|/*&n; * Here is where we want to put optimized versions of the string&n; * routines.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN&t;1 /* see arch/ia64/lib/strlen.S */
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET&t;1 /* see arch/ia64/lib/memset.S */
r_extern
id|__kernel_size_t
id|strlen
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memset
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_STRING_H */
eof
