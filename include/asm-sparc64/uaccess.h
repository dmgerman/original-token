multiline_comment|/* $Id: uaccess.h,v 1.14 1997/06/13 14:03:11 davem Exp $ */
macro_line|#ifndef _ASM_UACCESS_H
DECL|macro|_ASM_UACCESS_H
mdefine_line|#define _ASM_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Sparc is not segmented, however we need to be able to fool verify_area()&n; * when doing system calls from kernel mode legitimately.&n; *&n; * &quot;For historical reasons, these macros are grossly misnamed.&quot; -Linus&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS   0x00
DECL|macro|USER_DS
mdefine_line|#define USER_DS     0x2B /* har har har */
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
DECL|macro|get_fs
mdefine_line|#define get_fs() (current-&gt;tss.current_ds)
DECL|macro|get_ds
mdefine_line|#define get_ds() (KERNEL_DS)
DECL|macro|set_fs
mdefine_line|#define set_fs(val)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;tss.current_ds = (val);&t;&bslash;&n;&t;if ((val) == KERNEL_DS) {&t;&t;&bslash;&n;&t;&t;flushw_user ();&t;&t;&t;&bslash;&n;&t;&t;current-&gt;tss.ctx = 0;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;tss.ctx = (current-&gt;mm-&gt;context &amp; 0x1fff); &bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;spitfire_set_secondary_context(current-&gt;tss.ctx); &bslash;&n;&t;__asm__ __volatile__(&quot;flush %g4&quot;);&t;&bslash;&n;} while(0)
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) 1
DECL|macro|__kernel_ok
mdefine_line|#define __kernel_ok (get_fs() == KERNEL_DS)
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) 1
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) 1
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The exception table consists of pairs of addresses: the first is the&n; * address of an instruction that is allowed to fault, and the second is&n; * the address at which the program should continue.  No registers are&n; * modified, so it is entirely up to the continuation code to figure out&n; * what to do.&n; *&n; * All the routines below use bits of fixup code that are out of line&n; * with the main instruction path.  This means when everything is well,&n; * we don&squot;t even have to jump over them.  Further, they do not intrude&n; * on our cache or tlb entries.&n; *&n; * There is a special way how to put a range of potentially faulting&n; * insns (like twenty ldd/std&squot;s with now intervening other instructions)&n; * You specify address of first in insn and 0 in fixup and in the next&n; * exception_table_entry you specify last potentially faulting insn + 1&n; * and in fixup the routine which should handle the fault.&n; * That fixup code will get&n; * (faulting_insn_address - first_insn_in_the_range_address)/4&n; * in %g2 (ie. index of the faulting instruction in the range).&n; */
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|insn
DECL|member|fixup
r_int
r_int
id|insn
comma
id|fixup
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Returns 0 if exception not found and fixup otherwise.  */
r_extern
r_int
r_int
id|search_exception_table
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__ret_efault
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the uglyness from the user.&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user_nocheck((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr))); })
DECL|macro|put_user_ret
mdefine_line|#define put_user_ret(x,ptr,retval) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user_nocheck_ret((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr)),retval); })
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user_nocheck((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr))); })
DECL|macro|get_user_ret
mdefine_line|#define get_user_ret(x,ptr,retval) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user_nocheck_ret((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr)),retval); })
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) put_user(x,ptr)
DECL|macro|__put_user_ret
mdefine_line|#define __put_user_ret(x,ptr,retval) put_user_ret(x,ptr,retval)
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) get_user(x,ptr)
DECL|macro|__get_user_ret
mdefine_line|#define __get_user_ret(x,ptr,retval) get_user_ret(x,ptr,retval)
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
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(data,addr,size) ({ &bslash;&n;register int __pu_ret; &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(data,b,addr,__pu_ret); break; &bslash;&n;case 2: __put_user_asm(data,h,addr,__pu_ret); break; &bslash;&n;case 4: __put_user_asm(data,w,addr,__pu_ret); break; &bslash;&n;case 8: __put_user_asm(data,x,addr,__pu_ret); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} __pu_ret; })
DECL|macro|__put_user_nocheck_ret
mdefine_line|#define __put_user_nocheck_ret(data,addr,size,retval) ({ &bslash;&n;register int __foo __asm__ (&quot;l1&quot;); &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm_ret(data,b,addr,retval,__foo); break; &bslash;&n;case 2: __put_user_asm_ret(data,h,addr,retval,__foo); break; &bslash;&n;case 4: __put_user_asm_ret(data,w,addr,retval,__foo); break; &bslash;&n;case 8: __put_user_asm_ret(data,x,addr,retval,__foo); break; &bslash;&n;default: if (__put_user_bad()) return retval; break; &bslash;&n;} })
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x,size,addr,ret)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user asm, inline. */&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;st&quot;#size &quot;a %1, [%2] %4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;clr&t;%0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;2:&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;2b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;%3, %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.xword&t;1b, 3b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (ret) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;&t; &quot;i&quot; (-EFAULT), &quot;i&quot; (ASI_S))
DECL|macro|__put_user_asm_ret
mdefine_line|#define __put_user_asm_ret(x,size,addr,ret,foo)&t;&t;&t;&t;&bslash;&n;if (__builtin_constant_p(ret) &amp;&amp; ret == -EFAULT)&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;st&quot;#size &quot;a %1, [%2] %3&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.xword&t;1b, __ret_efault&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (foo) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)), &quot;i&quot; (ASI_S));&t;&t;&bslash;&n;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;st&quot;#size &quot;a %1, [%2] %4&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ret&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; restore %%g0, %3, %%o0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.xword&t;1b, 3b&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (foo) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)),&t;&t;&t;&t;&bslash;&n;         &quot;i&quot; (ret), &quot;i&quot; (ASI_S))
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(data,addr,size,type) ({ &bslash;&n;register int __gu_ret; &bslash;&n;register unsigned long __gu_val; &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(__gu_val,ub,addr,__gu_ret); break; &bslash;&n;case 2: __get_user_asm(__gu_val,uh,addr,__gu_ret); break; &bslash;&n;case 4: __get_user_asm(__gu_val,uw,addr,__gu_ret); break; &bslash;&n;case 8: __get_user_asm(__gu_val,x,addr,__gu_ret); break; &bslash;&n;default: __gu_val = 0; __gu_ret = __get_user_bad(); break; &bslash;&n;} data = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_nocheck_ret
mdefine_line|#define __get_user_nocheck_ret(data,addr,size,type,retval) ({ &bslash;&n;register unsigned long __gu_val __asm__ (&quot;l1&quot;); &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm_ret(__gu_val,ub,addr,retval); break; &bslash;&n;case 2: __get_user_asm_ret(__gu_val,uh,addr,retval); break; &bslash;&n;case 4: __get_user_asm_ret(__gu_val,uw,addr,retval); break; &bslash;&n;case 8: __get_user_asm_ret(__gu_val,x,addr,retval); break; &bslash;&n;default: if (__get_user_bad()) return retval; &bslash;&n;} data = (type) __gu_val; })
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x,size,addr,ret)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user asm, inline. */&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;ld&quot;#size &quot;a [%2] %4, %1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;clr&t;%0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;2:&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;clr&t;%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;2b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;%3, %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.xword&t;1b, 3b&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (ret), &quot;=r&quot; (x) : &quot;r&quot; (__m(addr)),&t;&t;&t;&bslash;&n;&t; &quot;i&quot; (-EFAULT), &quot;i&quot; (ASI_S))
DECL|macro|__get_user_asm_ret
mdefine_line|#define __get_user_asm_ret(x,size,addr,retval)&t;&t;&t;&t;&bslash;&n;if (__builtin_constant_p(retval) &amp;&amp; retval == -EFAULT)&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;ld&quot;#size &quot;a [%1] %2, %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.xword&t;1b,__ret_efault&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (x) : &quot;r&quot; (__m(addr)), &quot;i&quot; (ASI_S));&t;&t;&t;&bslash;&n;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;ld&quot;#size &quot;a [%1] %2, %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ret&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; restore %%g0, %3, %%o0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.xword&t;1b, 3b&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (x) : &quot;r&quot; (__m(addr)), &quot;i&quot; (retval), &quot;i&quot; (ASI_S))
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|__kernel_size_t
id|__copy_to_user
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
id|__kernel_size_t
id|size
)paren
suffix:semicolon
r_extern
id|__kernel_size_t
id|__copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
id|__kernel_size_t
id|size
)paren
suffix:semicolon
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n) &bslash;&n;&t;__copy_to_user((void *)(to), &bslash;&n;&t;(void *) (from), (__kernel_size_t)(n))
DECL|macro|copy_to_user_ret
mdefine_line|#define copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_to_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_to_user_ret
mdefine_line|#define __copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (__copy_to_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_from_user((void *)(to),&t;&bslash;&n;&t;&t;    (void *)(from), (__kernel_size_t)(n))
DECL|macro|copy_from_user_ret
mdefine_line|#define copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_from_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_from_user_ret
mdefine_line|#define __copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (__copy_from_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|function|__clear_user
r_extern
id|__inline__
id|__kernel_size_t
id|__clear_user
c_func
(paren
r_void
op_star
id|addr
comma
id|__kernel_size_t
id|size
)paren
(brace
id|__kernel_size_t
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
"&quot;"
dot
id|section
id|__ex_table
comma
macro_line|#alloc
dot
id|align
l_int|8
dot
id|xword
l_float|1f
comma
l_int|3
dot
id|previous
l_int|1
suffix:colon
id|wr
op_mod
op_mod
id|g0
comma
op_mod
l_int|3
comma
op_mod
op_mod
id|asi
id|mov
op_mod
l_int|2
comma
op_mod
op_mod
id|o1
id|call
id|__bzero_noasi
id|mov
op_mod
l_int|1
comma
op_mod
op_mod
id|o0
id|mov
op_mod
op_mod
id|o0
comma
op_mod
l_int|0
l_string|&quot; : &quot;
op_assign
id|r
l_string|&quot; (ret) : &quot;
id|r
l_string|&quot; (addr), &quot;
id|r
l_string|&quot; (size), &quot;
id|i
"&quot;"
(paren
id|ASI_S
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;o0&quot;
comma
l_string|&quot;o1&quot;
comma
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|clear_user
mdefine_line|#define clear_user(addr,n) &bslash;&n;&t;__clear_user((void *)(addr), (__kernel_size_t)(n))
DECL|macro|clear_user_ret
mdefine_line|#define clear_user_ret(addr,size,retval) ({ &bslash;&n;if (clear_user(addr,size)) &bslash;&n;&t;return retval; &bslash;&n;})
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
mdefine_line|#define strncpy_from_user(dest,src,count) &bslash;&n;&t;__strncpy_from_user((unsigned long)(dest), (unsigned long)(src), (int)(count))
r_extern
r_int
id|__strlen_user
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|macro|strlen_user
mdefine_line|#define strlen_user __strlen_user
macro_line|#endif  /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_UACCESS_H */
eof
