multiline_comment|/* $Id: byteorder.h,v 1.6 1997/06/14 17:35:07 davem Exp $ */
macro_line|#ifndef _SPARC64_BYTEORDER_H
DECL|macro|_SPARC64_BYTEORDER_H
mdefine_line|#define _SPARC64_BYTEORDER_H
macro_line|#include &lt;asm/asi.h&gt;
DECL|macro|ntohl
mdefine_line|#define ntohl(x) ((unsigned long int)(x))
DECL|macro|ntohs
mdefine_line|#define ntohs(x) ((unsigned short int)(x))
DECL|macro|htonl
mdefine_line|#define htonl(x) ((unsigned long int)(x))
DECL|macro|htons
mdefine_line|#define htons(x) ((unsigned short int)(x))
multiline_comment|/* Some programs depend upon these being around. */
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) ((unsigned long int)(x))
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) ((unsigned short int)(x))
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ((unsigned long int)(x))
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ((unsigned short int)(x))
macro_line|#ifndef __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN 4321
macro_line|#endif
macro_line|#ifndef __BIG_ENDIAN_BITFIELD
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/* Convert from CPU byte order, to specified byte order. */
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
(paren
id|value
op_rshift
l_int|8
)paren
op_or
(paren
id|value
op_lshift
l_int|8
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
(paren
id|value
op_rshift
l_int|24
)paren
op_or
(paren
(paren
id|value
op_rshift
l_int|8
)paren
op_amp
l_int|0xff00
)paren
op_or
(paren
(paren
id|value
op_lshift
l_int|8
)paren
op_amp
l_int|0xff0000
)paren
op_or
(paren
id|value
op_lshift
l_int|24
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_le64
r_extern
id|__inline__
id|__u64
id|cpu_to_le64
c_func
(paren
id|__u64
id|value
)paren
(brace
r_return
(paren
(paren
(paren
id|value
op_rshift
l_int|56
)paren
op_amp
l_int|0x00000000000000ffUL
)paren
op_or
(paren
(paren
id|value
op_rshift
l_int|40
)paren
op_amp
l_int|0x000000000000ff00UL
)paren
op_or
(paren
(paren
id|value
op_rshift
l_int|24
)paren
op_amp
l_int|0x0000000000ff0000UL
)paren
op_or
(paren
(paren
id|value
op_rshift
l_int|8
)paren
op_amp
l_int|0x00000000ff000000UL
)paren
op_or
(paren
(paren
id|value
op_lshift
l_int|8
)paren
op_amp
l_int|0x000000ff00000000UL
)paren
op_or
(paren
(paren
id|value
op_lshift
l_int|24
)paren
op_amp
l_int|0x0000ff0000000000UL
)paren
op_or
(paren
(paren
id|value
op_lshift
l_int|40
)paren
op_amp
l_int|0x00ff000000000000UL
)paren
op_or
(paren
(paren
id|value
op_lshift
l_int|56
)paren
op_amp
l_int|0xff00000000000000UL
)paren
)paren
suffix:semicolon
)brace
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x)  (x)
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x)  (x)
DECL|macro|cpu_to_be64
mdefine_line|#define cpu_to_be64(x)&t;(x)
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
id|__u16
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
)paren
suffix:semicolon
r_return
id|ret
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
id|__u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduwa [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cpu_to_le64p
r_extern
id|__inline__
id|__u64
id|cpu_to_le64p
c_func
(paren
id|__u64
op_star
id|addr
)paren
(brace
id|__u64
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ldxa [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
)paren
suffix:semicolon
r_return
id|ret
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
DECL|function|cpu_to_be64p
r_extern
id|__inline__
id|__u64
id|cpu_to_be64p
c_func
(paren
id|__u64
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
op_star
id|addr
op_assign
id|cpu_to_le16p
c_func
(paren
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
id|cpu_to_le32p
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_le64s
r_extern
id|__inline__
r_void
id|cpu_to_le64s
c_func
(paren
id|__u64
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|cpu_to_le64p
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|cpu_to_be16s
mdefine_line|#define cpu_to_be16s(x) do { } while (0)
DECL|macro|cpu_to_be32s
mdefine_line|#define cpu_to_be32s(x) do { } while (0)
DECL|macro|cpu_to_be64s
mdefine_line|#define cpu_to_be64s(x) do { } while (0)
multiline_comment|/* Convert from specified byte order, to CPU byte order. */
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu(x)&t;cpu_to_le16(x)
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu(x)&t;cpu_to_le32(x)
DECL|macro|le64_to_cpu
mdefine_line|#define le64_to_cpu(x)&t;cpu_to_le64(x)
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu(x)  cpu_to_be16(x)
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu(x)  cpu_to_be32(x)
DECL|macro|be64_to_cpu
mdefine_line|#define be64_to_cpu(x)&t;cpu_to_be64(x)
DECL|macro|le16_to_cpup
mdefine_line|#define le16_to_cpup(x)&t;cpu_to_le16p(x)
DECL|macro|le32_to_cpup
mdefine_line|#define le32_to_cpup(x)&t;cpu_to_le32p(x)
DECL|macro|le64_to_cpup
mdefine_line|#define le64_to_cpup(x)&t;cpu_to_le64p(x)
DECL|macro|be16_to_cpup
mdefine_line|#define be16_to_cpup(x)&t;cpu_to_be16p(x)
DECL|macro|be32_to_cpup
mdefine_line|#define be32_to_cpup(x)&t;cpu_to_be32p(x)
DECL|macro|be64_to_cpup
mdefine_line|#define be64_to_cpup(x)&t;cpu_to_be64p(x)
DECL|macro|le16_to_cpus
mdefine_line|#define le16_to_cpus(x)&t;cpu_to_le16s(x)
DECL|macro|le32_to_cpus
mdefine_line|#define le32_to_cpus(x)&t;cpu_to_le32s(x)
DECL|macro|le64_to_cpus
mdefine_line|#define le64_to_cpus(x)&t;cpu_to_le64s(x)
DECL|macro|be16_to_cpus
mdefine_line|#define be16_to_cpus(x)&t;cpu_to_be16s(x)
DECL|macro|be32_to_cpus
mdefine_line|#define be32_to_cpus(x)&t;cpu_to_be32s(x)
DECL|macro|be64_to_cpus
mdefine_line|#define be64_to_cpus(x)&t;cpu_to_be64s(x)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC64_BYTEORDER_H) */
eof
