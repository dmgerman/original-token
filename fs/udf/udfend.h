macro_line|#ifndef __UDF_ENDIAN_H
DECL|macro|__UDF_ENDIAN_H
mdefine_line|#define __UDF_ENDIAN_H
macro_line|#ifndef __KERNEL__ 
macro_line|#if __BYTE_ORDER == 0
macro_line|#error &quot;__BYTE_ORDER must be defined&quot;
macro_line|#elif __BYTE_ORDER == __BIG_ENDIAN
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu(x) &bslash;&n;&t;((Uint16)((((Uint16)(x) &amp; 0x00FFU) &lt;&lt; 8) | &bslash;&n;&t;&t;  (((Uint16)(x) &amp; 0xFF00U) &gt;&gt; 8)))
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu(x) &bslash;&n;&t;((Uint32)((((Uint32)(x) &amp; 0x000000FFU) &lt;&lt; 24) | &bslash;&n;&t;&t;  (((Uint32)(x) &amp; 0x0000FF00U) &lt;&lt;  8) | &bslash;&n;&t;&t;  (((Uint32)(x) &amp; 0x00FF0000U) &gt;&gt;  8) | &bslash;&n;&t;&t;  (((Uint32)(x) &amp; 0xFF000000U) &gt;&gt; 24)))
DECL|macro|le64_to_cpu
mdefine_line|#define le64_to_cpu(x) &bslash;&n;&t;((Uint64)((((Uint64)(x) &amp; 0x00000000000000FFULL) &lt;&lt; 56) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0x000000000000FF00ULL) &lt;&lt; 40) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0x0000000000FF0000ULL) &lt;&lt; 24) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0x00000000FF000000ULL) &lt;&lt;  8) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0x000000FF00000000ULL) &gt;&gt;  8) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0x0000FF0000000000ULL) &gt;&gt; 24) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0x00FF000000000000ULL) &gt;&gt; 40) | &bslash;&n;&t;&t;  (((Uint64)(x) &amp; 0xFF00000000000000ULL) &gt;&gt; 56)))&t;&t;
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) (le16_to_cpu(x))
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) (le32_to_cpu(x))
DECL|macro|cpu_to_le64
mdefine_line|#define cpu_to_le64(x) (le64_to_cpu(x))
macro_line|#else /* __BYTE_ORDER == __LITTLE_ENDIAN */
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu(x) (x)
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu(x) (x)
DECL|macro|le64_to_cpu
mdefine_line|#define le64_to_cpu(x) (x)
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16(x) (x)
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32(x) (x)
DECL|macro|cpu_to_le64
mdefine_line|#define cpu_to_le64(x) (x)
macro_line|#endif
macro_line|#endif
DECL|function|lelb_to_cpu
r_static
r_inline
id|lb_addr
id|lelb_to_cpu
c_func
(paren
id|lb_addr
id|in
)paren
(brace
id|lb_addr
id|out
suffix:semicolon
id|out.logicalBlockNum
op_assign
id|le32_to_cpu
c_func
(paren
id|in.logicalBlockNum
)paren
suffix:semicolon
id|out.partitionReferenceNum
op_assign
id|le16_to_cpu
c_func
(paren
id|in.partitionReferenceNum
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lelb
r_static
r_inline
id|lb_addr
id|cpu_to_lelb
c_func
(paren
id|lb_addr
id|in
)paren
(brace
id|lb_addr
id|out
suffix:semicolon
id|out.logicalBlockNum
op_assign
id|cpu_to_le32
c_func
(paren
id|in.logicalBlockNum
)paren
suffix:semicolon
id|out.partitionReferenceNum
op_assign
id|cpu_to_le16
c_func
(paren
id|in.partitionReferenceNum
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|lets_to_cpu
r_static
r_inline
id|timestamp
id|lets_to_cpu
c_func
(paren
id|timestamp
id|in
)paren
(brace
id|timestamp
id|out
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|out
comma
op_amp
id|in
comma
r_sizeof
(paren
id|timestamp
)paren
)paren
suffix:semicolon
id|out.typeAndTimezone
op_assign
id|le16_to_cpu
c_func
(paren
id|in.typeAndTimezone
)paren
suffix:semicolon
id|out.year
op_assign
id|le16_to_cpu
c_func
(paren
id|in.year
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|lela_to_cpu
r_static
r_inline
id|long_ad
id|lela_to_cpu
c_func
(paren
id|long_ad
id|in
)paren
(brace
id|long_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extLocation
op_assign
id|lelb_to_cpu
c_func
(paren
id|in.extLocation
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lela
r_static
r_inline
id|long_ad
id|cpu_to_lela
c_func
(paren
id|long_ad
id|in
)paren
(brace
id|long_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|cpu_to_le32
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extLocation
op_assign
id|cpu_to_lelb
c_func
(paren
id|in.extLocation
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|leea_to_cpu
r_static
r_inline
id|extent_ad
id|leea_to_cpu
c_func
(paren
id|extent_ad
id|in
)paren
(brace
id|extent_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extLocation
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLocation
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lets
r_static
r_inline
id|timestamp
id|cpu_to_lets
c_func
(paren
id|timestamp
id|in
)paren
(brace
id|timestamp
id|out
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|out
comma
op_amp
id|in
comma
r_sizeof
(paren
id|timestamp
)paren
)paren
suffix:semicolon
id|out.typeAndTimezone
op_assign
id|cpu_to_le16
c_func
(paren
id|in.typeAndTimezone
)paren
suffix:semicolon
id|out.year
op_assign
id|cpu_to_le16
c_func
(paren
id|in.year
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
macro_line|#endif /* __UDF_ENDIAN_H */
eof
