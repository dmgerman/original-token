macro_line|#ifndef __ASM_ARM_IRQ_H
DECL|macro|__ASM_ARM_IRQ_H
mdefine_line|#define __ASM_ARM_IRQ_H
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#ifndef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;128
macro_line|#endif
multiline_comment|/*&n; * Use this value to indicate lack of interrupt&n; * capability&n; */
macro_line|#ifndef NO_IRQ
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;255
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
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
macro_line|#endif
eof
