multiline_comment|/* $Id: ptrace.h,v 1.1 1996/12/12 11:59:35 davem Exp $ */
macro_line|#ifndef _SPARC64_PTRACE_H
DECL|macro|_SPARC64_PTRACE_H
mdefine_line|#define _SPARC64_PTRACE_H
macro_line|#include &lt;asm/pstate.h&gt;
multiline_comment|/* This struct defines the way the registers are stored on the &n; * stack during a system call and basically all traps.&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* globals and ins */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
DECL|member|tpc
r_int
r_int
id|tpc
suffix:semicolon
DECL|member|tnpc
r_int
r_int
id|tnpc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UREG_G0
mdefine_line|#define UREG_G0        0
DECL|macro|UREG_G1
mdefine_line|#define UREG_G1        1
DECL|macro|UREG_G2
mdefine_line|#define UREG_G2        2
DECL|macro|UREG_G3
mdefine_line|#define UREG_G3        3
DECL|macro|UREG_G4
mdefine_line|#define UREG_G4        4
DECL|macro|UREG_G5
mdefine_line|#define UREG_G5        5
DECL|macro|UREG_G6
mdefine_line|#define UREG_G6        6
DECL|macro|UREG_G7
mdefine_line|#define UREG_G7        7
DECL|macro|UREG_I0
mdefine_line|#define UREG_I0        8
DECL|macro|UREG_I1
mdefine_line|#define UREG_I1        9
DECL|macro|UREG_I2
mdefine_line|#define UREG_I2        10
DECL|macro|UREG_I3
mdefine_line|#define UREG_I3        11
DECL|macro|UREG_I4
mdefine_line|#define UREG_I4        12
DECL|macro|UREG_I5
mdefine_line|#define UREG_I5        13
DECL|macro|UREG_I6
mdefine_line|#define UREG_I6        14
DECL|macro|UREG_I7
mdefine_line|#define UREG_I7        15
DECL|macro|UREG_FP
mdefine_line|#define UREG_FP        UREG_I6
DECL|macro|UREG_RETPC
mdefine_line|#define UREG_RETPC     UREG_I7
multiline_comment|/* A V9 register window */
DECL|struct|reg_window
r_struct
id|reg_window
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A 32-bit register window. */
DECL|struct|reg_window_32
r_struct
id|reg_window_32
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A V9 Sparc stack frame */
DECL|struct|sparc_stackf
r_struct
id|sparc_stackf
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fp
r_struct
id|sparc_stackf
op_star
id|fp
suffix:semicolon
DECL|member|callers_pc
r_int
r_int
id|callers_pc
suffix:semicolon
DECL|member|structptr
r_char
op_star
id|structptr
suffix:semicolon
DECL|member|xargs
r_int
r_int
id|xargs
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|xxargs
r_int
r_int
id|xxargs
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A 32-bit Sparc stack frame */
DECL|struct|sparc_stackf_32
r_struct
id|sparc_stackf_32
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|callers_pc
r_int
r_int
id|callers_pc
suffix:semicolon
DECL|member|structptr
r_int
r_int
id|structptr
suffix:semicolon
DECL|member|xargs
r_int
r_int
id|xargs
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|xxargs
r_int
r_int
id|xxargs
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TRACEREG_SZ
mdefine_line|#define TRACEREG_SZ   sizeof(struct pt_regs)
DECL|macro|STACKFRAME_SZ
mdefine_line|#define STACKFRAME_SZ sizeof(struct sparc_stackf)
DECL|macro|REGWIN_SZ
mdefine_line|#define REGWIN_SZ     sizeof(struct reg_window)
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!((regs)-&gt;tstate &amp; PSR_PS))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;tpc)
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
macro_line|#else /* __ASSEMBLY__ */
multiline_comment|/* For assembly code. */
DECL|macro|TRACEREG_SZ
mdefine_line|#define TRACEREG_SZ       0x50
DECL|macro|STACKFRAME_SZ
mdefine_line|#define STACKFRAME_SZ     0x60
DECL|macro|REGWIN_SZ
mdefine_line|#define REGWIN_SZ         0x40
macro_line|#endif
eof
