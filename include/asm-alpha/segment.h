macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
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
mdefine_line|#define __access_ok(addr,size,mask) &bslash;&n;&t;(((mask)&amp;((addr | size | (addr+size)) &gt;&gt; 42))==0)
DECL|macro|__access_mask
mdefine_line|#define __access_mask (-(long)get_fs())
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;&t;__access_ok(((unsigned long)(addr)),(size),__access_mask)
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * As the alpha uses the same address space for kernel and user&n; * data, we can just do these as direct assignments.  (Of course, the&n; * exception handling means that it&squot;s no longer &quot;just&quot;...)&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof/typeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
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
mdefine_line|#define __copy_tofrom_user(to,from,n,v)&t;&t;&t;&t;&t;    &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;register void * __cu_to __asm__(&quot;$6&quot;) = (to);&t;&t;&t;    &bslash;&n;&t;register const void * __cu_from __asm__(&quot;$7&quot;) = (from);&t;&t;    &bslash;&n;&t;register long __cu_len __asm__(&quot;$0&quot;) = (n);&t;&t;&t;    &bslash;&n;&t;if (__access_ok(((long)(v)),__cu_len,__access_mask)) {&t;&t;    &bslash;&n;&t;&t;register void * __cu_ex __asm__(&quot;$8&quot;);&t;&t;&t;    &bslash;&n;&t;&t;__cu_ex = &amp;current-&gt;tss.ex;&t;&t;&t;&t;    &bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;&t;&quot;jsr $28,(%7),__copy_user&quot;&t;&t;&t;    &bslash;&n;&t;&t;&t;: &quot;=r&quot; (__cu_len), &quot;=r&quot; (__cu_from), &quot;=r&quot; (__cu_to) &bslash;&n;&t;&t;&t;: &quot;0&quot; (__cu_len), &quot;1&quot; (__cu_from), &quot;2&quot; (__cu_to),   &bslash;&n;&t;&t;&t;  &quot;r&quot; (__cu_ex), &quot;r&quot; (__copy_user)&t;&t;    &bslash;&n;&t;&t;&t;: &quot;$1&quot;,&quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$28&quot;,&quot;memory&quot;);&t;    &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;__cu_len;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;})
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr,size,mask)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) *__gu_addr = (ptr);&t;&t;&bslash;&n;&t;if (__access_ok((long)__gu_addr,size,mask)) {&t;&t;&bslash;&n;&t;&t;long __gu_ex_count = current-&gt;tss.ex.count;&t;&bslash;&n;&t;&t;switch (size) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 1: __get_user_8; break;&t;&t;&t;&bslash;&n;&t;&t;case 2: __get_user_16; break;&t;&t;&t;&bslash;&n;&t;&t;case 4: __get_user_32; break;&t;&t;&t;&bslash;&n;&t;&t;case 8: __get_user_64; break;&t;&t;&t;&bslash;&n;&t;&t;default: __get_user_unknown(); break;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_64
mdefine_line|#define __get_user_64&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __get_user_64 */&bslash;n&bslash;t&quot;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;/* exception! */&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%3&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;ldq %1,%2&bslash;n&bslash;t&quot;&t;&t;/* actual data load */&t;&t;   &bslash;&n;&t;&t;&quot;stq %4,%3&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __get_user_64 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_err), &quot;=r&quot;(__gu_val)&t;&t;&t;   &bslash;&n;&t;&t;: &quot;m&quot;(*__gu_addr), &quot;m&quot;(current-&gt;tss.ex.count),&t;&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__gu_ex_count), &quot;r&quot;(__gu_ex_count+1),&t;&t;   &bslash;&n;&t;&t;  &quot;0&quot;(__gu_err), &quot;1&quot;(__gu_val)&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
DECL|macro|__get_user_32
mdefine_line|#define __get_user_32&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __get_user_32 */&bslash;n&bslash;t&quot;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;/* exception! */&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%3&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;ldl %1,%2&bslash;n&bslash;t&quot;&t;&t;/* actual data load */&t;&t;   &bslash;&n;&t;&t;&quot;stq %4,%3&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __get_user_32 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_err), &quot;=r&quot;(__gu_val)&t;&t;&t;   &bslash;&n;&t;&t;: &quot;m&quot;(*__gu_addr), &quot;m&quot;(current-&gt;tss.ex.count),&t;&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__gu_ex_count), &quot;r&quot;(__gu_ex_count+1),&t;&t;   &bslash;&n;&t;&t;  &quot;0&quot;(__gu_err), &quot;1&quot;(__gu_val)&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
DECL|macro|__get_user_16
mdefine_line|#define __get_user_16&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __get_user_16 */&bslash;n&bslash;t&quot;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;/* exception! */&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %6,%4&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;ldq_u %1,%2&bslash;n&bslash;t&quot;&t;/* actual data load */&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%4&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&bslash;t&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;extwl %1,%3,%1&bslash;n&quot;&t;/* extract the short */&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __get_user_16 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_err), &quot;=r&quot;(__gu_val)&t;&t;&t;   &bslash;&n;&t;&t;: &quot;m&quot;(*__gu_addr), &quot;r&quot;(__gu_addr),&t;&t;&t;   &bslash;&n;&t;&t;  &quot;m&quot;(current-&gt;tss.ex.count), &quot;r&quot;(__gu_ex_count),&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__gu_ex_count+1), &quot;0&quot;(__gu_err), &quot;1&quot;(__gu_val)&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
DECL|macro|__get_user_8
mdefine_line|#define __get_user_8&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __get_user_8 */&bslash;n&bslash;t&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;/* exception! */&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %6,%4&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;ldq_u %1,%2&bslash;n&bslash;t&quot;&t;/* actual data load */&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%4&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&bslash;t&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;extbl %1,%3,%1&bslash;n&quot;&t;/* extract the byte */&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __get_user_8 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__gu_err), &quot;=r&quot;(__gu_val)&t;&t;&t;   &bslash;&n;&t;&t;: &quot;m&quot;(*__gu_addr), &quot;r&quot;(__gu_addr),&t;&t;&t;   &bslash;&n;&t;&t;  &quot;m&quot;(current-&gt;tss.ex.count), &quot;r&quot;(__gu_ex_count),&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__gu_ex_count+1), &quot;0&quot;(__gu_err), &quot;1&quot;(__gu_val)&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
r_extern
r_void
id|__put_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr,size,mask)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&bslash;&n;        __typeof__(*(ptr)) __pu_val = (x);&t;&t;&t;&bslash;&n;&t;if (__access_ok((long)__pu_addr,size,mask)) {&t;&t;&bslash;&n;&t;&t;long __pu_ex_count = current-&gt;tss.ex.count;&t;&bslash;&n;&t;&t;switch (size) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case 1: __put_user_8; break;&t;&t;&t;&bslash;&n;&t;&t;case 2: __put_user_16; break;&t;&t;&t;&bslash;&n;&t;&t;case 4: __put_user_32; break;&t;&t;&t;&bslash;&n;&t;&t;case 8: __put_user_64; break;&t;&t;&t;&bslash;&n;&t;&t;default: __put_user_unknown(); break;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_64
mdefine_line|#define __put_user_64&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __put_user_64 */&bslash;n&bslash;t&quot;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;/* exception! */&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%3&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;stq %2,%1&bslash;n&bslash;t&quot;&t;&t;/* actual data store */&t;&t;   &bslash;&n;&t;&t;&quot;stq %4,%3&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __put_user_64 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err), &quot;=m&quot;(*__pu_addr)&t;&t;&t;   &bslash;&n;&t;&t;: &quot;r&quot;(__pu_val), &quot;m&quot;(current-&gt;tss.ex.count),&t;&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__pu_ex_count), &quot;r&quot;(__pu_ex_count+1),&t;&t;   &bslash;&n;&t;&t;  &quot;0&quot;(__pu_err)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
DECL|macro|__put_user_32
mdefine_line|#define __put_user_32&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __put_user_32 */&bslash;n&bslash;t&quot;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;/* exception! */&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%3&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;stl %2,%1&bslash;n&bslash;t&quot;&t;&t;/* actual data store */&t;&t;   &bslash;&n;&t;&t;&quot;stq %4,%3&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __put_user_32 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err), &quot;=m&quot;(*__pu_addr)&t;&t;&t;   &bslash;&n;&t;&t;: &quot;r&quot;(__pu_val), &quot;m&quot;(current-&gt;tss.ex.count),&t;&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__pu_ex_count), &quot;r&quot;(__pu_ex_count+1),&t;&t;   &bslash;&n;&t;&t;  &quot;0&quot;(__pu_err)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
DECL|macro|__put_user_16
mdefine_line|#define __put_user_16&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __put_user_16 */&bslash;n&bslash;t&quot;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;lda %0,%7&bslash;n&bslash;t&quot;&t;&t;/* exception! error = -EFAULT */   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %6,%4&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;ldq_u %0,%1&bslash;n&bslash;t&quot;&t;/* masked data store */&t;&t;   &bslash;&n;&t;&t;&quot;inswl %2,%3,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;mskwl %0,%3,%0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;or %0,%2,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq_u %2,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%4&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __put_user_16 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err), &quot;=m&quot;(*__pu_addr), &quot;=r&quot;(__pu_val)&t;   &bslash;&n;&t;&t;: &quot;r&quot;(__pu_addr), &quot;m&quot;(current-&gt;tss.ex.count),&t;&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__pu_ex_count), &quot;r&quot;(__pu_ex_count+1), &quot;i&quot;(-EFAULT),  &bslash;&n;&t;&t;  &quot;2&quot;(__pu_val)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
DECL|macro|__put_user_8
mdefine_line|#define __put_user_8&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;__asm__(&quot;/* Inline __put_user_8 */&bslash;n&bslash;t&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;br $28,1f&bslash;n&bslash;t&quot;&t;&t;/* set up exception address */&t;   &bslash;&n;&t;&t;&quot;lda %0,%7&bslash;n&bslash;t&quot;&t;&t;/* exception! error = -EFAULT */   &bslash;&n;&t;&t;&quot;br 2f&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %6,%4&bslash;n&bslash;t&quot;&t;&t;/* store inc&squot;ed exception count */ &bslash;&n;&t;&t;&quot;ldq_u %0,%1&bslash;n&bslash;t&quot;&t;/* masked data store */&t;&t;   &bslash;&n;&t;&t;&quot;insbl %2,%3,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;mskbl %0,%3,%0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;or %0,%2,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq_u %2,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;stq %5,%4&bslash;n&bslash;t&quot;&t;&t;/* restore exception count */&t;   &bslash;&n;&t;&t;&quot;clr %0&bslash;n&quot;&t;&t;/* no exception: error = 0 */&t;   &bslash;&n;&t;&t;&quot;2:&bslash;t/* End __put_user_8 */&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=r&quot;(__pu_err), &quot;=m&quot;(*__pu_addr), &quot;=r&quot;(__pu_val)&t;   &bslash;&n;&t;&t;: &quot;r&quot;(__pu_addr), &quot;m&quot;(current-&gt;tss.ex.count),&t;&t;   &bslash;&n;&t;&t;  &quot;r&quot;(__pu_ex_count), &quot;r&quot;(__pu_ex_count+1), &quot;i&quot;(-EFAULT),  &bslash;&n;&t;&t;  &quot;2&quot;(__pu_val)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;$28&quot;)
r_extern
r_void
id|__clear_user
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|clear_user
mdefine_line|#define clear_user(to,n)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register void * __cl_to __asm__(&quot;$6&quot;) = (to);&t;&t;&t;&bslash;&n;&t;register long __cl_len __asm__(&quot;$0&quot;) = (n);&t;&t;&t;&bslash;&n;&t;if (__access_ok(((long)__cl_to),__cl_len,__access_mask)) {&t;&bslash;&n;&t;&t;register void * __cl_ex __asm__(&quot;$7&quot;);&t;&t;&t;&bslash;&n;&t;&t;__cl_ex = &amp;current-&gt;tss.ex;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;jsr $28,(%2),__clear_user&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot;(__cl_len), &quot;=r&quot;(__cl_to)&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;r&quot;(__clear_user), &quot;r&quot;(__cl_ex),&t;&t;&bslash;&n;&t;&t;&t;  &quot;0&quot;(__cl_len), &quot;1&quot;(__cl_to)&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;$1&quot;,&quot;$2&quot;,&quot;$3&quot;,&quot;$4&quot;,&quot;$5&quot;,&quot;$28&quot;,&quot;memory&quot;);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__cl_len;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Returns: -EFAULT if exception before terminator, N if the entire&n;   buffer filled, else strlen.  */
r_struct
id|exception_struct
suffix:semicolon
r_extern
r_int
id|__strncpy_from_user
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__to_len
comma
r_struct
id|exception_struct
op_star
)paren
suffix:semicolon
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(to,from,n)&t;&t;&t;&t;&t;      &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;char * __sfu_to = (to);&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const char * __sfu_from = (from);&t;&t;&t;&t;      &bslash;&n;&t;long __sfu_len = (n), __sfu_ret = -EFAULT;&t;&t;&t;      &bslash;&n;&t;if (__access_ok(((long)__sfu_from),__sfu_len,__access_mask)) {&t;      &bslash;&n;&t;&t;__sfu_ret = __strncpy_from_user(__sfu_to,__sfu_from,&t;      &bslash;&n;&t;&t;&t;&t;&t;&t;__sfu_len, &amp;current-&gt;tss.ex); &bslash;&n;&t;__sfu_ret;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;})
macro_line|#endif /* _ASM_SEGMENT_H */
eof
