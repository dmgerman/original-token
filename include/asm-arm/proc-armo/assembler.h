multiline_comment|/*&n; * linux/asm-arm/proc-armo/assembler.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * This file contains arm architecture specific defines&n; * for the different processors&n; */
multiline_comment|/*&n; * LOADREGS: multiple register load (ldm) with pc in register list&n; *&t;&t;(takes account of ARM6 not using ^)&n; *&n; * RETINSTR: return instruction: adds the &squot;s&squot; in at the end of the&n; *&t;&t;instruction if this is not an ARM6&n; *&n; * SAVEIRQS: save IRQ state (not required on ARM2/ARM3 - done&n; *&t;&t;implicitly&n; *&n; * RESTOREIRQS: restore IRQ state (not required on ARM2/ARM3 - done&n; *&t;&t;implicitly with ldm ... ^ or movs.&n; *&n; * These next two need thinking about - can&squot;t easily use stack... (see system.S)&n; * DISABLEIRQS: disable IRQS in SVC mode&n; *&n; * ENABLEIRQS: enable IRQS in SVC mode&n; *&n; * USERMODE: switch to USER mode&n; *&n; * SVCMODE: switch to SVC mode&n; */
DECL|macro|N_BIT
mdefine_line|#define N_BIT&t;(1 &lt;&lt; 31)
DECL|macro|Z_BIT
mdefine_line|#define Z_BIT&t;(1 &lt;&lt; 30)
DECL|macro|C_BIT
mdefine_line|#define C_BIT&t;(1 &lt;&lt; 29)
DECL|macro|V_BIT
mdefine_line|#define V_BIT&t;(1 &lt;&lt; 28)
DECL|macro|PCMASK
mdefine_line|#define PCMASK&t;0xfc000003
macro_line|#ifdef __ASSEMBLER__
DECL|macro|I_BIT
mdefine_line|#define I_BIT&t;(1 &lt;&lt; 27)
DECL|macro|F_BIT
mdefine_line|#define F_BIT&t;(1 &lt;&lt; 26)
DECL|macro|MODE_USR
mdefine_line|#define MODE_USR&t;0
DECL|macro|MODE_FIQ
mdefine_line|#define MODE_FIQ&t;1
DECL|macro|MODE_IRQ
mdefine_line|#define MODE_IRQ&t;2
DECL|macro|MODE_SVC
mdefine_line|#define MODE_SVC&t;3
DECL|macro|DEFAULT_FIQ
mdefine_line|#define DEFAULT_FIQ&t;MODE_FIQ
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm##cond&t;base,reglist^
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr##s&t;regs
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
macro_line|#endif
eof
