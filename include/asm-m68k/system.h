macro_line|#ifndef _M68K_SYSTEM_H
DECL|macro|_M68K_SYSTEM_H
mdefine_line|#define _M68K_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt; /* get configuration macros */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|function|rdusp
r_extern
r_inline
r_int
r_int
id|rdusp
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|usp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move %/usp,%0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|usp
)paren
)paren
suffix:semicolon
r_return
id|usp
suffix:semicolon
)brace
DECL|function|wrusp
r_extern
r_inline
r_void
id|wrusp
c_func
(paren
r_int
r_int
id|usp
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move %0,%/usp&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|usp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * switch_to(n) should switch tasks to task ptr, first checking that&n; * ptr isn&squot;t the current task, in which case it does nothing.  This&n; * also clears the TS-flag if the task we switched to has used the&n; * math co-processor latest.&n; */
multiline_comment|/*&n; * switch_to() saves the extra registers, that are not saved&n; * automatically by SAVE_SWITCH_STACK in resume(), ie. d0-d5 and&n; * a0-a1. Some of these are used by schedule() and its predecessors&n; * and so we might get see unexpected behaviors when a task returns&n; * with unexpected register values.&n; *&n; * syscall stores these registers itself and none of them are used&n; * by syscall after the function in the syscall has been called.&n; *&n; * Beware that resume now expects *next to be in d1 and the offset of&n; * tss to be in a1. This saves a few instructions as we no longer have&n; * to push them onto the stack and read them back right after.&n; *&n; * 02/17/96 - Jes Sorensen (jds@kom.auc.dk)&n; *&n; * Changed 96/09/19 by Andreas Schwab&n; * pass prev in a0, next in a1, offset of tss in d1, and whether&n; * the mm structures are shared in d2 (to avoid atc flushing).&n; */
id|asmlinkage
r_void
id|resume
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) { &bslash;&n;  register void *_prev __asm__ (&quot;a0&quot;) = (prev); &bslash;&n;  register void *_next __asm__ (&quot;a1&quot;) = (next); &bslash;&n;  register void *_last __asm__ (&quot;d1&quot;); &bslash;&n;  __asm__ __volatile__(&quot;jbsr &quot; SYMBOL_NAME_STR(resume) &bslash;&n;&t;&t;       : &quot;=d&quot; (_last) : &quot;a&quot; (_prev), &quot;a&quot; (_next) &bslash;&n;&t;&t;       : &quot;d0&quot;, &quot;d1&quot;, &quot;d2&quot;, &quot;d3&quot;, &quot;d4&quot;, &quot;d5&quot;, &quot;a0&quot;, &quot;a1&quot;); &bslash;&n;  (last) = _last; &bslash;&n;}
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|struct|__xchg_dummy
DECL|member|a
r_struct
id|__xchg_dummy
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__xg
mdefine_line|#define __xg(x) ((volatile struct __xchg_dummy *)(x))
macro_line|#if defined(MACH_ATARI_ONLY) &amp;&amp; !defined(CONFIG_HADES)
multiline_comment|/* block out HSYNC on the atari */
DECL|macro|__sti
mdefine_line|#define __sti() __asm__ __volatile__ (&quot;andiw #0xfbff,%/sr&quot;: : : &quot;memory&quot;)
macro_line|#else /* portable version */
DECL|macro|__sti
mdefine_line|#define __sti() __asm__ __volatile__ (&quot;andiw #0xf8ff,%/sr&quot;: : : &quot;memory&quot;)
macro_line|#endif /* machine compilation types */ 
DECL|macro|__cli
mdefine_line|#define __cli() __asm__ __volatile__ (&quot;oriw  #0x0700,%/sr&quot;: : : &quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;::)
DECL|macro|mb
mdefine_line|#define mb()  __asm__ __volatile__ (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()  __asm__ __volatile__ (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()  __asm__ __volatile__ (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x) &bslash;&n;__asm__ __volatile__(&quot;movew %/sr,%0&quot;:&quot;=d&quot; (x) : /* no input */ :&quot;memory&quot;)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) &bslash;&n;__asm__ __volatile__(&quot;movew %0,%/sr&quot;: /* no outputs */ :&quot;d&quot; (x) : &quot;memory&quot;)
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)   do { save_flags(flags); cli(); } while(0)
macro_line|#ifndef CONFIG_RMW_INSNS
DECL|function|__xchg
r_static
r_inline
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|tmp
comma
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;moveb %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movew %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;movew %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#else
DECL|function|__xchg
r_static
r_inline
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;casb %0,%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movew %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;casw %0,%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;casl %0,%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _M68K_SYSTEM_H */
eof
