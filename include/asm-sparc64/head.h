multiline_comment|/* $Id: head.h,v 1.2 1996/12/28 18:39:49 davem Exp $ */
macro_line|#ifndef _SPARC64_HEAD_H
DECL|macro|_SPARC64_HEAD_H
mdefine_line|#define _SPARC64_HEAD_H
DECL|macro|BOOT_KERNEL
mdefine_line|#define BOOT_KERNEL b sparc64_boot; nop; nop; nop; nop; nop; nop; nop;
DECL|macro|BTRAP
mdefine_line|#define BTRAP(lvl)
DECL|macro|BTRAPTL1
mdefine_line|#define BTRAPTL1(lvl)
DECL|macro|CLEAN_WINDOW
mdefine_line|#define CLEAN_WINDOW&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clr&t;%o0;&t;clr&t;%o1;&t;clr&t;%o2;&t;clr&t;%o3;&t;&bslash;&n;&t;clr&t;%o4;&t;clr&t;%o5;&t;clr&t;%o6;&t;clr&t;%o7;&t;&bslash;&n;&t;clr&t;%l0;&t;clr&t;%l1;&t;clr&t;%l2;&t;clr&t;%l3;&t;&bslash;&n;&t;clr&t;%l4;&t;clr&t;%l5;&t;clr&t;%l6;&t;clr&t;%l7;&t;&bslash;&n;&t;rdpr %cleanwin, %g1; &t;&t;add %g1, 1, %g1;&t;&t;&bslash;&n;&t;wrpr %g1, 0x0, %cleanwin;&t;retry;&t;&t;&t;&t;&bslash;&n;&t;nop;&t;&t;nop;&t;&t;nop;&t;&t;nop;
DECL|macro|TRAP
mdefine_line|#define TRAP(routine)&t;&t;&t;&bslash;&n;&t;b&t;etrap;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&bslash;&n;&t; add&t;%sp, REGWIN_SZ, %o0;&t;&bslash;&n;&t;b&t;rtrap;&t;&t;&t;&bslash;&n;&t; subcc&t;%g0, %o0, %g0;&t;&t;&bslash;&n;&t;nop;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_IRQ
mdefine_line|#define TRAP_IRQ(routine, level)&t;&bslash;&n;&t;b&t;etrap;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&bslash;&n;&t;add&t;%sp, REGWIN_SZ, %o0;&t;&bslash;&n;&t;call&t;routine;&t;&t;&bslash;&n;&t; mov&t;level, %o1;&t;&t;&bslash;&n;&t;b&t;rtrap;&t;&t;&t;&bslash;&n;&t; subcc&t;%g0, %o0, %g0;&t;&t;&bslash;&n;&t;nop;
macro_line|#endif /* !(_SPARC64_HEAD_H) */
eof
