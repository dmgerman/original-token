multiline_comment|/* $Id: processor.h,v 1.29 1995/11/26 05:01:29 davem Exp $&n; * include/asm-sparc/processor.h&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC_PROCESSOR_H
DECL|macro|__ASM_SPARC_PROCESSOR_H
mdefine_line|#define __ASM_SPARC_PROCESSOR_H
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * Write Protection works right in supervisor mode on the Sparc...&n; * And then there came the Swift module, which isn&squot;t so swift...&n; */
r_extern
r_char
id|wp_works_ok
suffix:semicolon
multiline_comment|/* Whee, this is STACK_TOP and the lowest kernel address too... */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(KERNBASE)
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
multiline_comment|/* Where our page table lives. */
DECL|member|pgd_ptr
r_int
r_int
id|pgd_ptr
suffix:semicolon
multiline_comment|/* The context currently allocated to this process&n;&t; * or -1 if no context has been allocated to this&n;&t; * task yet.&n;&t; */
DECL|member|context
r_int
id|context
suffix:semicolon
multiline_comment|/* Floating point regs */
DECL|member|float_regs
r_int
r_int
id|float_regs
(braket
l_int|64
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
DECL|member|fpqueue
)brace
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
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, (0xf0000000UL), (0xfe100000UL), &bslash;&n;&t;&t;    __pgprot(0x0) , VM_READ | VM_WRITE | VM_EXEC }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;/* uwinmask, sig_address, sig_desc, ksp, kpc, kpsr, kwim */ &bslash;&n;   0,        0,           0,        0,   0,   0,    0, &bslash;&n;/* reg_window */  &bslash;&n;{ { { 0, }, { 0, } }, }, &bslash;&n;/* rwbuf_stkptrs */  &bslash;&n;{ 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;/* w_saved, pgd_ptr,                context */  &bslash;&n;   0,       (long) &amp;swapper_pg_dir, -1, &bslash;&n;/* FPU regs */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;/* FPU status, FPU qdepth, FPU queue */ &bslash;&n;   0,          0,  { { 0, 0, }, }, &bslash;&n;/* sstk_info */ &bslash;&n;{ 0, 0, }, &bslash;&n;}
multiline_comment|/* Return saved PC of a blocked thread. */
DECL|function|thread_saved_pc
r_extern
r_inline
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
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
id|t-&gt;ksp
op_amp
(paren
op_complement
l_int|0xfff
)paren
)paren
op_plus
(paren
l_int|0x1000
op_minus
id|TRACEREG_SZ
)paren
)paren
)paren
op_member_access_from_pointer
id|pc
suffix:semicolon
)brace
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
r_extern
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
suffix:semicolon
macro_line|#endif /* __ASM_SPARC_PROCESSOR_H */
eof
