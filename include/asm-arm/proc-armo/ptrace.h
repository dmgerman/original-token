multiline_comment|/*&n; * linux/include/asm-arm/proc-armo/ptrace.h&n; *&n; * Copyright (C) 1996 Russell King&n; */
macro_line|#ifndef __ASM_PROC_PTRACE_H
DECL|macro|__ASM_PROC_PTRACE_H
mdefine_line|#define __ASM_PROC_PTRACE_H
multiline_comment|/* this struct defines the way the registers are stored on the&n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|uregs
r_int
id|uregs
(braket
l_int|17
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ARM_pc
mdefine_line|#define ARM_pc&t;&t;uregs[15]
DECL|macro|ARM_lr
mdefine_line|#define ARM_lr&t;&t;uregs[14]
DECL|macro|ARM_sp
mdefine_line|#define ARM_sp&t;&t;uregs[13]
DECL|macro|ARM_ip
mdefine_line|#define ARM_ip&t;&t;uregs[12]
DECL|macro|ARM_fp
mdefine_line|#define ARM_fp&t;&t;uregs[11]
DECL|macro|ARM_r10
mdefine_line|#define ARM_r10&t;&t;uregs[10]
DECL|macro|ARM_r9
mdefine_line|#define ARM_r9&t;&t;uregs[9]
DECL|macro|ARM_r8
mdefine_line|#define ARM_r8&t;&t;uregs[8]
DECL|macro|ARM_r7
mdefine_line|#define ARM_r7&t;&t;uregs[7]
DECL|macro|ARM_r6
mdefine_line|#define ARM_r6&t;&t;uregs[6]
DECL|macro|ARM_r5
mdefine_line|#define ARM_r5&t;&t;uregs[5]
DECL|macro|ARM_r4
mdefine_line|#define ARM_r4&t;&t;uregs[4]
DECL|macro|ARM_r3
mdefine_line|#define ARM_r3&t;&t;uregs[3]
DECL|macro|ARM_r2
mdefine_line|#define ARM_r2&t;&t;uregs[2]
DECL|macro|ARM_r1
mdefine_line|#define ARM_r1&t;&t;uregs[1]
DECL|macro|ARM_r0
mdefine_line|#define ARM_r0&t;&t;uregs[0]
DECL|macro|ARM_ORIG_r0
mdefine_line|#define ARM_ORIG_r0&t;uregs[16] /* -1 */
DECL|macro|USR26_MODE
mdefine_line|#define USR26_MODE&t;0x00
DECL|macro|FIQ26_MODE
mdefine_line|#define FIQ26_MODE&t;0x01
DECL|macro|IRQ26_MODE
mdefine_line|#define IRQ26_MODE&t;0x02
DECL|macro|SVC26_MODE
mdefine_line|#define SVC26_MODE&t;0x03
DECL|macro|MODE_MASK
mdefine_line|#define MODE_MASK&t;0x03
DECL|macro|F_BIT
mdefine_line|#define F_BIT&t;&t;(1 &lt;&lt; 26)
DECL|macro|I_BIT
mdefine_line|#define I_BIT&t;&t;(1 &lt;&lt; 27)
DECL|macro|CC_V_BIT
mdefine_line|#define CC_V_BIT&t;(1 &lt;&lt; 28)
DECL|macro|CC_C_BIT
mdefine_line|#define CC_C_BIT&t;(1 &lt;&lt; 29)
DECL|macro|CC_Z_BIT
mdefine_line|#define CC_Z_BIT&t;(1 &lt;&lt; 30)
DECL|macro|CC_N_BIT
mdefine_line|#define CC_N_BIT&t;(1 &lt;&lt; 31)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) &bslash;&n;&t;(((regs)-&gt;ARM_pc &amp; MODE_MASK) == USR26_MODE)
DECL|macro|processor_mode
mdefine_line|#define processor_mode(regs) &bslash;&n;&t;((regs)-&gt;ARM_pc &amp; MODE_MASK)
DECL|macro|interrupts_enabled
mdefine_line|#define interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_pc &amp; I_BIT))
DECL|macro|fast_interrupts_enabled
mdefine_line|#define fast_interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_pc &amp; F_BIT))
DECL|macro|condition_codes
mdefine_line|#define condition_codes(regs) &bslash;&n;&t;((regs)-&gt;ARM_pc &amp; (CC_V_BIT|CC_C_BIT|CC_Z_BIT|CC_N_BIT))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs)&t;((regs)-&gt;ARM_pc &amp; 0x03fffffc)
DECL|macro|pc_pointer
mdefine_line|#define pc_pointer(v)&t;&t;&t;((v) &amp; 0x03fffffc)
macro_line|#endif
eof