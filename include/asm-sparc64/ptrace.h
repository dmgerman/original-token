multiline_comment|/* $Id: ptrace.h,v 1.4 1996/12/28 18:39:54 davem Exp $ */
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
DECL|struct|pt_regs32
r_struct
id|pt_regs32
(brace
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
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
DECL|struct|reg_window32
r_struct
id|reg_window32
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
DECL|struct|sparc_stackf32
r_struct
id|sparc_stackf32
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
DECL|struct|sparc_trapf
r_struct
id|sparc_trapf
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
DECL|member|_unused
r_int
r_int
id|_unused
suffix:semicolon
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TRACEREG_SZ
mdefine_line|#define TRACEREG_SZ&t;sizeof(struct pt_regs)
DECL|macro|STACKFRAME_SZ
mdefine_line|#define STACKFRAME_SZ&t;sizeof(struct sparc_stackf)
DECL|macro|REGWIN_SZ
mdefine_line|#define REGWIN_SZ&t;sizeof(struct reg_window)
DECL|macro|TRACEREG32_SZ
mdefine_line|#define TRACEREG32_SZ&t;sizeof(struct pt_regs32)
DECL|macro|STACKFRAME32_SZ
mdefine_line|#define STACKFRAME32_SZ&t;sizeof(struct sparc_stackf32)
DECL|macro|REGWIN32_SZ
mdefine_line|#define REGWIN32_SZ&t;sizeof(struct reg_window32)
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!((regs)-&gt;tstate &amp; TSTATE_PRIV))
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
mdefine_line|#define TRACEREG_SZ&t;&t;XXX
DECL|macro|STACKFRAME_SZ
mdefine_line|#define STACKFRAME_SZ&t;&t;YYY
DECL|macro|REGWIN_SZ
mdefine_line|#define REGWIN_SZ&t;&t;ZZZ
DECL|macro|TRACEREG32_SZ
mdefine_line|#define TRACEREG32_SZ&t;&t;0x50
DECL|macro|STACKFRAME32_SZ
mdefine_line|#define STACKFRAME32_SZ&t;&t;0x60
DECL|macro|REGWIN32_SZ
mdefine_line|#define REGWIN32_SZ&t;&t;0x40
macro_line|#endif
macro_line|#endif /* !(_SPARC64_PTRACE_H) */
eof
