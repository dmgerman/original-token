multiline_comment|/* $Id: processor.h,v 1.32 1997/07/01 21:59:38 davem Exp $&n; * include/asm-sparc64/processor.h&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC64_PROCESSOR_H
DECL|macro|__ASM_SPARC64_PROCESSOR_H
mdefine_line|#define __ASM_SPARC64_PROCESSOR_H
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
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;((1UL &lt;&lt; (PAGE_SHIFT - 3)) * PGDIR_SIZE)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|NSWINS
mdefine_line|#define NSWINS&t;&t;8
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
DECL|member|kpc
r_int
r_int
id|kpc
suffix:semicolon
DECL|member|wstate
multiline_comment|/*DC2*/
r_int
r_int
id|wstate
suffix:semicolon
DECL|member|cwp
r_int
r_int
id|cwp
suffix:semicolon
DECL|member|ctx
r_int
r_int
id|ctx
suffix:semicolon
DECL|member|flags
multiline_comment|/*DC3*/
r_int
r_int
id|flags
suffix:semicolon
DECL|member|new_signal
r_int
r_int
id|new_signal
suffix:semicolon
DECL|member|current_ds
r_int
r_int
id|current_ds
suffix:semicolon
DECL|member|w_saved
multiline_comment|/*DC4*/
r_int
r_int
id|w_saved
suffix:semicolon
DECL|member|kregs
r_struct
id|pt_regs
op_star
id|kregs
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
DECL|member|sstk_info
r_struct
id|sigstack
id|sstk_info
suffix:semicolon
DECL|member|core_exec
r_struct
id|exec
id|core_exec
suffix:semicolon
multiline_comment|/* just what it says. */
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
DECL|macro|SPARC_FLAG_KTHREAD
mdefine_line|#define SPARC_FLAG_KTHREAD      0x1    /* task is a kernel thread */
DECL|macro|SPARC_FLAG_UNALIGNED
mdefine_line|#define SPARC_FLAG_UNALIGNED    0x2    /* is allowed to do unaligned accesses */
DECL|macro|SPARC_FLAG_NEWSIGNALS
mdefine_line|#define SPARC_FLAG_NEWSIGNALS   0x4    /* task wants new-style signals */
DECL|macro|SPARC_FLAG_32BIT
mdefine_line|#define SPARC_FLAG_32BIT        0x8    /* task is older 32-bit binary */
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, 0xfffff80000000000, 0xfffff80001000000, &bslash;&n;&t;&t;    PAGE_SHARED , VM_READ | VM_WRITE | VM_EXEC, NULL, &amp;init_mm.mmap }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;/* ksp, kpc, wstate, cwp, secctx */ &t;&t;&t;&t;&t;&bslash;&n;   0,   0,   0,&t;     0,&t;  0,&t;&t;&t;&t;&t;&t;&bslash;&n;/* flags,              new_signal, current_ds, */&t;&t;&t;&bslash;&n;   SPARC_FLAG_KTHREAD, 0,          USER_DS,&t;&t;&t;&t;&bslash;&n;/* w_saved, kregs, */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   0,       0,&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;/* reg_window */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   { { { 0, }, { 0, } }, }, &t;&t;&t;&t;&t;&t;&bslash;&n;/* rwbuf_stkptrs */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   { 0, 0, 0, 0, 0, 0, 0, 0, },&t;&t;&t;&t;&t;&t;&bslash;&n;/* sig_address, sig_desc, sstk_info, core_exec */&t;&t;&t;&bslash;&n;   0,           0,        { 0, 0, }, { 0, },&t;&t;&t;&t;&bslash;&n;}
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
r_return
id|t-&gt;kpc
suffix:semicolon
)brace
multiline_comment|/* Do necessary setup to start up a newly executed thread. */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP)) | (TSTATE_IE|TSTATE_PEF); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;current-&gt;tss.flags &amp;= ~SPARC_FLAG_32BIT; &bslash;&n;&t;current-&gt;tss.wstate = (1 &lt;&lt; 3); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (1 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - REGWIN_SZ - STACK_BIAS), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0]))); &bslash;&n;} while(0)
DECL|macro|start_thread32
mdefine_line|#define start_thread32(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;register unsigned int zero asm(&quot;g1&quot;); &bslash;&n;&bslash;&n;&t;pc &amp;= 0x00000000ffffffffUL; &bslash;&n;&t;sp &amp;= 0x00000000ffffffffUL; &bslash;&n;&bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP))|(TSTATE_IE|TSTATE_AM|TSTATE_PEF); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;current-&gt;tss.flags |= SPARC_FLAG_32BIT; &bslash;&n;&t;current-&gt;tss.wstate = (2 &lt;&lt; 3); &bslash;&n;&t;zero = 0; &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (2 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - REGWIN32_SZ), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0])), &bslash;&n;&t;  &quot;r&quot; (zero)); &bslash;&n;} while(0)
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(tsk)&t;&t;do { } while(0)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Allocation and freeing of task_struct and kernel stack. */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()   ((struct task_struct *)__get_free_pages(GFP_KERNEL, 1, 0))
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
