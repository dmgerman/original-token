multiline_comment|/*&n; * linux/include/asm-mips/ptrace.h&n; *&n; * machine dependend structs and defines to help the user use&n; * the ptrace system call.&n; */
macro_line|#ifndef __ASM_MIPS_PTRACE_H
DECL|macro|__ASM_MIPS_PTRACE_H
mdefine_line|#define __ASM_MIPS_PTRACE_H
multiline_comment|/*&n; * use ptrace (3 or 6, pid, PT_EXCL, data); to read or write&n; * the processes registers.&n; *&n; * This defines/structures corrospond to the register layout on stack -&n; * if the order here is changed, it needs to be updated in&n; * arch/mips/fork.c:copy_process, asm/mips/signal.c:do_signal,&n; * asm-mips/ptrace.c, include/asm-mips/ptrace.h.&n; */
macro_line|#include &lt;asm/stackframe.h&gt;
multiline_comment|/*&n; * This struct defines the way the registers are stored on the &n; * stack during a system call/exception. As usual the registers&n; * k0/k1 aren&squot;t being saved.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/*&n;&t; * Pad bytes for argument save space on the stack&n;&t; */
DECL|member|pad0
r_int
r_int
id|pad0
(braket
id|FR_REG1
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * saved main processor registers&n;&t; */
DECL|member|reg1
DECL|member|reg2
DECL|member|reg3
DECL|member|reg4
DECL|member|reg5
DECL|member|reg6
DECL|member|reg7
r_int
id|reg1
comma
id|reg2
comma
id|reg3
comma
id|reg4
comma
id|reg5
comma
id|reg6
comma
id|reg7
suffix:semicolon
DECL|member|reg8
DECL|member|reg9
DECL|member|reg10
DECL|member|reg11
DECL|member|reg12
DECL|member|reg13
DECL|member|reg14
DECL|member|reg15
r_int
id|reg8
comma
id|reg9
comma
id|reg10
comma
id|reg11
comma
id|reg12
comma
id|reg13
comma
id|reg14
comma
id|reg15
suffix:semicolon
DECL|member|reg16
DECL|member|reg17
DECL|member|reg18
DECL|member|reg19
DECL|member|reg20
DECL|member|reg21
DECL|member|reg22
DECL|member|reg23
r_int
id|reg16
comma
id|reg17
comma
id|reg18
comma
id|reg19
comma
id|reg20
comma
id|reg21
comma
id|reg22
comma
id|reg23
suffix:semicolon
DECL|member|reg24
DECL|member|reg25
DECL|member|reg28
DECL|member|reg29
DECL|member|reg30
DECL|member|reg31
r_int
id|reg24
comma
id|reg25
comma
id|reg28
comma
id|reg29
comma
id|reg30
comma
id|reg31
suffix:semicolon
multiline_comment|/*&n;&t; * Saved special registers&n;&t; */
DECL|member|lo
r_int
id|lo
suffix:semicolon
DECL|member|hi
r_int
id|hi
suffix:semicolon
multiline_comment|/*&n;&t; * saved cp0 registers&n;&t; */
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
DECL|member|cp0_epc
r_int
r_int
id|cp0_epc
suffix:semicolon
DECL|member|cp0_cause
r_int
r_int
id|cp0_cause
suffix:semicolon
multiline_comment|/*&n;&t; * Some goodies...&n;&t; */
DECL|member|interrupt
r_int
r_int
id|interrupt
suffix:semicolon
DECL|member|orig_reg2
r_int
id|orig_reg2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Does the process account for user or for system time?&n; */
macro_line|#if defined (__R4000__)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!((regs)-&gt;cp0_status &amp; 0x18))
macro_line|#else /* !defined (__R4000__) */
macro_line|#error &quot;#define user_mode(regs) for R3000!&quot;
macro_line|#endif /* !defined (__R4000__) */
macro_line|#endif /* __KERNEL */
multiline_comment|/*&n; * This function computes the interrupt number from the stack frame&n; */
DECL|macro|pt_regs2irq
mdefine_line|#define pt_regs2irq(p) ((int) ((struct pt_regs *)p)-&gt;interrupt)        
macro_line|#endif /* __ASM_MIPS_PTRACE_H */
eof
