multiline_comment|/* asmmacro.h: Assembler macros.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ASMMACRO_H
DECL|macro|_SPARC_ASMMACRO_H
mdefine_line|#define _SPARC_ASMMACRO_H
DECL|macro|GET_PROCESSOR_ID
mdefine_line|#define GET_PROCESSOR_ID(reg) &bslash;&n;&t;rd&t;%tbr, %reg; &bslash;&n;&t;srl&t;%reg, 12, %reg; &bslash;&n;&t;and&t;%reg, 3, %reg;
DECL|macro|GET_PROCESSOR_MID
mdefine_line|#define GET_PROCESSOR_MID(reg, tmp) &bslash;&n;&t;rd&t;%tbr, %reg; &bslash;&n;&t;sethi&t;C_LABEL(mid_xlate), %tmp; &bslash;&n;&t;srl&t;%reg, 12, %reg; &bslash;&n;&t;or&t;%tmp, %lo(C_LABEL(mid_xlate)), %tmp; &bslash;&n;&t;and&t;%reg, 3, %reg; &bslash;&n;&t;ldub&t;[%tmp + %reg], %reg;
DECL|macro|GET_PROCESSOR_OFFSET
mdefine_line|#define GET_PROCESSOR_OFFSET(reg) &bslash;&n;&t;GET_PROCESSOR_ID(reg) &bslash;&n;&t;sll&t;%reg, 2, %reg;
DECL|macro|PROCESSOR_OFFSET_TO_ID
mdefine_line|#define PROCESSOR_OFFSET_TO_ID(reg) &bslash;&n;&t;srl&t;%reg, 2, %reg;
DECL|macro|PROCESSOR_ID_TO_OFFSET
mdefine_line|#define PROCESSOR_ID_TO_OFFSET(reg) &bslash;&n;&t;sll&t;%reg, 2, %reg;
multiline_comment|/* All trap entry points _must_ begin with this macro or else you&n; * lose.  It makes sure the kernel has a proper window so that&n; * c-code can be called.&n; */
DECL|macro|SAVE_ALL_HEAD
mdefine_line|#define SAVE_ALL_HEAD &bslash;&n;&t;sethi&t;%hi(trap_setup), %l4; &bslash;&n;&t;jmpl&t;%l4 + %lo(trap_setup), %l6;
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;SAVE_ALL_HEAD &bslash;&n;&t; nop;
multiline_comment|/* All traps low-level code here must end with this macro. */
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL b ret_trap_entry; clr %l6;
macro_line|#endif /* !(_SPARC_ASMMACRO_H) */
eof
