macro_line|#ifndef _STDDEF_H
DECL|macro|_STDDEF_H
mdefine_line|#define _STDDEF_H
macro_line|#ifndef _PTRDIFF_T
DECL|macro|_PTRDIFF_T
mdefine_line|#define _PTRDIFF_T
DECL|typedef|ptrdiff_t
r_typedef
r_int
r_int
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _SIZE_T
DECL|macro|_SIZE_T
mdefine_line|#define _SIZE_T
DECL|typedef|size_t
r_typedef
r_int
r_int
r_int
suffix:semicolon
macro_line|#endif
DECL|macro|NULL
macro_line|#undef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *)0)
DECL|macro|offsetof
mdefine_line|#define offsetof(TYPE, MEMBER) ((size_t) &amp;((TYPE *)0)-&gt;MEMBER)
macro_line|#endif
eof
