macro_line|#ifndef _SPARC_PTRACE_H
DECL|macro|_SPARC_PTRACE_H
mdefine_line|#define _SPARC_PTRACE_H
multiline_comment|/* I have not looked enough into how this should be done. Without playing&n; * lots of tricks to optimize I think we need to save the whole register&n; * window frame plus the floating-point registers. We&squot;ll see...&n; */
multiline_comment|/* this struct defines the way the registers are stored on the &n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|ps
r_int
r_int
id|ps
suffix:semicolon
multiline_comment|/* previous supervisor, same as alpha I believe */
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
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* stack and frame pointer */
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
multiline_comment|/* for condition codes */
DECL|member|nuwin
r_int
r_int
id|nuwin
suffix:semicolon
multiline_comment|/* number of user windows */
multiline_comment|/* not sure yet whether all regs are necessary&n;&t; * but this is how it is traditionally done on the sparc.&n;&t; */
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|24
op_star
l_int|16
)braket
suffix:semicolon
DECL|member|f_regs
r_int
r_int
id|f_regs
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* yuck yuck yuck */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (0x0)  /* if previous supervisor is 0, came from user */
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
