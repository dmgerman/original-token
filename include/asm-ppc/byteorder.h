macro_line|#ifndef _PPC_BYTEORDER_H
DECL|macro|_PPC_BYTEORDER_H
mdefine_line|#define _PPC_BYTEORDER_H
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
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ntohl(x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ntohs(x)
multiline_comment|/*&n; * In-kernel byte order macros to handle stuff like&n; * byte-order-dependent filesystems etc.&n; */
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) le32_to_cpu((x))
DECL|function|le32_to_cpu
r_extern
id|__inline__
r_int
r_int
id|le32_to_cpu
c_func
(paren
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
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) le16_to_cpu((x))
DECL|function|le16_to_cpu
r_extern
id|__inline__
r_int
r_int
id|le16_to_cpu
c_func
(paren
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
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x) (x)
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu(x) (x)
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x) (x)
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu(x) (x)
macro_line|#endif /* !(_PPC_BYTEORDER_H) */
eof
