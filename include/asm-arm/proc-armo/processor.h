multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/processor.h&n; *&n; *  Copyright (C) 1996 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   27-06-1996&t;RMK&t;Created&n; *   10-10-1996&t;RMK&t;Brought up to date with SA110&n; *   26-09-1996&t;RMK&t;Added &squot;EXTRA_THREAD_STRUCT*&squot;&n; *   28-09-1996&t;RMK&t;Moved start_thread into the processor dependencies&n; *   11-01-1998&t;RMK&t;Added new uaccess_t&n; *   09-09-1998&t;PJB&t;Delete redundant `wp_works_ok&squot;&n; *   30-05-1999&t;PJB&t;Save sl across context switches&n; */
macro_line|#ifndef __ASM_PROC_PROCESSOR_H
DECL|macro|__ASM_PROC_PROCESSOR_H
mdefine_line|#define __ASM_PROC_PROCESSOR_H
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE 4096
DECL|struct|context_save_struct
r_struct
id|context_save_struct
(brace
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|sl
r_int
r_int
id|sl
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_CSS
mdefine_line|#define INIT_CSS (struct context_save_struct){ 0, 0, 0, 0, 0, 0, 0, 0, SVC26_MODE }
r_typedef
r_struct
(brace
DECL|member|put_byte
r_void
(paren
op_star
id|put_byte
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|get_byte
r_void
(paren
op_star
id|get_byte
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|put_half
r_void
(paren
op_star
id|put_half
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|get_half
r_void
(paren
op_star
id|get_half
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|put_word
r_void
(paren
op_star
id|put_word
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|get_word
r_void
(paren
op_star
id|get_word
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special calling convention */
DECL|member|copy_from_user
r_int
r_int
(paren
op_star
id|copy_from_user
)paren
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|copy_to_user
r_int
r_int
(paren
op_star
id|copy_to_user
)paren
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|clear_user
r_int
r_int
(paren
op_star
id|clear_user
)paren
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|strncpy_from_user
r_int
r_int
(paren
op_star
id|strncpy_from_user
)paren
(paren
r_char
op_star
id|to
comma
r_const
r_char
op_star
id|from
comma
r_int
r_int
id|sz
)paren
suffix:semicolon
DECL|member|strnlen_user
r_int
r_int
(paren
op_star
id|strnlen_user
)paren
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
suffix:semicolon
DECL|typedef|uaccess_t
)brace
id|uaccess_t
suffix:semicolon
r_extern
id|uaccess_t
id|uaccess_user
comma
id|uaccess_kernel
suffix:semicolon
DECL|macro|EXTRA_THREAD_STRUCT
mdefine_line|#define EXTRA_THREAD_STRUCT&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;uaccess_t&t;*uaccess;&t;&t;/* User access functions*/
DECL|macro|EXTRA_THREAD_STRUCT_INIT
mdefine_line|#define EXTRA_THREAD_STRUCT_INIT&t;&t;&bslash;&n;&t;uaccess:&t;&amp;uaccess_kernel,
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,pc,sp)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long *stack = (unsigned long *)sp;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memzero(regs-&gt;uregs, sizeof (regs-&gt;uregs));&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_pc = pc;&t;&t;/* pc */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_sp = sp;&t;&t;/* sp */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r2 = stack[2];&t;/* r2 (envp) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r1 = stack[1];&t;/* r1 (argv) */&t;&t;&t;&bslash;&n;&t;regs-&gt;ARM_r0 = stack[0];&t;/* r0 (argc) */&t;&t;&t;&bslash;&n;})
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)))[1022])
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)&t;(((unsigned long *)(4096+(unsigned long)(tsk)))[1020])
multiline_comment|/* Allocation and freeing of basic task resources. */
multiline_comment|/*&n; * NOTE! The task struct and the stack go together&n; */
r_extern
r_int
r_int
id|get_page_8k
c_func
(paren
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|free_page_8k
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
DECL|macro|ll_alloc_task_struct
mdefine_line|#define ll_alloc_task_struct()&t;((struct task_struct *)get_page_8k(GFP_KERNEL))
DECL|macro|ll_free_task_struct
mdefine_line|#define ll_free_task_struct(p)  free_page_8k((unsigned long)(p))
macro_line|#endif
eof
