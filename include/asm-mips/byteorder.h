macro_line|#ifndef __ASM_MIPS_BYTEORDER_H
DECL|macro|__ASM_MIPS_BYTEORDER_H
mdefine_line|#define __ASM_MIPS_BYTEORDER_H
multiline_comment|/*&n; * FIXME: Add big endian support&n; */
DECL|macro|ntohl
macro_line|#undef ntohl
DECL|macro|ntohs
macro_line|#undef ntohs
DECL|macro|htonl
macro_line|#undef htonl
DECL|macro|htons
macro_line|#undef htons
macro_line|#if defined (__MIPSEL__)
DECL|macro|__LITTLE_ENDIAN
mdefine_line|#define __LITTLE_ENDIAN
DECL|macro|__LITTLE_ENDIAN_BITFIELD
mdefine_line|#define __LITTLE_ENDIAN_BITFIELD
macro_line|#elif defined (__MIPSEB__)
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#else
macro_line|#error &quot;MIPS but neither __MIPSEL__ nor __MIPSEB__?&quot;
macro_line|#endif
r_extern
r_int
r_int
r_int
id|ntohl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|ntohs
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|htonl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|htons
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
r_int
id|__ntohl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
r_int
id|__ntohs
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
r_int
id|__constant_ntohl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
r_int
id|__constant_ntohs
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * The constant and non-constant versions here are the same.&n; * Maybe I&squot;ll come up with an mips-optimized routine for the&n; * non-constant ones (the constant ones don&squot;t need it: gcc&n; * will optimize it to the correct constant).  Oh, and the&n; * big endian routines that are still missing will be fairly&n; * easy to write :-)&n; */
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__ntohl
id|__ntohl
c_func
(paren
r_int
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
op_amp
l_int|0x000000ffU
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0x0000ff00U
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0x00ff0000U
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff000000U
)paren
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) &bslash;&n;&t;((unsigned long int)((((unsigned long int)(x) &amp; 0x000000ffU) &lt;&lt; 24) | &bslash;&n;&t;&t;&t;     (((unsigned long int)(x) &amp; 0x0000ff00U) &lt;&lt;  8) | &bslash;&n;&t;&t;&t;     (((unsigned long int)(x) &amp; 0x00ff0000U) &gt;&gt;  8) | &bslash;&n;&t;&t;&t;     (((unsigned long int)(x) &amp; 0xff000000U) &gt;&gt; 24)))
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__ntohs
id|__ntohs
c_func
(paren
r_int
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
op_amp
l_int|0x00ff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) &bslash;&n;&t;((unsigned short int)((((unsigned short int)(x) &amp; 0x00ff) &lt;&lt; 8) | &bslash;&n;&t;&t;&t;      (((unsigned short int)(x) &amp; 0xff00) &gt;&gt; 8))) &bslash;&n;
DECL|macro|__htonl
mdefine_line|#define __htonl(x) __ntohl(x)
DECL|macro|__htons
mdefine_line|#define __htons(x) __ntohs(x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) __constant_ntohl(x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) __constant_ntohs(x)
macro_line|#ifdef  __OPTIMIZE__
DECL|macro|ntohl
macro_line|#  define ntohl(x) &bslash;&n;(__builtin_constant_p((long)(x)) ? &bslash;&n; __constant_ntohl((x)) : &bslash;&n; __ntohl((x)))
DECL|macro|ntohs
macro_line|#  define ntohs(x) &bslash;&n;(__builtin_constant_p((short)(x)) ? &bslash;&n; __constant_ntohs((x)) : &bslash;&n; __ntohs((x)))
DECL|macro|htonl
macro_line|#  define htonl(x) &bslash;&n;(__builtin_constant_p((long)(x)) ? &bslash;&n; __constant_htonl((x)) : &bslash;&n; __htonl((x)))
DECL|macro|htons
macro_line|#  define htons(x) &bslash;&n;(__builtin_constant_p((short)(x)) ? &bslash;&n; __constant_htons((x)) : &bslash;&n; __htons((x)))
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_BYTEORDER_H */
eof
