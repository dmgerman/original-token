macro_line|#ifndef _ASM_UACCESS_H
DECL|macro|_ASM_UACCESS_H
mdefine_line|#define _ASM_UACCESS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS   (0)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;(1)
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ&t;0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE&t;1
DECL|macro|get_fs
mdefine_line|#define get_fs() (current-&gt;tss.fs)
DECL|macro|get_ds
mdefine_line|#define get_ds() (KERNEL_DS)
DECL|macro|set_fs
mdefine_line|#define set_fs(val) ( current-&gt;tss.fs = (val))
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) (((size) &lt;= 0x80000000)&amp;&amp;((addr) &lt;= 0x80000000-(size)))
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
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * As the powerpc uses the same address space for kernel and user&n; * data, we can just do these as direct assignments.  (Of course, the&n; * exception handling means that it&squot;s no longer &quot;just&quot;...)&n; *&n; * Careful to not&n; * (a) re-use the arguments for side effects (sizeof/typeof is ok)&n; * (b) require any knowledge of processes at this stage&n; */
multiline_comment|/*&n; * The &quot;__xxx&quot; versions do not do address space checking, useful when&n; * doing multiple accesses to the same area (the programmer has to do the&n; * checks by hand with &quot;access_ok()&quot;)&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) ({ &bslash;&n;unsigned long __pu_addr = (unsigned long)(ptr); &bslash;&n;__put_user_check((__typeof__(*(ptr)))(x),__pu_addr,sizeof(*(ptr))); })
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) ({ &bslash;&n;unsigned long __gu_addr = (unsigned long)(ptr); &bslash;&n;__get_user_check((x),__gu_addr,sizeof(*(ptr)),__typeof__(*(ptr))); })
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
mdefine_line|#define __put_user_check(x,addr,size) ({ &bslash;&n;int __pu_ret; &bslash;&n;__pu_ret = -EFAULT; &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __pu_ret =__put_user_8(x,addr); break; &bslash;&n;case 2: __pu_ret =__put_user_16(x,addr); break; &bslash;&n;case 4: __pu_ret =__put_user_32(x,addr); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} } __pu_ret; })
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,addr,size) ({ &bslash;&n;int __pu_ret; &bslash;&n;__pu_ret = -EFAULT; &bslash;&n;switch (size) { &bslash;&n;case 1: __pu_ret =__put_user_8(x,addr); break; &bslash;&n;case 2: __pu_ret =__put_user_16(x,addr); break; &bslash;&n;case 4: __pu_ret =__put_user_32(x,addr); break; &bslash;&n;default: __pu_ret = __put_user_bad(); break; &bslash;&n;} __pu_ret; })
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,addr,size,type) ({ &bslash;&n;register int __gu_ret asm(&quot;r4&quot;); &bslash;&n;unsigned long __gu_val = 0; &bslash;&n;__gu_ret = -EFAULT; &bslash;&n;if (__access_ok(addr,size)) { &bslash;&n;switch (size) { &bslash;&n;case 1: __gu_val = __get_user_8(__gu_val,addr); break; &bslash;&n;case 2: __gu_val = __get_user_16(__gu_val,addr); break; &bslash;&n;case 4: __gu_val = __get_user_32(__gu_val,addr); break; &bslash;&n;default: __get_user_bad(); break; &bslash;&n;} } (x) = (type) __gu_val; __gu_ret; })
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,addr,size,type) ({ &bslash;&n;register int __gu_ret asm(&quot;r4&quot;); &bslash;&n;unsigned long __gu_val = 0; &bslash;&n;__gu_ret = -EFAULT; &bslash;&n;switch (size) { &bslash;&n;case 1: __gu_val =__get_user_8(__gu_val,addr); break; &bslash;&n;case 2: __gu_val =__get_user_16(__gu_val,addr); break; &bslash;&n;case 4: __gu_val =__get_user_32(__gu_val,addr); break; &bslash;&n;default: __gu_val = __get_user_bad(); break; &bslash;&n;} (x) = (type) __gu_val; __gu_ret;  })
multiline_comment|/* more complex routines */
r_extern
r_int
id|__copy_tofrom_user
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
mdefine_line|#define copy_to_user(to,from,n) ({ &bslash;&n;unsigned long __copy_to = (unsigned long) (to); &bslash;&n;unsigned long __copy_size = (unsigned long) (n); &bslash;&n;unsigned long __copy_res = -EFAULT; &bslash;&n;if(__copy_size &amp;&amp; __access_ok(__copy_to, __copy_size)) { &bslash;&n;__copy_res = __copy_tofrom_user(__copy_to, (unsigned long) (from), __copy_size); &bslash;&n;}  &bslash;&n;__copy_res; })
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n) ({ &bslash;&n;unsigned long __copy_from = (unsigned long) (from); &bslash;&n;unsigned long __copy_size = (unsigned long) (n); &bslash;&n;unsigned long __copy_res = -EFAULT; &bslash;&n;if(__copy_size &amp;&amp; __access_ok(__copy_from, __copy_size)) { &bslash;&n;__copy_res = __copy_tofrom_user((unsigned long) (to), __copy_from, __copy_size); &bslash;&n;} &bslash;&n;__copy_res; })
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
mdefine_line|#define clear_user(addr,n) ({ &bslash;&n;unsigned long __clear_addr = (unsigned long) (addr); &bslash;&n;int __clear_size = (int) (n); &bslash;&n;int __clear_res = -EFAULT; &bslash;&n;if(__clear_size &amp;&amp; __access_ok(__clear_addr, __clear_size)) { &bslash;&n;__clear_res = __clear_user(__clear_addr, __clear_size); &bslash;&n;} &bslash;&n;__clear_res; })
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
