multiline_comment|/* $Id: sigcontext.h,v 1.4 1997/04/04 00:50:28 davem Exp $ */
macro_line|#ifndef __SPARC64_SIGCONTEXT_H
DECL|macro|__SPARC64_SIGCONTEXT_H
mdefine_line|#define __SPARC64_SIGCONTEXT_H
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/* XXX This gets exported to userland as well as kernel, it is probably&n; * XXX riddled with many hard to find 32-bit binary compatability issues.&n; * XXX Signals and this file need to be investigated heavily. -DaveM&n; */
DECL|macro|SUNOS_MAXWIN
mdefine_line|#define SUNOS_MAXWIN   31
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* SunOS system call sigstack() uses this arg. */
DECL|struct|sunos_sigstack
r_struct
id|sunos_sigstack
(brace
DECL|member|sig_sp
r_int
r_int
id|sig_sp
suffix:semicolon
DECL|member|onstack_flag
r_int
id|onstack_flag
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is what SunOS does, so shall I. */
DECL|struct|sigcontext32
r_struct
id|sigcontext32
(brace
DECL|member|sigc_onstack
r_int
id|sigc_onstack
suffix:semicolon
multiline_comment|/* state to restore */
DECL|member|sigc_mask
r_int
id|sigc_mask
suffix:semicolon
multiline_comment|/* sigmask to restore */
DECL|member|sigc_sp
r_int
id|sigc_sp
suffix:semicolon
multiline_comment|/* stack pointer */
DECL|member|sigc_pc
r_int
id|sigc_pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|sigc_npc
r_int
id|sigc_npc
suffix:semicolon
multiline_comment|/* next program counter */
DECL|member|sigc_psr
r_int
id|sigc_psr
suffix:semicolon
multiline_comment|/* for condition codes etc */
DECL|member|sigc_g1
r_int
id|sigc_g1
suffix:semicolon
multiline_comment|/* User uses these two registers */
DECL|member|sigc_o0
r_int
id|sigc_o0
suffix:semicolon
multiline_comment|/* within the trampoline code. */
multiline_comment|/* Now comes information regarding the users window set&n;&t; * at the time of the signal.&n;&t; */
DECL|member|sigc_oswins
r_int
id|sigc_oswins
suffix:semicolon
multiline_comment|/* outstanding windows */
multiline_comment|/* stack ptrs for each regwin buf */
multiline_comment|/* XXX 32-bit ptrs pinhead... */
DECL|member|sigc_spbuf
r_int
id|sigc_spbuf
(braket
id|SUNOS_MAXWIN
)braket
suffix:semicolon
multiline_comment|/* Windows to restore after signal */
DECL|member|sigc_wbuf
r_struct
id|reg_window32
id|sigc_wbuf
(braket
id|SUNOS_MAXWIN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is what SunOS doesn&squot;t, so we have to write this alone. */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sigc_onstack
r_int
id|sigc_onstack
suffix:semicolon
multiline_comment|/* state to restore */
DECL|member|sigc_mask
r_int
id|sigc_mask
suffix:semicolon
multiline_comment|/* sigmask to restore */
DECL|member|sigc_sp
r_int
id|sigc_sp
suffix:semicolon
multiline_comment|/* stack pointer */
DECL|member|sigc_pc
r_int
id|sigc_pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|sigc_npc
r_int
id|sigc_npc
suffix:semicolon
multiline_comment|/* next program counter */
DECL|member|sigc_psr
r_int
id|sigc_psr
suffix:semicolon
multiline_comment|/* for condition codes etc */
DECL|member|sigc_g1
r_int
id|sigc_g1
suffix:semicolon
multiline_comment|/* User uses these two registers */
DECL|member|sigc_o0
r_int
id|sigc_o0
suffix:semicolon
multiline_comment|/* within the trampoline code. */
multiline_comment|/* Now comes information regarding the users window set&n;&t; * at the time of the signal.&n;&t; */
DECL|member|sigc_oswins
r_int
id|sigc_oswins
suffix:semicolon
multiline_comment|/* outstanding windows */
multiline_comment|/* stack ptrs for each regwin buf */
DECL|member|sigc_spbuf
r_char
op_star
id|sigc_spbuf
(braket
id|SUNOS_MAXWIN
)braket
suffix:semicolon
multiline_comment|/* Windows to restore after signal */
DECL|member|sigc_wbuf
r_struct
id|reg_window
id|sigc_wbuf
(braket
id|SUNOS_MAXWIN
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|si_regs
r_struct
id|pt_regs32
id|si_regs
suffix:semicolon
DECL|member|si_mask
r_int
id|si_mask
suffix:semicolon
DECL|typedef|__siginfo32_t
)brace
id|__siginfo32_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|si_float_regs
r_int
r_int
id|si_float_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|si_fsr
r_int
r_int
id|si_fsr
suffix:semicolon
DECL|member|si_fpqdepth
r_int
r_int
id|si_fpqdepth
suffix:semicolon
r_struct
(brace
DECL|member|insn_addr
r_int
r_int
op_star
id|insn_addr
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|si_fpqueue
)brace
id|si_fpqueue
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|__siginfo_fpu32_t
)brace
id|__siginfo_fpu32_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|si_regs
r_struct
id|pt_regs
id|si_regs
suffix:semicolon
DECL|member|si_mask
r_int
id|si_mask
suffix:semicolon
DECL|typedef|__siginfo_t
)brace
id|__siginfo_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|si_float_regs
r_int
r_int
id|si_float_regs
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|si_fsr
r_int
r_int
id|si_fsr
suffix:semicolon
DECL|member|si_fpqdepth
r_int
r_int
id|si_fpqdepth
suffix:semicolon
r_struct
(brace
DECL|member|insn_addr
r_int
r_int
op_star
id|insn_addr
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|si_fpqueue
)brace
id|si_fpqueue
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|__siginfo_fpu_t
)brace
id|__siginfo_fpu_t
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_SIGCONTEXT_H) */
eof
