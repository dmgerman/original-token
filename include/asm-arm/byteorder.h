macro_line|#ifndef __ASM_ARM_BYTEORDER_H
DECL|macro|__ASM_ARM_BYTEORDER_H
mdefine_line|#define __ASM_ARM_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if defined(__GNUC__) &amp;&amp; __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 8
multiline_comment|/* Recent versions of GCC can open code the swaps at least as well&n;   as we can write them by hand, so the &quot;optimisations&quot; here only &n;   make sense for older compilers.  Worse, some versions of GCC&n;   actually go wrong in the presence of the assembler versions.&n;   We play it safe and only turn them on for compilers older than&n;   GCC 2.8.0.  */
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
r_int
r_int
id|xx
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;eor&bslash;t%1, %0, %0, ror #16&bslash;n&bslash;t&quot;
l_string|&quot;bic&bslash;t%1, %1, #0xff0000&bslash;n&bslash;t&quot;
l_string|&quot;mov&bslash;t%0, %0, ror #8&bslash;n&bslash;t&quot;
l_string|&quot;eor&bslash;t%0, %0, %1, lsr #8&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|xx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|x
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
id|__asm__
c_func
(paren
l_string|&quot;eor&bslash;t%0, %0, %0, lsr #8&bslash;n&bslash;t&quot;
l_string|&quot;eor&bslash;t%0, %0, %0, lsl #8&bslash;n&bslash;t&quot;
l_string|&quot;bic&bslash;t%0, %0, #0xff0000&bslash;n&bslash;t&quot;
l_string|&quot;eor&bslash;t%0, %0, %0, lsr #8&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
macro_line|#endif /* __GNUC__ */
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif
eof
