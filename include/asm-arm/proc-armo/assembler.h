multiline_comment|/*&n; * linux/asm-arm/proc-armo/assembler.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * This file contains arm architecture specific defines&n; * for the different processors&n; */
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
multiline_comment|/*&n; * Save the current IRQ state and disable IRQs&n; * Note that this macro assumes FIQs are enabled, and&n; * that the processor is in SVC mode.&n; */
DECL|variable|oldcpsr
dot
id|macro
id|save_and_disable_irqs
comma
id|oldcpsr
comma
id|temp
DECL|variable|oldcpsr
id|mov
"&bslash;"
id|oldcpsr
comma
id|pc
DECL|variable|temp
DECL|variable|oldcpsr
id|orr
"&bslash;"
id|temp
comma
"&bslash;"
id|oldcpsr
comma
macro_line|#0x08000000
DECL|variable|temp
id|teqp
"&bslash;"
id|temp
comma
macro_line|#0
dot
id|endm
multiline_comment|/*&n; * Restore interrupt state previously stored in&n; * a register&n; * ** Actually do nothing on Arc - hope that the caller uses a MOVS PC soon&n; * after!&n; */
dot
id|macro
id|restore_irqs
comma
id|oldcpsr
"@"
id|This
id|be
id|restore_irqs
dot
id|endm
eof
