macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PMAC
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;32
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;16
macro_line|#endif
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
macro_line|#endif
eof
