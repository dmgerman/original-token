macro_line|#ifndef _SPARC_PTRACE_H
DECL|macro|_SPARC_PTRACE_H
mdefine_line|#define _SPARC_PTRACE_H
multiline_comment|/* I have not looked enough into how this should be done. Without playing&n; * lots of tricks to optimize I think we need to save the whole register&n; * window frame plus the floating-point registers. We&squot;ll see...&n; */
multiline_comment|/* this struct defines the way the registers are stored on the &n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
multiline_comment|/* for condition codes */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* current and next program counter */
DECL|member|npc
r_int
r_int
id|npc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
multiline_comment|/* not sure yet whether all regs are necessary&n;&t; * but this is how it is traditionally done on the sparc.&n;&t; */
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* globals and ins */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* if previous supervisor is 0, came from user */
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (0x0)
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
