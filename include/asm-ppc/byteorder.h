macro_line|#ifndef _PPC_BYTEORDER_H
DECL|macro|_PPC_BYTEORDER_H
mdefine_line|#define _PPC_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifndef __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN
macro_line|#endif
macro_line|#ifndef __BIG_ENDIAN_BITFIELD
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif
DECL|macro|ntohl
mdefine_line|#define ntohl(x) (x)
DECL|macro|ntohs
mdefine_line|#define ntohs(x) (x)
DECL|macro|htonl
mdefine_line|#define htonl(x) (x)
DECL|macro|htons
mdefine_line|#define htons(x) (x)
DECL|macro|__htonl
mdefine_line|#define __htonl(x) ntohl(x)
DECL|macro|__htons
mdefine_line|#define __htons(x) ntohs(x)
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) ntohs(x)
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) ntohl(x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ntohl(x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ntohs(x)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * 16 and 32 bit little-endian loads and stores.&n; */
DECL|function|ld_le16
r_extern
r_inline
r_int
id|ld_le16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|val
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;lhbrx %0,0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|st_le16
r_extern
r_inline
r_void
id|st_le16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;sthbrx %0,0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|ld_le32
r_extern
r_inline
r_int
id|ld_le32
c_func
(paren
r_volatile
r_int
op_star
id|addr
)paren
(brace
r_int
id|val
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;lwbrx %0,0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|st_le32
r_extern
r_inline
r_void
id|st_le32
c_func
(paren
r_volatile
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;stwbrx %0,0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_le16
r_extern
id|__inline__
id|__u16
id|cpu_to_le16
c_func
(paren
id|__u16
id|value
)paren
(brace
r_return
id|ld_le16
c_func
(paren
op_amp
id|value
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_le32
r_extern
id|__inline__
id|__u32
id|cpu_to_le32
c_func
(paren
id|__u32
id|value
)paren
(brace
r_return
id|ld_le32
c_func
(paren
op_amp
id|value
)paren
suffix:semicolon
)brace
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
id|ld_le16
c_func
(paren
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
id|ld_le32
c_func
(paren
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
op_star
id|addr
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
op_star
id|addr
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
id|st_le16
c_func
(paren
id|addr
comma
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
id|st_le32
c_func
(paren
id|addr
comma
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_PPC_BYTEORDER_H) */
eof
