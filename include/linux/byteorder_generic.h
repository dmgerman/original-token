macro_line|#ifndef _LINUX_BYTEORDER_GENERIC_H
DECL|macro|_LINUX_BYTEORDER_GENERIC_H
mdefine_line|#define _LINUX_BYTEORDER_GENERIC_H
multiline_comment|/*&n; * linux/byteorder_generic.h&n; * Generic Byteswap support&n; *&n; * Francois-Rene Rideau &lt;rideau@ens.fr&gt; 19970707&n; *    gathered all the good ideas from all asm-foo/byteorder.h into one file,&n; *    cleaned them up.&n; *    I hope it is compliant with non-GCC compilers.&n; *    I decided to put __BYTEORDER_HAS_U64__ in byteorder.h,&n; *    because I wasn&squot;t sure it would be ok to put it in types.h&n; *    Upgraded it to 2.1.43&n; * Francois-Rene Rideau &lt;rideau@ens.fr&gt; 19971012&n; *    Upgraded it to 2.1.57&n; *    to please Linus T., replaced huge #ifdef&squot;s between little/big endian&n; *    by nestedly #include&squot;d files.&n; *&n; * TODO:&n; *   = Regular kernel maintainers could also replace all these manual&n; *    byteswap macros that remain, disseminated among drivers,&n; *    after some grep or the sources...&n; *   = Linus might want to rename all these macros and files to fit his taste,&n; *    to fit his personal naming scheme.&n; *   = it seems that many drivers would also appreciate&n; *    nybble swapping support...&n; *   = every architecture could add their byteswap macro in asm/byteorder.h&n; *    see how some architectures already do (i386, alpha, ppc, etc)&n; */
multiline_comment|/*&n; * This file is included by both &lt;linux/byteorder_little_endian.h&gt; and&n; * &lt;linux/byteorder_big_endian.h&gt;. People porting from machines with&n; * bizarre bytedisorder (like the VAX?) will have to write a different one.&n; * Actually, this file mostly does byteswapping, and could be named&n; * &lt;byteswap.h&gt; or &lt;swab.h&gt; rather than &lt;linux/byteorder_generic.h&gt;&n; *&n; */
multiline_comment|/*&n; * The following macros are to be defined by &lt;asm/byteorder.h&gt;:&n; *&n; * Conversion of long and short int between network and host format&n; *&t;ntohl(__u32 x)&n; *&t;ntohs(__u16 x)&n; *&t;htonl(__u32 x)&n; *&t;htons(__u16 x)&n; * It seems that some programs (which? where? or perhaps a standard? POSIX?)&n; * might like the above to be functions, not macros (why?).&n; * if that&squot;s true, then detect them, and take measures.&n; * Anyway, the measure is: define only ___ntohl as a macro instead,&n; * and in a separate file, have&n; * unsigned long inline ntohl(x){return ___ntohl(x);}&n; *&n; * The same for constant arguments&n; *&t;__constant_ntohl(__u32 x)&n; *&t;__constant_ntohs(__u16 x)&n; *&t;__constant_htonl(__u32 x)&n; *&t;__constant_htons(__u16 x)&n; *&n; * Conversion of XX-bit integers (16- 32- or 64-)&n; * between native cpu format and little/big endian format&n; * 64-bit stuff only defined for proper architectures&n; *&t;cpu_to_[bl]eXX(__uXX x)&n; *&t;[bl]eXX_to_cpu(__uXX x)&n; *&n; * The same, but takes a pointer to the value to convert&n; *&t;cpu_to_[bl]eXXp(__uXX x)&n; *&t;[bl]eXX_to_cpup(__uXX x)&n; *&n; * The same, but change in situ&n; *&t;cpu_to_[bl]eXXs(__uXX x)&n; *&t;[bl]eXX_to_cpus(__uXX x)&n; *&n; * Byteswapping, independently from cpu endianness&n; *&t;swabXX[ps]?(foo)&n; *&n; *&n; * See asm-foo/byteorder.h for examples of how to provide&n; * architecture-optimized versions&n; *&n; */
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * Generic byte swapping routines. We fall back on&n; * these if we don&squot;t have any optimized code, and&n; * when we have constants that we want the compiler&n; * to byte swap for us..&n; */
DECL|macro|___swab16
mdefine_line|#define ___swab16(x) &bslash;&n;&t;((__u16)( &bslash;&n;&t;&t;(((__u16)(x) &amp; 0x00ffU) &lt;&lt; 8) | &bslash;&n;&t;&t;(((__u16)(x) &amp; 0xff00U) &gt;&gt; 8) ))
DECL|macro|___swab32
mdefine_line|#define ___swab32(x) &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x000000ffUL) &lt;&lt; 24) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x0000ff00UL) &lt;&lt;  8) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x00ff0000UL) &gt;&gt;  8) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0xff000000UL) &gt;&gt; 24) ))
DECL|macro|___swab64
mdefine_line|#define ___swab64(x) &bslash;&n;&t;((__u64)( &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x00000000000000ffULL) &lt;&lt; 56) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x000000000000ff00ULL) &lt;&lt; 40) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x0000000000ff0000ULL) &lt;&lt; 24) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x00000000ff000000ULL) &lt;&lt;  8) | &bslash;&n;&t;        (__u64)(((__u64)(x) &amp; (__u64)0x000000ff00000000ULL) &gt;&gt;  8) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x0000ff0000000000ULL) &gt;&gt; 24) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x00ff000000000000ULL) &gt;&gt; 40) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0xff00000000000000ULL) &gt;&gt; 56) ))
multiline_comment|/*&n; * These do constant folding - this allows the&n; * compiler to do any constants at compile&n; * time.  Any architecture inline asm optimizations&n; * would be pessimizations.&n; */
DECL|macro|__swab16
mdefine_line|#define __swab16(x) &bslash;&n;&t;(__builtin_constant_p((__u16)(x)) ? &bslash;&n;&t; ___swab16((x)) : __fswab16((x)))
DECL|macro|__swab32
mdefine_line|#define __swab32(x) &bslash;&n;&t;(__builtin_constant_p((__u32)(x)) ? &bslash;&n;&t; ___swab32((x)) : __fswab32((x)))
DECL|macro|__swab64
mdefine_line|#define __swab64(x) &bslash;&n;&t;(__builtin_constant_p((__u64)(x)) ? &bslash;&n;&t; ___swab64((x)) : __fswab64((x)))
multiline_comment|/*&n; * provide defaults when no architecture-specific optimization is detected&n; */
macro_line|#ifndef __arch__swab16
DECL|macro|__arch__swab16
macro_line|#  define __arch__swab16(x) ___swab16(x)
macro_line|#endif
macro_line|#ifndef __arch__swab32
DECL|macro|__arch__swab32
macro_line|#  define __arch__swab32(x) ___swab32(x)
macro_line|#endif
macro_line|#ifndef __arch__swab64
DECL|macro|__arch__swab64
macro_line|#  define __arch__swab64(x) ___swab64(x)
macro_line|#endif
macro_line|#ifndef __arch__swab16p
DECL|macro|__arch__swab16p
macro_line|#  define __arch__swab16p(x) __swab16(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swab32p
DECL|macro|__arch__swab32p
macro_line|#  define __arch__swab32p(x) __swab32(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swab64p
DECL|macro|__arch__swab64p
macro_line|#  define __arch__swab64p(x) __swab64(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swab16s
DECL|macro|__arch__swab16s
macro_line|#  define __arch__swab16s(x) *(x) = __swab16p((x))
macro_line|#endif
macro_line|#ifndef __arch__swab32s
DECL|macro|__arch__swab32s
macro_line|#  define __arch__swab32s(x) *(x) = __swab32p((x))
macro_line|#endif
macro_line|#ifndef __arch__swab64s
DECL|macro|__arch__swab64s
macro_line|#  define __arch__swab64s(x) *(x) = __swab64p((x))
macro_line|#endif
DECL|function|__fswab16
r_extern
id|__inline__
id|__const__
id|__u16
id|__fswab16
c_func
(paren
id|__u16
id|x
)paren
(brace
r_return
id|__arch__swab16
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab16p
r_extern
id|__inline__
id|__u16
id|__swab16p
c_func
(paren
id|__u16
op_star
id|x
)paren
(brace
r_return
id|__arch__swab16p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab16s
r_extern
id|__inline__
r_void
id|__swab16s
c_func
(paren
id|__u16
op_star
id|addr
)paren
(brace
id|__arch__swab16s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__fswab32
r_extern
id|__inline__
id|__const__
id|__u32
id|__fswab32
c_func
(paren
id|__u32
id|x
)paren
(brace
r_return
id|__arch__swab32
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab32p
r_extern
id|__inline__
id|__u32
id|__swab32p
c_func
(paren
id|__u32
op_star
id|x
)paren
(brace
r_return
id|__arch__swab32p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab32s
r_extern
id|__inline__
r_void
id|__swab32s
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
id|__arch__swab32s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#ifdef __BYTEORDER_HAS_U64__
DECL|function|__fswab64
r_extern
id|__inline__
id|__const__
id|__u64
id|__fswab64
c_func
(paren
id|__u64
id|x
)paren
(brace
macro_line|#  ifdef __SWAB_64_THRU_32__
id|__u32
id|h
op_assign
id|x
op_rshift
l_int|32
suffix:semicolon
id|__u32
id|l
op_assign
id|x
op_amp
(paren
(paren
l_int|1ULL
op_lshift
l_int|32
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
id|__u64
)paren
id|__swab32
c_func
(paren
id|l
)paren
)paren
op_lshift
l_int|32
)paren
op_or
(paren
(paren
id|__u64
)paren
(paren
id|__swab32
c_func
(paren
id|h
)paren
)paren
)paren
suffix:semicolon
macro_line|#  else
r_return
id|__arch__swab64
c_func
(paren
id|x
)paren
suffix:semicolon
macro_line|#  endif
)brace
DECL|function|__swab64p
r_extern
id|__inline__
id|__u64
id|__swab64p
c_func
(paren
id|__u64
op_star
id|x
)paren
(brace
r_return
id|__arch__swab64p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab64s
r_extern
id|__inline__
r_void
id|__swab64s
c_func
(paren
id|__u64
op_star
id|addr
)paren
(brace
id|__arch__swab64s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif /* __BYTEORDER_HAS_U64__ */
macro_line|#if defined(__KERNEL__) || defined(__REQUIRE_CPU_TO_XX)
DECL|macro|swab16
mdefine_line|#define swab16 __swab16
DECL|macro|swab32
mdefine_line|#define swab32 __swab32
DECL|macro|swab64
mdefine_line|#define swab64 __swab64
DECL|macro|swab16p
mdefine_line|#define swab16p __swab16p
DECL|macro|swab32p
mdefine_line|#define swab32p __swab32p
DECL|macro|swab64p
mdefine_line|#define swab64p __swab64p
DECL|macro|swab16s
mdefine_line|#define swab16s __swab16s
DECL|macro|swab32s
mdefine_line|#define swab32s __swab32s
DECL|macro|swab64s
mdefine_line|#define swab64s __swab64s
DECL|macro|cpu_to_le64
mdefine_line|#define cpu_to_le64 __cpu_to_le64
DECL|macro|le64_to_cpu
mdefine_line|#define le64_to_cpu __le64_to_cpu
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32 __cpu_to_le32
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu __le32_to_cpu
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16 __cpu_to_le16
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu __le16_to_cpu
DECL|macro|cpu_to_be64
mdefine_line|#define cpu_to_be64 __cpu_to_be64
DECL|macro|be64_to_cpu
mdefine_line|#define be64_to_cpu __be64_to_cpu
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32 __cpu_to_be32
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu __be32_to_cpu
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16 __cpu_to_be16
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu __be16_to_cpu
DECL|macro|cpu_to_le64p
mdefine_line|#define cpu_to_le64p __cpu_to_le64p
DECL|macro|le64_to_cpup
mdefine_line|#define le64_to_cpup __le64_to_cpup
DECL|macro|cpu_to_le32p
mdefine_line|#define cpu_to_le32p __cpu_to_le32p
DECL|macro|le32_to_cpup
mdefine_line|#define le32_to_cpup __le32_to_cpup
DECL|macro|cpu_to_le16p
mdefine_line|#define cpu_to_le16p __cpu_to_le16p
DECL|macro|le16_to_cpup
mdefine_line|#define le16_to_cpup __le16_to_cpup
DECL|macro|cpu_to_be64p
mdefine_line|#define cpu_to_be64p __cpu_to_be64p
DECL|macro|be64_to_cpup
mdefine_line|#define be64_to_cpup __be64_to_cpup
DECL|macro|cpu_to_be32p
mdefine_line|#define cpu_to_be32p __cpu_to_be32p
DECL|macro|be32_to_cpup
mdefine_line|#define be32_to_cpup __be32_to_cpup
DECL|macro|cpu_to_be16p
mdefine_line|#define cpu_to_be16p __cpu_to_be16p
DECL|macro|be16_to_cpup
mdefine_line|#define be16_to_cpup __be16_to_cpup
DECL|macro|cpu_to_le64s
mdefine_line|#define cpu_to_le64s __cpu_to_le64s
DECL|macro|le64_to_cpus
mdefine_line|#define le64_to_cpus __le64_to_cpus
DECL|macro|cpu_to_le32s
mdefine_line|#define cpu_to_le32s __cpu_to_le32s
DECL|macro|le32_to_cpus
mdefine_line|#define le32_to_cpus __le32_to_cpus
DECL|macro|cpu_to_le16s
mdefine_line|#define cpu_to_le16s __cpu_to_le16s
DECL|macro|le16_to_cpus
mdefine_line|#define le16_to_cpus __le16_to_cpus
DECL|macro|cpu_to_be64s
mdefine_line|#define cpu_to_be64s __cpu_to_be64s
DECL|macro|be64_to_cpus
mdefine_line|#define be64_to_cpus __be64_to_cpus
DECL|macro|cpu_to_be32s
mdefine_line|#define cpu_to_be32s __cpu_to_be32s
DECL|macro|be32_to_cpus
mdefine_line|#define be32_to_cpus __be32_to_cpus
DECL|macro|cpu_to_be16s
mdefine_line|#define cpu_to_be16s __cpu_to_be16s
DECL|macro|be16_to_cpus
mdefine_line|#define be16_to_cpus __be16_to_cpus
macro_line|#endif
multiline_comment|/*&n; * Handle ntohl and suches. These have various compatibility&n; * issues - like we want to give the prototype even though we&n; * also have a macro for them in case some strange program&n; * wants to take the address of the thing or something..&n; *&n; * Note that these traditionally return a &quot;long&quot;, even though&n; * long is often 64-bit these days.. Thus the casts.&n; *&n; * They have to be macros in order to do the constant folding&n; * correctly - if the argument passed into a inline function&n; * it is no longer constant according to gcc..&n; */
DECL|macro|ntohl
macro_line|#undef ntohl
DECL|macro|ntohs
macro_line|#undef ntohs
DECL|macro|htonl
macro_line|#undef htonl
DECL|macro|htons
macro_line|#undef htons
multiline_comment|/*&n; * Do the prototypes. Somebody might want to take the&n; * address or some such sick thing..&n; */
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
DECL|macro|___htonl
mdefine_line|#define ___htonl(x) __cpu_to_be32(x)
DECL|macro|___htons
mdefine_line|#define ___htons(x) __cpu_to_be16(x)
DECL|macro|___ntohl
mdefine_line|#define ___ntohl(x) __be32_to_cpu(x)
DECL|macro|___ntohs
mdefine_line|#define ___ntohs(x) __be16_to_cpu(x)
DECL|macro|htonl
mdefine_line|#define htonl(x) ((unsigned long)___htonl(x))
DECL|macro|htons
mdefine_line|#define htons(x) ___htons(x)
DECL|macro|ntohl
mdefine_line|#define ntohl(x) ((unsigned long)___ntohl(x))
DECL|macro|ntohs
mdefine_line|#define ntohs(x) ___ntohs(x)
macro_line|#endif /* _LINUX_BYTEORDER_H */
eof
