multiline_comment|/*&n; * Makefile for MIPS Linux main source directory&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_REG_H
DECL|macro|__ASM_MIPS_REG_H
mdefine_line|#define __ASM_MIPS_REG_H
multiline_comment|/*&n; * This defines/structures correspond to the register layout on stack -&n; * if the order here is changed, it needs to be updated in&n; * include/asm-mips/stackframe.h&n; */
DECL|macro|EF_REG1
mdefine_line|#define EF_REG1       5
DECL|macro|EF_REG2
mdefine_line|#define EF_REG2       6
DECL|macro|EF_REG3
mdefine_line|#define EF_REG3       7
DECL|macro|EF_REG4
mdefine_line|#define EF_REG4       8
DECL|macro|EF_REG5
mdefine_line|#define EF_REG5       9
DECL|macro|EF_REG6
mdefine_line|#define EF_REG6       10
DECL|macro|EF_REG7
mdefine_line|#define EF_REG7       11
DECL|macro|EF_REG8
mdefine_line|#define EF_REG8       12
DECL|macro|EF_REG9
mdefine_line|#define EF_REG9       13
DECL|macro|EF_REG10
mdefine_line|#define EF_REG10      14
DECL|macro|EF_REG11
mdefine_line|#define EF_REG11      15
DECL|macro|EF_REG12
mdefine_line|#define EF_REG12      16
DECL|macro|EF_REG13
mdefine_line|#define EF_REG13      17
DECL|macro|EF_REG14
mdefine_line|#define EF_REG14      18
DECL|macro|EF_REG15
mdefine_line|#define EF_REG15      19
DECL|macro|EF_REG16
mdefine_line|#define EF_REG16      20
DECL|macro|EF_REG17
mdefine_line|#define EF_REG17      21
DECL|macro|EF_REG18
mdefine_line|#define EF_REG18      22
DECL|macro|EF_REG19
mdefine_line|#define EF_REG19      23
DECL|macro|EF_REG20
mdefine_line|#define EF_REG20      24
DECL|macro|EF_REG21
mdefine_line|#define EF_REG21      25
DECL|macro|EF_REG22
mdefine_line|#define EF_REG22      26
DECL|macro|EF_REG23
mdefine_line|#define EF_REG23      27
DECL|macro|EF_REG24
mdefine_line|#define EF_REG24      28
DECL|macro|EF_REG25
mdefine_line|#define EF_REG25      29
multiline_comment|/*&n; * k0/k1 unsaved&n; */
DECL|macro|EF_REG28
mdefine_line|#define EF_REG28      30
DECL|macro|EF_REG29
mdefine_line|#define EF_REG29      31
DECL|macro|EF_REG30
mdefine_line|#define EF_REG30      32
DECL|macro|EF_REG31
mdefine_line|#define EF_REG31      33
multiline_comment|/*&n; * Saved special registers&n; */
DECL|macro|EF_LO
mdefine_line|#define EF_LO         34
DECL|macro|EF_HI
mdefine_line|#define EF_HI         35
multiline_comment|/*&n; * saved cp0 registers&n; */
DECL|macro|EF_CP0_STATUS
mdefine_line|#define EF_CP0_STATUS 36
DECL|macro|EF_CP0_EPC
mdefine_line|#define EF_CP0_EPC    37
DECL|macro|EF_CP0_CAUSE
mdefine_line|#define EF_CP0_CAUSE  38
multiline_comment|/*&n; * Some goodies&n; */
DECL|macro|EF_INTERRUPT
mdefine_line|#define EF_INTERRUPT  39
DECL|macro|EF_ORIG_REG2
mdefine_line|#define EF_ORIG_REG2  40
DECL|macro|EF_SIZE
mdefine_line|#define EF_SIZE&t;&t;(41*4)
multiline_comment|/*&n; * Map register number into core file offset.&n; */
DECL|macro|CORE_REG
mdefine_line|#define CORE_REG(reg, ubase) &bslash;&n;&t;(((unsigned long *)((unsigned long)(ubase)))[reg])
macro_line|#endif /* __ASM_MIPS_REG_H */
eof
