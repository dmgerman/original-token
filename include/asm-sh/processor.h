multiline_comment|/*&n; * include/asm-sh/processor.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; */
macro_line|#ifndef __ASM_SH_PROCESSOR_H
DECL|macro|__ASM_SH_PROCESSOR_H
mdefine_line|#define __ASM_SH_PROCESSOR_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;mova&t;1f,%0&bslash;n1:&quot;:&quot;=z&quot; (pc)); pc; })
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; */
DECL|struct|sh_cpuinfo
r_struct
id|sh_cpuinfo
(brace
DECL|member|loops_per_sec
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sh_cpuinfo
id|boot_cpu_data
suffix:semicolon
DECL|macro|cpu_data
mdefine_line|#define cpu_data &amp;boot_cpu_data
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
multiline_comment|/*&n; * User space process size: 2GB.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x80000000
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|trap_no
DECL|member|error_code
r_int
r_int
id|trap_no
comma
id|error_code
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* Hardware debugging registers may come here */
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0x80000000, 0xa0000000, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sizeof(init_stack) + (long) &amp;init_stack, /* sp */&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t; /* pc */&t;&bslash;&n;&t;0, 0, &bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_pc, new_sp)&t; &bslash;&n;&t;set_fs(USER_DS);&t;&t;&t; &bslash;&n;&t;regs-&gt;pr = 0;   &t;&t; &t; &bslash;&n;&t;regs-&gt;sr = 0;&t;&t;/* User mode. */ &bslash;&n;&t;regs-&gt;pc = new_pc;&t;&t;&t; &bslash;&n;&t;regs-&gt;u_regs[UREG_SP] = new_sp
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
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
multiline_comment|/*&n; * create a kernel thread without removing it from tasklists&n; */
r_extern
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(p, mm)&t;do { } while(0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;do { } while(0)
DECL|macro|forget_segments
mdefine_line|#define forget_segments()&t;do { } while (0)
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
id|t-&gt;pc
suffix:semicolon
)brace
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
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
macro_line|#endif /* __ASM_SH_PROCESSOR_H */
eof
