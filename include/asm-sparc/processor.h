multiline_comment|/* $Id: processor.h,v 1.61 1997/10/22 09:25:42 jj Exp $&n; * include/asm-sparc/processor.h&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC_PROCESSOR_H
DECL|macro|__ASM_SPARC_PROCESSOR_H
mdefine_line|#define __ASM_SPARC_PROCESSOR_H
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * The sparc has no problems with write protection&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* Whee, this is STACK_TOP + PAGE_SIZE and the lowest kernel address too... &n; * That one page is used to protect kernel from intruders, so that&n; * we can make our access_ok test faster&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(page_offset)
DECL|macro|COPY_TASK_STRUCT
mdefine_line|#define COPY_TASK_STRUCT(dst, src) &t;&bslash;&n;do {&t;&t;&t;&t;&t;&bslash;&n;&t;*dst = *src;&t;&t;&t;&bslash;&n;} while (0)
DECL|struct|fpq
r_struct
id|fpq
(brace
DECL|member|insn_addr
r_int
r_int
op_star
id|insn_addr
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|seg
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
DECL|member|uwinmask
r_int
r_int
id|uwinmask
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
DECL|member|kregs
r_struct
id|pt_regs
op_star
id|kregs
suffix:semicolon
multiline_comment|/* For signal handling */
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
multiline_comment|/* Context switch saved kernel state. */
DECL|member|ksp
r_int
r_int
id|ksp
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
DECL|member|kpc
r_int
r_int
id|kpc
suffix:semicolon
DECL|member|kpsr
r_int
r_int
id|kpsr
suffix:semicolon
DECL|member|kwim
r_int
r_int
id|kwim
suffix:semicolon
multiline_comment|/* Special child fork kpsr/kwim values. */
DECL|member|fork_kpsr
r_int
r_int
id|fork_kpsr
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
DECL|member|fork_kwim
r_int
r_int
id|fork_kwim
suffix:semicolon
multiline_comment|/* A place to store user windows and stack pointers&n;&t; * when the stack needs inspection.&n;&t; */
DECL|macro|NSWINS
mdefine_line|#define NSWINS 8
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
l_int|8
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
DECL|member|w_saved
r_int
r_int
id|w_saved
suffix:semicolon
multiline_comment|/* Floating point regs */
DECL|member|float_regs
r_int
r_int
id|float_regs
(braket
l_int|32
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
DECL|member|fsr
r_int
r_int
id|fsr
suffix:semicolon
DECL|member|fpqdepth
r_int
r_int
id|fpqdepth
suffix:semicolon
DECL|member|fpqueue
r_struct
id|fpq
id|fpqueue
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sstk_info
r_struct
id|sigstack
id|sstk_info
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|current_ds
id|mm_segment_t
id|current_ds
suffix:semicolon
DECL|member|core_exec
r_struct
id|exec
id|core_exec
suffix:semicolon
multiline_comment|/* just what it says. */
DECL|member|new_signal
r_int
id|new_signal
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPARC_FLAG_KTHREAD
mdefine_line|#define SPARC_FLAG_KTHREAD      0x1    /* task is a kernel thread */
DECL|macro|SPARC_FLAG_UNALIGNED
mdefine_line|#define SPARC_FLAG_UNALIGNED    0x2    /* is allowed to do unaligned accesses */
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, (0), (0), &bslash;&n;&t;&t;    __pgprot(0x0) , VM_READ | VM_WRITE | VM_EXEC, NULL, &amp;init_mm.mmap }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;/* uwinmask, kregs, sig_address, sig_desc, ksp, kpc, kpsr, kwim */ &bslash;&n;   0,        0,     0,           0,        0,   0,   0,    0, &bslash;&n;/* fork_kpsr, fork_kwim */ &bslash;&n;   0,         0, &bslash;&n;/* reg_window */  &bslash;&n;{ { { 0, }, { 0, } }, }, &bslash;&n;/* rwbuf_stkptrs */  &bslash;&n;{ 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;/* w_saved */ &bslash;&n;   0, &bslash;&n;/* FPU regs */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;/* FPU status, FPU qdepth, FPU queue */ &bslash;&n;   0,          0,  { { 0, 0, }, }, &bslash;&n;/* sstk_info */ &bslash;&n;{ 0, 0, }, &bslash;&n;/* flags,              current_ds, */ &bslash;&n;   SPARC_FLAG_KTHREAD, KERNEL_DS, &bslash;&n;/* core_exec */ &bslash;&n;{ 0, }, &bslash;&n;/* new_signal */ &bslash;&n;  0, &bslash;&n;}
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
DECL|function|start_thread
r_extern
id|__inline__
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
)paren
(brace
r_register
r_int
r_int
id|zero
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|regs-&gt;psr
op_assign
(paren
id|regs-&gt;psr
op_amp
(paren
id|PSR_CWP
)paren
)paren
op_or
id|PSR_S
suffix:semicolon
id|regs-&gt;pc
op_assign
(paren
(paren
id|pc
op_amp
(paren
op_complement
l_int|3
)paren
)paren
op_minus
l_int|4
)paren
suffix:semicolon
id|regs-&gt;npc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;y
op_assign
l_int|0
suffix:semicolon
id|zero
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x18]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x20]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x28]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x30]&bslash;n&bslash;t&quot;
l_string|&quot;st&bslash;t%1, [%0 + %3 + 0x38]&bslash;n&bslash;t&quot;
l_string|&quot;st&bslash;t%%g0, [%0 + %3 + 0x3c]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regs
)paren
comma
l_string|&quot;r&quot;
(paren
id|sp
op_minus
id|REGWIN_SZ
)paren
comma
l_string|&quot;r&quot;
(paren
id|zero
)paren
comma
l_string|&quot;i&quot;
(paren
(paren
r_const
r_int
r_int
)paren
(paren
op_amp
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|u_regs
(braket
l_int|0
)braket
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(tsk)&t;&t;do { } while(0)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Allocation and freeing of basic task resources. */
r_extern
r_struct
id|task_struct
op_star
(paren
op_star
id|alloc_task_struct
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|free_task_struct
)paren
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif
macro_line|#endif /* __ASM_SPARC_PROCESSOR_H */
eof
