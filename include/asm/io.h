macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
DECL|function|outb
r_extern
r_void
r_inline
id|outb
c_func
(paren
r_char
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;outb %0,%1&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
(paren
r_char
)paren
id|value
)paren
comma
l_string|&quot;d&quot;
(paren
(paren
r_int
r_int
)paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|outb_p
r_extern
r_void
r_inline
id|outb_p
c_func
(paren
r_char
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;outb %0,%1&bslash;n&quot;
l_string|&quot;&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
(paren
r_char
)paren
id|value
)paren
comma
l_string|&quot;d&quot;
(paren
(paren
r_int
r_int
)paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|inb
r_extern
r_int
r_char
r_inline
id|inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|_v
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;inb %1,%0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
(paren
r_int
r_int
)paren
id|port
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
DECL|function|inb_p
r_extern
r_int
r_char
r_inline
id|inb_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|_v
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;inb %1,%0&bslash;n&quot;
l_string|&quot;&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
(paren
r_int
r_int
)paren
id|port
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
macro_line|#endif
eof
