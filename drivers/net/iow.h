macro_line|#ifndef _ASM_IOW_H
DECL|macro|_ASM_IOW_H
mdefine_line|#define _ASM_IOW_H
multiline_comment|/* I added a few.  Please add to the distributed files.&t;-djb. */
multiline_comment|/* This file is copied 1:1 from /linux/include/asm/io.h, and changed all&n;   al to ax, all inb to inw and all outb to outw (to get word in/out)&n;   the four inlines here should be added to the original, and&n;   then this one rm&squot;d (and the #include &quot;iow.h&quot; in depca.c removed)... &n;   Gruss PB &n;*/
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe abou using 0x80.&n; *&n; *&t;&t;Linus&n; */
multiline_comment|/* This is the more general version of outw.. */
DECL|function|__outw
r_extern
r_inline
r_void
id|__outw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;outw %w0,%w1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|value
)paren
comma
l_string|&quot;d&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* this is used for constant port numbers &lt; 256.. */
DECL|function|__outwc
r_extern
r_inline
r_void
id|__outwc
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;outw %w0,%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|value
)paren
comma
l_string|&quot;i&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* general version of inw */
DECL|function|__inw
r_extern
r_inline
r_int
r_int
id|__inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;inw %w1,%w0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
multiline_comment|/* inw with constant port nr 0-255 */
DECL|function|__inwc
r_extern
r_inline
r_int
r_int
id|__inwc
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;inw %1,%w0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
DECL|function|__outw_p
r_extern
r_inline
r_void
id|__outw_p
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;outw %w0,%w1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|value
)paren
comma
l_string|&quot;d&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
)brace
DECL|function|__outwc_p
r_extern
r_inline
r_void
id|__outwc_p
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;outw %w0,%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|value
)paren
comma
l_string|&quot;i&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
)brace
DECL|function|__inw_p
r_extern
r_inline
r_int
r_int
id|__inw_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;inw %w1,%w0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
DECL|function|__inwc_p
r_extern
r_inline
r_int
r_int
id|__inwc_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;inw %1,%w0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|port
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that due to the way __builtin_constant_p() works, you&n; *  - can&squot;t use it inside a inlien function (it will never be true)&n; *  - you don&squot;t have to worry about side effects within the __builtin..&n; */
DECL|macro|outw
mdefine_line|#define outw(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outwc((val),(port)) : &bslash;&n;&t;__outw((val),(port)))
DECL|macro|inw
mdefine_line|#define inw(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inwc(port) : &bslash;&n;&t;__inw(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__outwc_p((val),(port)) : &bslash;&n;&t;__outw_p((val),(port)))
DECL|macro|inw_p
mdefine_line|#define inw_p(port) &bslash;&n;((__builtin_constant_p((port)) &amp;&amp; (port) &lt; 256) ? &bslash;&n;&t;__inwc_p(port) : &bslash;&n;&t;__inw_p(port))
macro_line|#endif
multiline_comment|/* The word-wide I/O operations are more general, but require a halved&n;   count.  */
DECL|macro|port_read
mdefine_line|#define port_read(port,buf,nr) &bslash;&n;__asm__(&quot;cld;rep;insw&quot;: :&quot;d&quot; (port),&quot;D&quot; (buf),&quot;c&quot; (nr):&quot;cx&quot;,&quot;di&quot;)
DECL|macro|port_write
mdefine_line|#define port_write(port,buf,nr) &bslash;&n;__asm__(&quot;cld;rep;outsw&quot;: :&quot;d&quot; (port),&quot;S&quot; (buf),&quot;c&quot; (nr):&quot;cx&quot;,&quot;si&quot;)
DECL|macro|port_read_b
mdefine_line|#define port_read_b(port,buf,nr) &bslash;&n;__asm__(&quot;cld;rep;insb&quot;: :&quot;d&quot; (port),&quot;D&quot; (buf),&quot;c&quot; (nr):&quot;cx&quot;,&quot;di&quot;)
DECL|macro|port_write_b
mdefine_line|#define port_write_b(port,buf,nr) &bslash;&n;__asm__(&quot;cld;rep;outsb&quot;: :&quot;d&quot; (port),&quot;S&quot; (buf),&quot;c&quot; (nr):&quot;cx&quot;,&quot;si&quot;)
eof