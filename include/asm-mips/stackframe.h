multiline_comment|/*&n; *  include/asm-mips/stackframe.h&n; *&n; *  Copyright (C) 1994, 1995 Waldorf Electronics&n; *  written by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_STACKFRAME_H
DECL|macro|__ASM_MIPS_STACKFRAME_H
mdefine_line|#define __ASM_MIPS_STACKFRAME_H
multiline_comment|/*&n; * Stack layout for all exceptions:&n; *&n; * ptrace needs to have all regs on the stack.&n; * if the order here is changed, it needs to be &n; * updated in asm/mips/fork.c:copy_process, asm/mips/signal.c:do_signal,&n; * asm-mips/ptrace.c, include/asm-mips/ptrace.h&n; * and asm-mips/ptrace&n; */
multiline_comment|/*&n; * Offsets into the Interrupt stackframe.&n; * The first 20 bytes are reserved for the usual MIPS calling sequence&n; */
DECL|macro|FR_REG1
mdefine_line|#define FR_REG1&t;&t;20
DECL|macro|FR_REG2
mdefine_line|#define FR_REG2&t;&t;((FR_REG1) + 4)
DECL|macro|FR_REG3
mdefine_line|#define FR_REG3&t;&t;((FR_REG2) + 4)
DECL|macro|FR_REG4
mdefine_line|#define FR_REG4&t;&t;((FR_REG3) + 4)
DECL|macro|FR_REG5
mdefine_line|#define FR_REG5&t;&t;((FR_REG4) + 4)
DECL|macro|FR_REG6
mdefine_line|#define FR_REG6&t;&t;((FR_REG5) + 4)
DECL|macro|FR_REG7
mdefine_line|#define FR_REG7&t;&t;((FR_REG6) + 4)
DECL|macro|FR_REG8
mdefine_line|#define FR_REG8&t;&t;((FR_REG7) + 4)
DECL|macro|FR_REG9
mdefine_line|#define FR_REG9&t;&t;((FR_REG8) + 4)
DECL|macro|FR_REG10
mdefine_line|#define FR_REG10&t;((FR_REG9) + 4)
DECL|macro|FR_REG11
mdefine_line|#define FR_REG11&t;((FR_REG10) + 4)
DECL|macro|FR_REG12
mdefine_line|#define FR_REG12&t;((FR_REG11) + 4)
DECL|macro|FR_REG13
mdefine_line|#define FR_REG13&t;((FR_REG12) + 4)
DECL|macro|FR_REG14
mdefine_line|#define FR_REG14&t;((FR_REG13) + 4)
DECL|macro|FR_REG15
mdefine_line|#define FR_REG15&t;((FR_REG14) + 4)
DECL|macro|FR_REG16
mdefine_line|#define FR_REG16&t;((FR_REG15) + 4)
DECL|macro|FR_REG17
mdefine_line|#define FR_REG17&t;((FR_REG16) + 4)
DECL|macro|FR_REG18
mdefine_line|#define FR_REG18&t;((FR_REG17) + 4)
DECL|macro|FR_REG19
mdefine_line|#define FR_REG19&t;((FR_REG18) + 4)
DECL|macro|FR_REG20
mdefine_line|#define FR_REG20&t;((FR_REG19) + 4)
DECL|macro|FR_REG21
mdefine_line|#define FR_REG21&t;((FR_REG20) + 4)
DECL|macro|FR_REG22
mdefine_line|#define FR_REG22&t;((FR_REG21) + 4)
DECL|macro|FR_REG23
mdefine_line|#define FR_REG23&t;((FR_REG22) + 4)
DECL|macro|FR_REG24
mdefine_line|#define FR_REG24&t;((FR_REG23) + 4)
DECL|macro|FR_REG25
mdefine_line|#define FR_REG25&t;((FR_REG24) + 4)
multiline_comment|/*&n; * $26 (k0) and $27 (k1) not saved&n; */
DECL|macro|FR_REG28
mdefine_line|#define FR_REG28&t;((FR_REG25) + 4)
DECL|macro|FR_REG29
mdefine_line|#define FR_REG29&t;((FR_REG28) + 4)
DECL|macro|FR_REG30
mdefine_line|#define FR_REG30&t;((FR_REG29) + 4)
DECL|macro|FR_REG31
mdefine_line|#define FR_REG31&t;((FR_REG30) + 4)
multiline_comment|/*&n; * Saved special registers&n; */
DECL|macro|FR_LO
mdefine_line|#define FR_LO&t;&t;((FR_REG31) + 4)
DECL|macro|FR_HI
mdefine_line|#define FR_HI&t;&t;((FR_LO) + 4)
multiline_comment|/*&n; * Saved cp0 registers follow&n; */
DECL|macro|FR_STATUS
mdefine_line|#define FR_STATUS&t;((FR_HI) + 4)
DECL|macro|FR_EPC
mdefine_line|#define FR_EPC&t;&t;((FR_STATUS) + 4)
DECL|macro|FR_CAUSE
mdefine_line|#define FR_CAUSE&t;((FR_EPC) + 4)
multiline_comment|/*&n; * Some goodies...&n; */
DECL|macro|FR_INTERRUPT
mdefine_line|#define FR_INTERRUPT&t;((FR_CAUSE) + 4)
DECL|macro|FR_ORIG_REG2
mdefine_line|#define FR_ORIG_REG2&t;((FR_INTERRUPT) + 4)
multiline_comment|/*&n; * Size of stack frame&n; */
DECL|macro|FR_SIZE
mdefine_line|#define FR_SIZE&t;&t;((FR_ORIG_REG2) + 4)
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL                                &bslash;&n;&t;&t;mfc0&t;k0,CP0_STATUS;          &bslash;&n;&t;&t;andi&t;k0,0x18;                /* extract KSU bits */ &bslash;&n;&t;&t;beqz&t;k0,1f;                  &bslash;&n;&t;&t;move&t;k1,sp;                  &bslash;&n;&t;&t;/*                              &bslash;&n;&t;&t; * Called from user mode, new stack &bslash;&n;&t;&t; */                             &bslash;&n;&t;&t;lui&t;k1,%hi(_kernelsp);      &bslash;&n;&t;&t;lw&t;k1,%lo(_kernelsp)(k1);  &bslash;&n;1:&t;&t;move&t;k0,sp;                  &bslash;&n;&t;&t;subu&t;sp,k1,FR_SIZE;          &bslash;&n;&t;&t;sw&t;k0,FR_REG29(sp);        &bslash;&n;&t;&t;sw&t;$2,FR_REG2(sp);         &bslash;&n;&t;&t;sw&t;$2,FR_ORIG_REG2(sp);    &bslash;&n;&t;&t;mfc0&t;v0,CP0_STATUS;          &bslash;&n;&t;&t;sw&t;v0,FR_STATUS(sp);       &bslash;&n;&t;&t;mfc0&t;v0,CP0_CAUSE;           &bslash;&n;&t;&t;sw&t;v0,FR_CAUSE(sp);        &bslash;&n;&t;&t;mfc0&t;v0,CP0_EPC;             &bslash;&n;&t;&t;sw&t;v0,FR_EPC(sp);          &bslash;&n;&t;&t;mfhi&t;v0;                     &bslash;&n;&t;&t;sw&t;v0,FR_HI(sp);           &bslash;&n;&t;&t;mflo&t;v0;                     &bslash;&n;&t;&t;sw&t;v0,FR_LO(sp);           &bslash;&n;&t;&t;sw&t;$1,FR_REG1(sp);         &bslash;&n;&t;&t;sw&t;$3,FR_REG3(sp);         &bslash;&n;&t;&t;sw&t;$4,FR_REG4(sp);         &bslash;&n;&t;&t;sw&t;$5,FR_REG5(sp);         &bslash;&n;&t;&t;sw&t;$6,FR_REG6(sp);         &bslash;&n;&t;&t;sw&t;$7,FR_REG7(sp);         &bslash;&n;&t;&t;sw&t;$8,FR_REG8(sp);         &bslash;&n;&t;&t;sw&t;$9,FR_REG9(sp);         &bslash;&n;&t;&t;sw&t;$10,FR_REG10(sp);       &bslash;&n;&t;&t;sw&t;$11,FR_REG11(sp);       &bslash;&n;&t;&t;sw&t;$12,FR_REG12(sp);       &bslash;&n;&t;&t;sw&t;$13,FR_REG13(sp);       &bslash;&n;&t;&t;sw&t;$14,FR_REG14(sp);       &bslash;&n;&t;&t;sw&t;$15,FR_REG15(sp);       &bslash;&n;&t;&t;sw&t;$16,FR_REG16(sp);       &bslash;&n;&t;&t;sw&t;$17,FR_REG17(sp);       &bslash;&n;&t;&t;sw&t;$18,FR_REG18(sp);       &bslash;&n;&t;&t;sw&t;$19,FR_REG19(sp);       &bslash;&n;&t;&t;sw&t;$20,FR_REG20(sp);       &bslash;&n;&t;&t;sw&t;$21,FR_REG21(sp);       &bslash;&n;&t;&t;sw&t;$22,FR_REG22(sp);       &bslash;&n;&t;&t;sw&t;$23,FR_REG23(sp);       &bslash;&n;&t;&t;sw&t;$24,FR_REG24(sp);       &bslash;&n;&t;&t;sw&t;$25,FR_REG25(sp);       &bslash;&n;&t;&t;sw&t;$28,FR_REG28(sp);       &bslash;&n;&t;&t;sw&t;$30,FR_REG30(sp);       &bslash;&n;&t;&t;sw&t;$31,FR_REG31(sp)
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL                             &bslash;&n;&t;&t;lw&t;v1,FR_EPC(sp);          &bslash;&n;&t;&t;lw&t;v0,FR_HI(sp);           &bslash;&n;&t;&t;mtc0&t;v1,CP0_EPC;             &bslash;&n;&t;&t;lw&t;v1,FR_LO(sp);           &bslash;&n;&t;&t;mthi&t;v0;                     &bslash;&n;&t;&t;lw&t;v0,FR_STATUS(sp);       &bslash;&n;&t;&t;mtlo&t;v1;                     &bslash;&n;&t;&t;mtc0&t;v0,CP0_STATUS;          &bslash;&n;&t;&t;lw&t;$31,FR_REG31(sp);       &bslash;&n;&t;&t;lw&t;$30,FR_REG30(sp);       &bslash;&n;&t;&t;lw&t;$28,FR_REG28(sp);       &bslash;&n;&t;&t;lw&t;$25,FR_REG25(sp);       &bslash;&n;&t;&t;lw&t;$24,FR_REG24(sp);       &bslash;&n;&t;&t;lw&t;$23,FR_REG23(sp);       &bslash;&n;&t;&t;lw&t;$22,FR_REG22(sp);       &bslash;&n;&t;&t;lw&t;$21,FR_REG21(sp);       &bslash;&n;&t;&t;lw&t;$20,FR_REG20(sp);       &bslash;&n;&t;&t;lw&t;$19,FR_REG19(sp);       &bslash;&n;&t;&t;lw&t;$18,FR_REG18(sp);       &bslash;&n;&t;&t;lw&t;$17,FR_REG17(sp);       &bslash;&n;&t;&t;lw&t;$16,FR_REG16(sp);       &bslash;&n;&t;&t;lw&t;$15,FR_REG15(sp);       &bslash;&n;&t;&t;lw&t;$14,FR_REG14(sp);       &bslash;&n;&t;&t;lw&t;$13,FR_REG13(sp);       &bslash;&n;&t;&t;lw&t;$12,FR_REG12(sp);       &bslash;&n;&t;&t;lw&t;$11,FR_REG11(sp);       &bslash;&n;&t;&t;lw&t;$10,FR_REG10(sp);       &bslash;&n;&t;&t;lw&t;$9,FR_REG9(sp);         &bslash;&n;&t;&t;lw&t;$8,FR_REG8(sp);         &bslash;&n;&t;&t;lw&t;$7,FR_REG7(sp);         &bslash;&n;&t;&t;lw&t;$6,FR_REG6(sp);         &bslash;&n;&t;&t;lw&t;$5,FR_REG5(sp);         &bslash;&n;&t;&t;lw&t;$4,FR_REG4(sp);         &bslash;&n;&t;&t;lw&t;$3,FR_REG3(sp);         &bslash;&n;&t;&t;lw&t;$2,FR_REG2(sp);         &bslash;&n;&t;&t;lw&t;$1,FR_REG1(sp);         &bslash;&n;&t;&t;lw&t;sp,FR_REG29(sp); /* Deallocate stack */ &bslash;&n;&t;&t;eret
multiline_comment|/*&n; * Move to kernel mode and disable interrupts&n; */
DECL|macro|CLI
mdefine_line|#define CLI                                     &bslash;&n;&t;&t;mfc0&t;k0,CP0_STATUS;          &bslash;&n;&t;&t;ori&t;k0,k0,0x1f;             &bslash;&n;&t;&t;xori&t;k0,k0,0x1f;             &bslash;&n;&t;&t;mtc0&t;k0,CP0_STATUS
multiline_comment|/*&n; * Move to kernel mode and enable interrupts&n; */
DECL|macro|STI
mdefine_line|#define STI                                     &bslash;&n;&t;&t;mfc0&t;k0,CP0_STATUS;          &bslash;&n;&t;&t;ori&t;k0,k0,0x1f;             &bslash;&n;&t;&t;xori&t;k0,k0,0x1e;             &bslash;&n;&t;&t;mtc0&t;k0,CP0_STATUS
macro_line|#endif /* __ASM_MIPS_STACKFRAME_H */
eof
