macro_line|#ifndef _ASM_IA64_UNWIND_H
DECL|macro|_ASM_IA64_UNWIND_H
mdefine_line|#define _ASM_IA64_UNWIND_H
multiline_comment|/*&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * A simple API for unwinding kernel stacks.  This is used for&n; * debugging and error reporting purposes.  The kernel doesn&squot;t need&n; * full-blown stack unwinding with all the bells and whitles, so there&n; * is not much point in implementing the full IA-64 unwind API (though&n; * it would of course be possible to implement the kernel API on top&n; * of it).&n; */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* forward declaration */
r_struct
id|switch_stack
suffix:semicolon
multiline_comment|/* forward declaration */
multiline_comment|/*&n; * The following declarations are private to the unwind&n; * implementation:&n; */
DECL|struct|ia64_stack
r_struct
id|ia64_stack
(brace
DECL|member|limit
r_int
r_int
op_star
id|limit
suffix:semicolon
DECL|member|top
r_int
r_int
op_star
id|top
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * No user of this module should every access this structure directly&n; * as it is subject to change.  It is declared here solely so we can&n; * use automatic variables.&n; */
DECL|struct|ia64_frame_info
r_struct
id|ia64_frame_info
(brace
DECL|member|regstk
r_struct
id|ia64_stack
id|regstk
suffix:semicolon
DECL|member|bsp
r_int
r_int
op_star
id|bsp
suffix:semicolon
DECL|member|top_rnat
r_int
r_int
id|top_rnat
suffix:semicolon
multiline_comment|/* RSE NaT collection at top of backing store */
DECL|member|cfm
r_int
r_int
id|cfm
suffix:semicolon
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* instruction pointer */
)brace
suffix:semicolon
multiline_comment|/*&n; * The official API follows below:&n; */
multiline_comment|/*&n; * Prepare to unwind blocked task t.&n; */
r_extern
r_void
id|ia64_unwind_init_from_blocked_task
(paren
r_struct
id|ia64_frame_info
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*&n; * Prepare to unwind the current task.  For this to work, the kernel&n; * stack identified by REGS must look like this:&n; *&n; *&t;//&t;&t;      //&n; *&t;|&t;&t;      |&n; *&t;|   kernel stack      |&n; *&t;|&t;&t;      |&n; *&t;+=====================+&n; *&t;|   struct pt_regs    |&n; *&t;+---------------------+ &lt;--- REGS&n; *&t;| struct switch_stack |&n; *&t;+---------------------+&n; */
r_extern
r_void
id|ia64_unwind_init_from_current
(paren
r_struct
id|ia64_frame_info
op_star
id|info
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * Unwind to previous to frame.  Returns 0 if successful, negative&n; * number in case of an error.&n; */
r_extern
r_int
id|ia64_unwind_to_previous_frame
(paren
r_struct
id|ia64_frame_info
op_star
id|info
)paren
suffix:semicolon
DECL|macro|ia64_unwind_get_ip
mdefine_line|#define ia64_unwind_get_ip(info)&t;((info)-&gt;ip)
DECL|macro|ia64_unwind_get_bsp
mdefine_line|#define ia64_unwind_get_bsp(info)&t;((unsigned long) (info)-&gt;bsp)
macro_line|#endif /* _ASM_IA64_UNWIND_H */
eof
