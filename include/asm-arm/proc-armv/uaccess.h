multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/uaccess.h&n; */
multiline_comment|/*&n; * The fs functions are implemented on the ARMV3 and V4 architectures&n; * using the domain register.&n; *&n; *  DOMAIN_IO     - domain 2 includes all IO only&n; *  DOMAIN_KERNEL - domain 1 includes all kernel memory only&n; *  DOMAIN_USER   - domain 0 includes all user memory only&n; */
DECL|macro|DOMAIN_CLIENT
mdefine_line|#define DOMAIN_CLIENT&t;1
DECL|macro|DOMAIN_MANAGER
mdefine_line|#define DOMAIN_MANAGER&t;3
DECL|macro|DOMAIN_USER_CLIENT
mdefine_line|#define DOMAIN_USER_CLIENT&t;((DOMAIN_CLIENT) &lt;&lt; 0)
DECL|macro|DOMAIN_USER_MANAGER
mdefine_line|#define DOMAIN_USER_MANAGER&t;((DOMAIN_MANAGER) &lt;&lt; 0)
DECL|macro|DOMAIN_KERNEL_CLIENT
mdefine_line|#define DOMAIN_KERNEL_CLIENT&t;((DOMAIN_CLIENT) &lt;&lt; 2)
DECL|macro|DOMAIN_KERNEL_MANAGER
mdefine_line|#define DOMAIN_KERNEL_MANAGER&t;((DOMAIN_MANAGER) &lt;&lt; 2)
DECL|macro|DOMAIN_IO_CLIENT
mdefine_line|#define DOMAIN_IO_CLIENT&t;((DOMAIN_CLIENT) &lt;&lt; 4)
DECL|macro|DOMAIN_IO_MANAGER
mdefine_line|#define DOMAIN_IO_MANAGER&t;((DOMAIN_MANAGER) &lt;&lt; 4)
multiline_comment|/*&n; * When we want to access kernel memory in the *_user functions,&n; * we change the domain register to KERNEL_DS, thus allowing&n; * unrestricted access&n; */
DECL|macro|KERNEL_DOMAIN
mdefine_line|#define KERNEL_DOMAIN&t;(DOMAIN_USER_CLIENT | DOMAIN_KERNEL_MANAGER | DOMAIN_IO_CLIENT)
DECL|macro|USER_DOMAIN
mdefine_line|#define USER_DOMAIN&t;(DOMAIN_USER_CLIENT | DOMAIN_KERNEL_CLIENT  | DOMAIN_IO_CLIENT)
multiline_comment|/*&n; * Note that this is actually 0x1,0000,0000&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0x00000000
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;0xc0000000
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current-&gt;addr_limit)
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a) == (b))
DECL|function|set_fs
r_extern
id|__inline__
r_void
id|set_fs
(paren
id|mm_segment_t
id|fs
)paren
(brace
id|current-&gt;addr_limit
op_assign
id|fs
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mcr&t;p15, 0, %0, c3, c0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|fs
ques
c_cond
id|USER_DOMAIN
suffix:colon
id|KERNEL_DOMAIN
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * a + s   &lt;= 2^32  -&gt; C = 0 || Z = 0 (LS)&n; * (a + s) &lt;= l     -&gt; C = 0 || Z = 0 (LS)&n; */
DECL|macro|__range_ok
mdefine_line|#define __range_ok(addr,size) ({ &bslash;&n;&t;unsigned long flag, sum; &bslash;&n;&t;__asm__ __volatile__(&quot;adds %1, %2, %3; cmpls %1, %0; movls %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag), &quot;=&amp;r&quot; (sum) &bslash;&n;&t;&t;: &quot;r&quot; (addr), &quot;Ir&quot; (size), &quot;0&quot; (current-&gt;addr_limit) &bslash;&n;&t;&t;: &quot;cc&quot;); &bslash;&n;&t;flag; })
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(addr) ({ &bslash;&n;&t;unsigned long flag; &bslash;&n;&t;__asm__ __volatile__(&quot;cmp %2, %0; movlo %0, #0&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (flag) &bslash;&n;&t;&t;: &quot;0&quot; (current-&gt;addr_limit), &quot;r&quot; (addr) &bslash;&n;&t;&t;: &quot;cc&quot;); &bslash;&n;&t;(flag == 0); })
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) (__range_ok(addr,size) == 0)
DECL|macro|__put_user_asm_byte
mdefine_line|#define __put_user_asm_byte(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strbt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mvn&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;i&quot; (EFAULT), &quot;0&quot; (err))
DECL|macro|__put_user_asm_half
mdefine_line|#define __put_user_asm_half(x,addr,err)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __temp = (unsigned long)(x);&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strbt&t;%1,[%3],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&t;strbt&t;%2,[%4],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;4:&t;mvn&t;%0, %5&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;2b, 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__temp), &quot;r&quot; (__temp &gt;&gt; 8),&t;&t;&t;&bslash;&n;&t;  &quot;r&quot; (addr), &quot;r&quot; ((int)(addr) + 1),&t;&t;&t;&bslash;&n;&t;   &quot;i&quot; (EFAULT), &quot;0&quot; (err));&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_asm_word
mdefine_line|#define __put_user_asm_word(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;strt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mvn&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x), &quot;r&quot; (addr), &quot;i&quot; (EFAULT), &quot;0&quot; (err))
DECL|macro|__get_user_asm_byte
mdefine_line|#define __get_user_asm_byte(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrbt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mvn&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;i&quot; (EFAULT), &quot;0&quot; (err))
DECL|macro|__get_user_asm_half
mdefine_line|#define __get_user_asm_half(x,addr,err)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __temp;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrbt&t;%1,[%3],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&t;ldrbt&t;%2,[%4],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;orr&t;%1, %1, %2, lsl #8&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;4:&t;mvn&t;%0, %5&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;2b, 4b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x), &quot;=&amp;r&quot; (__temp)&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;r&quot; ((int)(addr) + 1),&t;&t;&t;&bslash;&n;&t;   &quot;i&quot; (EFAULT), &quot;0&quot; (err));&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_asm_word
mdefine_line|#define __get_user_asm_word(x,addr,err)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;ldrt&t;%1,[%2],#0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mvn&t;%0, %3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=r&quot; (x)&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (addr), &quot;i&quot; (EFAULT), &quot;0&quot; (err))
r_extern
r_int
r_int
id|__arch_copy_from_user
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
suffix:semicolon
DECL|macro|__do_copy_from_user
mdefine_line|#define __do_copy_from_user(to,from,n)&t;&t;&t;&t;&bslash;&n;&t;(n) = __arch_copy_from_user(to,from,n)
r_extern
r_int
r_int
id|__arch_copy_to_user
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
suffix:semicolon
DECL|macro|__do_copy_to_user
mdefine_line|#define __do_copy_to_user(to,from,n)&t;&t;&t;&t;&bslash;&n;&t;(n) = __arch_copy_to_user(to,from,n)
r_extern
r_int
r_int
id|__arch_clear_user
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|n
)paren
suffix:semicolon
DECL|macro|__do_clear_user
mdefine_line|#define __do_clear_user(addr,sz)&t;&t;&t;&t;&bslash;&n;&t;(sz) = __arch_clear_user(addr,sz)
r_extern
r_int
r_int
id|__arch_strncpy_from_user
c_func
(paren
r_char
op_star
id|to
comma
r_const
r_char
op_star
id|from
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|macro|__do_strncpy_from_user
mdefine_line|#define __do_strncpy_from_user(dst,src,count,res)&t;&t;&bslash;&n;&t;(res) = __arch_strncpy_from_user(dst,src,count)
r_extern
r_int
r_int
id|__arch_strlen_user
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
DECL|macro|__do_strlen_user
mdefine_line|#define __do_strlen_user(s,res)&t;&t;&t;&t;&t;&bslash;&n;&t;(res) = __arch_strlen_user(s)
eof