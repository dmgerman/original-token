macro_line|#ifndef _I386_BYTEORDER_H
DECL|macro|_I386_BYTEORDER_H
mdefine_line|#define _I386_BYTEORDER_H
DECL|macro|ntohl
macro_line|#undef ntohl
DECL|macro|ntohs
macro_line|#undef ntohs
DECL|macro|htonl
macro_line|#undef htonl
DECL|macro|htons
macro_line|#undef htons
macro_line|#ifndef __LITTLE_ENDIAN
DECL|macro|__LITTLE_ENDIAN
mdefine_line|#define __LITTLE_ENDIAN 1234
macro_line|#endif
macro_line|#ifndef __LITTLE_ENDIAN_BITFIELD
DECL|macro|__LITTLE_ENDIAN_BITFIELD
mdefine_line|#define __LITTLE_ENDIAN_BITFIELD
macro_line|#endif
multiline_comment|/* For avoiding bswap on i386 */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(CONFIG_M386)
id|__asm__
c_func
(paren
l_string|&quot;bswap %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
macro_line|#else
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%h0&bslash;n&bslash;t&quot;
multiline_comment|/* swap lower bytes&t;*/
l_string|&quot;rorl $16,%0&bslash;n&bslash;t&quot;
multiline_comment|/* swap words&t;&t;*/
l_string|&quot;xchgb %b0,%h0&quot;
multiline_comment|/* swap higher bytes&t;*/
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
macro_line|#endif&t;
r_return
id|x
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
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%h0&quot;
multiline_comment|/* swap bytes&t;&t;*/
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|x
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
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-kernel byte order macros to handle stuff like&n; * byte-order-dependent filesystems etc.&n; */
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) (x)
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) (x)
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x) htonl((x))
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x) htons((x))
multiline_comment|/* The same, but returns converted value from the location pointer by addr. */
DECL|function|cpu_to_le16p
r_extern
id|__inline__
id|__u16
id|cpu_to_le16p
c_func
(paren
id|__u16
op_star
id|addr
)paren
(brace
r_return
id|cpu_to_le16
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_le32p
r_extern
id|__inline__
id|__u32
id|cpu_to_le32p
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
r_return
id|cpu_to_le32
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_be16p
r_extern
id|__inline__
id|__u16
id|cpu_to_be16p
c_func
(paren
id|__u16
op_star
id|addr
)paren
(brace
r_return
id|cpu_to_be16
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_be32p
r_extern
id|__inline__
id|__u32
id|cpu_to_be32p
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
r_return
id|cpu_to_be32
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* The same, but do the conversion in situ, ie. put the value back to addr. */
DECL|macro|cpu_to_le16s
mdefine_line|#define cpu_to_le16s(x) do { } while (0)
DECL|macro|cpu_to_le32s
mdefine_line|#define cpu_to_le32s(x) do { } while (0)
DECL|function|cpu_to_be16s
r_extern
id|__inline__
r_void
id|cpu_to_be16s
c_func
(paren
id|__u16
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|cpu_to_be16
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_be32s
r_extern
id|__inline__
r_void
id|cpu_to_be32s
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|cpu_to_be32
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert from specified byte order, to CPU byte order. */
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu(x)  cpu_to_le16(x)
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu(x)  cpu_to_le32(x)
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu(x)  cpu_to_be16(x)
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu(x)  cpu_to_be32(x)
DECL|macro|le16_to_cpup
mdefine_line|#define le16_to_cpup(x) cpu_to_le16p(x)
DECL|macro|le32_to_cpup
mdefine_line|#define le32_to_cpup(x) cpu_to_le32p(x)
DECL|macro|be16_to_cpup
mdefine_line|#define be16_to_cpup(x) cpu_to_be16p(x)
DECL|macro|be32_to_cpup
mdefine_line|#define be32_to_cpup(x) cpu_to_be32p(x)
DECL|macro|le16_to_cpus
mdefine_line|#define le16_to_cpus(x) cpu_to_le16s(x)
DECL|macro|le32_to_cpus
mdefine_line|#define le32_to_cpus(x) cpu_to_le32s(x)
DECL|macro|be16_to_cpus
mdefine_line|#define be16_to_cpus(x) cpu_to_be16s(x)
DECL|macro|be32_to_cpus
mdefine_line|#define be32_to_cpus(x) cpu_to_be32s(x)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
