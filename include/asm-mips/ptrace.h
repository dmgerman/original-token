multiline_comment|/*&n; * linux/include/asm-mips/ptrace.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996 by Ralf Baechle&n; *&n; * Machine dependent structs and defines to help the user use&n; * the ptrace system call.&n; */
macro_line|#ifndef __ASM_MIPS_PTRACE_H
DECL|macro|__ASM_MIPS_PTRACE_H
mdefine_line|#define __ASM_MIPS_PTRACE_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * This struct defines the way the registers are stored on the stack during a&n; * system call/exception. As usual the registers k0/k1 aren&squot;t being saved.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/* Pad bytes for argument save space on the stack. */
DECL|member|pad0
r_int
r_int
id|pad0
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Saved main processor registers. */
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Other saved registers. */
DECL|member|lo
r_int
r_int
id|lo
suffix:semicolon
DECL|member|hi
r_int
r_int
id|hi
suffix:semicolon
DECL|member|orig_reg2
r_int
r_int
id|orig_reg2
suffix:semicolon
DECL|member|orig_reg7
r_int
r_int
id|orig_reg7
suffix:semicolon
multiline_comment|/*&n;&t; * saved cp0 registers&n;&t; */
DECL|member|cp0_epc
r_int
r_int
id|cp0_epc
suffix:semicolon
DECL|member|cp0_badvaddr
r_int
r_int
id|cp0_badvaddr
suffix:semicolon
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
DECL|member|cp0_cause
r_int
r_int
id|cp0_cause
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Does the process account for user or for system time?&n; */
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((regs)-&gt;cp0_status &amp; 0x10)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;cp0_epc)
r_extern
r_void
(paren
op_star
id|show_regs
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_PTRACE_H */
eof
