macro_line|#ifndef _ALPHA_BYTEORDER_H
DECL|macro|_ALPHA_BYTEORDER_H
mdefine_line|#define _ALPHA_BYTEORDER_H
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
r_extern
r_int
r_int
id|ntohl
c_func
(paren
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
id|htonl
c_func
(paren
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
r_int
r_int
id|__ntohl
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
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
macro_line|#ifdef __GNUC__
r_extern
r_int
r_int
id|__constant_ntohl
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
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
DECL|function|__ntohl
id|__ntohl
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|t1
comma
id|t2
comma
id|t3
suffix:semicolon
multiline_comment|/* Break the final or&squot;s out of the block so that gcc can&n;&t;   schedule them at will.  Further, use add not or so that&n;&t;   we elide the sign extend gcc will put in because the&n;&t;   return type is not a long.  */
id|__asm__
c_func
(paren
l_string|&quot;insbl&t;%3,3,%1&t;&t;# %1 = dd000000&bslash;n&bslash;t&quot;
l_string|&quot;zapnot&t;%3,2,%2&t;&t;# %2 = 0000cc00&bslash;n&bslash;t&quot;
l_string|&quot;sll&t;%2,8,%2&t;&t;# %2 = 00cc0000&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%2,%1,%1&t;# %1 = ddcc0000&bslash;n&bslash;t&quot;
l_string|&quot;zapnot&t;%3,4,%2&t;&t;# %2 = 00bb0000&bslash;n&bslash;t&quot;
l_string|&quot;extbl&t;%3,3,%0&t;&t;# %0 = 000000aa&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%2,8,%2&t;&t;# %2 = 0000bb00&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|t3
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|t3
op_plus
id|t2
op_plus
id|t1
suffix:semicolon
)brace
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) &bslash;&n;   ((unsigned int)((((x) &amp; 0x000000ff) &lt;&lt; 24) | &bslash;&n;&t;&t;   (((x) &amp; 0x0000ff00) &lt;&lt;  8) | &bslash;&n;&t;&t;   (((x) &amp; 0x00ff0000) &gt;&gt;  8) | &bslash;&n;&t;&t;   (((x) &amp; 0xff000000) &gt;&gt; 24)))
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
r_int
r_int
r_int
id|t1
comma
id|t2
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;insbl&t;%2,1,%1&t;&t;# %1 = bb00&bslash;n&bslash;t&quot;
l_string|&quot;extbl&t;%2,1,%0&t;&t;# %0 = 00aa&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|t1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|t1
op_or
id|t2
suffix:semicolon
)brace
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) &bslash;&n;((unsigned short int)((((x) &amp; 0x00ff) &lt;&lt; 8) | &bslash;&n;&t;&t;      (((x) &amp; 0xff00) &gt;&gt; 8)))
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
macro_line|#endif /* __OPTIMIZE__ */
macro_line|#endif /* __GNUC__ */
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
macro_line|#endif /* _ALPHA_BYTEORDER_H */
eof
