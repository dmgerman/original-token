multiline_comment|/*&n; * Functions depending of the byteorder.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997 by Ralf Baechle&n; *&n; * $Id: byteorder.h,v 1.5 1997/06/25 19:10:18 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_BYTEORDER_H
DECL|macro|__ASM_MIPS_BYTEORDER_H
mdefine_line|#define __ASM_MIPS_BYTEORDER_H
DECL|macro|__swap32
mdefine_line|#define __swap32(x) &bslash;&n;&t;((unsigned long int)((((unsigned long int)(x) &amp; 0x000000ffU) &lt;&lt; 24) | &bslash;&n;&t;&t;&t;     (((unsigned long int)(x) &amp; 0x0000ff00U) &lt;&lt;  8) | &bslash;&n;&t;&t;&t;     (((unsigned long int)(x) &amp; 0x00ff0000U) &gt;&gt;  8) | &bslash;&n;&t;&t;&t;     (((unsigned long int)(x) &amp; 0xff000000U) &gt;&gt; 24)))
DECL|macro|__swap16
mdefine_line|#define __swap16(x) &bslash;&n;&t;((unsigned short int)((((unsigned short int)(x) &amp; 0x00ff) &lt;&lt; 8) | &bslash;&n;&t;&t;&t;      (((unsigned short int)(x) &amp; 0xff00) &gt;&gt; 8)))
macro_line|#if defined (__MIPSEB__)
macro_line|#ifndef __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN
macro_line|#endif
macro_line|#ifndef __BIG_ENDIAN_BITFIELD
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) (x)
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) (x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) (x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) (x)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-kernel byte order macros to handle stuff like&n; * byte-order-dependent filesystems etc.&n; */
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) __swap32((x))
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu(x) __swap32((x))
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) __swap16((x))
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu(x) __swap16((x))
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x) (x)
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu(x) (x)
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x) (x)
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu(x) (x)
macro_line|#endif /* __KERNEL__ */
macro_line|#elif defined (__MIPSEL__)
macro_line|#ifndef __LITTLE_ENDIAN
DECL|macro|__LITTLE_ENDIAN
mdefine_line|#define __LITTLE_ENDIAN
macro_line|#endif
macro_line|#ifndef __LITTLE_ENDIAN_BITFIELD
DECL|macro|__LITTLE_ENDIAN_BITFIELD
mdefine_line|#define __LITTLE_ENDIAN_BITFIELD
macro_line|#endif
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) __swap32(x)
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) __swap16(x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) __swap32(x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) __swap16(x)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-kernel byte order macros to handle stuff like&n; * byte-order-dependent filesystems etc.&n; */
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) (x)
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu(x) (x)
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) (x)
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu(x) (x)
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32(x) __swap32((x))
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu(x) __swap32((x))
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16(x) __swap16((x))
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu(x) __swap16((x))
macro_line|#endif /* __KERNEL__ */
macro_line|#else
macro_line|#error &quot;MIPS but neither __MIPSEL__ nor __MIPSEB__?&quot;
macro_line|#endif
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
DECL|macro|le16_to_cpup
mdefine_line|#define le16_to_cpup(x) cpu_to_le16p(x)
DECL|macro|le32_to_cpup
mdefine_line|#define le32_to_cpup(x) cpu_to_le32p(x)
DECL|macro|be16_to_cpup
mdefine_line|#define be16_to_cpup(x) cpu_to_be16p(x)
DECL|macro|be32_to_cpup
mdefine_line|#define be32_to_cpup(x) cpu_to_be32p(x)
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
DECL|macro|le16_to_cpus
mdefine_line|#define le16_to_cpus(x) cpu_to_le16s(x)
DECL|macro|le32_to_cpus
mdefine_line|#define le32_to_cpus(x) cpu_to_le32s(x)
DECL|macro|be16_to_cpus
mdefine_line|#define be16_to_cpus(x) cpu_to_be16s(x)
DECL|macro|be32_to_cpus
mdefine_line|#define be32_to_cpus(x) cpu_to_be32s(x)
macro_line|#ifdef __KERNEL__
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
id|__x
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
id|__x
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
id|__x
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
id|__x
)paren
suffix:semicolon
DECL|function|ntohl
r_extern
id|__inline__
r_int
r_int
r_int
id|ntohl
c_func
(paren
r_int
r_int
r_int
id|__x
)paren
(brace
r_return
id|__constant_ntohl
c_func
(paren
id|__x
)paren
suffix:semicolon
)brace
DECL|function|ntohs
r_extern
id|__inline__
r_int
r_int
r_int
id|ntohs
c_func
(paren
r_int
r_int
r_int
id|__x
)paren
(brace
r_return
id|__constant_ntohs
c_func
(paren
id|__x
)paren
suffix:semicolon
)brace
DECL|function|htonl
r_extern
id|__inline__
r_int
r_int
r_int
id|htonl
c_func
(paren
r_int
r_int
r_int
id|__x
)paren
(brace
r_return
id|__constant_htonl
c_func
(paren
id|__x
)paren
suffix:semicolon
)brace
DECL|function|htons
r_extern
id|__inline__
r_int
r_int
r_int
id|htons
c_func
(paren
r_int
r_int
r_int
id|__x
)paren
(brace
r_return
id|__constant_htons
c_func
(paren
id|__x
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_MIPS_BYTEORDER_H */
eof
