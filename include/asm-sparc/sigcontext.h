multiline_comment|/* $Id: sigcontext.h,v 1.9 1996/10/27 08:55:42 davem Exp $ */
macro_line|#ifndef _ASMsparc_SIGCONTEXT_H
DECL|macro|_ASMsparc_SIGCONTEXT_H
mdefine_line|#define _ASMsparc_SIGCONTEXT_H
macro_line|#include &lt;asm/ptrace.h&gt;
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
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_ASMsparc_SIGCONTEXT_H) */
eof
