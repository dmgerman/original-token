macro_line|#ifndef __ASM_SH_PTRACE_H
DECL|macro|__ASM_SH_PTRACE_H
mdefine_line|#define __ASM_SH_PTRACE_H
multiline_comment|/*&n; * Copyright (C) 1999  Niibe Yutaka&n; *&n; */
multiline_comment|/*&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|syscall_nr
r_int
id|syscall_nr
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|gbr
r_int
r_int
id|gbr
suffix:semicolon
DECL|member|mach
r_int
r_int
id|mach
suffix:semicolon
DECL|member|macl
r_int
r_int
id|macl
suffix:semicolon
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;sr &amp; 0x40000000)==0)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;pc)
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
macro_line|#endif /* __ASM_SH_PTRACE_H */
eof
