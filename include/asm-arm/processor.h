multiline_comment|/*&n; * include/asm-arm/processor.h&n; *&n; * Copyright (C) 1995 Russell King&n; */
macro_line|#ifndef __ASM_ARM_PROCESSOR_H
DECL|macro|__ASM_ARM_PROCESSOR_H
mdefine_line|#define __ASM_ARM_PROCESSOR_H
DECL|struct|fp_hard_struct
r_struct
id|fp_hard_struct
(brace
DECL|member|save
r_int
r_int
id|save
(braket
l_int|140
op_div
l_int|4
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
l_int|140
op_div
l_int|4
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
DECL|macro|DECLARE_THREAD_STRUCT
mdefine_line|#define DECLARE_THREAD_STRUCT&t;&t;&t;&t;&t;&t;&t;&bslash;&n;struct thread_struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long&t;address;&t;&t;/* Address of fault&t;*/&t;&bslash;&n;&t;unsigned long&t;trap_no;&t;&t;/* Trap number&t;&t;*/&t;&bslash;&n;&t;unsigned long&t;error_code;&t;&t;/* Error code of trap&t;*/&t;&bslash;&n;&t;union fp_state&t;fpstate;&t;&t;/* FPE save state&t;*/&t;&bslash;&n;&t;EXTRA_THREAD_STRUCT&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#include &lt;asm/arch/processor.h&gt;
macro_line|#include &lt;asm/proc/processor.h&gt;
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  {&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&bslash;&n;&t;{ { { 0, }, }, },&t;&t;&bslash;&n;&t;EXTRA_THREAD_STRUCT_INIT&t;&bslash;&n;}
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
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* __ASM_ARM_PROCESSOR_H */
eof