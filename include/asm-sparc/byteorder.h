multiline_comment|/* $Id: byteorder.h,v 1.12 1996/12/19 08:08:20 davem Exp $ */
macro_line|#ifndef _SPARC_BYTEORDER_H
DECL|macro|_SPARC_BYTEORDER_H
mdefine_line|#define _SPARC_BYTEORDER_H
DECL|macro|ntohl
mdefine_line|#define ntohl(x) (x)
DECL|macro|ntohs
mdefine_line|#define ntohs(x) (x)
DECL|macro|htonl
mdefine_line|#define htonl(x) (x)
DECL|macro|htons
mdefine_line|#define htons(x) (x)
multiline_comment|/* Some programs depend upon these being around. */
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) (x)
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) (x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) (x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) (x)
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
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x)  (x)
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x)  (x)
multiline_comment|/* Convert from specified byte order, to CPU byte order. */
DECL|function|le16_to_cpu
r_extern
id|__inline__
id|__u16
id|le16_to_cpu
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
DECL|function|le32_to_cpu
r_extern
id|__inline__
id|__u32
id|le32_to_cpu
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
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu(x)  (x)
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu(x)  (x)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC_BYTEORDER_H) */
eof
