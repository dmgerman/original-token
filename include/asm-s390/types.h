multiline_comment|/*&n; *  include/asm-s390/types.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/types.h&quot;&n; */
macro_line|#ifndef _S390_TYPES_H
DECL|macro|_S390_TYPES_H
mdefine_line|#define _S390_TYPES_H
DECL|typedef|umode_t
r_typedef
r_int
r_int
id|umode_t
suffix:semicolon
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
multiline_comment|/* A address type so that arithmetic can be done on it &amp; it can be upgraded to&n;   64 bit when neccessary &n;*/
DECL|typedef|addr_t
r_typedef
id|__u32
id|addr_t
suffix:semicolon
DECL|typedef|saddr_t
r_typedef
id|__s32
id|saddr_t
suffix:semicolon
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
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
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 32
DECL|typedef|dma_addr_t
r_typedef
id|u32
id|dma_addr_t
suffix:semicolon
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
macro_line|#endif                                 /* __KERNEL__                       */
macro_line|#endif
eof
