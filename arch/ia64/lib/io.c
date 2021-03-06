macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Copy data from IO memory space to &quot;real&quot; memory space.&n; * This needs to be optimized.&n; */
r_void
DECL|function|__ia64_memcpy_fromio
id|__ia64_memcpy_fromio
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|to
op_assign
id|readb
c_func
(paren
id|from
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|to
)paren
op_increment
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Copy data from &quot;real&quot; memory space to IO memory space.&n; * This needs to be optimized.&n; */
r_void
DECL|function|__ia64_memcpy_toio
id|__ia64_memcpy_toio
(paren
r_int
r_int
id|to
comma
r_void
op_star
id|from
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|writeb
c_func
(paren
op_star
(paren
r_char
op_star
)paren
id|from
comma
id|to
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|from
)paren
op_increment
suffix:semicolon
id|to
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * &quot;memset&quot; on IO memory space.&n; * This needs to be optimized.&n; */
r_void
DECL|function|__ia64_memset_c_io
id|__ia64_memset_c_io
(paren
r_int
r_int
id|dst
comma
r_int
r_int
id|c
comma
r_int
id|count
)paren
(brace
r_int
r_char
id|ch
op_assign
(paren
r_char
)paren
(paren
id|c
op_amp
l_int|0xff
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|writeb
c_func
(paren
id|ch
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_IA64_GENERIC
r_int
r_int
DECL|function|ia64_inb
id|ia64_inb
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|__ia64_inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|ia64_inw
id|ia64_inw
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|__ia64_inw
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|ia64_inl
id|ia64_inl
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|__ia64_inl
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_outb
id|ia64_outb
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|__ia64_outb
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_outw
id|ia64_outw
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|__ia64_outw
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_outl
id|ia64_outl
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|__ia64_outl
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/* define aliases: */
id|asm
(paren
l_string|&quot;.global __ia64_inb, __ia64_inw, __ia64_inl&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;__ia64_inb = ia64_inb&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;__ia64_inw = ia64_inw&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;__ia64_inl = ia64_inl&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;.global __ia64_outb, __ia64_outw, __ia64_outl&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;__ia64_outb = ia64_outb&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;__ia64_outw = ia64_outw&quot;
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;__ia64_outl = ia64_outl&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IA64_GENERIC */
eof
