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
mdefine_line|#define __LITTLE_ENDIAN
macro_line|#endif
macro_line|#ifndef __LITTLE_ENDIAN_BITFIELD
DECL|macro|__LITTLE_ENDIAN_BITFIELD
mdefine_line|#define __LITTLE_ENDIAN_BITFIELD
macro_line|#endif
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
r_int
id|htonl
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
r_int
id|__ntohl
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
r_int
id|__ntohs
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
r_int
id|__constant_ntohl
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
r_int
id|__constant_ntohs
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * The constant and non-constant versions here are the same.&n; * Maybe I&squot;ll come up with an alpha-optimized routine for the&n; * non-constant ones (the constant ones don&squot;t need it: gcc&n; * will optimize it to the correct constant)&n; */
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__ntohl
id|__ntohl
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
id|res
comma
id|t1
comma
id|t2
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;# bswap input: %0 (aabbccdd)&bslash;n&bslash;t&quot;
l_string|&quot;# output: %0, used %1 %2&bslash;n&bslash;t&quot;
l_string|&quot;extlh&t;%0,5,%1&t;&t;# %1 = dd000000&bslash;n&bslash;t&quot;
l_string|&quot;zap&t;%0,0xfd,%2&t;# %2 = 0000cc00&bslash;n&bslash;t&quot;
l_string|&quot;sll&t;%2,5,%2&t;&t;# %2 = 00198000&bslash;n&bslash;t&quot;
l_string|&quot;s8addq&t;%2,%1,%1&t;# %1 = ddcc0000&bslash;n&bslash;t&quot;
l_string|&quot;zap&t;%0,0xfb,%2&t;# %2 = 00bb0000&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%2,8,%2&t;&t;# %2 = 0000bb00&bslash;n&bslash;t&quot;
l_string|&quot;extbl&t;%0,3,%0&t;&t;# %0 = 000000aa&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%1,%0,%0&t;# %0 = ddcc00aa&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%2,%0,%0&t;# %0 = ddccbbaa&bslash;n&quot;
suffix:colon
l_string|&quot;r=&quot;
(paren
id|res
)paren
comma
l_string|&quot;r=&quot;
(paren
id|t1
)paren
comma
l_string|&quot;r=&quot;
(paren
id|t2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
op_amp
l_int|0xffffffffUL
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) &bslash;&n;   ((unsigned long int)((((x) &amp; 0x000000ffUL) &lt;&lt; 24) | &bslash;&n;&t;&t;&t;(((x) &amp; 0x0000ff00UL) &lt;&lt;  8) | &bslash;&n;&t;&t;&t;(((x) &amp; 0x00ff0000UL) &gt;&gt;  8) | &bslash;&n;&t;&t;&t;(((x) &amp; 0xff000000UL) &gt;&gt; 24)))
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
id|res
comma
id|t1
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;# v0 is result; swap in-place.&bslash;n&bslash;t&quot;
l_string|&quot;bis&t;%2,%2,%0&t;# v0 = aabb&bslash;n&bslash;t&quot;
l_string|&quot;extwh&t;%0,7,%1&t;&t;# t1 = bb00&bslash;n&bslash;t&quot;
l_string|&quot;extbl&t;%0,1,%0&t;&t;# v0 = 00aa&bslash;n&bslash;t&quot;
l_string|&quot;bis&t;%0,%1,%0&t;# v0 = bbaa&bslash;n&quot;
suffix:colon
l_string|&quot;r=&quot;
(paren
id|res
)paren
comma
l_string|&quot;r=&quot;
(paren
id|t1
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) &bslash;&n;((unsigned short int)((((unsigned short int)(x) &amp; 0x00ff) &lt;&lt; 8) | &bslash;&n;&t;&t;      (((unsigned short int)(x) &amp; 0xff00) &gt;&gt; 8)))
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
macro_line|#endif
macro_line|#endif
eof
