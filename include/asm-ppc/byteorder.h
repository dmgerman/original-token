macro_line|#ifndef _PPC_BYTEORDER_H
DECL|macro|_PPC_BYTEORDER_H
mdefine_line|#define _PPC_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
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
macro_line|#if 0
macro_line|#  define __arch_swab16(x) ld_le16(&amp;x)
macro_line|#  define __arch_swab32(x) ld_le32(&amp;x)
macro_line|#else
DECL|function|___arch__swab16
r_static
id|__inline__
id|__const__
id|__u16
id|___arch__swab16
c_func
(paren
id|__u16
id|value
)paren
(brace
id|__u16
id|result
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;rlwimi %0,%1,8,16,23&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;0&quot;
(paren
id|value
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|___arch__swab32
r_static
id|__inline__
id|__const__
id|__u32
id|___arch__swab32
c_func
(paren
id|__u32
id|value
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;rlwimi %0,%1,24,16,23&bslash;n&bslash;t&quot;
l_string|&quot;rlwimi %0,%1,8,8,15&bslash;n&bslash;t&quot;
l_string|&quot;rlwimi %0,%1,24,0,7&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;0&quot;
(paren
id|value
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
macro_line|#endif /* 0 */
multiline_comment|/* The same, but returns converted value from the location pointer by addr. */
DECL|macro|__arch__swab16p
mdefine_line|#define __arch__swab16p(addr) ld_le16(addr)
DECL|macro|__arch__swab32p
mdefine_line|#define __arch__swab32p(addr) ld_le32(addr)
multiline_comment|/* The same, but do the conversion in situ, ie. put the value back to addr. */
DECL|macro|__arch__swab16s
mdefine_line|#define __arch__swab16s(addr) st_le16(addr,*addr)
DECL|macro|__arch__swab32s
mdefine_line|#define __arch__swab32s(addr) st_le32(addr,*addr)
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _PPC_BYTEORDER_H */
eof
