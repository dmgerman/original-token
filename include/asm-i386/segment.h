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
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; * &n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current-&gt;tss.segment)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)&t;(current-&gt;tss.segment = (x))
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) &bslash;&n;((size &lt;= 0xC0000000) &amp;&amp; (addr &lt;= 0xC0000000 - size))
DECL|macro|__kernel_ok
mdefine_line|#define __kernel_ok &bslash;&n;(get_fs() == KERNEL_DS)
r_extern
r_int
id|__verify_write
c_func
(paren
r_const
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#if CPU &gt; 386
DECL|macro|__access_ok
mdefine_line|#define __access_ok(type,addr,size) &bslash;&n;(__kernel_ok || __user_ok(addr,size))
macro_line|#else
DECL|macro|__access_ok
mdefine_line|#define __access_ok(type,addr,size) &bslash;&n;(__kernel_ok || (__user_ok(addr,size) &amp;&amp; &bslash;&n;  ((type) == VERIFY_READ || wp_works_ok || __verify_write((void *)(addr),(size)))))
macro_line|#endif /* CPU */
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;__access_ok((type),(unsigned long)(addr),(size))
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the uglyness from the user.&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr))); })
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr))); })
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
mdefine_line|#define __m(x) (*(struct __large_struct *)(x))
DECL|macro|__put_user
mdefine_line|#define __put_user(x,addr,size) ({ &bslash;&n;int __pu_ret = -EFAULT; &bslash;&n;if (access_ok(VERIFY_WRITE,addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_8(x,addr,__pu_ret); break; &bslash;&n;case 2: __put_user_16(x,addr,__pu_ret); break; &bslash;&n;case 4: __put_user_32(x,addr,__pu_ret); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} } __pu_ret; })
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x,addr,ret,bwl,reg,rtype) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movl $1f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incl %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&quot; #bwl &quot; %&quot; reg &quot;1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;xorl %0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decl %3&bslash;n1:&quot; &bslash;&n;:&quot;=d&quot; (ret) &bslash;&n;:#rtype (x), &quot;m&quot; (__m(addr)),&quot;m&quot; (current-&gt;tss.ex.count), &quot;0&quot; (ret))
DECL|macro|__put_user_8
mdefine_line|#define __put_user_8(x,addr,ret) &bslash;&n;__put_user_asm(x,addr,ret,b,&quot;b&quot;,&quot;iq&quot;)
DECL|macro|__put_user_16
mdefine_line|#define __put_user_16(x,addr,ret) &bslash;&n;__put_user_asm(x,addr,ret,w,&quot;w&quot;,&quot;ir&quot;)
DECL|macro|__put_user_32
mdefine_line|#define __put_user_32(x,addr,ret) &bslash;&n;__put_user_asm(x,addr,ret,l,&quot;&quot;,&quot;ir&quot;)
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user
mdefine_line|#define __get_user(x,addr,size,type) ({ &bslash;&n;int __gu_ret = -EFAULT; &bslash;&n;unsigned long __gu_val = 0; &bslash;&n;if (access_ok(VERIFY_WRITE,addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_8(__gu_val,addr,__gu_ret); break; &bslash;&n;case 2: __get_user_16(__gu_val,addr,__gu_ret); break; &bslash;&n;case 4: __get_user_32(__gu_val,addr,__gu_ret); break; &bslash;&n;default: __gu_ret = __get_user_bad(); break; &bslash;&n;} } x = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x,addr,ret,bwl,reg,rtype) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movl $1f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incl %3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov&quot; #bwl &quot; %2,%&quot; reg &quot;1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;xorl %0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decl %3&bslash;n1:&quot; &bslash;&n;:&quot;=d&quot; (ret), #rtype (x) &bslash;&n;:&quot;m&quot; (__m(addr)),&quot;m&quot; (current-&gt;tss.ex.count), &quot;0&quot; (ret), &quot;1&quot; (x))
DECL|macro|__get_user_8
mdefine_line|#define __get_user_8(x,addr,ret) &bslash;&n;__get_user_asm(x,addr,ret,b,&quot;b&quot;,&quot;=q&quot;)
DECL|macro|__get_user_16
mdefine_line|#define __get_user_16(x,addr,ret) &bslash;&n;__get_user_asm(x,addr,ret,w,&quot;w&quot;,&quot;=r&quot;)
DECL|macro|__get_user_32
mdefine_line|#define __get_user_32(x,addr,ret) &bslash;&n;__get_user_asm(x,addr,ret,l,&quot;&quot;,&quot;=r&quot;)
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__copy_user
mdefine_line|#define __copy_user(to,from,size) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movl $3f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incl %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rep; movsl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;testb $2,%b3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;je 1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movsw&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subb $2,%b3&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;t&quot; &bslash;&n;&t;&quot;testb $1,%b3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;je 2f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movsb&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decb %b3&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;t&quot; &bslash;&n;&t;&quot;decl %2&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;tlea 0(%3,%1,4),%0&quot; &bslash;&n;&t;:&quot;=d&quot; (size) &bslash;&n;&t;:&quot;c&quot; (size &gt;&gt; 2), &quot;m&quot; (current-&gt;tss.ex), &quot;q&quot; (size &amp; 3), &bslash;&n;&t; &quot;D&quot; (to), &quot;S&quot; (from), &quot;0&quot; (size) &bslash;&n;&t;:&quot;cx&quot;,&quot;di&quot;,&quot;si&quot;,&quot;memory&quot;);
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;unsigned long __cu_to = (unsigned long) (to); &bslash;&n;unsigned long __cu_size = (unsigned long) (n); &bslash;&n;if (__cu_size &amp;&amp; __access_ok(VERIFY_WRITE, __cu_to, __cu_size)) &bslash;&n;__copy_user(__cu_to,from,__cu_size); &bslash;&n;__cu_size; })
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;unsigned long __cu_from = (unsigned long) (from); &bslash;&n;unsigned long __cu_size = (unsigned long) (n); &bslash;&n;if (__cu_size &amp;&amp; __access_ok(VERIFY_READ, __cu_from, __cu_size)) &bslash;&n;__copy_user(to,__cu_from,__cu_size); &bslash;&n;__cu_size; })
DECL|macro|__clear_user
mdefine_line|#define __clear_user(addr,size) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movl $3f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incl %2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rep; stosl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;testl $2,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;je 1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stosw&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subl $2,%3&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;t&quot; &bslash;&n;&t;&quot;testl $1,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;je 2f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stosb&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decl %3&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;t&quot; &bslash;&n;&t;&quot;decl %2&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;tlea 0(%3,%1,4),%0&quot; &bslash;&n;&t;:&quot;=d&quot; (size) &bslash;&n;&t;:&quot;c&quot; (size &gt;&gt; 2), &quot;m&quot; (current-&gt;tss.ex), &quot;r&quot; (size &amp; 3), &bslash;&n;&t; &quot;D&quot; (addr), &quot;0&quot; (size), &quot;a&quot; (0) &bslash;&n;&t;:&quot;cx&quot;,&quot;di&quot;,&quot;memory&quot;);
DECL|macro|clear_user
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;void * __cl_addr = (addr); &bslash;&n;unsigned long __cl_size = (n); &bslash;&n;if (__cl_size &amp;&amp; __access_ok(VERIFY_WRITE, ((unsigned long)(__cl_addr)), __cl_size)) &bslash;&n;__clear_user(__cl_addr, __cl_size); &bslash;&n;__cl_size; })
DECL|macro|__strncpy_from_user
mdefine_line|#define __strncpy_from_user(dst,src,count,res) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $3f,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incl %2&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tdecl %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;js 2f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;lodsb&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stosb&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;testb %%al,%%al&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jne 1b&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;t&quot; &bslash;&n;&t;&quot;incl %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;xorl %0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decl %2&bslash;n&quot; &bslash;&n;&t;&quot;3:&quot; &bslash;&n;&t;:&quot;=d&quot; (res), &quot;=r&quot; (count) &bslash;&n;&t;:&quot;m&quot; (current-&gt;tss.ex), &quot;1&quot; (count), &quot;S&quot; (src),&quot;D&quot; (dst),&quot;0&quot; (res) &bslash;&n;&t;:&quot;si&quot;,&quot;di&quot;,&quot;ax&quot;,&quot;cx&quot;,&quot;memory&quot;)
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(dest,src,count) ({ &bslash;&n;const void * __sc_src = (src); &bslash;&n;unsigned long __sc_count = (count); &bslash;&n;long __sc_res = -EFAULT; &bslash;&n;if (__access_ok(VERIFY_READ, ((unsigned long)(__sc_src)), __sc_count)) { &bslash;&n;&t;unsigned long __sc_residue = __sc_count; &bslash;&n;&t;__strncpy_from_user(dest,__sc_src,__sc_count,__sc_res); &bslash;&n;&t;if (!__sc_res) __sc_res = __sc_residue - __sc_count; &bslash;&n;} __sc_res; })
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_SEGMENT_H */
eof
