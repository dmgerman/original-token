multiline_comment|/* $Id: uaccess.h,v 1.2 1996/10/31 00:59:56 davem Exp $ */
macro_line|#ifndef _ASM_UACCESS_H
DECL|macro|_ASM_UACCESS_H
mdefine_line|#define _ASM_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Sparc is not segmented, however we need to be able to fool verify_area()&n; * when doing system calls from kernel mode legitimately.&n; *&n; * &quot;For historical reasons, these macros are grossly misnamed.&quot; -Linus&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS   0
DECL|macro|USER_DS
mdefine_line|#define USER_DS     1
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
DECL|macro|get_fs
mdefine_line|#define get_fs() (current-&gt;tss.current_ds)
DECL|macro|get_ds
mdefine_line|#define get_ds() (KERNEL_DS)
DECL|macro|set_fs
mdefine_line|#define set_fs(val) ((current-&gt;tss.current_ds) = (val))
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) (((size) &lt;= page_offset)&amp;&amp;((addr) &lt;= page_offset-(size)))
DECL|macro|__kernel_ok
mdefine_line|#define __kernel_ok (get_fs() == KERNEL_DS)
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) (__kernel_ok || __user_ok((addr),(size)))
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) __access_ok((unsigned long)(addr),(size))
DECL|function|verify_area
r_extern
r_inline
r_int
id|verify_area
c_func
(paren
r_int
id|type
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|access_ok
c_func
(paren
id|type
comma
id|addr
comma
id|size
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the uglyness from the user.&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user_check((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr))); })
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user_check((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr))); })
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the user has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) __put_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) __get_user_nocheck((x),(ptr),sizeof(*(ptr)),__typeof__(*(ptr)))
DECL|struct|__large_struct
DECL|member|buf
r_struct
id|__large_struct
(brace
r_int
r_int
id|buf
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__m
mdefine_line|#define __m(x) ((struct __large_struct *)(x))
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,addr,size) ({ &bslash;&n;register int __pu_ret asm(&quot;g1&quot;); &bslash;&n;__pu_ret = -EFAULT; &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_8(x,addr,__pu_ret); break; &bslash;&n;case 2: __put_user_16(x,addr,__pu_ret); break; &bslash;&n;case 4: __put_user_32(x,addr,__pu_ret); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} } __pu_ret; })
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,addr,size) ({ &bslash;&n;register int __pu_ret asm(&quot;g1&quot;); &bslash;&n;__pu_ret = -EFAULT; &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_8(x,addr,__pu_ret); break; &bslash;&n;case 2: __put_user_16(x,addr,__pu_ret); break; &bslash;&n;case 4: __put_user_32(x,addr,__pu_ret); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} __pu_ret; })
DECL|macro|__put_user_8
mdefine_line|#define __put_user_8(x,addr,ret)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user 8, inline. */&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%%g6 + %3], %%g2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;set&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;add&t;%%g2, 1, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%0, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g3, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stb&t;%1, [%2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g2, [%%g6 + %3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;n&quot; : &quot;=&amp;r&quot; (ret) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.count)),&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.expc))&t;&bslash;&n;       : &quot;g2&quot;, &quot;g3&quot;)
DECL|macro|__put_user_16
mdefine_line|#define __put_user_16(x,addr,ret)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user 16, inline. */&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%%g6 + %3], %%g2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;set&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;add&t;%%g2, 1, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%0, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g3, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sth&t;%1, [%2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g2, [%%g6 + %3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;n&quot; : &quot;=&amp;r&quot; (ret) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.count)),&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.expc))&t;&bslash;&n;       : &quot;g2&quot;, &quot;g3&quot;)
DECL|macro|__put_user_32
mdefine_line|#define __put_user_32(x,addr,ret)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user 32, inline. */&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%%g6 + %3], %%g2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;set&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;add&t;%%g2, 1, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%0, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g3, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%1, [%2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g2, [%%g6 + %3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;n&quot; : &quot;=&amp;r&quot; (ret) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.count)),&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.expc))&t;&bslash;&n;       : &quot;g2&quot;, &quot;g3&quot;)
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,addr,size,type) ({ &bslash;&n;register int __gu_ret asm(&quot;g1&quot;); &bslash;&n;register unsigned long __gu_val = 0; &bslash;&n;__gu_ret = -EFAULT; &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_8(__gu_val,addr,__gu_ret); break; &bslash;&n;case 2: __get_user_16(__gu_val,addr,__gu_ret); break; &bslash;&n;case 4: __get_user_32(__gu_val,addr,__gu_ret); break; &bslash;&n;default: __gu_ret = __get_user_bad(); break; &bslash;&n;} } x = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,addr,size,type) ({ &bslash;&n;register int __gu_ret asm(&quot;g1&quot;); &bslash;&n;register unsigned long __gu_val = 0; &bslash;&n;__gu_ret = -EFAULT; &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_8(__gu_val,addr,__gu_ret); break; &bslash;&n;case 2: __get_user_16(__gu_val,addr,__gu_ret); break; &bslash;&n;case 4: __get_user_32(__gu_val,addr,__gu_ret); break; &bslash;&n;default: __gu_ret = __get_user_bad(); break; &bslash;&n;} x = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_8
mdefine_line|#define __get_user_8(x,addr,ret)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user 8, inline. */&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%%g6 + %3], %%g2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;set&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;add&t;%%g2, 1, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%0, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g3, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldub&t;[%2], %1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g2, [%%g6 + %3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;n&quot; : &quot;=&amp;r&quot; (ret), &quot;=&amp;r&quot; (x) : &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.count)),&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.expc))&t;&bslash;&n;       : &quot;g2&quot;, &quot;g3&quot;)
DECL|macro|__get_user_16
mdefine_line|#define __get_user_16(x,addr,ret)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user 16, inline. */&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%%g6 + %3], %%g2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;set&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;add&t;%%g2, 1, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%0, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g3, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;lduh&t;[%2], %1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g2, [%%g6 + %3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;n&quot; : &quot;=&amp;r&quot; (ret), &quot;=&amp;r&quot; (x) : &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.count)),&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.expc))&t;&bslash;&n;       : &quot;g2&quot;, &quot;g3&quot;)
DECL|macro|__get_user_32
mdefine_line|#define __get_user_32(x,addr,ret)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user 32, inline. */&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%%g6 + %3], %%g2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;set&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;add&t;%%g2, 1, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%0, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g3, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld&t;[%2], %1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;0, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%g2, [%%g6 + %3]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;n&quot; : &quot;=&amp;r&quot; (ret), &quot;=&amp;r&quot; (x) : &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.count)),&t;&bslash;&n;&t; &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ex.expc))&t;&bslash;&n;       : &quot;g2&quot;, &quot;g3&quot;)
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|__copy_to_user
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|__copy_from_user
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;unsigned long __copy_to = (unsigned long) (to); &bslash;&n;unsigned long __copy_size = (unsigned long) (n); &bslash;&n;unsigned long __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok(__copy_to, __copy_size)) { &bslash;&n;__copy_res = __copy_to_user(__copy_to, (unsigned long) (from), __copy_size); &bslash;&n;if(__copy_res) __copy_res = __copy_size - __copy_res; &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;unsigned long __copy_from = (unsigned long) (from); &bslash;&n;unsigned long __copy_size = (unsigned long) (n); &bslash;&n;unsigned long __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok(__copy_from, __copy_size)) { &bslash;&n;__copy_res = __copy_from_user((unsigned long) (to), __copy_from, __copy_size); &bslash;&n;if(__copy_res) __copy_res = __copy_size - __copy_res; &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
r_extern
r_int
id|__clear_user
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|clear_user
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;unsigned long __clear_addr = (unsigned long) (addr); &bslash;&n;int __clear_size = (int) (n); &bslash;&n;int __clear_res; &bslash;&n;if(__clear_size &amp;&amp; __access_ok(__clear_addr, __clear_size)) { &bslash;&n;__clear_res = __clear_user(__clear_addr, __clear_size); &bslash;&n;if(__clear_res) __clear_res = __clear_size - __clear_res; &bslash;&n;} else __clear_res = __clear_size; &bslash;&n;__clear_res; })
r_extern
r_int
id|__strncpy_from_user
c_func
(paren
r_int
r_int
id|dest
comma
r_int
r_int
id|src
comma
r_int
id|count
)paren
suffix:semicolon
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(dest,src,count) ({ &bslash;&n;unsigned long __sfu_src = (unsigned long) (src); &bslash;&n;int __sfu_count = (int) (count); &bslash;&n;long __sfu_res = -EFAULT; &bslash;&n;if(__access_ok(__sfu_src, __sfu_count)) { &bslash;&n;__sfu_res = __strncpy_from_user((unsigned long) (dest), __sfu_src, __sfu_count); &bslash;&n;} __sfu_res; })
macro_line|#endif  /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_UACCESS_H */
eof
