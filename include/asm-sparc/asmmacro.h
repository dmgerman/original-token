multiline_comment|/* asmmacro.h: Assembler macros.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ASMMACRO_H
DECL|macro|_SPARC_ASMMACRO_H
mdefine_line|#define _SPARC_ASMMACRO_H
multiline_comment|/* #define SMP_DEBUG */
DECL|macro|GET_PROCESSOR_ID
mdefine_line|#define GET_PROCESSOR_ID(reg) &bslash;&n;&t;rd&t;%tbr, %reg; &bslash;&n;&t;srl&t;%reg, 12, %reg; &bslash;&n;&t;and&t;%reg, 3, %reg;
DECL|macro|GET_PROCESSOR_MID
mdefine_line|#define GET_PROCESSOR_MID(reg, tmp) &bslash;&n;&t;GET_PROCESSOR_ID(reg) &bslash;&n;&t;set&t;C_LABEL(mid_xlate), %tmp; &bslash;&n;&t;ldub&t;[%tmp + %reg], %reg;
DECL|macro|GET_PROCESSOR_OFFSET
mdefine_line|#define GET_PROCESSOR_OFFSET(reg) &bslash;&n;&t;rd&t;%tbr, %reg; &bslash;&n;&t;srl&t;%reg, 10, %reg; &bslash;&n;&t;and&t;%reg, 0xc, %reg;
DECL|macro|PROCESSOR_OFFSET_TO_ID
mdefine_line|#define PROCESSOR_OFFSET_TO_ID(reg) &bslash;&n;&t;srl&t;%reg, 2, %reg;
DECL|macro|PROCESSOR_ID_TO_OFFSET
mdefine_line|#define PROCESSOR_ID_TO_OFFSET(reg) &bslash;&n;&t;sll&t;%reg, 2, %reg;
multiline_comment|/* All trap entry points _must_ begin with this macro or else you&n; * lose.  It makes sure the kernel has a proper window so that&n; * c-code can be called.&n; */
macro_line|#ifndef SMP_DEBUG
DECL|macro|SAVE_ALL_HEAD
mdefine_line|#define SAVE_ALL_HEAD &bslash;&n;&t;sethi&t;%hi(trap_setup), %l4; &bslash;&n;&t;jmpl&t;%l4 + %lo(trap_setup), %l6;
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;SAVE_ALL_HEAD &bslash;&n;&t; nop;
macro_line|#else
DECL|macro|SAVE_ALL_HEAD
mdefine_line|#define SAVE_ALL_HEAD &bslash;&n;&t;GET_PROCESSOR_ID(l4); &bslash;&n;&t;set&t;C_LABEL(trap_log), %l5; &bslash;&n;&t;sll&t;%l4, 11, %l6; &bslash;&n;&t;add&t;%l5, %l6, %l5; &bslash;&n;&t;set&t;C_LABEL(trap_log_ent), %l6; &bslash;&n;&t;sll&t;%l4, 2, %l4; &bslash;&n;&t;add&t;%l6, %l4, %l6; &bslash;&n;&t;ld&t;[%l6], %l6; &bslash;&n;&t;sll&t;%l6, 3, %l6; &bslash;&n;&t;st&t;%l1, [%l5 + %l6]; &bslash;&n;&t;add&t;%l5, 4, %l5; &bslash;&n;&t;st&t;%l0, [%l5 + %l6]; &bslash;&n;&t;set&t;C_LABEL(trap_log_ent), %l5; &bslash;&n;&t;add&t;%l5, %l4, %l5; &bslash;&n;&t;srl&t;%l6, 3, %l6; &bslash;&n;&t;add&t;%l6, 1, %l6; &bslash;&n;&t;and&t;%l6, 255, %l6; &bslash;&n;&t;st&t;%l6, [%l5]; &bslash;&n;&t;sethi&t;%hi(trap_setup), %l4; &bslash;&n;&t;jmpl&t;%l4 + %lo(trap_setup), %l6;
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;SAVE_ALL_HEAD &bslash;&n;&t; nop;
macro_line|#endif
multiline_comment|/* All traps low-level code here must end with this macro.&n; * For SMP configurations the ret_trap_entry routine will&n; * have to appropriate code to actually release the kernel&n; * entry lock.&n; */
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL b ret_trap_entry; clr %l6;
macro_line|#ifndef __SMP__
DECL|macro|ENTER_SYSCALL
mdefine_line|#define ENTER_SYSCALL
DECL|macro|LEAVE_SYSCALL
mdefine_line|#define LEAVE_SYSCALL
DECL|macro|ENTER_IRQ
mdefine_line|#define ENTER_IRQ
DECL|macro|LEAVE_IRQ
mdefine_line|#define LEAVE_IRQ
macro_line|#else
DECL|macro|INCREMENT_COUNTER
mdefine_line|#define INCREMENT_COUNTER(symbol, tmp1, tmp2) &bslash;&n;&t;set&t;C_LABEL(symbol), %tmp1; &bslash;&n;&t;ld&t;[%tmp1], %tmp2; &bslash;&n;&t;add&t;%tmp2, 1, %tmp2; &bslash;&n;&t;st&t;%tmp2, [%tmp1];
DECL|macro|DECREMENT_COUNTER
mdefine_line|#define DECREMENT_COUNTER(symbol, tmp1, tmp2) &bslash;&n;&t;set&t;C_LABEL(symbol), %tmp1; &bslash;&n;&t;ld&t;[%tmp1], %tmp2; &bslash;&n;&t;sub&t;%tmp2, 1, %tmp2; &bslash;&n;&t;st&t;%tmp2, [%tmp1];
multiline_comment|/* This is so complicated I suggest you don&squot;t look at it. */
DECL|macro|ENTER_MASK
mdefine_line|#define ENTER_MASK(mask) &bslash;&n;&t;GET_PROCESSOR_OFFSET(l4) &bslash;&n;&t;set&t;C_LABEL(smp_proc_in_lock), %l5; &bslash;&n;&t;ld&t;[%l5 + %l4], %l6; &bslash;&n;&t;or&t;%l6, mask, %l6; &bslash;&n;&t;st&t;%l6, [%l5 + %l4]; &bslash;&n;1: &bslash;&n;&t;set&t;C_LABEL(kernel_flag), %l5; &bslash;&n;&t;ldstub&t;[%l5], %l6; &bslash;&n;&t;cmp&t;%l6, 0; &bslash;&n;&t;be&t;3f; &bslash;&n;&t; nop; &bslash;&n;&t;set&t;C_LABEL(active_kernel_processor), %l5; &bslash;&n;&t;GET_PROCESSOR_ID(l4) &bslash;&n;&t;ldub&t;[%l5], %l6; &bslash;&n;&t;cmp&t;%l6, %l4; &bslash;&n;&t;be&t;4f; &bslash;&n;&t; nop; &bslash;&n;2: &bslash;&n;&t;GET_PROCESSOR_MID(l4, l5) &bslash;&n;&t;set&t;C_LABEL(sun4m_interrupts), %l5; &bslash;&n;&t;ld&t;[%l5], %l5; &bslash;&n;&t;sll&t;%l4, 12, %l4; &bslash;&n;&t;add&t;%l5, %l4, %l5; &bslash;&n;&t;ld&t;[%l5], %l4; &bslash;&n;&t;sethi&t;%hi(0x80000000), %l6; &bslash;&n;&t;andcc&t;%l6, %l4, %g0; &bslash;&n;&t;be&t;5f; &bslash;&n;&t; nop; &bslash;&n;&t;st&t;%l6, [%l5 + 4]; &bslash;&n;&t;nop; nop; nop; &bslash;&n;&t;ld&t;[%l5], %g0; &bslash;&n;&t;nop; nop; nop; &bslash;&n;&t;or&t;%l0, PSR_PIL, %l4; &bslash;&n;&t;wr&t;%l4, 0x0, %psr; &bslash;&n;&t;nop; nop; nop; &bslash;&n;&t;wr&t;%l4, PSR_ET, %psr; &bslash;&n;&t;nop; nop; nop; &bslash;&n;&t;call&t;C_LABEL(smp_message_irq); &bslash;&n;       &t; nop; &bslash;&n;&t;wr&t;%l0, 0x0, %psr; &bslash;&n;&t;nop; nop; nop; &bslash;&n;5: &bslash;&n;&t;set&t;C_LABEL(kernel_flag), %l5; &bslash;&n;&t;ldub&t;[%l5], %l6; &bslash;&n;&t;cmp&t;%l6, 0; &bslash;&n;&t;bne&t;2b; &bslash;&n;&t; nop; &bslash;&n;&t;b&t;1b; &bslash;&n;&t; nop; &bslash;&n;3: &bslash;&n;&t;GET_PROCESSOR_ID(l4) &bslash;&n;&t;set&t;C_LABEL(active_kernel_processor), %l5; &bslash;&n;&t;stb&t;%l4, [%l5]; &bslash;&n;&t;GET_PROCESSOR_MID(l4, l5) &bslash;&n;&t;set&t;C_LABEL(irq_rcvreg), %l5; &bslash;&n;&t;ld&t;[%l5], %l5; &bslash;&n;&t;st&t;%l4, [%l5]; &bslash;&n;4: &bslash;&n;
DECL|macro|ENTER_SYSCALL
mdefine_line|#define ENTER_SYSCALL &bslash;&n;&t;ENTER_MASK(SMP_FROM_SYSCALL) &bslash;&n;&t;INCREMENT_COUNTER(kernel_counter, l6, l5) &bslash;&n;&t;INCREMENT_COUNTER(syscall_count, l6, l5)
DECL|macro|ENTER_IRQ
mdefine_line|#define ENTER_IRQ &bslash;&n;&t;ENTER_MASK(SMP_FROM_INT) &bslash;&n;&t;INCREMENT_COUNTER(kernel_counter, l6, l5)
DECL|macro|LEAVE_MASK
mdefine_line|#define LEAVE_MASK(mask) &bslash;&n;&t;GET_PROCESSOR_OFFSET(l4) &bslash;&n;&t;set&t;C_LABEL(smp_proc_in_lock), %l5; &bslash;&n;&t;ld&t;[%l5 + %l4], %l6; &bslash;&n;&t;andn&t;%l6, mask, %l6; &bslash;&n;&t;st&t;%l6, [%l5 + %l4];
DECL|macro|LEAVE_SYSCALL
mdefine_line|#define LEAVE_SYSCALL &bslash;&n;&t;LEAVE_MASK(SMP_FROM_SYSCALL) &bslash;&n;&t;DECREMENT_COUNTER(syscall_count, l6, l5) &bslash;&n;&t;set&t;C_LABEL(kernel_counter), %l6; &bslash;&n;&t;ld&t;[%l6], %l5; &bslash;&n;&t;subcc&t;%l5, 1, %l5; &bslash;&n;&t;st&t;%l5, [%l6]; &bslash;&n;&t;bne&t;1f; &bslash;&n;&t; nop; &bslash;&n;&t;set&t;C_LABEL(active_kernel_processor), %l6; &bslash;&n;&t;mov&t;NO_PROC_ID, %l5; &bslash;&n;&t;stb&t;%l5, [%l6]; &bslash;&n;&t;set&t;C_LABEL(kernel_flag), %l6; &bslash;&n;&t;stb&t;%g0, [%l6]; &bslash;&n;1:
DECL|macro|LEAVE_IRQ
mdefine_line|#define LEAVE_IRQ &bslash;&n;&t;LEAVE_MASK(SMP_FROM_INT) &bslash;&n;&t;INCREMENT_COUNTER(syscall_count, l6, l5)
DECL|macro|RESTORE_ALL_FASTIRQ
mdefine_line|#define RESTORE_ALL_FASTIRQ b,a&t;ret_irq_entry;
macro_line|#endif /* !(__SMP__) */
macro_line|#endif /* !(_SPARC_ASMMACRO_H) */
eof
