macro_line|#ifndef _SPARC_TYPES_H
DECL|macro|_SPARC_TYPES_H
mdefine_line|#define _SPARC_TYPES_H
multiline_comment|/*&n; * _xx is ok: it doesn&squot;t pollute the POSIX namespace. Use these in the&n; * header files exported to user space   &lt;-- Linus sez this&n; */
multiline_comment|/* NOTE: I will have to change these when the V9 sparcs come into play,&n; *       however this won&squot;t be for a while.&n; */
macro_line|#ifndef _SIZE_T
DECL|macro|_SIZE_T
mdefine_line|#define _SIZE_T
macro_line|#ifdef __svr4__
DECL|typedef|size_t
r_typedef
r_int
r_int
r_int
suffix:semicolon
multiline_comment|/* solaris sucks */
macro_line|#else
DECL|typedef|size_t
r_typedef
r_int
r_int
r_int
r_int
suffix:semicolon
multiline_comment|/* sunos is much better */
macro_line|#endif /* !(__svr4__) */
macro_line|#endif
macro_line|#ifndef _SSIZE_T
DECL|macro|_SSIZE_T
mdefine_line|#define _SSIZE_T
DECL|typedef|ssize_t
r_typedef
r_int
id|ssize_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _PTRDIFF_T
DECL|macro|_PTRDIFF_T
mdefine_line|#define _PTRDIFF_T
DECL|typedef|ptrdiff_t
r_typedef
r_int
r_int
suffix:semicolon
macro_line|#endif
DECL|typedef|__s8
r_typedef
r_int
r_char
id|__s8
suffix:semicolon
DECL|typedef|__u8
r_typedef
r_int
r_char
id|__u8
suffix:semicolon
DECL|typedef|__s16
r_typedef
r_int
r_int
id|__s16
suffix:semicolon
DECL|typedef|__u16
r_typedef
r_int
r_int
id|__u16
suffix:semicolon
DECL|typedef|__s32
r_typedef
r_int
r_int
id|__s32
suffix:semicolon
DECL|typedef|__u32
r_typedef
r_int
r_int
id|__u32
suffix:semicolon
multiline_comment|/* Only 32-bit sparcs for now so.... */
DECL|typedef|__s64
r_typedef
r_int
r_int
r_int
id|__s64
suffix:semicolon
DECL|typedef|__u64
r_typedef
r_int
r_int
r_int
id|__u64
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|typedef|s8
r_typedef
r_int
r_char
id|s8
suffix:semicolon
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|s16
r_typedef
r_int
r_int
id|s16
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|s32
r_typedef
r_int
r_int
id|s32
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
multiline_comment|/* Again, only have to worry about 32-bits */
DECL|typedef|s64
r_typedef
r_int
r_int
r_int
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
r_int
r_int
r_int
id|u64
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* defined(_SPARC_TYPES_H) */
eof
