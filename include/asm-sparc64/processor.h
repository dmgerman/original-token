multiline_comment|/* $Id: processor.h,v 1.53 1999/01/19 07:57:51 davem Exp $&n; * include/asm-sparc64/processor.h&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC64_PROCESSOR_H
DECL|macro|__ASM_SPARC64_PROCESSOR_H
mdefine_line|#define __ASM_SPARC64_PROCESSOR_H
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/pstate.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/* Bus types */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* The sparc has no problems with write protection */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* User lives in his very own context, and cannot reference us. */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;((unsigned long)-PGDIR_SIZE)
macro_line|#else
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0xfffffffc00000000
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|NSWINS
mdefine_line|#define NSWINS&t;&t;7
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
multiline_comment|/* The Sparc processor specific thread struct. */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
multiline_comment|/*DC1*/
r_int
r_int
id|ksp
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|member|wstate
r_int
r_int
id|wstate
suffix:semicolon
DECL|member|cwp
r_int
r_int
id|cwp
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ctx
r_int
r_int
id|ctx
suffix:semicolon
DECL|member|w_saved
multiline_comment|/*DC2*/
r_int
r_int
id|w_saved
suffix:semicolon
DECL|member|new_signal
r_int
r_int
id|new_signal
suffix:semicolon
DECL|member|___pad
r_int
r_int
id|___pad
suffix:semicolon
DECL|member|current_ds
id|mm_segment_t
id|current_ds
suffix:semicolon
DECL|member|kregs
multiline_comment|/*DC3*/
r_struct
id|pt_regs
op_star
id|kregs
suffix:semicolon
DECL|member|utraps
r_int
r_int
op_star
id|utraps
suffix:semicolon
DECL|member|reg_window
r_struct
id|reg_window
id|reg_window
(braket
id|NSWINS
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|member|rwbuf_stkptrs
r_int
r_int
id|rwbuf_stkptrs
(braket
id|NSWINS
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|member|sig_address
r_int
r_int
id|sig_address
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|member|sig_desc
r_int
r_int
id|sig_desc
suffix:semicolon
multiline_comment|/* Performance counter state */
DECL|member|user_cntd0
DECL|member|user_cntd1
id|u64
op_star
id|user_cntd0
comma
op_star
id|user_cntd1
suffix:semicolon
DECL|member|kernel_cntd0
DECL|member|kernel_cntd1
id|u64
id|kernel_cntd0
comma
id|kernel_cntd1
suffix:semicolon
DECL|member|pcr_reg
id|u64
id|pcr_reg
suffix:semicolon
DECL|member|fpdepth
r_int
r_char
id|fpdepth
suffix:semicolon
DECL|member|fpsaved
r_int
r_char
id|fpsaved
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|gsr
r_int
r_char
id|gsr
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|xfsr
r_int
r_int
id|xfsr
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
DECL|macro|SPARC_FLAG_KTHREAD
mdefine_line|#define SPARC_FLAG_KTHREAD      0x010    /* task is a kernel thread */
DECL|macro|SPARC_FLAG_UNALIGNED
mdefine_line|#define SPARC_FLAG_UNALIGNED    0x020    /* is allowed to do unaligned accesses */
DECL|macro|SPARC_FLAG_NEWSIGNALS
mdefine_line|#define SPARC_FLAG_NEWSIGNALS   0x040    /* task wants new-style signals */
DECL|macro|SPARC_FLAG_32BIT
mdefine_line|#define SPARC_FLAG_32BIT        0x080    /* task is older 32-bit binary */
DECL|macro|SPARC_FLAG_NEWCHILD
mdefine_line|#define SPARC_FLAG_NEWCHILD     0x100    /* task is just-spawned child process */
DECL|macro|SPARC_FLAG_PERFCTR
mdefine_line|#define SPARC_FLAG_PERFCTR&t;0x200    /* task has performance counters active */
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, 0xfffff80000000000, 0xfffff80001000000, &bslash;&n;&t;&t;    NULL, PAGE_SHARED , VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  {&t;&t;&t;&t;&t;&t;&bslash;&n;/* ksp, wstate, cwp, flags,              ctx, */ &t;&t;&bslash;&n;   0,   0,      0,   SPARC_FLAG_KTHREAD, 0,&t;&t;&t;&bslash;&n;/* w_saved, new_signal, padding, current_ds, */&t;&t;&t;&bslash;&n;   0,       0,          0,       KERNEL_DS,&t;&t;&t;&bslash;&n;/* kregs,   utraps, */&t;&t;&t;&t;&t;&t;&bslash;&n;   0,       0,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;/* reg_window */&t;&t;&t;&t;&t;&t;&bslash;&n;   { { { 0, }, { 0, } }, }, &t;&t;&t;&t;&t;&bslash;&n;/* rwbuf_stkptrs */&t;&t;&t;&t;&t;&t;&bslash;&n;   { 0, 0, 0, 0, 0, 0, 0, },&t;&t;&t;&t;&t;&bslash;&n;/* sig_address, sig_desc */&t;&t;&t;&t;&t;&bslash;&n;   0,           0,&t;&t;&t;&t;&t;&t;&bslash;&n;/* user_cntd0, user_cndd1, kernel_cntd0, kernel_cntd0, pcr_reg */ &bslash;&n;   0,          0,          0,&t;&t; 0,            0,&t;&bslash;&n;/* fpdepth, fpsaved, gsr,   xfsr */&t;&t;&t;&t;&bslash;&n;   0,       { 0 },   { 0 }, { 0 },&t;&t;&t;&t;&bslash;&n;}
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Return saved PC of a blocked thread. */
DECL|function|thread_saved_pc
r_extern
id|__inline__
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_int
r_int
op_star
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|t-&gt;ksp
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
r_int
r_int
op_star
id|fp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|sp
(braket
l_int|14
)braket
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
r_return
id|fp
(braket
l_int|15
)braket
suffix:semicolon
)brace
multiline_comment|/* On Uniprocessor, even in RMO processes see TSO semantics */
macro_line|#ifdef __SMP__
DECL|macro|TSTATE_INITIAL_MM
mdefine_line|#define TSTATE_INITIAL_MM&t;TSTATE_TSO
macro_line|#else
DECL|macro|TSTATE_INITIAL_MM
mdefine_line|#define TSTATE_INITIAL_MM&t;TSTATE_RMO
macro_line|#endif
multiline_comment|/* Do necessary setup to start up a newly executed thread. */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP)) | (TSTATE_INITIAL_MM|TSTATE_IE) | (ASI_PNF &lt;&lt; 24); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;current-&gt;tss.flags &amp;= ~SPARC_FLAG_32BIT; &bslash;&n;&t;current-&gt;tss.wstate = (1 &lt;&lt; 3); &bslash;&n;&t;if (current-&gt;tss.utraps) { &bslash;&n;&t;&t;if (*(current-&gt;tss.utraps) &lt; 2) &bslash;&n;&t;&t;&t;kfree (current-&gt;tss.utraps); &bslash;&n;&t;&t;else &bslash;&n;&t;&t;&t;(*(current-&gt;tss.utraps))--; &bslash;&n;&t;&t;current-&gt;tss.utraps = NULL; &bslash;&n;&t;} &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (1 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - REGWIN_SZ - STACK_BIAS), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0]))); &bslash;&n;} while(0)
DECL|macro|start_thread32
mdefine_line|#define start_thread32(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;pc &amp;= 0x00000000ffffffffUL; &bslash;&n;&t;sp &amp;= 0x00000000ffffffffUL; &bslash;&n;&bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP))|(TSTATE_INITIAL_MM|TSTATE_IE|TSTATE_AM); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;current-&gt;tss.flags |= SPARC_FLAG_32BIT; &bslash;&n;&t;current-&gt;tss.wstate = (2 &lt;&lt; 3); &bslash;&n;&t;if (current-&gt;tss.utraps) { &bslash;&n;&t;&t;if (*(current-&gt;tss.utraps) &lt; 2) &bslash;&n;&t;&t;&t;kfree (current-&gt;tss.utraps); &bslash;&n;&t;&t;else &bslash;&n;&t;&t;&t;(*(current-&gt;tss.utraps))--; &bslash;&n;&t;&t;current-&gt;tss.utraps = NULL; &bslash;&n;&t;} &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stxa&t;&t;%3, [%4] %5&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (2 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - REGWIN32_SZ), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0])), &bslash;&n;&t;  &quot;r&quot; (((unsigned long)current-&gt;mm-&gt;pgd[0])&lt;&lt;11UL), &bslash;&n;&t;  &quot;r&quot; (TSB_REG), &quot;i&quot; (ASI_DMMU)); &bslash;&n;} while(0)
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(tsk)&t;&t;do { } while(0)
DECL|macro|copy_segments
mdefine_line|#define copy_segments(nr, tsk, mm)&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
DECL|macro|forget_segments
mdefine_line|#define forget_segments()&t;&t;do { } while (0)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Allocation and freeing of task_struct and kernel stack. */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()   ((struct task_struct *)__get_free_pages(GFP_KERNEL, 1))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(tsk) free_pages((unsigned long)(tsk),1)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__ASM_SPARC64_PROCESSOR_H) */
eof
