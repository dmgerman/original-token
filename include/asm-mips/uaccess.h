multiline_comment|/*&n; * include/asm-mips/uaccess.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Ralf Baechle&n; *&n; * $Id: uaccess.h,v 1.4 1997/07/01 08:23:56 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_UACCESS_H
DECL|macro|__ASM_MIPS_UACCESS_H
mdefine_line|#define __ASM_MIPS_UACCESS_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
DECL|macro|STR
mdefine_line|#define STR(x)  __STR(x)
DECL|macro|__STR
mdefine_line|#define __STR(x)  #x
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS 0
DECL|macro|USER_DS
mdefine_line|#define USER_DS 1
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ    0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE   1
r_extern
r_int
id|active_ds
suffix:semicolon
DECL|macro|get_fs
mdefine_line|#define get_fs()        active_ds
DECL|macro|set_fs
mdefine_line|#define set_fs(x)       (active_ds=(x))
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
id|KERNEL_DS
suffix:semicolon
)brace
multiline_comment|/*&n; * Is a address valid? This does a straighforward calculation rather&n; * than tests.&n; *&n; * Address valid if:&n; *  - &quot;addr&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;size&quot; doesn&squot;t have any high-bits set&n; *  - AND &quot;addr+size&quot; doesn&squot;t have any high-bits set&n; *  - OR we are in kernel mode.&n; */
DECL|macro|__access_ok
mdefine_line|#define __access_ok(addr,size,mask) &bslash;&n;&t;(((__signed__ long)((mask)&amp;(addr | size | (addr+size)))) &gt;= 0)
DECL|macro|__access_mask
mdefine_line|#define __access_mask (-(long)get_fs())
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;__access_ok(((unsigned long)(addr)),(size),__access_mask)
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
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines ...&n; * They automatically use the right size if we just have the right&n; * pointer type ...&n; *&n; * As MIPS uses the same address space for kernel and user data, we&n; * can just do these as direct assignments.&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;__put_user_check((x),(ptr),sizeof(*(ptr)),__access_mask)
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) __get_user_check((x),(ptr),sizeof(*(ptr)),__access_mask)
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the user has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) __put_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
multiline_comment|/*&n; * The &quot;xxx_ret&quot; versions return constant specified in third argument, if&n; * something bad happens. These macros can be optimized for the&n; * case of just returning from the function xxx_ret is used.&n; */
DECL|macro|put_user_ret
mdefine_line|#define put_user_ret(x,ptr,ret) ({ &bslash;&n;if (put_user(x,ptr)) return ret; })
DECL|macro|get_user_ret
mdefine_line|#define get_user_ret(x,ptr,ret) ({ &bslash;&n;if (get_user(x,ptr)) return ret; })
DECL|macro|__put_user_ret
mdefine_line|#define __put_user_ret(x,ptr,ret) ({ &bslash;&n;if (__put_user(x,ptr)) return ret; })
DECL|macro|__get_user_ret
mdefine_line|#define __get_user_ret(x,ptr,ret) ({ &bslash;&n;if (__get_user(x,ptr)) return ret; })
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
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n)   __copy_tofrom_user((to),(from),(n),__cu_to)
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) __copy_tofrom_user((to),(from),(n),__cu_from)
r_extern
r_int
id|__copy_user
c_func
(paren
r_void
op_star
id|__to
comma
r_const
r_void
op_star
id|__from
comma
r_int
id|__n
)paren
suffix:semicolon
DECL|macro|__copy_tofrom_user
mdefine_line|#define __copy_tofrom_user(to,from,n,v) ({ &bslash;&n;&t;void * __cu_to; &bslash;&n;&t;const void * __cu_from; &bslash;&n;&t;long __cu_len; &bslash;&n;&t;&bslash;&n;&t;__cu_to = (to); &bslash;&n;&t;__cu_from = (from); &bslash;&n;&t;__cu_len = (n); &bslash;&n;&t;if (__access_ok(((unsigned long)(v)),__cu_len,__access_mask)) &bslash;&n;&t;&t;__cu_len = __copy_user(__cu_to, __cu_from, __cu_len); &bslash;&n;&t;__cu_len; &bslash;&n;})
multiline_comment|/*&n; * Yuck.  We need two variants, one for 64bit operation and one&n; * for 32 bit mode and old iron.&n; */
macro_line|#ifdef __mips64
DECL|macro|__GET_USER_DW
mdefine_line|#define __GET_USER_DW __get_user_asm(&quot;ld&quot;)
macro_line|#else
DECL|macro|__GET_USER_DW
mdefine_line|#define __GET_USER_DW __get_user_asm_ll32
macro_line|#endif
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size) ({ &bslash;&n;long __gu_err; &bslash;&n;__typeof(*(ptr)) __gu_val; &bslash;&n;long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(&quot;lb&quot;); break; &bslash;&n;case 2: __get_user_asm(&quot;lh&quot;); break; &bslash;&n;case 4: __get_user_asm(&quot;lw&quot;); break; &bslash;&n;case 8: __GET_USER_DW; break; &bslash;&n;default: __get_user_unknown(); break; &bslash;&n;} x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size,mask) ({ &bslash;&n;long __gu_err; &bslash;&n;__typeof__(*(ptr)) __gu_val; &bslash;&n;long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;if (__access_ok(__gu_addr,size,mask)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __get_user_asm(&quot;lb&quot;); break; &bslash;&n;case 2: __get_user_asm(&quot;lh&quot;); break; &bslash;&n;case 4: __get_user_asm(&quot;lw&quot;); break; &bslash;&n;case 8: __GET_USER_DW; break; &bslash;&n;default: __get_user_unknown(); break; &bslash;&n;} } x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;t&quot; insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;t.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;la&bslash;t$1,2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t%0,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jr&bslash;t$1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;STR(PTR)&quot;&bslash;t1b,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__gu_err), &quot;=r&quot; (__gu_val) &bslash;&n;&t;:&quot;o&quot; (__m(__gu_addr)), &quot;i&quot; (-EFAULT) &bslash;&n;&t;:&quot;$1&quot;); })
multiline_comment|/*&n; * Get a long long 64 using 32 bit registers.&n; */
DECL|macro|__get_user_asm_ll32
mdefine_line|#define __get_user_asm_ll32 &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;tlw&bslash;t%1,%2&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;tlw&bslash;t%D1,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;t.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;4:&bslash;t.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;la&bslash;t$1,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t%0,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jr&bslash;t$1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;STR(PTR)&quot;&bslash;t1b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;STR(PTR)&quot;&bslash;t2b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__gu_err), &quot;=&amp;r&quot; (__gu_val) &bslash;&n;&t;:&quot;o&quot; (__m(__gu_addr)), &quot;o&quot; (__m(__gu_addr + 4)), &bslash;&n;&t; &quot;i&quot; (-EFAULT) &bslash;&n;&t;:&quot;$1&quot;); })
r_extern
r_void
id|__get_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Yuck.  We need two variants, one for 64bit operation and one&n; * for 32 bit mode and old iron.&n; */
macro_line|#ifdef __mips64
DECL|macro|__PUT_USER_DW
mdefine_line|#define __PUT_USER_DW __put_user_asm(&quot;sd&quot;)
macro_line|#else
DECL|macro|__PUT_USER_DW
mdefine_line|#define __PUT_USER_DW __put_user_asm_ll32
macro_line|#endif
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size) ({ &bslash;&n;long __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(&quot;sb&quot;); break; &bslash;&n;case 2: __put_user_asm(&quot;sh&quot;); break; &bslash;&n;case 4: __put_user_asm(&quot;sw&quot;); break; &bslash;&n;case 8: __PUT_USER_DW; break; &bslash;&n;default: __put_user_unknown(); break; &bslash;&n;} __pu_err; })
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size,mask) ({ &bslash;&n;long __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;if (__access_ok(__pu_addr,size,mask)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __put_user_asm(&quot;sb&quot;); break; &bslash;&n;case 2: __put_user_asm(&quot;sh&quot;); break; &bslash;&n;case 4: __put_user_asm(&quot;sw&quot;); break; &bslash;&n;case 8: __PUT_USER_DW; break; &bslash;&n;default: __put_user_unknown(); break; &bslash;&n;} } __pu_err; })
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;t&quot; insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;t.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;la&bslash;t$1,2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t%0,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jr&bslash;t$1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;STR(PTR)&quot;&bslash;t1b,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__pu_err) &bslash;&n;&t;:&quot;r&quot; (__pu_val), &quot;o&quot; (__m(__pu_addr)), &quot;i&quot; (-EFAULT) &bslash;&n;&t;:&quot;$1&quot;); })
DECL|macro|__put_user_asm_ll32
mdefine_line|#define __put_user_asm_ll32 &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;1:&bslash;tsw&bslash;t%1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;2:&bslash;tsw&bslash;t%D1,%3&bslash;n&quot; &bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;4:&bslash;t.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;la&bslash;t$1,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;li&bslash;t%0,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jr&bslash;t$1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;STR(PTR)&quot;&bslash;t1b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;STR(PTR)&quot;&bslash;t2b,4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__pu_err) &bslash;&n;&t;:&quot;r&quot; (__pu_val), &quot;o&quot; (__m(__pu_addr)), &quot;o&quot; (__m(__pu_addr + 4)), &bslash;&n;&t; &quot;i&quot; (-EFAULT) &bslash;&n;&t;:&quot;$1&quot;); })
r_extern
r_void
id|__put_user_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|copy_to_user_ret
mdefine_line|#define copy_to_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_to_user(to,from,n)) &bslash;&n;        return retval; &bslash;&n;})
DECL|macro|copy_from_user_ret
mdefine_line|#define copy_from_user_ret(to,from,n,retval) ({ &bslash;&n;if (copy_from_user(to,from,n)) &bslash;&n;        return retval; &bslash;&n;})
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to,from,n)                       &bslash;&n;         __copy_user((to),(from),(n))
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to,from,n)                     &bslash;&n;         __copy_user((to),(from),(n))
DECL|macro|__clear_user
mdefine_line|#define __clear_user(addr,size) &bslash;&n;({ &bslash;&n;&t;void *__cu_end; &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;1:&bslash;tsb&bslash;t$0,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;bne&bslash;t%0,%1,1b&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;addiu&bslash;t%0,1&bslash;n&quot; &bslash;&n;&t;&t;&quot;2:&bslash;t.set&bslash;treorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;&quot;3:&bslash;t.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;la&bslash;t$1,2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;jr&bslash;t$1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;STR(PTR)&quot;&bslash;t1b,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.previous&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (addr), &quot;=r&quot; (__cu_end) &bslash;&n;&t;&t;:&quot;0&quot; (addr), &quot;1&quot; (addr + size - 1), &quot;i&quot; (-EFAULT) &bslash;&n;&t;&t;:&quot;$1&quot;,&quot;memory&quot;); &bslash;&n;&t;&t;size = __cu_end - (addr) - 1; &bslash;&n;})
DECL|macro|clear_user
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;void * __cl_addr = (addr); &bslash;&n;unsigned long __cl_size = (n); &bslash;&n;if (__cl_size &amp;&amp; __access_ok(VERIFY_WRITE, ((unsigned long)(__cl_addr)), __cl_size)) &bslash;&n;__clear_user(__cl_addr, __cl_size); &bslash;&n;__cl_size; })
multiline_comment|/*&n; * Returns: -EFAULT if exception before terminator, N if the entire&n; * buffer filled, else strlen.&n; */
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
)paren
suffix:semicolon
DECL|macro|strncpy_from_user
mdefine_line|#define strncpy_from_user(dest,src,count) ({                            &bslash;&n;&t;const void * __sc_src = (src);                                  &bslash;&n;&t;long __sc_res = -EFAULT;                                        &bslash;&n;&t;if (access_ok(VERIFY_READ, __sc_src, 0)) {                      &bslash;&n;&t;&t;__sc_res = __strncpy_from_user(dest, __sc_src, count);  &bslash;&n;} __sc_res; })
multiline_comment|/* Returns: 0 if bad, string length+1 (memory size) of string if ok */
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
r_inline
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
r_return
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|str
comma
l_int|0
)paren
ques
c_cond
id|__strlen_user
c_func
(paren
id|str
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|nextinsn
r_int
r_int
id|nextinsn
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Returns 0 if exception not found and fixup.unit otherwise.  */
r_extern
r_int
r_int
id|search_exception_table
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* Returns the new pc */
DECL|macro|fixup_exception
mdefine_line|#define fixup_exception(map_reg, fixup_unit, pc)                &bslash;&n;({                                                              &bslash;&n;&t;fixup_unit;                                             &bslash;&n;})
macro_line|#endif /* __ASM_MIPS_UACCESS_H */
eof
