macro_line|#ifndef __ASM_ARM_IRQ_H
DECL|macro|__ASM_ARM_IRQ_H
mdefine_line|#define __ASM_ARM_IRQ_H
macro_line|#include &lt;asm/irq-no.h&gt;
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
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
macro_line|#endif
eof
