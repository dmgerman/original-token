macro_line|#ifndef _LINUX_BYTEORDER_VAX_ENDIAN_H
DECL|macro|_LINUX_BYTEORDER_VAX_ENDIAN_H
mdefine_line|#define _LINUX_BYTEORDER_VAX_ENDIAN_H
multiline_comment|/*&n; * Could have been named NUXI-endian&n; * This file isn&squot;t operational.&n; * It&squot;s the beginning of what vaxlinux implementers will have to do.&n; * I just hope we won&squot;t have to write standardized cpu_to_ve32() and suches!&n; * little endian is 1234; bigendian is 4321; vaxendian is 3412&n; * But what does a __u64 look like: is it 34127856 or 78563412 ???&n; * I don&squot;t dare imagine!&n; */
macro_line|#ifndef __VAX_ENDIAN
DECL|macro|__VAX_ENDIAN
mdefine_line|#define __VAX_ENDIAN 3412
macro_line|#endif
macro_line|#ifndef __VAX_ENDIAN_BITFIELD
DECL|macro|__VAX_ENDIAN_BITFIELD
mdefine_line|#define __VAX_ENDIAN_BITFIELD
macro_line|#endif
DECL|macro|___swahw32
mdefine_line|#define ___swahw32(x) &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x0000ffffUL) &lt;&lt; 16) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0xffff0000UL) &gt;&gt; 16) ))
DECL|macro|___swahb32
mdefine_line|#define ___swahb32(x) &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x00ff00ffUL) &lt;&lt; 16) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0xff00ff00UL) &gt;&gt; 16) ))
macro_line|#ifndef __arch__swahw32
DECL|macro|__arch__swahw32
macro_line|#  define __arch__swahw32(x) ___swahw32(x)
macro_line|#endif
macro_line|#ifndef __arch__swahb32
DECL|macro|__arch__swahb32
macro_line|#  define __arch__swahb32(x) ___swahb32(x)
macro_line|#endif
macro_line|#ifndef __arch__swahw32p
DECL|macro|__arch__swahw32p
macro_line|#  define __arch__swahw32p(x) __swahw32(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swahb32p
DECL|macro|__arch__swahb32p
macro_line|#  define __arch__swahb32p(x) __swahb32(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swahw32s
DECL|macro|__arch__swahw32s
macro_line|#  define __arch__swahw32s(x) *(x) = __swahw32p((x))
macro_line|#endif
macro_line|#ifndef __arch__swahb32s
DECL|macro|__arch__swahb32s
macro_line|#  define __arch__swahb32s(x) *(x) = __swahb32p((x))
macro_line|#endif
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ___swahb32((x))
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) ___swahb32((x))
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ___swab16((x))
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) ___swab16((x))
DECL|macro|__cpu_to_le64
mdefine_line|#define __cpu_to_le64(x) I DON&squot;T KNOW
DECL|macro|__le64_to_cpu
mdefine_line|#define __le64_to_cpu(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_le32
mdefine_line|#define __cpu_to_le32(x) ___swahw32((x))
DECL|macro|__le32_to_cpu
mdefine_line|#define __le32_to_cpu(x) ___swahw32((x))
DECL|macro|__cpu_to_le16
mdefine_line|#define __cpu_to_le16(x) ((__u16)(x)
DECL|macro|__le16_to_cpu
mdefine_line|#define __le16_to_cpu(x) ((__u16)(x)
DECL|macro|__cpu_to_be64
mdefine_line|#define __cpu_to_be64(x) I DON&squot;T KNOW
DECL|macro|__be64_to_cpu
mdefine_line|#define __be64_to_cpu(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_be32
mdefine_line|#define __cpu_to_be32(x) __swahb32((x))
DECL|macro|__be32_to_cpu
mdefine_line|#define __be32_to_cpu(x) __swahb32((x))
DECL|macro|__cpu_to_be16
mdefine_line|#define __cpu_to_be16(x) __swab16((x))
DECL|macro|__be16_to_cpu
mdefine_line|#define __be16_to_cpu(x) __swab16((x))
DECL|macro|__cpu_to_le64p
mdefine_line|#define __cpu_to_le64p(x) I DON&squot;T KNOW
DECL|macro|__le64_to_cpup
mdefine_line|#define __le64_to_cpup(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_le32p
mdefine_line|#define __cpu_to_le32p(x) ___swahw32p((x))
DECL|macro|__le32_to_cpup
mdefine_line|#define __le32_to_cpup(x) ___swahw32p((x))
DECL|macro|__cpu_to_le16p
mdefine_line|#define __cpu_to_le16p(x) (*(__u16*)(x))
DECL|macro|__le16_to_cpup
mdefine_line|#define __le16_to_cpup(x) (*(__u16*)(x))
DECL|macro|__cpu_to_be64p
mdefine_line|#define __cpu_to_be64p(x) I DON&squot;T KNOW
DECL|macro|__be64_to_cpup
mdefine_line|#define __be64_to_cpup(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_be32p
mdefine_line|#define __cpu_to_be32p(x) __swahb32p((x))
DECL|macro|__be32_to_cpup
mdefine_line|#define __be32_to_cpup(x) __swahb32p((x))
DECL|macro|__cpu_to_be16p
mdefine_line|#define __cpu_to_be16p(x) __swab16p((x))
DECL|macro|__be16_to_cpup
mdefine_line|#define __be16_to_cpup(x) __swab16p((x))
DECL|macro|__cpu_to_le64s
mdefine_line|#define __cpu_to_le64s(x) I DON&squot;T KNOW
DECL|macro|__le64_to_cpus
mdefine_line|#define __le64_to_cpus(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_le32s
mdefine_line|#define __cpu_to_le32s(x) ___swahw32s((x))
DECL|macro|__le32_to_cpus
mdefine_line|#define __le32_to_cpus(x) ___swahw32s((x))
DECL|macro|__cpu_to_le16s
mdefine_line|#define __cpu_to_le16s(x) do {} while (0)
DECL|macro|__le16_to_cpus
mdefine_line|#define __le16_to_cpus(x) do {} while (0)
DECL|macro|__cpu_to_be64s
mdefine_line|#define __cpu_to_be64s(x) I DON&squot;T KNOW
DECL|macro|__be64_to_cpus
mdefine_line|#define __be64_to_cpus(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_be32s
mdefine_line|#define __cpu_to_be32s(x) __swahb32s((x))
DECL|macro|__be32_to_cpus
mdefine_line|#define __be32_to_cpus(x) __swahb32s((x))
DECL|macro|__cpu_to_be16s
mdefine_line|#define __cpu_to_be16s(x) __swab16s((x))
DECL|macro|__be16_to_cpus
mdefine_line|#define __be16_to_cpus(x) __swab16s((x))
macro_line|#include &lt;linux/byteorder_generic.h&gt;
macro_line|#endif /* _LINUX_BYTEORDER_VAX_ENDIAN_H */
eof
