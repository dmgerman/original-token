macro_line|#ifndef _I386_PTRACE_H
DECL|macro|_I386_PTRACE_H
mdefine_line|#define _I386_PTRACE_H
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
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
DECL|member|a0
r_int
r_int
id|a0
suffix:semicolon
DECL|member|a1
r_int
r_int
id|a1
suffix:semicolon
DECL|member|a2
r_int
r_int
id|a2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((regs)-&gt;ps &amp; 8)
macro_line|#endif
eof
