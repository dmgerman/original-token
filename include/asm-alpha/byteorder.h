macro_line|#ifndef _ALPHA_BYTEORDER_H
DECL|macro|_ALPHA_BYTEORDER_H
mdefine_line|#define _ALPHA_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
DECL|function|___arch__swab32
r_static
id|__inline__
id|__const__
id|__u32
id|___arch__swab32
c_func
(paren
id|__u32
id|x
)paren
(brace
id|__u64
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
DECL|function|___arch__swab16
r_static
id|__inline__
id|__const__
id|__u16
id|___arch__swab16
c_func
(paren
id|__u16
id|x
)paren
(brace
id|__u64
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
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
macro_line|#endif /* __GNUC__ */
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#include &lt;linux/byteorder_little_endian.h&gt;
macro_line|#endif /* _ALPHA_BYTEORDER_H */
eof
