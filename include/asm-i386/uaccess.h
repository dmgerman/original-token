macro_line|#ifndef __i386_UACCESS_H
DECL|macro|__i386_UACCESS_H
mdefine_line|#define __i386_UACCESS_H
multiline_comment|/*&n; * User space memory access functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current-&gt;tss.segment)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)&t;(current-&gt;tss.segment = (x))
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
multiline_comment|/*&n; * Address Ok:&n; *&n; *&t;&t;&t;    low two bits of segment&n; *&t;&t;&t;00 (kernel)&t;&t;11 (user)&n; *&n; * high&t;&t;00&t;1&t;&t;&t;1&n; * two &t;&t;01&t;1&t;&t;&t;1&n; * bits of&t;10&t;1&t;&t;&t;1&n; * address&t;11&t;1&t;&t;&t;0&n; */
DECL|macro|__addr_ok
mdefine_line|#define __addr_ok(x) &bslash;&n;&t;((((unsigned long)(x)&gt;&gt;30)&amp;get_fs()) != 3)
DECL|macro|__user_ok
mdefine_line|#define __user_ok(addr,size) &bslash;&n;&t;((size &lt;= 0xC0000000UL) &amp;&amp; (addr &lt;= 0xC0000000UL - size))
DECL|macro|__kernel_ok
mdefine_line|#define __kernel_ok &bslash;&n;&t;(!(get_fs() &amp; 3))
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
mdefine_line|#define __access_ok(type,addr,size) &bslash;&n;&t;(__kernel_ok || __user_ok(addr,size))
macro_line|#else
DECL|macro|__access_ok
mdefine_line|#define __access_ok(type,addr,size) &bslash;&n;&t;(__kernel_ok || (__user_ok(addr,size) &amp;&amp; &bslash;&n;&t;&t;&t; ((type) == VERIFY_READ || wp_works_ok || &bslash;&n;&t;&t;&t;  __verify_write((void *)(addr),(size)))))
macro_line|#endif /* CPU */
DECL|macro|access_ok
mdefine_line|#define access_ok(type,addr,size) &bslash;&n;&t;__access_ok((type),(unsigned long)(addr),(size))
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
multiline_comment|/*&n; * The exception table consists of pairs of addresses: the first is the&n; * address of an instruction that is allowed to fault, and the second is&n; * the address at which the program should continue.  No registers are&n; * modified, so it is entirely up to the continuation code to figure out&n; * what to do.&n; *&n; * All the routines below use bits of fixup code that are out of line&n; * with the main instruction path.  This means when everything is well,&n; * we don&squot;t even have to jump over them.  Further, they do not intrude&n; * on our cache or tlb entries.&n; */
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
)paren
suffix:semicolon
multiline_comment|/*&n; * These are the main single-value transfer routines.  They automatically&n; * use the right size if we just have the right pointer type.&n; *&n; * This gets kind of ugly. We want to return _two_ values in &quot;get_user()&quot;&n; * and yet we don&squot;t want to do any pointers, because that is too much&n; * of a performance impact. Thus we have a few rather ugly macros here,&n; * and hide all the uglyness from the user.&n; *&n; * The &quot;__xxx&quot; versions of the user access functions are versions that&n; * do not verify the address space, that must have been done previously&n; * with a separate &quot;access_ok()&quot; call (this is used when we do multiple&n; * accesses to the same area of user memory).&n; */
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) &bslash;&n;  __get_user_check((x),(ptr),sizeof(*(ptr)))
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) &bslash;&n;  __put_user_check((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
DECL|macro|__get_user
mdefine_line|#define __get_user(x,ptr) &bslash;&n;  __get_user_nocheck((x),(ptr),sizeof(*(ptr)))
DECL|macro|__put_user
mdefine_line|#define __put_user(x,ptr) &bslash;&n;  __put_user_nocheck((__typeof__(*(ptr)))(x),(ptr),sizeof(*(ptr)))
r_extern
r_int
id|__put_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_user_nocheck
mdefine_line|#define __put_user_nocheck(x,ptr,size)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&bslash;&n;&t;__put_user_size((x),(ptr),(size),__pu_err);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_check
mdefine_line|#define __put_user_check(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err = -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) *__pu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_WRITE,__pu_addr,size))&t;&t;&bslash;&n;&t;&t;__put_user_size((x),__pu_addr,(size),__pu_err);&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_user_size
mdefine_line|#define __put_user_size(x,ptr,size,retval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __put_user_asm(x,ptr,retval,&quot;b&quot;,&quot;b&quot;,&quot;iq&quot;); break;&t;&bslash;&n;&t;  case 2: __put_user_asm(x,ptr,retval,&quot;w&quot;,&quot;w&quot;,&quot;ir&quot;); break;&t;&bslash;&n;&t;  case 4: __put_user_asm(x,ptr,retval,&quot;l&quot;,&quot;&quot;,&quot;ir&quot;); break;&t;&bslash;&n;&t;  default: __put_user_bad();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
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
multiline_comment|/*&n; * Tell gcc we read from memory instead of writing: this is because&n; * we do not write to any memory gcc knows about, so there are no&n; * aliasing issues.&n; */
DECL|macro|__put_user_asm
mdefine_line|#define __put_user_asm(x, addr, err, itype, rtype, ltype)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;mov&quot;itype&quot; %&quot;rtype&quot;1,%2&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: ltype (x), &quot;m&quot;(__m(addr)), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
DECL|macro|__get_user_nocheck
mdefine_line|#define __get_user_nocheck(x,ptr,size)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err, __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__get_user_size(__gu_val,(ptr),(size),__gu_err);&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_user_check
mdefine_line|#define __get_user_check(x,ptr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err = -EFAULT, __gu_val = 0;&t;&t;&t;&t;&bslash;&n;&t;const __typeof__(*(ptr)) *__gu_addr = (ptr);&t;&t;&t;&bslash;&n;&t;if (access_ok(VERIFY_READ,__gu_addr,size))&t;&t;&t;&bslash;&n;&t;&t;__get_user_size(__gu_val,__gu_addr,(size),__gu_err);&t;&bslash;&n;&t;(x) = (__typeof__(*(ptr)))__gu_val;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_extern
r_int
id|__get_user_bad
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__get_user_size
mdefine_line|#define __get_user_size(x,ptr,size,retval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  case 1: __get_user_asm(x,ptr,retval,&quot;b&quot;,&quot;b&quot;,&quot;=q&quot;); break;&t;&bslash;&n;&t;  case 2: __get_user_asm(x,ptr,retval,&quot;w&quot;,&quot;w&quot;,&quot;=r&quot;); break;&t;&bslash;&n;&t;  case 4: __get_user_asm(x,ptr,retval,&quot;l&quot;,&quot;&quot;,&quot;=r&quot;); break;&t;&bslash;&n;&t;  default: (x) = __get_user_bad();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__get_user_asm
mdefine_line|#define __get_user_asm(x, addr, err, itype, rtype, ltype)&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;mov&quot;itype&quot; %2,%&quot;rtype&quot;1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;movl %3,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;xor&quot;itype&quot; %&quot;rtype&quot;1,%&quot;rtype&quot;1&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(err), ltype (x)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;m&quot;(__m(addr)), &quot;i&quot;(-EFAULT), &quot;0&quot;(err))
multiline_comment|/*&n; * Copy To/From Userspace&n; */
multiline_comment|/* Generic arbitrary sized copy.  */
DECL|macro|__copy_user
mdefine_line|#define __copy_user(to,from,size)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; movsb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%1,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=c&quot;(size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(size &amp; 3), &quot;0&quot;(size / 4), &quot;D&quot;(to), &quot;S&quot;(from)&t;&bslash;&n;&t;&t;: &quot;di&quot;, &quot;si&quot;, &quot;memory&quot;)
multiline_comment|/* Optimize just a little bit when we know the size of the move. */
DECL|macro|__constant_copy_user
mdefine_line|#define __constant_copy_user(to, from, size)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size &amp; 3) {&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;2:&t;shl $2,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;jmp 1b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 0b,2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=c&quot;(size)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;S&quot;(from), &quot;D&quot;(to), &quot;0&quot;(size/4)&t;&bslash;&n;&t;&t;&t;: &quot;di&quot;, &quot;si&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1:&t;movsb&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;3:&t;shl $2,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;4:&t;incl %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 1b,4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=c&quot;(size)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;S&quot;(from), &quot;D&quot;(to), &quot;0&quot;(size/4)&t;&bslash;&n;&t;&t;&t;: &quot;di&quot;, &quot;si&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1:&t;movsw&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;3:&t;shl $2,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;4:&t;addl $2,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 1b,4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=c&quot;(size)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;S&quot;(from), &quot;D&quot;(to), &quot;0&quot;(size/4)&t;&bslash;&n;&t;&t;&t;: &quot;di&quot;, &quot;si&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 3:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;0:&t;rep; movsl&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1:&t;movsw&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;2:&t;movsb&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;4:&t;shl $2,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;5:&t;addl $2,%0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;6:&t;incl %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;jmp 3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 0b,4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 1b,5b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;&t;.long 2b,6b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=c&quot;(size)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;S&quot;(from), &quot;D&quot;(to), &quot;0&quot;(size/4)&t;&bslash;&n;&t;&t;&t;: &quot;di&quot;, &quot;si&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
r_static
r_inline
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
r_static
r_inline
r_int
r_int
DECL|function|__constant_copy_to_user
id|__constant_copy_to_user
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
id|__constant_copy_user
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
r_static
r_inline
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
r_static
r_inline
r_int
r_int
DECL|function|__constant_copy_from_user
id|__constant_copy_from_user
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
id|__constant_copy_user
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
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(to,from,n)&t;&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(n) ?&t;&t;&t;&bslash;&n;&t; __constant_copy_to_user((to),(from),(n)) :&t;&bslash;&n;&t; __generic_copy_to_user((to),(from),(n)))
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user(to,from,n)&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(n) ?&t;&t;&t;&bslash;&n;&t; __constant_copy_from_user((to),(from),(n)) :&t;&bslash;&n;&t; __generic_copy_from_user((to),(from),(n)))
multiline_comment|/*&n; * Zero Userspace&n; */
DECL|macro|__clear_user
mdefine_line|#define __clear_user(addr,size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;0:&t;rep; stosl&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;movl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;rep; stosb&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;lea 0(%1,%0,4),%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,2b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=c&quot;(size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot;(size &amp; 3), &quot;0&quot;(size / 4), &quot;D&quot;(addr), &quot;a&quot;(0)&t;&bslash;&n;&t;&t;: &quot;di&quot;)
r_static
r_inline
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
id|__clear_user
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
multiline_comment|/*&n; * Copy a null terminated string from userspace.&n; */
DECL|macro|__strncpy_from_user
mdefine_line|#define __strncpy_from_user(dst,src,count,res)&t;&t;&t;&t;   &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testl %1,%1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 2f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;0:&t;lodsb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;stosb&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;testb %%al,%%al&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jz 1f&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;decl %1&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jnz 0b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;1:&t;subl %1,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;3:&t;movl %2,%0&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;jmp 2b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.align 4&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;&t;.long 0b,3b&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;&quot;.text&quot;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;=d&quot;(res), &quot;=c&quot;(count)&t;&t;&t;&t;   &bslash;&n;&t;&t;: &quot;i&quot;(-EFAULT), &quot;0&quot;(count), &quot;1&quot;(count), &quot;S&quot;(src), &quot;D&quot;(dst) &bslash;&n;&t;&t;: &quot;si&quot;, &quot;di&quot;, &quot;ax&quot;, &quot;memory&quot;)
r_static
r_inline
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
id|__strncpy_from_user
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
multiline_comment|/*&n; * Return the size of a string (including the ending 0)&n; *&n; * Return 0 for error&n; */
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
id|s
)paren
(brace
r_int
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;0:&t;repne; scasb&bslash;n&quot;
l_string|&quot;&t;notl %0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;xorl %0,%0&bslash;n&quot;
l_string|&quot;&t;jmp 1b&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 0b,2b&bslash;n&quot;
l_string|&quot;.text&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
id|res
)paren
comma
l_string|&quot;=D&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
op_minus
id|__addr_ok
c_func
(paren
id|s
)paren
)paren
)paren
suffix:semicolon
r_return
id|res
op_amp
op_minus
id|__addr_ok
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
macro_line|#endif /* __i386_UACCESS_H */
eof
