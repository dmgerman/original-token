macro_line|#ifndef __ASM_MIPS_TYPES_H
DECL|macro|__ASM_MIPS_TYPES_H
mdefine_line|#define __ASM_MIPS_TYPES_H
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
multiline_comment|/*&n; * __xx is ok: it doesn&squot;t pollute the POSIX namespace. Use these in the&n; * header files exported to user space&n; */
DECL|typedef|__s8
r_typedef
id|__signed__
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
id|__signed__
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
id|__signed__
r_int
id|__s32
suffix:semicolon
DECL|typedef|__u32
r_typedef
r_int
r_int
id|__u32
suffix:semicolon
macro_line|#if ((~0UL) == 0xffffffff)
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__)
DECL|typedef|__s64
r_typedef
id|__signed__
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
macro_line|#endif
macro_line|#else
DECL|typedef|__s64
r_typedef
id|__signed__
r_int
id|__s64
suffix:semicolon
DECL|typedef|__u64
r_typedef
r_int
r_int
id|__u64
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
macro_line|#ifdef __KERNEL__
DECL|typedef|s8
r_typedef
id|__signed
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
id|__signed
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
id|__signed
r_int
id|s32
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
macro_line|#if ((~0UL) == 0xffffffff)
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__)
DECL|typedef|s64
r_typedef
id|__signed__
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
macro_line|#endif
macro_line|#else
DECL|typedef|s64
r_typedef
id|__signed__
r_int
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
r_int
r_int
id|u64
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * These definitions double the definitions from &lt;gnu/types.h&gt;.&n; */
DECL|macro|__FDELT
macro_line|#undef  __FDELT
DECL|macro|__FDELT
mdefine_line|#define __FDELT(d)      ((d) / __NFDBITS)
DECL|macro|__FDMASK
macro_line|#undef  __FDMASK
DECL|macro|__FDMASK
mdefine_line|#define __FDMASK(d)     (1 &lt;&lt; ((d) % __NFDBITS))
DECL|macro|__FD_SET
macro_line|#undef  __FD_SET
DECL|macro|__FD_SET
mdefine_line|#define __FD_SET(d, set)        ((set)-&gt;fds_bits[__FDELT(d)] |= __FDMASK(d))
DECL|macro|__FD_CLR
macro_line|#undef  __FD_CLR
DECL|macro|__FD_CLR
mdefine_line|#define __FD_CLR(d, set)        ((set)-&gt;fds_bits[__FDELT(d)] &amp;= ~__FDMASK(d))
DECL|macro|__FD_ISSET
macro_line|#undef  __FD_ISSET
DECL|macro|__FD_ISSET
mdefine_line|#define __FD_ISSET(d, set)      ((set)-&gt;fds_bits[__FDELT(d)] &amp; __FDMASK(d))
DECL|macro|__FD_ZERO
macro_line|#undef  __FD_ZERO
DECL|macro|__FD_ZERO
mdefine_line|#define __FD_ZERO(fdsetp) (memset (fdsetp, 0, sizeof(*(fd_set *)fdsetp)))
macro_line|#endif /* __ASM_MIPS_TYPES_H */
eof
