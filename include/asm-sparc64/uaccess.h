multiline_comment|/* $Id: uaccess.h,v 1.6 1997/03/03 16:51:54 jj Exp $ */
macro_line|#ifndef _ASM_UACCESS_H
DECL|macro|_ASM_UACCESS_H
mdefine_line|#define _ASM_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Sparc is not segmented, however we need to be able to fool verify_area()&n; * when doing system calls from kernel mode legitimately.&n; *&n; * &quot;For historical reasons, these macros are grossly misnamed.&quot; -Linus&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS   0
DECL|macro|USER_DS
mdefine_line|#define USER_DS     -1
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
multiline_comment|/* We have there a nice not-mapped page at page_offset - PAGE_SIZE, so that this test&n; * can be fairly lightweight.&n; * No one can read/write anything from userland in the kernel space by setting&n; * large size and address near to page_offset - a fault will break his intentions.&n; */
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) ((addr) &lt; PAGE_OFFSET)
DECL|macro|__kernel_ok
mdefine_line|#define __kernel_ok (get_fs() == KERNEL_DS)
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size) (__user_ok((addr) &amp; get_fs(),(size)))
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
mdefine_line|#define put_user(x,ptr) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user_check((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr))); })
DECL|macro|put_user_ret
mdefine_line|#define put_user_ret(x,ptr,retval) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user_check_ret((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr)),retval); })
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user_check((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr))); })
DECL|macro|get_user_ret
mdefine_line|#define get_user_ret(x,ptr,retval) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user_check_ret((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr)),retval); })
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the user has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) __put_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user_ret
mdefine_line|#define __put_user_ret(x,ptr,retval) __put_user_nocheck_ret((x),(ptr),sizeof(*(ptr)),retval)
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) __get_user_nocheck((x),(ptr),sizeof(*(ptr)),__typeof__(*(ptr)))
DECL|macro|__get_user_ret
mdefine_line|#define __get_user_ret(x,ptr,retval) __get_user_nocheck_ret((x),(ptr),sizeof(*(ptr)),__typeof__(*(ptr)),retval)
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
mdefine_line|#define __put_user_check(data,addr,size) ({ &bslash;&n;register int __pu_ret; &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(data,b,addr,__pu_ret); break; &bslash;&n;case 2: __put_user_asm(data,h,addr,__pu_ret); break; &bslash;&n;case 4: __put_user_asm(data,w,addr,__pu_ret); break; &bslash;&n;case 8: __put_user_asm(data,x,addr,__pu_ret); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} } else { __pu_ret = -EFAULT; } __pu_ret; })
DECL|macro|__put_user_check_ret
mdefine_line|#define __put_user_check_ret(data,addr,size,retval) ({ &bslash;&n;register int __foo __asm__ (&quot;l1&quot;); &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm_ret(data,b,addr,retval,__foo); break; &bslash;&n;case 2: __put_user_asm_ret(data,h,addr,retval,__foo); break; &bslash;&n;case 4: __put_user_asm_ret(data,w,addr,retval,__foo); break; &bslash;&n;case 8: __put_user_asm_ret(data,x,addr,retval,__foo); break; &bslash;&n;default: if (__put_user_bad()) return retval; break; &bslash;&n;} } else return retval; })
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(data,addr,size) ({ &bslash;&n;register int __pu_ret; &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(data,b,addr,__pu_ret); break; &bslash;&n;case 2: __put_user_asm(data,h,addr,__pu_ret); break; &bslash;&n;case 4: __put_user_asm(data,w,addr,__pu_ret); break; &bslash;&n;case 8: __put_user_asm(data,x,addr,__pu_ret); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} __pu_ret; })
DECL|macro|__put_user_nocheck_ret
mdefine_line|#define __put_user_nocheck_ret(data,addr,size,retval) ({ &bslash;&n;register int __foo __asm__ (&quot;l1&quot;); &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm_ret(data,b,addr,retval,__foo); break; &bslash;&n;case 2: __put_user_asm_ret(data,h,addr,retval,__foo); break; &bslash;&n;case 4: __put_user_asm_ret(data,w,addr,retval,__foo); break; &bslash;&n;case 8: __put_user_asm_ret(data,x,addr,retval,__foo); break; &bslash;&n;default: if (__put_user_bad()) return retval; break; &bslash;&n;} })
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x,size,addr,ret)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user asm, inline. */&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;st&quot;#size &quot; %1, [%2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;clr&t;%0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;2:&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;2b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;%3, %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;1b, 3b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=&amp;r&quot; (ret) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)),&t;&t;&t;&bslash;&n;&t; &quot;i&quot; (-EFAULT))
DECL|macro|__put_user_asm_ret
mdefine_line|#define __put_user_asm_ret(x,size,addr,ret,foo)&t;&t;&t;&t;&bslash;&n;if (__builtin_constant_p(ret) &amp;&amp; ret == -EFAULT)&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;st&quot;#size &quot; %1, [%2]&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;1b, __ret_efault&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (foo) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)));&t;&t;&t;&bslash;&n;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Put user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;st&quot;#size &quot; %1, [%2]&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ret&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; restore %%g0, %3, %%o0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;1b, 3b&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=r&quot; (foo) : &quot;r&quot; (x), &quot;r&quot; (__m(addr)), &quot;i&quot; (ret))
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(data,addr,size,type) ({ &bslash;&n;register int __gu_ret; &bslash;&n;register unsigned long __gu_val; &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(__gu_val,ub,addr,__gu_ret); break; &bslash;&n;case 2: __get_user_asm(__gu_val,uh,addr,__gu_ret); break; &bslash;&n;case 4: __get_user_asm(__gu_val,uw,addr,__gu_ret); break; &bslash;&n;case 8: __get_user_asm(__gu_val,x,addr,__gu_ret); break; &bslash;&n;default: __gu_val = 0; __gu_ret = __get_user_bad(); break; &bslash;&n;} } else { __gu_val = 0; __gu_ret = -EFAULT; } data = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_check_ret
mdefine_line|#define __get_user_check_ret(data,addr,size,type,retval) ({ &bslash;&n;register unsigned long __gu_val __asm__ (&quot;l1&quot;); &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm_ret(__gu_val,ub,addr,retval); break; &bslash;&n;case 2: __get_user_asm_ret(__gu_val,uh,addr,retval); break; &bslash;&n;case 4: __get_user_asm_ret(__gu_val,uw,addr,retval); break; &bslash;&n;case 8: __get_user_asm_ret(__gu_val,x,addr,retval); break; &bslash;&n;default: if (__get_user_bad()) return retval; &bslash;&n;} data = (type) __gu_val; } else return retval; })
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(data,addr,size,type) ({ &bslash;&n;register int __gu_ret; &bslash;&n;register unsigned long __gu_val; &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(__gu_val,ub,addr,__gu_ret); break; &bslash;&n;case 2: __get_user_asm(__gu_val,uh,addr,__gu_ret); break; &bslash;&n;case 4: __get_user_asm(__gu_val,uw,addr,__gu_ret); break; &bslash;&n;case 8: __get_user_asm(__gu_val,x,addr,__gu_ret); break; &bslash;&n;default: __gu_val = 0; __gu_ret = __get_user_bad(); break; &bslash;&n;} data = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_nocheck_ret
mdefine_line|#define __get_user_nocheck_ret(data,addr,size,type,retval) ({ &bslash;&n;register unsigned long __gu_val __asm__ (&quot;l1&quot;); &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm_ret(__gu_val,ub,addr,retval); break; &bslash;&n;case 2: __get_user_asm_ret(__gu_val,uh,addr,retval); break; &bslash;&n;case 4: __get_user_asm_ret(__gu_val,uw,addr,retval); break; &bslash;&n;case 8: __get_user_asm_ret(__gu_val,x,addr,retval); break; &bslash;&n;default: if (__get_user_bad()) return retval; &bslash;&n;} data = (type) __gu_val; })
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x,size,addr,ret)&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user asm, inline. */&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;ld&quot;#size &quot; [%2], %1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;clr&t;%0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;2:&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;clr&t;%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b&t;2b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;%3, %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;1b, 3b&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=&amp;r&quot; (ret), &quot;=&amp;r&quot; (x) : &quot;r&quot; (__m(addr)),&t;&t;&t;&bslash;&n;&t; &quot;i&quot; (-EFAULT))
DECL|macro|__get_user_asm_ret
mdefine_line|#define __get_user_asm_ret(x,size,addr,retval)&t;&t;&t;&t;&bslash;&n;if (__builtin_constant_p(retval) &amp;&amp; retval == -EFAULT)&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;ld&quot;#size &quot; [%1], %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;1b,__ret_efault&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=&amp;r&quot; (x) : &quot;r&quot; (__m(addr)));&t;&t;&t;&t;&t;&bslash;&n;else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;/* Get user asm ret, inline. */&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&bslash;t&quot;&t;&quot;ld&quot;#size &quot; [%1], %0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section .fixup,#alloc,#execinstr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;3:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ret&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; restore %%g0, %2, %%o0&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&t;4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.word&t;1b, 3b&bslash;n&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=&amp;r&quot; (x) : &quot;r&quot; (__m(addr)), &quot;i&quot; (retval))
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
id|__copy_user
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
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;void *__copy_to = (void *) (to); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok(__copy_to, __copy_size)) { &bslash;&n;__copy_res = __copy_user(__copy_to, (void *) (from), __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|copy_to_user_ret
mdefine_line|#define copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_to_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((unsigned long)(to),&t;&bslash;&n;&t;&t;    (unsigned long)(from), n)
DECL|macro|__copy_to_user_ret
mdefine_line|#define __copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (__copy_to_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;void *__copy_from = (void *) (from); &bslash;&n;__kernel_size_t __copy_size = (__kernel_size_t) (n); &bslash;&n;__kernel_size_t __copy_res; &bslash;&n;if(__copy_size &amp;&amp; __access_ok(__copy_from, __copy_size)) { &bslash;&n;__copy_res = __copy_user((void *) (to), __copy_from, __copy_size); &bslash;&n;} else __copy_res = __copy_size; &bslash;&n;__copy_res; })
DECL|macro|copy_from_user_ret
mdefine_line|#define copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_from_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n)&t;&t;&bslash;&n;&t;__copy_user((unsigned long)(to),&t;&bslash;&n;&t;&t;    (unsigned long)(from), n)
DECL|macro|__copy_from_user_ret
mdefine_line|#define __copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (__copy_from_user(to,from,n)) &bslash;&n;&t;return retval; &bslash;&n;})
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
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;unsigned long __clear_addr = (unsigned long) (addr); &bslash;&n;int __clear_size = (int) (n); &bslash;&n;int __clear_res; &bslash;&n;if(__clear_size &amp;&amp; __access_ok(__clear_addr, __clear_size)) { &bslash;&n;__clear_res = __clear_user(__clear_addr, __clear_size); &bslash;&n;} else __clear_res = __clear_size; &bslash;&n;__clear_res; })
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
mdefine_line|#define strncpy_from_user(dest,src,count) ({ &bslash;&n;unsigned long __sfu_src = (unsigned long) (src); &bslash;&n;int __sfu_count = (int) (count); &bslash;&n;long __sfu_res = -EFAULT; &bslash;&n;if(__access_ok(__sfu_src, __sfu_count)) { &bslash;&n;__sfu_res = __strncpy_from_user((unsigned long) (dest), __sfu_src, __sfu_count); &bslash;&n;} __sfu_res; })
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
DECL|function|strlen_user
r_extern
id|__inline__
r_int
id|strlen_user
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|str
comma
l_int|0
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
id|__strlen_user
c_func
(paren
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif  /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_UACCESS_H */
eof
