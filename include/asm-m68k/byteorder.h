macro_line|#ifndef _M68K_BYTEORDER_H
DECL|macro|_M68K_BYTEORDER_H
mdefine_line|#define _M68K_BYTEORDER_H
macro_line|#ifndef __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN 4321
macro_line|#endif
macro_line|#ifndef __BIG_ENDIAN_BITFIELD
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * In-kernel byte order macros to handle stuff like&n; * byte-order-dependent filesystems etc.&n; */
DECL|function|__swab16
r_extern
id|__inline__
id|__u16
id|__swab16
(paren
id|__u16
id|val
)paren
(brace
r_return
(paren
id|val
op_lshift
l_int|8
)paren
op_or
(paren
id|val
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|__constant_swab32
r_extern
id|__inline__
id|__u32
id|__constant_swab32
(paren
id|__u32
id|val
)paren
(brace
r_return
(paren
id|val
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_amp
l_int|0xff0000
)paren
op_or
(paren
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff00
)paren
op_or
(paren
id|val
op_rshift
l_int|24
)paren
suffix:semicolon
)brace
DECL|function|__swab32
r_extern
id|__inline__
id|__u32
id|__swab32
(paren
id|__u32
id|val
)paren
(brace
id|__asm__
(paren
l_string|&quot;rolw #8,%0; swap %0; rolw #8,%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* Convert from CPU byte order, to specified byte order. */
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(__val) __swab16(__val)
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(__val) &bslash;&n;(__builtin_constant_p(__val) ? __constant_swab32(__val) : __swab32(__val))
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x)  (x)
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x)  (x)
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
DECL|function|cpu_to_le16s
r_extern
id|__inline__
r_void
id|cpu_to_le16s
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
id|cpu_to_le16
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_le32s
r_extern
id|__inline__
r_void
id|cpu_to_le32s
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
id|cpu_to_le32
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|cpu_to_be16s
mdefine_line|#define cpu_to_be16s(x) do { } while (0)
DECL|macro|cpu_to_be32s
mdefine_line|#define cpu_to_be32s(x) do { } while (0)
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
macro_line|#endif
DECL|macro|ntohl
macro_line|#undef ntohl
DECL|macro|ntohs
macro_line|#undef ntohs
DECL|macro|htonl
macro_line|#undef htonl
DECL|macro|htons
macro_line|#undef htons
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
id|x
suffix:semicolon
)brace
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
id|x
suffix:semicolon
)brace
DECL|macro|__htonl
mdefine_line|#define __htonl(x) __ntohl(x)
DECL|macro|__htons
mdefine_line|#define __htons(x) __ntohs(x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) (x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) (x)
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) (x)
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) (x)
macro_line|#ifdef __OPTIMIZE__
DECL|macro|ntohl
mdefine_line|#define ntohl(x) __ntohl(x)
DECL|macro|ntohs
mdefine_line|#define ntohs(x) __ntohs(x)
DECL|macro|htonl
mdefine_line|#define htonl(x) __htonl(x)
DECL|macro|htons
mdefine_line|#define htons(x) __htons(x)
macro_line|#endif
macro_line|#endif
eof
