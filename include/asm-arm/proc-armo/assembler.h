multiline_comment|/*&n; * linux/asm-arm/proc-armo/assembler.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * This file contains arm architecture specific defines&n; * for the different processors&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#error &quot;Only include this from assembly code&quot;
macro_line|#endif
DECL|macro|MODE_USR
mdefine_line|#define MODE_USR&t;USR26_MODE
DECL|macro|MODE_FIQ
mdefine_line|#define MODE_FIQ&t;FIQ26_MODE
DECL|macro|MODE_IRQ
mdefine_line|#define MODE_IRQ&t;IRQ26_MODE
DECL|macro|MODE_SVC
mdefine_line|#define MODE_SVC&t;SVC26_MODE
DECL|macro|DEFAULT_FIQ
mdefine_line|#define DEFAULT_FIQ&t;MODE_FIQ
macro_line|#ifdef __STDC__
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm##cond&t;base,reglist^
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr##s&t;regs
macro_line|#else
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm/**/cond&t;base,reglist^
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr/**/s&t;regs
macro_line|#endif
DECL|macro|MODENOP
mdefine_line|#define MODENOP&bslash;&n;&t;mov&t;r0, r0
DECL|macro|MODE
mdefine_line|#define MODE(savereg,tmpreg,mode) &bslash;&n;&t;mov&t;savereg, pc; &bslash;&n;&t;bic&t;tmpreg, savereg, $0x0c000003; &bslash;&n;&t;orr&t;tmpreg, tmpreg, $mode; &bslash;&n;&t;teqp&t;tmpreg, $0
DECL|macro|RESTOREMODE
mdefine_line|#define RESTOREMODE(savereg) &bslash;&n;&t;teqp&t;savereg, $0
DECL|macro|SAVEIRQS
mdefine_line|#define SAVEIRQS(tmpreg)
DECL|macro|RESTOREIRQS
mdefine_line|#define RESTOREIRQS(tmpreg)
DECL|macro|DISABLEIRQS
mdefine_line|#define DISABLEIRQS(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x08000003
DECL|macro|ENABLEIRQS
mdefine_line|#define ENABLEIRQS(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x00000003
DECL|macro|USERMODE
mdefine_line|#define USERMODE(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x00000000;&bslash;&n;&t;mov&t;r0, r0
DECL|macro|SVCMODE
mdefine_line|#define SVCMODE(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x00000003;&bslash;&n;&t;mov&t;r0, r0
eof
