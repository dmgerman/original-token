multiline_comment|/*&n; * include/asm-arm/processor.h&n; *&n; * Copyright (C) 1995 Russell King&n; */
macro_line|#ifndef __ASM_ARM_PROCESSOR_H
DECL|macro|__ASM_ARM_PROCESSOR_H
mdefine_line|#define __ASM_ARM_PROCESSOR_H
DECL|macro|FP_SIZE
mdefine_line|#define FP_SIZE 35
DECL|struct|fp_hard_struct
r_struct
id|fp_hard_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
id|FP_SIZE
)braket
suffix:semicolon
multiline_comment|/* as yet undefined */
)brace
suffix:semicolon
DECL|struct|fp_soft_struct
r_struct
id|fp_soft_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
id|FP_SIZE
)braket
suffix:semicolon
multiline_comment|/* undefined information */
)brace
suffix:semicolon
DECL|union|fp_state
r_union
id|fp_state
(brace
DECL|member|hard
r_struct
id|fp_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|fp_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mm_segment_t
r_typedef
r_int
r_int
id|mm_segment_t
suffix:semicolon
multiline_comment|/* domain register&t;*/
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/assembler.h&gt; 
DECL|macro|NR_DEBUGS
mdefine_line|#define NR_DEBUGS&t;5
macro_line|#include &lt;asm/arch/processor.h&gt;
macro_line|#include &lt;asm/proc/processor.h&gt;
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* Address of fault&t;*/
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
multiline_comment|/* Trap number&t;*/
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
multiline_comment|/* Error code of trap&t;*/
DECL|member|fpstate
r_union
id|fp_state
id|fpstate
suffix:semicolon
multiline_comment|/* FPE save state&t;*/
DECL|member|debug
r_int
r_int
id|debug
(braket
id|NR_DEBUGS
)braket
suffix:semicolon
multiline_comment|/* Debug/ptrace&t;*/
DECL|member|save
r_struct
id|context_save_struct
op_star
id|save
suffix:semicolon
multiline_comment|/* context save&t;*/
DECL|member|memmap
r_int
r_int
id|memmap
suffix:semicolon
multiline_comment|/* page tables&t;*/
id|EXTRA_THREAD_STRUCT
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  {&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;{ { { 0, }, }, },&t;&t;&t;&bslash;&n;&t;{ 0, },&t;&t;&t;&t;&t;&bslash;&n;&t;(struct context_save_struct *)0,&t;&bslash;&n;&t;SWAPPER_PG_DIR&t;&t;&t;&t;&bslash;&n;&t;EXTRA_THREAD_STRUCT_INIT&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
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
id|t-&gt;save
ques
c_cond
id|t-&gt;save-&gt;pc
op_amp
op_complement
id|PCMASK
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|get_css_fp
r_extern
id|__inline__
r_int
r_int
id|get_css_fp
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_return
id|t-&gt;save
ques
c_cond
id|t-&gt;save-&gt;fp
suffix:colon
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_sys_call&quot;
)paren
suffix:semicolon
DECL|function|init_thread_css
r_extern
id|__inline__
r_void
id|init_thread_css
c_func
(paren
r_struct
id|context_save_struct
op_star
id|save
)paren
(brace
op_star
id|save
op_assign
id|INIT_CSS
suffix:semicolon
id|save-&gt;pc
op_or_assign
(paren
r_int
r_int
)paren
id|ret_from_sys_call
suffix:semicolon
)brace
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|mm_struct
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
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(nr, tsk, mm)&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
DECL|macro|forget_segments
mdefine_line|#define forget_segments()&t;&t;do { } while (0)
r_extern
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif
macro_line|#endif /* __ASM_ARM_PROCESSOR_H */
eof
