macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
DECL|function|get_fs_byte
r_static
r_inline
r_int
r_char
id|get_fs_byte
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
(paren
l_string|&quot;movb %%fs:%1,%0&quot;
suffix:colon
l_string|&quot;=q&quot;
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
DECL|function|get_fs_byte
r_static
r_inline
r_int
r_char
id|get_fs_byte
c_func
(paren
r_const
r_int
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
(paren
l_string|&quot;movb %%fs:%1,%0&quot;
suffix:colon
l_string|&quot;=q&quot;
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
DECL|function|get_fs_word
r_static
r_inline
r_int
r_int
id|get_fs_word
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
(paren
l_string|&quot;movw %%fs:%1,%0&quot;
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
DECL|function|get_fs_word
r_static
r_inline
r_int
r_int
id|get_fs_word
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
(paren
l_string|&quot;movw %%fs:%1,%0&quot;
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
DECL|function|get_fs_long
r_static
r_inline
r_int
r_int
id|get_fs_long
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
(paren
l_string|&quot;movl %%fs:%1,%0&quot;
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
"&bslash;"
r_return
id|_v
suffix:semicolon
)brace
DECL|function|get_fs_long
r_static
r_inline
r_int
r_int
id|get_fs_long
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
(paren
l_string|&quot;movl %%fs:%1,%0&quot;
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
"&bslash;"
r_return
id|_v
suffix:semicolon
)brace
DECL|function|get_fs_long
r_static
r_inline
r_int
r_int
id|get_fs_long
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
(paren
l_string|&quot;movl %%fs:%1,%0&quot;
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
"&bslash;"
r_return
id|_v
suffix:semicolon
)brace
DECL|function|get_fs_long
r_static
r_inline
r_int
r_int
id|get_fs_long
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
(paren
l_string|&quot;movl %%fs:%1,%0&quot;
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
"&bslash;"
r_return
id|_v
suffix:semicolon
)brace
DECL|function|put_fs_byte
r_static
r_inline
r_void
id|put_fs_byte
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
(paren
l_string|&quot;movb %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;iq&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_byte
r_static
r_inline
r_void
id|put_fs_byte
c_func
(paren
r_char
id|val
comma
r_int
r_char
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movb %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;iq&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_word
r_static
r_inline
r_void
id|put_fs_word
c_func
(paren
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movw %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;ir&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_word
r_static
r_inline
r_void
id|put_fs_word
c_func
(paren
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movw %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;ir&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_long
r_static
r_inline
r_void
id|put_fs_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movl %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;ir&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_long
r_static
r_inline
r_void
id|put_fs_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movl %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;ir&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_long
r_static
r_inline
r_void
id|put_fs_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movl %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;ir&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_fs_long
r_static
r_inline
r_void
id|put_fs_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
id|__asm__
(paren
l_string|&quot;movl %0,%%fs:%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;ir&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|memcpy_tofs
r_static
r_inline
r_void
id|memcpy_tofs
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;push %%es&bslash;n&bslash;t&quot;
l_string|&quot;push %%fs&bslash;n&bslash;t&quot;
l_string|&quot;pop %%es&bslash;n&bslash;t&quot;
l_string|&quot;testb $1,%%cl&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;1:&bslash;ttestb $2,%%cl&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;2:&bslash;tshrl $2,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;rep ; movsl&bslash;n&bslash;t&quot;
l_string|&quot;pop %%es&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;c&quot;
(paren
id|n
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|to
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|from
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
)brace
DECL|function|memcpy_fromfs
r_static
r_inline
r_void
id|memcpy_fromfs
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;testb $1,%%cl&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;fs ; movsb&bslash;n&quot;
l_string|&quot;1:&bslash;ttestb $2,%%cl&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;fs ; movsw&bslash;n&quot;
l_string|&quot;2:&bslash;tshrl $2,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;rep ; fs ; movsl&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;c&quot;
(paren
id|n
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|to
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|from
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Someone who knows GNU asm better than I should double check the followig.&n; * It seems to work, but I don&squot;t know if I&squot;m doing something subtly wrong.&n; * --- TYT, 11/24/91&n; * [ nothing wrong here, Linus: I just changed the ax to be any reg ]&n; */
DECL|function|get_fs
r_static
r_inline
r_int
r_int
id|get_fs
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %%fs,%w0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|_v
)paren
suffix:colon
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
DECL|function|get_ds
r_static
r_inline
r_int
r_int
id|get_ds
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|_v
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %%ds,%w0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|_v
)paren
suffix:colon
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
DECL|function|set_fs
r_static
r_inline
r_void
id|set_fs
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %w0,%%fs&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SEGMENT_H */
eof
