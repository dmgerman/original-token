multiline_comment|/* $Id: system.h,v 1.50 1999/05/08 03:03:22 davem Exp $ */
macro_line|#ifndef __SPARC64_SYSTEM_H
DECL|macro|__SPARC64_SYSTEM_H
mdefine_line|#define __SPARC64_SYSTEM_H
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/asm_offsets.h&gt;
macro_line|#include &lt;asm/visasm.h&gt;
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
multiline_comment|/* This cannot ever be a sun4c nor sun4 :) That&squot;s just history. */
DECL|macro|ARCH_SUN4C_SUN4
mdefine_line|#define ARCH_SUN4C_SUN4 0
DECL|macro|ARCH_SUN4
mdefine_line|#define ARCH_SUN4 0
r_extern
r_int
r_int
id|empty_bad_page
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
mdefine_line|#define getipl() &bslash;&n;({ unsigned long retval; __asm__ __volatile__(&quot;rdpr&t;%%pil, %0&quot; : &quot;=r&quot; (retval)); retval; })
DECL|macro|swap_pil
mdefine_line|#define swap_pil(__new_pil) &bslash;&n;({&t;unsigned long retval; &bslash;&n;&t;__asm__ __volatile__(&quot;rdpr&t;%%pil, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;wrpr&t;%1, %%pil&quot; &bslash;&n;&t;&t;&t;     : &quot;=&amp;r&quot; (retval) &bslash;&n;&t;&t;&t;     : &quot;r&quot; (__new_pil) &bslash;&n;&t;&t;&t;     : &quot;memory&quot;); &bslash;&n;&t;retval; &bslash;&n;})
DECL|macro|read_pil_and_cli
mdefine_line|#define read_pil_and_cli() &bslash;&n;({&t;unsigned long retval; &bslash;&n;&t;__asm__ __volatile__(&quot;rdpr&t;%%pil, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;wrpr&t;15, %%pil&quot; &bslash;&n;&t;&t;&t;     : &quot;=r&quot; (retval) &bslash;&n;&t;&t;&t;     : : &quot;memory&quot;); &bslash;&n;&t;retval; &bslash;&n;})
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
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__global_cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__global_save_flags
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_restore_flags
c_func
(paren
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;__global_cli()
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;__global_sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x)&t;&t;((x) = __global_save_flags())
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;__global_restore_flags(flags)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)&t;do { save_flags(flags); cli(); } while(0)
macro_line|#endif
DECL|macro|mb
mdefine_line|#define mb()  &t;&t;__asm__ __volatile__ (&quot;stbar&quot; : : : &quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() &t;&t;__asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|membar
mdefine_line|#define membar(type)&t;__asm__ __volatile__ (&quot;membar &quot; type : : : &quot;memory&quot;);
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;membar(&quot;#LoadLoad | #LoadStore&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;membar(&quot;#StoreLoad | #StoreStore&quot;)
DECL|macro|flushi
mdefine_line|#define flushi(addr)&t;__asm__ __volatile__ (&quot;flush %0&quot; : : &quot;r&quot; (addr) : &quot;memory&quot;)
DECL|macro|flushw_all
mdefine_line|#define flushw_all()&t;__asm__ __volatile__(&quot;flushw&quot;)
multiline_comment|/* Performance counter register access. */
DECL|macro|read_pcr
mdefine_line|#define read_pcr(__p)  __asm__ __volatile__(&quot;rd&t;%%pcr, %0&quot; : &quot;=r&quot; (__p))
DECL|macro|write_pcr
mdefine_line|#define write_pcr(__p) __asm__ __volatile__(&quot;wr&t;%0, 0x0, %%pcr&quot; : : &quot;r&quot; (__p));
DECL|macro|read_pic
mdefine_line|#define read_pic(__p)  __asm__ __volatile__(&quot;rd %%pic, %0&quot; : &quot;=r&quot; (__p))
DECL|macro|reset_pic
mdefine_line|#define reset_pic()    __asm__ __volatile__(&quot;wr&t;%g0, 0x0, %pic&quot;);
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|synchronize_user_stack
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|brz
comma
id|pt
op_mod
op_mod
id|g1
comma
l_float|1f
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g3
id|call
id|__flushw_user
id|clr
op_mod
op_mod
id|g2
l_int|1
suffix:colon
l_string|&quot;&t;: : : &quot;
id|g1
l_string|&quot;, &quot;
id|g2
l_string|&quot;, &quot;
id|g3
"&quot;"
)paren
suffix:semicolon
)brace
DECL|macro|flush_user_windows
mdefine_line|#define flush_user_windows flushw_user
multiline_comment|/* See what happens when you design the chip correctly?&n;&t; *&n;&t; * We tell gcc we clobber all non-fixed-usage registers except&n;&t; * for l0/l1.  It will use one for &squot;next&squot; and the other to hold&n;&t; * the output value of &squot;last&squot;.  &squot;next&squot; is not referenced again&n;&t; * past the invocation of switch_to in the scheduler, so we need&n;&t; * not preserve it&squot;s value.  Hairy, but it lets us remove 2 loads&n;&t; * and 2 stores in this critical code path.  -DaveM&n;&t; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;if (current-&gt;tss.flags &amp; SPARC_FLAG_PERFCTR) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __tmp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;read_pcr(__tmp);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;tss.pcr_reg = __tmp;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;read_pic(__tmp);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;tss.kernel_cntd0 += (unsigned int)(__tmp);&t;&t;&bslash;&n;&t;&t;current-&gt;tss.kernel_cntd1 += ((__tmp) &gt;&gt; 32);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;save_and_clear_fpu();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;flushw&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%g0, 0x94, %pstate&bslash;n&bslash;t&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;__get_mmu_context(next);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(next)-&gt;mm-&gt;cpu_vm_mask |= (1UL &lt;&lt; smp_processor_id());&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%g6, %%g5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g0, 0x95, %%pstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%i6, [%%sp + 2047 + 0x70]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%i7, [%%sp + 2047 + 0x78]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rdpr&t;%%wstate, %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%o6, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sth&t;%%o5, [%%g6 + %2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rdpr&t;%%cwp, %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sth&t;%%o5, [%%g6 + %5]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%1, %%g6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;lduh&t;[%1 + %5], %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g1, %%cwp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %3], %%o6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;lduh&t;[%%g6 + %2], %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;lduh&t;[%%g6 + %4], %%o7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%g6, %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%o5, 0x0, %%wstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%sp + 2047 + 0x70], %%i6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%sp + 2047 + 0x78], %%i7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g0, 0x94, %%pstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%l2, %%g6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g0, 0x96, %%pstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;andcc&t;%%o7, 0x100, %%g0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;bne,pn&t;%%icc, ret_from_syscall&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;%%g5, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (last)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (next),&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.wstate)),&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.ksp)),&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.flags)),&t;&bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct task_struct *)0)-&gt;tss.cwp))&t;&bslash;&n;&t;: &quot;cc&quot;, &quot;g1&quot;, &quot;g2&quot;, &quot;g3&quot;, &quot;g5&quot;, &quot;g7&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;l2&quot;, &quot;l3&quot;, &quot;l4&quot;, &quot;l5&quot;, &quot;l6&quot;, &quot;l7&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i0&quot;, &quot;i1&quot;, &quot;i2&quot;, &quot;i3&quot;, &quot;i4&quot;, &quot;i5&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;o3&quot;, &quot;o4&quot;, &quot;o5&quot;, &quot;o7&quot;);&t;&t;&t;&t;&bslash;&n;&t;/* If you fuck with this, update ret_from_syscall code too. */&t;&t;&bslash;&n;&t;if (current-&gt;tss.flags &amp; SPARC_FLAG_PERFCTR) {&t;&t;&t;&t;&bslash;&n;&t;&t;write_pcr(current-&gt;tss.pcr_reg);&t;&t;&t;&t;&bslash;&n;&t;&t;reset_pic();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|function|xchg32
r_extern
id|__inline__
r_int
r_int
id|xchg32
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
"&quot;"
id|mov
op_mod
l_int|0
comma
op_mod
op_mod
id|g5
l_int|1
suffix:colon
id|lduw
(braket
op_mod
l_int|2
)braket
comma
op_mod
op_mod
id|g7
id|cas
(braket
op_mod
l_int|2
)braket
comma
op_mod
op_mod
id|g7
comma
op_mod
l_int|0
id|cmp
op_mod
op_mod
id|g7
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
id|icc
comma
l_int|1
id|b
id|mov
op_mod
op_mod
id|g5
comma
op_mod
l_int|0
id|membar
macro_line|#StoreLoad | #StoreStore
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
"&quot;"
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
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|xchg64
r_extern
id|__inline__
r_int
r_int
id|xchg64
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
"&quot;"
id|mov
op_mod
l_int|0
comma
op_mod
op_mod
id|g5
l_int|1
suffix:colon
id|ldx
(braket
op_mod
l_int|2
)braket
comma
op_mod
op_mod
id|g7
id|casx
(braket
op_mod
l_int|2
)braket
comma
op_mod
op_mod
id|g7
comma
op_mod
l_int|0
id|cmp
op_mod
op_mod
id|g7
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
id|mov
op_mod
op_mod
id|g5
comma
op_mod
l_int|0
id|membar
macro_line|#StoreLoad | #StoreStore
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
"&quot;"
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
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
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
id|xchg32
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
id|xchg64
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
