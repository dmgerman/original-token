multiline_comment|/*&n; * linux/asm-arm/proc-armv/assembler.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * This file contains arm architecture specific defines&n; * for the different processors&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#error &quot;Only include this from assembly code&quot;
macro_line|#endif
DECL|macro|MODE_USR
mdefine_line|#define MODE_USR&t;USR_MODE
DECL|macro|MODE_FIQ
mdefine_line|#define MODE_FIQ&t;FIQ_MODE
DECL|macro|MODE_IRQ
mdefine_line|#define MODE_IRQ&t;IRQ_MODE
DECL|macro|MODE_SVC
mdefine_line|#define MODE_SVC&t;SVC_MODE
DECL|macro|DEFAULT_FIQ
mdefine_line|#define DEFAULT_FIQ&t;MODE_FIQ
multiline_comment|/*&n; * LOADREGS - ldm with PC in register list (eg, ldmfd sp!, {pc})&n; * RETINSTR - return instruction (eg, mov pc, lr)&n; */
macro_line|#ifdef __STDC__
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm##cond&t;base,reglist
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr&t;regs
macro_line|#else
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm/**/cond&t;base,reglist
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr&t;&t;regs
macro_line|#endif
multiline_comment|/*&n; * No nop required after mode change&n; */
DECL|macro|MODENOP
mdefine_line|#define MODENOP
multiline_comment|/*&n; * Change to `mode&squot;&n; */
DECL|macro|MODE
mdefine_line|#define MODE(savereg,tmpreg,mode) &bslash;&n;&t;mrs&t;savereg, cpsr; &bslash;&n;&t;bic&t;tmpreg, savereg, $0x1f; &bslash;&n;&t;orr&t;tmpreg, tmpreg, $mode; &bslash;&n;&t;msr&t;cpsr, tmpreg
multiline_comment|/*&n; * Restore mode&n; */
DECL|macro|RESTOREMODE
mdefine_line|#define RESTOREMODE(savereg) &bslash;&n;&t;msr&t;cpsr, savereg
multiline_comment|/*&n; * save interrupt state (uses stack)&n; */
DECL|macro|SAVEIRQS
mdefine_line|#define SAVEIRQS(tmpreg)&bslash;&n;&t;mrs&t;tmpreg, cpsr; &bslash;&n;&t;str&t;tmpreg, [sp, $-4]!
multiline_comment|/*&n; * restore interrupt state (uses stack)&n; */
DECL|macro|RESTOREIRQS
mdefine_line|#define RESTOREIRQS(tmpreg)&bslash;&n;&t;ldr&t;tmpreg, [sp], $4; &bslash;&n;&t;msr&t;cpsr, tmpreg
multiline_comment|/*&n; * disable IRQs&n; */
DECL|macro|DISABLEIRQS
mdefine_line|#define DISABLEIRQS(tmpreg)&bslash;&n;&t;mrs&t;tmpreg , cpsr; &bslash;&n;&t;orr&t;tmpreg , tmpreg , $I_BIT; &bslash;&n;&t;msr&t;cpsr, tmpreg
multiline_comment|/*&n; * enable IRQs&n; */
DECL|macro|ENABLEIRQS
mdefine_line|#define ENABLEIRQS(tmpreg)&bslash;&n;&t;mrs&t;tmpreg , cpsr; &bslash;&n;&t;bic&t;tmpreg , tmpreg , $I_BIT; &bslash;&n;&t;msr&t;cpsr, tmpreg
eof
