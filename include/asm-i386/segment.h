macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
DECL|macro|KERNEL_CS
mdefine_line|#define KERNEL_CS&t;0x10
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0x18
DECL|macro|USER_CS
mdefine_line|#define USER_CS&t;&t;0x23
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;0x2B
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) __put_user((unsigned long)(x),(ptr),sizeof(*(ptr)))
DECL|macro|get_user
mdefine_line|#define get_user(ptr) __get_user((ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * This is a silly but good way to make sure that&n; * the __put_user function is indeed always optimized,&n; * and that we use the correct sizes..&n; */
r_extern
r_int
id|bad_user_access_length
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * dummy pointer type structure.. gcc won&squot;t try to do something strange&n; * this way..&n; */
DECL|struct|__segment_dummy
DECL|member|a
r_struct
id|__segment_dummy
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__sd
mdefine_line|#define __sd(x) ((struct __segment_dummy *) (x))
DECL|function|__put_user
r_static
r_inline
r_void
id|__put_user
c_func
(paren
r_int
r_int
id|x
comma
r_void
op_star
id|y
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
(paren
l_string|&quot;movb %b1,%%fs:%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
suffix:colon
l_string|&quot;iq&quot;
(paren
(paren
r_int
r_char
)paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
(paren
l_string|&quot;movw %w1,%%fs:%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
(paren
r_int
r_int
)paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
(paren
l_string|&quot;movl %1,%%fs:%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bad_user_access_length
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|__get_user
r_static
r_inline
r_int
r_int
id|__get_user
c_func
(paren
r_const
r_void
op_star
id|y
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
(paren
l_string|&quot;movb %%fs:%1,%b0&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
r_char
)paren
id|result
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
(paren
l_string|&quot;movw %%fs:%1,%w0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|result
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
(paren
l_string|&quot;movl %%fs:%1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__sd
c_func
(paren
id|y
)paren
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_default
suffix:colon
r_return
id|bad_user_access_length
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * These are depracated..&n; */
DECL|function|get_user_byte
r_static
r_inline
r_int
r_char
id|get_user_byte
c_func
(paren
r_const
r_char
op_star
id|addr
)paren
(brace
r_return
id|__get_user
c_func
(paren
id|addr
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|get_fs_byte
mdefine_line|#define get_fs_byte(addr) get_user_byte((char *)(addr))
DECL|function|get_user_word
r_static
r_inline
r_int
r_int
id|get_user_word
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
id|__get_user
c_func
(paren
id|addr
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|macro|get_fs_word
mdefine_line|#define get_fs_word(addr) get_user_word((short *)(addr))
DECL|function|get_user_long
r_static
r_inline
r_int
r_int
id|get_user_long
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
id|__get_user
c_func
(paren
id|addr
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|macro|get_fs_long
mdefine_line|#define get_fs_long(addr) get_user_long((int *)(addr))
DECL|function|put_user_byte
r_static
r_inline
r_void
id|put_user_byte
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
id|__put_user
c_func
(paren
id|val
comma
id|addr
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|put_fs_byte
mdefine_line|#define put_fs_byte(x,addr) put_user_byte((x),(char *)(addr))
DECL|function|put_user_word
r_static
r_inline
r_void
id|put_user_word
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
id|__put_user
c_func
(paren
id|val
comma
id|addr
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|macro|put_fs_word
mdefine_line|#define put_fs_word(x,addr) put_user_word((x),(short *)(addr))
DECL|function|put_user_long
r_static
r_inline
r_void
id|put_user_long
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
id|__put_user
c_func
(paren
id|val
comma
id|addr
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|macro|put_fs_long
mdefine_line|#define put_fs_long(x,addr) put_user_long((x),(int *)(addr))
DECL|function|__generic_memcpy_tofs
r_static
r_inline
r_void
id|__generic_memcpy_tofs
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
DECL|function|__constant_memcpy_tofs
r_static
r_inline
r_void
id|__constant_memcpy_tofs
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
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_char
op_star
)paren
id|from
comma
(paren
r_char
op_star
)paren
id|to
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_int
op_star
)paren
id|from
comma
(paren
r_int
op_star
)paren
id|to
comma
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_int
op_star
)paren
id|from
comma
(paren
r_int
op_star
)paren
id|to
comma
l_int|2
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|2
op_plus
(paren
r_const
r_char
op_star
)paren
id|from
)paren
comma
l_int|2
op_plus
(paren
r_char
op_star
)paren
id|to
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_int
op_star
)paren
id|from
comma
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_int
op_star
)paren
id|from
comma
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|1
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
)paren
comma
l_int|1
op_plus
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|12
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_int
op_star
)paren
id|from
comma
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|1
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
)paren
comma
l_int|1
op_plus
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|2
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
)paren
comma
l_int|2
op_plus
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|16
suffix:colon
id|__put_user
c_func
(paren
op_star
(paren
r_const
r_int
op_star
)paren
id|from
comma
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|1
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
)paren
comma
l_int|1
op_plus
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|2
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
)paren
comma
l_int|2
op_plus
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
id|__put_user
c_func
(paren
op_star
(paren
l_int|3
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
)paren
comma
l_int|3
op_plus
(paren
r_int
op_star
)paren
id|to
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|macro|COMMON
mdefine_line|#define COMMON(x) &bslash;&n;__asm__(&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push %%fs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pop %%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rep ; movsl&bslash;n&bslash;t&quot; &bslash;&n;&t;x &bslash;&n;&t;&quot;pop %%es&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;:&quot;c&quot; (n/4),&quot;D&quot; ((long) to),&quot;S&quot; ((long) from) &bslash;&n;&t;:&quot;cx&quot;,&quot;di&quot;,&quot;si&quot;)
r_switch
c_cond
(paren
id|n
op_mod
l_int|4
)paren
(brace
r_case
l_int|0
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;movsb&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;movsw&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;movsw&bslash;n&bslash;tmovsb&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|macro|COMMON
macro_line|#undef COMMON
)brace
DECL|function|__generic_memcpy_fromfs
r_static
r_inline
r_void
id|__generic_memcpy_fromfs
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
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|__constant_memcpy_fromfs
r_static
r_inline
r_void
id|__constant_memcpy_fromfs
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
r_switch
c_cond
(paren
id|n
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
op_star
(paren
r_char
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_char
op_star
)paren
id|from
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|2
)paren
suffix:semicolon
op_star
(paren
(paren
r_char
op_star
)paren
id|to
op_plus
l_int|2
)paren
op_assign
id|__get_user
c_func
(paren
l_int|2
op_plus
(paren
r_const
r_char
op_star
)paren
id|from
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
op_star
(paren
l_int|1
op_plus
(paren
r_int
op_star
)paren
id|to
)paren
op_assign
id|__get_user
c_func
(paren
l_int|1
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|12
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
op_star
(paren
l_int|1
op_plus
(paren
r_int
op_star
)paren
id|to
)paren
op_assign
id|__get_user
c_func
(paren
l_int|1
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
op_star
(paren
l_int|2
op_plus
(paren
r_int
op_star
)paren
id|to
)paren
op_assign
id|__get_user
c_func
(paren
l_int|2
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|16
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|to
op_assign
id|__get_user
c_func
(paren
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
op_star
(paren
l_int|1
op_plus
(paren
r_int
op_star
)paren
id|to
)paren
op_assign
id|__get_user
c_func
(paren
l_int|1
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
op_star
(paren
l_int|2
op_plus
(paren
r_int
op_star
)paren
id|to
)paren
op_assign
id|__get_user
c_func
(paren
l_int|2
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
op_star
(paren
l_int|3
op_plus
(paren
r_int
op_star
)paren
id|to
)paren
op_assign
id|__get_user
c_func
(paren
l_int|3
op_plus
(paren
r_const
r_int
op_star
)paren
id|from
comma
l_int|4
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|macro|COMMON
mdefine_line|#define COMMON(x) &bslash;&n;__asm__(&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rep ; fs ; movsl&bslash;n&bslash;t&quot; &bslash;&n;&t;x &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;:&quot;c&quot; (n/4),&quot;D&quot; ((long) to),&quot;S&quot; ((long) from) &bslash;&n;&t;:&quot;cx&quot;,&quot;di&quot;,&quot;si&quot;,&quot;memory&quot;)
r_switch
c_cond
(paren
id|n
op_mod
l_int|4
)paren
(brace
r_case
l_int|0
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|1
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;fs ; movsb&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|2
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;fs ; movsw&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
id|COMMON
c_func
(paren
l_string|&quot;fs ; movsw&bslash;n&bslash;tfs ; movsb&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|macro|COMMON
macro_line|#undef COMMON
)brace
DECL|macro|memcpy_fromfs
mdefine_line|#define memcpy_fromfs(to, from, n) &bslash;&n;(__builtin_constant_p(n) ? &bslash;&n; __constant_memcpy_fromfs((to),(from),(n)) : &bslash;&n; __generic_memcpy_fromfs((to),(from),(n)))
DECL|macro|memcpy_tofs
mdefine_line|#define memcpy_tofs(to, from, n) &bslash;&n;(__builtin_constant_p(n) ? &bslash;&n; __constant_memcpy_tofs((to),(from),(n)) : &bslash;&n; __generic_memcpy_tofs((to),(from),(n)))
multiline_comment|/*&n; * Someone who knows GNU asm better than I should double check the following.&n; * It seems to work, but I don&squot;t know if I&squot;m doing something subtly wrong.&n; * --- TYT, 11/24/91&n; * [ nothing wrong here, Linus: I just changed the ax to be any reg ]&n; */
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
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_SEGMENT_H */
eof
