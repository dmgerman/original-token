multiline_comment|/* &n; * User address space access functions.&n; * The non inlined parts of asm-i386/uaccess.h are here.&n; *&n; * Copyright 1997 Andi Kleen &lt;ak@muc.de&gt;&n; * Copyright 1997 Linus Torvalds&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mmx.h&gt;
macro_line|#ifdef CONFIG_X86_USE_3DNOW_AND_WORKS
r_int
r_int
DECL|function|__generic_copy_to_user
id|__generic_copy_to_user
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
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|n
)paren
)paren
(brace
r_if
c_cond
(paren
id|n
OL
l_int|512
)paren
(brace
id|__copy_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
r_else
id|mmx_copy_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
r_int
r_int
DECL|function|__generic_copy_from_user
id|__generic_copy_from_user
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
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|from
comma
id|n
)paren
)paren
(brace
r_if
c_cond
(paren
id|n
OL
l_int|512
)paren
(brace
id|__copy_user_zeroing
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
r_else
id|mmx_copy_user_zeroing
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
macro_line|#else
r_int
r_int
DECL|function|__generic_copy_to_user
id|__generic_copy_to_user
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
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|n
)paren
)paren
id|__copy_user
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_int
r_int
DECL|function|__generic_copy_from_user
id|__generic_copy_from_user
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
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|from
comma
id|n
)paren
)paren
id|__copy_user_zeroing
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&t;   &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;int __d0, __d1, __d2;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testl %1,%1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 2f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;0:&t;lodsb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;stosb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testb %%al,%%al&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 1f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;decl %1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jnz 0b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&t;subl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;3:&t;movl %5,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=d&quot;(res), &quot;=c&quot;(count), &quot;=&amp;a&quot; (__d0), &quot;=&amp;S&quot; (__d1),&t;   &bslash;&n;&t;&t;  &quot;=&amp;D&quot; (__d2)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;3&quot;(src), &quot;4&quot;(dst) &bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;   &bslash;&n;} while (0)
r_int
DECL|function|__strncpy_from_user
id|__strncpy_from_user
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_int
id|res
suffix:semicolon
id|__do_strncpy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|count
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_int
DECL|function|strncpy_from_user
id|strncpy_from_user
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_int
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|src
comma
l_int|1
)paren
)paren
id|__do_strncpy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|count
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Zero Userspace&n; */
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,size)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __d0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; stosl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %2,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; stosb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%2,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;c&quot;(size), &quot;=&amp;D&quot; (__d0)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(size &amp; 3), &quot;0&quot;(size / 4), &quot;1&quot;(addr), &quot;a&quot;(0));&t;&bslash;&n;} while (0)
r_int
r_int
DECL|function|clear_user
id|clear_user
c_func
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|n
)paren
)paren
id|__do_clear_user
c_func
(paren
id|to
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_int
r_int
DECL|function|__clear_user
id|__clear_user
c_func
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|n
)paren
(brace
id|__do_clear_user
c_func
(paren
id|to
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 on exception, a value greater than N if too long&n; */
DECL|function|strnlen_user
r_int
id|strnlen_user
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_int
r_int
id|mask
op_assign
op_minus
id|__addr_ok
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
r_int
id|res
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;andl %0,%%ecx&bslash;n&quot;
l_string|&quot;0:&t;repne; scasb&bslash;n&quot;
l_string|&quot;&t;setne %%al&bslash;n&quot;
l_string|&quot;&t;subl %%ecx,%0&bslash;n&quot;
l_string|&quot;&t;addl %0,%%eax&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;xorl %%eax,%%eax&bslash;n&quot;
l_string|&quot;&t;jmp 1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 0b,2b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|n
)paren
comma
l_string|&quot;=D&quot;
(paren
id|s
)paren
comma
l_string|&quot;=a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=c&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|n
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;2&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;3&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
eof
