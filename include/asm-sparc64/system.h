multiline_comment|/* $Id: system.h,v 1.15 1997/04/10 23:32:49 davem Exp $ */
macro_line|#ifndef __SPARC64_SYSTEM_H
DECL|macro|__SPARC64_SYSTEM_H
mdefine_line|#define __SPARC64_SYSTEM_H
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/asm_offsets.h&gt;
DECL|macro|NCPUS
mdefine_line|#define NCPUS&t;4&t;/* No SMP yet */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Sparc (general) CPU types&n; */
DECL|enum|sparc_cpu
r_enum
id|sparc_cpu
(brace
DECL|enumerator|sun4
id|sun4
op_assign
l_int|0x00
comma
DECL|enumerator|sun4c
id|sun4c
op_assign
l_int|0x01
comma
DECL|enumerator|sun4m
id|sun4m
op_assign
l_int|0x02
comma
DECL|enumerator|sun4d
id|sun4d
op_assign
l_int|0x03
comma
DECL|enumerator|sun4e
id|sun4e
op_assign
l_int|0x04
comma
DECL|enumerator|sun4u
id|sun4u
op_assign
l_int|0x05
comma
multiline_comment|/* V8 ploos ploos */
DECL|enumerator|sun_unknown
id|sun_unknown
op_assign
l_int|0x06
comma
DECL|enumerator|ap1000
id|ap1000
op_assign
l_int|0x07
comma
multiline_comment|/* almost a sun4m */
)brace
suffix:semicolon
DECL|macro|sparc_cpu_model
mdefine_line|#define sparc_cpu_model sun4u
r_extern
r_int
r_int
id|empty_bad_page
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_pmd_table
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_pte_table
suffix:semicolon
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
macro_line|#endif
DECL|macro|setipl
mdefine_line|#define setipl(__new_ipl) &bslash;&n;&t;__asm__ __volatile__(&quot;wrpr&t;%0, %%pil&quot;  : : &quot;r&quot; (__new_ipl) : &quot;memory&quot;)
DECL|macro|__cli
mdefine_line|#define __cli() &bslash;&n;&t;__asm__ __volatile__(&quot;wrpr&t;15, %%pil&quot; : : : &quot;memory&quot;)
DECL|macro|__sti
mdefine_line|#define __sti() &bslash;&n;&t;__asm__ __volatile__(&quot;wrpr&t;0, %%pil&quot; : : : &quot;memory&quot;)
DECL|macro|getipl
mdefine_line|#define getipl() &bslash;&n;({ int retval; __asm__ __volatile__(&quot;rdpr&t;%%pil, %0&quot; : &quot;=r&quot; (retval)); retval; })
DECL|macro|swap_pil
mdefine_line|#define swap_pil(__new_pil) &bslash;&n;({&t;int retval; &bslash;&n;&t;__asm__ __volatile__(&quot;rdpr&t;%%pil, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;wrpr&t;%1, %%pil&quot; &bslash;&n;&t;&t;&t;     : &quot;=r&quot; (retval) &bslash;&n;&t;&t;&t;     : &quot;r&quot; (__new_pil) &bslash;&n;&t;&t;&t;     : &quot;memory&quot;); &bslash;&n;&t;retval; &bslash;&n;})
DECL|macro|read_pil_and_cli
mdefine_line|#define read_pil_and_cli() &bslash;&n;({&t;int retval; &bslash;&n;&t;__asm__ __volatile__(&quot;rdpr&t;%%pil, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;wrpr&t;15, %%pil&quot; &bslash;&n;&t;&t;&t;     : &quot;=r&quot; (retval) &bslash;&n;&t;&t;&t;     : : &quot;memory&quot;); &bslash;&n;&t;retval; &bslash;&n;})
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags)&t;((flags) = getipl())
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(flags)&t;((flags) = read_pil_and_cli())
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;setipl((flags))
macro_line|#ifndef __SMP__
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(x) __save_and_cli(x)
macro_line|#else
macro_line|#error SMP not supported on sparc64
macro_line|#endif
DECL|macro|mb
mdefine_line|#define mb()  &t;&t;__asm__ __volatile__ (&quot;stbar&quot; : : : &quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() &t;&t;__asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|membar
mdefine_line|#define membar(type)&t;__asm__ __volatile__ (&quot;membar &quot; type : : : &quot;memory&quot;);
DECL|macro|flushi
mdefine_line|#define flushi(addr)&t;__asm__ __volatile__ (&quot;flush %0&quot; : : &quot;r&quot; (addr))
DECL|macro|flushw_all
mdefine_line|#define flushw_all()&t;__asm__ __volatile__(&quot;flushw&quot;)
macro_line|#ifndef __ASSEMBLY__
DECL|function|flushw_user
r_extern
id|__inline__
r_void
id|flushw_user
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|rdpr
op_mod
op_mod
id|otherwin
comma
op_mod
op_mod
id|g1
l_int|1
suffix:colon
id|rdpr
op_mod
op_mod
id|otherwin
comma
op_mod
op_mod
id|g2
id|brnz
comma
id|pn
op_mod
op_mod
id|g2
comma
l_int|1
id|b
id|save
op_mod
op_mod
id|sp
comma
op_mod
l_int|0
comma
op_mod
op_mod
id|sp
l_int|1
suffix:colon
id|subcc
op_mod
op_mod
id|g1
comma
l_int|1
comma
op_mod
op_mod
id|g1
id|bne
comma
id|pn
op_mod
op_mod
id|xcc
comma
l_int|1
id|b
id|restore
op_mod
op_mod
id|g0
comma
op_mod
op_mod
id|g0
comma
op_mod
op_mod
id|g0
l_string|&quot; : : &quot;
id|i
"&quot;"
(paren
op_minus
id|REGWIN_SZ
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|flush_user_windows
mdefine_line|#define flush_user_windows flushw_user
macro_line|#ifdef __SMP__
macro_line|#error SMP not supported on sparc64
macro_line|#else
macro_line|#if 0
mdefine_line|#define SWITCH_DO_LAZY_FPU(next)&t;&t;&t;&bslash;&n;&t;if(last_task_used_math != (next))&t;&t;&bslash;&n;&t;&t;(next)-&gt;tss.kregs-&gt;tstate&amp;=~TSTATE_PEF
macro_line|#else
multiline_comment|/* XXX FIX ME BIG TIME XXX -DaveM */
DECL|macro|SWITCH_DO_LAZY_FPU
mdefine_line|#define SWITCH_DO_LAZY_FPU(next)&t;do { } while(0)
macro_line|#endif
macro_line|#endif
multiline_comment|/* See what happens when you design the chip correctly?&n;&t; * NOTE NOTE NOTE this is extremely non-trivial what I&n;&t; * am doing here.  GCC needs only two registers to stuff&n;&t; * things into (&squot;next&squot; and &amp;current_set[cpu])  So I &quot;claim&quot;&n;&t; * that I do not clobber them, when in fact I do.  Please,&n;&t; * when modifying this code inspect output of sched.s very&n;&t; * carefully to make sure things still work.  -DaveM&n;&t; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__label__ switch_continue;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register unsigned long task_pc asm(&quot;o7&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;SWITCH_DO_LAZY_FPU(next);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;task_pc = ((unsigned long) &amp;&amp;switch_continue) - 0x8;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;flushw&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%i6, [%%sp + 2047 + 0x70]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%i7, [%%sp + 2047 + 0x78]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%o6, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rdpr&t;%%wstate, %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%o7, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%6, %%o4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%o5, [%%g6 + %2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%%o4, [%%g6 + %7]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rdpr&t;%%cwp, %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%o5, [%%g6 + %8]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%1, %%g6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%g6, [%0]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %8], %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g1, %%cwp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %2], %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %3], %%o6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %4], %%o7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%o5, 0x0, %%wstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%sp + 2047 + 0x70], %%i6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jmpl&t;%%o7 + 0x8, %%g0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; ldx&t;[%%sp + 2047 + 0x78], %%i7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* No outputs */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (&amp;(current_set[smp_processor_id()])), &quot;r&quot; (next),&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.wstate)),&t;&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ksp)),&t;&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.kpc)),&t;&t;&bslash;&n;&t;  &quot;r&quot; (task_pc), &quot;i&quot; (255),&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;processor)),&t;&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.cwp))&t;&t;&bslash;&n;&t;: &quot;cc&quot;, &quot;g1&quot;, &quot;g2&quot;, &quot;g3&quot;, &quot;g5&quot;, &quot;g7&quot;,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;l2&quot;, &quot;l3&quot;, &quot;l4&quot;, &quot;l5&quot;, &quot;l6&quot;, &quot;l7&quot;,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i0&quot;, &quot;i1&quot;, &quot;i2&quot;, &quot;i3&quot;, &quot;i4&quot;, &quot;i5&quot;,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;o3&quot;, &quot;o4&quot;, &quot;o5&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;switch_continue: } while(0)
multiline_comment|/* Unlike the hybrid v7/v8 kernel, we can assume swap exists under V9. */
DECL|function|xchg_u32
r_extern
id|__inline__
r_int
r_int
id|xchg_u32
c_func
(paren
id|__volatile__
r_int
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;swap&t;[%2], %0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|m
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* Bolix, must use casx for 64-bit values. */
DECL|function|xchg_u64
r_extern
id|__inline__
r_int
r_int
id|xchg_u64
c_func
(paren
id|__volatile__
r_int
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|ldx
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|1
l_int|1
suffix:colon
id|casx
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|1
comma
op_mod
l_int|0
id|cmp
op_mod
l_int|1
comma
op_mod
l_int|0
id|bne
comma
id|a
comma
id|pn
op_mod
op_mod
id|xcc
comma
l_int|1
id|b
id|ldx
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|1
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
l_string|&quot; (val), &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|temp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|m
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__xchg
r_static
id|__inline__
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
id|__volatile__
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
l_int|4
suffix:colon
r_return
id|xchg_u32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
)brace
suffix:semicolon
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_SYSTEM_H) */
eof
