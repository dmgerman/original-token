multiline_comment|/*&n; * include/asm-alpha/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_ALPHA_PROCESSOR_H
DECL|macro|__ASM_ALPHA_PROCESSOR_H
mdefine_line|#define __ASM_ALPHA_PROCESSOR_H
multiline_comment|/*&n; * We have a 42-bit user address space: 4TB user VM...&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE (0x40000000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 1
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* the fields below are used by PALcode and must match struct pcb: */
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
DECL|member|ptbr
r_int
r_int
id|ptbr
suffix:semicolon
DECL|member|pcc
r_int
r_int
id|pcc
suffix:semicolon
DECL|member|asn
r_int
r_int
id|asn
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
multiline_comment|/*&n;&t; * bit  0: floating point enable&n;&t; * bit 62: performance monitor enable&n;&t; */
DECL|member|pal_flags
r_int
r_int
id|pal_flags
suffix:semicolon
DECL|member|res1
DECL|member|res2
r_int
r_int
id|res1
comma
id|res2
suffix:semicolon
multiline_comment|/* the fields below are Linux-specific: */
multiline_comment|/* bit 1..5: IEEE_TRAP_ENABLE bits (see fpu.h) */
multiline_comment|/* bit 6..8: UAC bits (see sysinfo.h) */
multiline_comment|/* bit 17..21: IEEE_STATUS_MASK bits (see fpu.h) */
multiline_comment|/* bit 63: die_if_kernel recursion lock */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* perform syscall argument validation (get/set_fs) */
DECL|member|fs
r_int
r_int
id|fs
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, 0xfffffc0000000000,  0xfffffc0010000000, &bslash;&n;&t;PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, NULL, &amp;init_mm.mmap }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, &bslash;&n;&t;0 &bslash;&n;}
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * Return saved PC of a blocked thread.  This assumes the frame&n; * pointer is the 6th saved long on the kernel stack and that the&n; * saved return address is the first long in the frame.  This all&n; * holds provided the thread blocked through a call to schedule() ($15&n; * is the frame pointer in schedule() and $15 is saved at offset 48 by&n; * entry.S:do_switch_stack).&n; */
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
r_int
r_int
id|fp
suffix:semicolon
id|fp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;ksp
)paren
(braket
l_int|6
)braket
suffix:semicolon
r_return
op_star
(paren
r_int
r_int
op_star
)paren
id|fp
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
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
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
multiline_comment|/* NOTE: The task struct and the stack go together!  */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;        ((struct task_struct *) __get_free_pages(GFP_KERNEL,1,0))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)     free_pages((unsigned long)(p),1)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* __ASM_ALPHA_PROCESSOR_H */
eof
