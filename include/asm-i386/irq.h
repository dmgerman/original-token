macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke &lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 16
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
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
