macro_line|#ifndef _M68K_IO_H
DECL|macro|_M68K_IO_H
mdefine_line|#define _M68K_IO_H
DECL|function|get_user_byte_io
r_static
r_inline
r_int
r_char
id|get_user_byte_io
c_func
(paren
r_const
r_char
op_star
id|addr
)paren
(brace
r_register
r_int
r_char
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
DECL|macro|inb_p
mdefine_line|#define inb_p(addr) get_user_byte_io((char *)(addr))
DECL|macro|inb
mdefine_line|#define inb(addr) get_user_byte_io((char *)(addr))
DECL|function|put_user_byte_io
r_static
r_inline
r_void
id|put_user_byte_io
c_func
(paren
r_char
id|val
comma
r_char
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %0,%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|outb_p
mdefine_line|#define outb_p(x,addr) put_user_byte_io((x),(char *)(addr))
DECL|macro|outb
mdefine_line|#define outb(x,addr) put_user_byte_io((x),(char *)(addr))
macro_line|#endif /* _M68K_IO_H */
eof
