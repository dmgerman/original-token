macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;1
DECL|macro|get_fs
mdefine_line|#define get_fs()  (current-&gt;tss.flags &amp; 0x1)
DECL|macro|set_fs
mdefine_line|#define set_fs(x) (current-&gt;tss.flags = (current-&gt;tss.flags &amp; ~0x1) | ((x) &amp; 0x1))
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Is a address valid? This does a straighforward calculation rather&n; * than tests.&n; *&n; * Address valid if:&n; *  - &quot;addr&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;size&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;addr+size&quot; doesn&squot;t have any high-bits set&n; *  - OR we are in kernel mode.&n; */
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size,mask) &bslash;&n;(((mask)&amp;((addr | size | (addr+size)) &gt;&gt; 42))==0)
DECL|macro|__access_mask
mdefine_line|#define __access_mask (-(long)get_fs())
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;__access_ok(((unsigned long)(addr)),(size),__access_mask)
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; *&n; * As the alpha uses the same address space for kernel and user&n; * data, we can just do these as direct assignments.&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;__put_user((x),(ptr),sizeof(*(ptr)),__access_mask)
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) __get_user((x),(ptr),sizeof(*(ptr)),__access_mask)
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n)   __copy_tofrom_user((to),(from),(n),__cu_to)
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) __copy_tofrom_user((to),(from),(n),__cu_from)
multiline_comment|/*&n; * Not pretty? What do you mean not &quot;not pretty&quot;?&n; */
r_extern
r_void
id|__copy_user
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__copy_tofrom_user
mdefine_line|#define __copy_tofrom_user(to,from,n,v) ({ &bslash;&n;register void * __cu_to __asm__(&quot;$6&quot;); &bslash;&n;register const void * __cu_from __asm__(&quot;$7&quot;); &bslash;&n;register long __cu_len __asm__(&quot;$0&quot;); &bslash;&n;__cu_to = (to); __cu_from = (from); &bslash;&n;__cu_len = (n); &bslash;&n;if (__access_ok(((unsigned long)(v)),__cu_len,__access_mask)) { &bslash;&n;register void * __cu_ex __asm__(&quot;$8&quot;); &bslash;&n;__cu_ex = &amp;current-&gt;tss.ex; &bslash;&n;__asm__ __volatile__(&quot;jsr $28,(%7),__copy_user&quot; &bslash;&n;:&quot;=r&quot; (__cu_len), &quot;=r&quot; (__cu_from), &quot;=r&quot; (__cu_to) &bslash;&n;:&quot;0&quot; (__cu_len), &quot;1&quot; (__cu_from), &quot;2&quot; (__cu_to), &bslash;&n; &quot;r&quot; (__cu_ex), &quot;r&quot; (__copy_user) &bslash;&n;:&quot;$1&quot;,&quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;memory&quot;); &bslash;&n;} __cu_len; })
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr,size,mask) ({ &bslash;&n;register long __gu_err __asm__(&quot;$0&quot;); &bslash;&n;register long __gu_val __asm__(&quot;$1&quot;); &bslash;&n;register long __gu_addr __asm__(&quot;$2&quot;); &bslash;&n;register void * __gu_ex __asm__(&quot;$3&quot;); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__gu_ex = &amp;current-&gt;tss.ex; &bslash;&n;__gu_err = -EFAULT; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;if (__access_ok(__gu_addr,size,mask)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(8); break; &bslash;&n;case 2: __get_user_asm(16); break; &bslash;&n;case 4: __get_user_asm(32); break; &bslash;&n;case 8: __get_user_asm(64); break; &bslash;&n;default: __get_user_asm(unknown); break; &bslash;&n;} } x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
r_extern
r_void
id|__get_user_8
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_16
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_32
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_64
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x) &bslash;&n;__asm__ __volatile__(&quot;jsr $28,(%4),__get_user_&quot; #x &bslash;&n;:&quot;=r&quot; (__gu_err),&quot;=r&quot; (__gu_val) &bslash;&n;:&quot;r&quot; (__gu_ex), &quot;r&quot; (__gu_addr),&quot;r&quot; (__get_user_##x) &bslash;&n;:&quot;$4&quot;,&quot;$5&quot;,&quot;$28&quot;)
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr,size,mask) ({ &bslash;&n;register long __pu_err __asm__(&quot;$0&quot;); &bslash;&n;register __typeof__(*(ptr)) __pu_val __asm__(&quot;$6&quot;); &bslash;&n;register long __pu_addr __asm__(&quot;$7&quot;); &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__pu_err = -EFAULT; &bslash;&n;if (__access_ok(__pu_addr,size,mask)) { &bslash;&n;register void * __pu_ex __asm__(&quot;$8&quot;); &bslash;&n;__pu_ex = &amp;current-&gt;tss.ex; &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(8); break; &bslash;&n;case 2: __put_user_asm(16); break; &bslash;&n;case 4: __put_user_asm(32); break; &bslash;&n;case 8: __put_user_asm(64); break; &bslash;&n;default: __put_user_asm(unknown); break; &bslash;&n;} } __pu_err; })
r_extern
r_void
id|__put_user_8
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_16
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_32
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_64
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__put_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x) &bslash;&n;__asm__ __volatile__(&quot;jsr $28,(%5),__put_user_&quot; #x &bslash;&n;:&quot;=r&quot; (__pu_err),&quot;=r&quot; (__pu_val) &bslash;&n;:&quot;1&quot; (__pu_val), &quot;r&quot; (__pu_ex), &quot;r&quot; (__pu_addr), &quot;r&quot; (__put_user_##x) &bslash;&n;:&quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$6&quot;,&quot;$28&quot;)
macro_line|#endif /* _ASM_SEGMENT_H */
eof
