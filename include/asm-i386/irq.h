macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
multiline_comment|/*&n; * 16 XT IRQ&squot;s, 8 potential APIC interrupt sources.&n; * Right now the APIC is only used for SMP, but this&n; * may change.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 24
DECL|function|irq_cannonicalize
r_static
id|__inline__
r_int
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
)paren
suffix:semicolon
)brace
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
eof
