multiline_comment|/*&n; * include/asm-m68k/processor.h&n; *&n; * Copyright (C) 1995 Hamish Macdonald&n; */
macro_line|#ifndef __ASM_M68K_PROCESSOR_H
DECL|macro|__ASM_M68K_PROCESSOR_H
mdefine_line|#define __ASM_M68K_PROCESSOR_H
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
multiline_comment|/*&n; * User space process size: 3.75GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xF0000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;0xC0000000UL
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
multiline_comment|/* &n; * if you change this structure, you must change the code and offsets&n; * in m68k/machasm.S&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* user stack pointer */
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
multiline_comment|/* saved status register */
DECL|member|fs
r_int
r_int
id|fs
suffix:semicolon
multiline_comment|/* saved fs (sfc, dfc) */
DECL|member|crp
r_int
r_int
id|crp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* cpu root pointer */
DECL|member|esp0
r_int
r_int
id|esp0
suffix:semicolon
multiline_comment|/* points to SR of stack frame */
DECL|member|fp
r_int
r_int
id|fp
(braket
l_int|8
op_star
l_int|3
)braket
suffix:semicolon
DECL|member|fpcntl
r_int
r_int
id|fpcntl
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fp control regs */
DECL|member|fpstate
r_int
r_char
id|fpstate
(braket
id|FPSTATESIZE
)braket
suffix:semicolon
multiline_comment|/* floating point state */
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, 0, 0x40000000, __pgprot(_PAGE_PRESENT|_PAGE_ACCESSED), VM_READ | VM_WRITE | VM_EXEC }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;sizeof(init_kernel_stack) + (long) init_kernel_stack, 0, &bslash;&n;&t;PS_S, KERNEL_DS, &bslash;&n;&t;{0, 0}, 0, {0,}, {0, 0, 0}, {0,}, &bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|function|start_thread
r_static
r_inline
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
id|usp
)paren
(brace
r_int
r_int
id|nilstate
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear floating point state */
id|__asm__
id|__volatile__
(paren
l_string|&quot;.chip 68k/68881&bslash;n&bslash;t&quot;
l_string|&quot;frestore %0@&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|nilstate
)paren
)paren
suffix:semicolon
multiline_comment|/* reads from user space */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|pc
suffix:semicolon
id|regs-&gt;sr
op_and_assign
op_complement
l_int|0x2000
suffix:semicolon
id|wrusp
c_func
(paren
id|usp
)paren
suffix:semicolon
)brace
multiline_comment|/* Free all resources held by a thread. */
r_extern
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
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
r_extern
r_int
id|sys_pause
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|schedule
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|switch_stack
op_star
id|sw
op_assign
(paren
r_struct
id|switch_stack
op_star
)paren
id|t-&gt;ksp
suffix:semicolon
multiline_comment|/* Check whether the thread is blocked in resume() */
r_if
c_cond
(paren
id|sw-&gt;retpc
op_ge
(paren
r_int
r_int
)paren
id|schedule
op_logical_and
id|sw-&gt;retpc
OL
(paren
r_int
r_int
)paren
id|sys_pause
)paren
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|sw-&gt;a6
)paren
(braket
l_int|1
)braket
suffix:semicolon
r_else
r_return
id|sw-&gt;retpc
suffix:semicolon
)brace
multiline_comment|/* Allocation and freeing of basic task resources. */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()&t;kmalloc(sizeof(struct task_struct), GFP_KERNEL)
DECL|macro|alloc_kernel_stack
mdefine_line|#define alloc_kernel_stack(p)&t;__get_free_page(GFP_KERNEL)
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)&t;kfree(p)
DECL|macro|free_kernel_stack
mdefine_line|#define free_kernel_stack(page) free_page((page))
macro_line|#endif
eof
