multiline_comment|/*&n; *  include/asm-mips/stackframe.h&n; *&n; *  Copyright (C) 1994, 1995, 1996 by Ralf Baechle and Paul M. Antoine.&n; */
macro_line|#ifndef __ASM_MIPS_STACKFRAME_H
DECL|macro|__ASM_MIPS_STACKFRAME_H
mdefine_line|#define __ASM_MIPS_STACKFRAME_H
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/offset.h&gt;
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL                                         &bslash;&n;&t;&t;mfc0&t;k0, CP0_STATUS;                  &bslash;&n;&t;&t;sll&t;k0, 3;     /* extract cu0 bit */ &bslash;&n;&t;&t;bltz&t;k0, 8f;                          &bslash;&n;&t;&t; move&t;k1, sp;                          &bslash;&n;&t;&t;/* Called from user mode, new stack. */  &bslash;&n;&t;&t;lui&t;k1, %hi(kernelsp);               &bslash;&n;&t;&t;lw&t;k1, %lo(kernelsp)(k1);           &bslash;&n;8:                                                       &bslash;&n;&t;&t;move&t;k0, sp;                          &bslash;&n;&t;&t;subu&t;sp, k1, PT_SIZE;                 &bslash;&n;&t;&t;sw&t;k0, PT_R29(sp);                  &bslash;&n;&t;&t;sw&t;$2, PT_R2(sp);                   &bslash;&n;&t;&t;sw&t;$1, PT_R1(sp);                   &bslash;&n;&t;&t;sw&t;$2, PT_OR2(sp);                  &bslash;&n;&t;&t;sw&t;$0, PT_R0(sp);&t;&t;&t; &bslash;&n;&t;&t;mfc0&t;v0, CP0_STATUS;                  &bslash;&n;&t;&t;sw&t;$3, PT_R3(sp);                   &bslash;&n;&t;&t;sw&t;v0, PT_STATUS(sp);               &bslash;&n;&t;&t;sw&t;$4, PT_R4(sp);                   &bslash;&n;&t;&t;mfc0&t;v0, CP0_CAUSE;                   &bslash;&n;&t;&t;sw&t;$5, PT_R5(sp);                   &bslash;&n;&t;&t;sw&t;v0, PT_CAUSE(sp);                &bslash;&n;&t;&t;sw&t;$6, PT_R6(sp);                   &bslash;&n;&t;&t;mfc0&t;v0, CP0_EPC;                     &bslash;&n;&t;&t;sw&t;$7, PT_R7(sp);                   &bslash;&n;&t;&t;sw&t;v0, PT_EPC(sp);                  &bslash;&n;&t;&t;sw&t;$7, PT_OR7(sp);                  &bslash;&n;&t;&t;sw&t;$8, PT_R8(sp);                   &bslash;&n;&t;&t;mfhi&t;v0;                              &bslash;&n;&t;&t;sw&t;$9, PT_R9(sp);                   &bslash;&n;&t;&t;sw&t;v0, PT_HI(sp);                   &bslash;&n;&t;&t;sw&t;$10,PT_R10(sp);                  &bslash;&n;&t;&t;mflo&t;v0;                              &bslash;&n;&t;&t;sw&t;$11, PT_R11(sp);                 &bslash;&n;&t;&t;sw&t;v0,  PT_LO(sp);                  &bslash;&n;&t;&t;sw&t;$12, PT_R12(sp);                 &bslash;&n;&t;&t;sw&t;$13, PT_R13(sp);                 &bslash;&n;&t;&t;sw&t;$14, PT_R14(sp);                 &bslash;&n;&t;&t;sw&t;$15, PT_R15(sp);                 &bslash;&n;&t;&t;sw&t;$16, PT_R16(sp);                 &bslash;&n;&t;&t;sw&t;$17, PT_R17(sp);                 &bslash;&n;&t;&t;sw&t;$18, PT_R18(sp);                 &bslash;&n;&t;&t;sw&t;$19, PT_R19(sp);                 &bslash;&n;&t;&t;sw&t;$20, PT_R20(sp);                 &bslash;&n;&t;&t;sw&t;$21, PT_R21(sp);                 &bslash;&n;&t;&t;sw&t;$22, PT_R22(sp);                 &bslash;&n;&t;&t;sw&t;$23, PT_R23(sp);                 &bslash;&n;&t;&t;sw&t;$24, PT_R24(sp);                 &bslash;&n;&t;&t;sw&t;$25, PT_R25(sp);                 &bslash;&n;&t;&t;sw&t;$28, PT_R28(sp);                 &bslash;&n;&t;&t;sw&t;$30, PT_R30(sp);                 &bslash;&n;&t;&t;sw&t;$31, PT_R31(sp);
multiline_comment|/*&n; * Note that we restore the IE flags from stack. This means&n; * that a modified IE mask will be nullified.&n; */
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL                                      &bslash;&n;&t;&t;mfc0&t;t0, CP0_STATUS;                  &bslash;&n;&t;&t;ori&t;t0, 0x1f;                        &bslash;&n;&t;&t;xori&t;t0, 0x1f;                        &bslash;&n;&t;&t;mtc0&t;t0, CP0_STATUS;                  &bslash;&n;&t;&t;lw&t;v0, PT_STATUS(sp);               &bslash;&n;&t;&t;lw&t;v1, PT_LO(sp);                   &bslash;&n;&t;&t;mtc0&t;v0, CP0_STATUS;                  &bslash;&n;&t;&t;mtlo&t;v1;                              &bslash;&n;&t;&t;lw&t;v0, PT_HI(sp);                   &bslash;&n;&t;&t;lw&t;v1, PT_EPC(sp);                  &bslash;&n;&t;&t;mthi&t;v0;                              &bslash;&n;&t;&t;mtc0&t;v1, CP0_EPC;                     &bslash;&n;&t;&t;lw&t;$31, PT_R31(sp);                 &bslash;&n;&t;&t;lw&t;$30, PT_R30(sp);                 &bslash;&n;&t;&t;lw&t;$28, PT_R28(sp);                 &bslash;&n;&t;&t;lw&t;$25, PT_R25(sp);                 &bslash;&n;&t;&t;lw&t;$24, PT_R24(sp);                 &bslash;&n;&t;&t;lw&t;$23, PT_R23(sp);                 &bslash;&n;&t;&t;lw&t;$22, PT_R22(sp);                 &bslash;&n;&t;&t;lw&t;$21, PT_R21(sp);                 &bslash;&n;&t;&t;lw&t;$20, PT_R20(sp);                 &bslash;&n;&t;&t;lw&t;$19, PT_R19(sp);                 &bslash;&n;&t;&t;lw&t;$18, PT_R18(sp);                 &bslash;&n;&t;&t;lw&t;$17, PT_R17(sp);                 &bslash;&n;&t;&t;lw&t;$16, PT_R16(sp);                 &bslash;&n;&t;&t;lw&t;$15, PT_R15(sp);                 &bslash;&n;&t;&t;lw&t;$14, PT_R14(sp);                 &bslash;&n;&t;&t;lw&t;$13, PT_R13(sp);                 &bslash;&n;&t;&t;lw&t;$12, PT_R12(sp);                 &bslash;&n;&t;&t;lw&t;$11, PT_R11(sp);                 &bslash;&n;&t;&t;lw&t;$10, PT_R10(sp);                 &bslash;&n;&t;&t;lw&t;$9,  PT_R9(sp);                  &bslash;&n;&t;&t;lw&t;$8,  PT_R8(sp);                  &bslash;&n;&t;&t;lw&t;$7,  PT_R7(sp);                  &bslash;&n;&t;&t;lw&t;$6,  PT_R6(sp);                  &bslash;&n;&t;&t;lw&t;$5,  PT_R5(sp);                  &bslash;&n;&t;&t;lw&t;$4,  PT_R4(sp);                  &bslash;&n;&t;&t;lw&t;$3,  PT_R3(sp);                  &bslash;&n;&t;&t;lw&t;$2,  PT_R2(sp);                  &bslash;&n;&t;&t;lw&t;$1,  PT_R1(sp);                  &bslash;&n;&t;&t;lw&t;sp,  PT_R29(sp);
multiline_comment|/*&n; * Move to kernel mode and disable interrupts.&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; */
DECL|macro|CLI
mdefine_line|#define CLI                                             &bslash;&n;&t;&t;mfc0&t;t0,CP0_STATUS;                  &bslash;&n;&t;&t;li&t;t1,ST0_CU0|0x1f;                &bslash;&n;&t;&t;or&t;t0,t1;                          &bslash;&n;&t;&t;xori&t;t0,0x1f;                        &bslash;&n;&t;&t;mtc0&t;t0,CP0_STATUS
multiline_comment|/*&n; * Move to kernel mode and enable interrupts.&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; *&n; * Note that the mtc0 will be effective on R4000 pipeline stage 7. This&n; * means that another three instructions will be executed with interrupts&n; * disabled.  Arch/mips/mips3/r4xx0.S makes use of this fact.&n; */
DECL|macro|STI
mdefine_line|#define STI                                             &bslash;&n;&t;&t;mfc0&t;t0,CP0_STATUS;                  &bslash;&n;&t;&t;li&t;t1,ST0_CU0|0x1f;                &bslash;&n;&t;&t;or&t;t0,t1;                          &bslash;&n;&t;&t;xori&t;t0,0x1e;                        &bslash;&n;&t;&t;mtc0&t;t0,CP0_STATUS
macro_line|#endif /* __ASM_MIPS_STACKFRAME_H */
eof
