macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; * this is the # irq&squot;s for all ppc arch&squot;s (pmac/chrp/prep)&n; * so it is the max of them all - which happens to be chrp&n; * -- Cort&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(NUM_8259_INTERRUPTS+NUM_OPENPIC_INTERRUPTS)
DECL|macro|NUM_8259_INTERRUPTS
mdefine_line|#define NUM_8259_INTERRUPTS&t;16
DECL|macro|NUM_OPENPIC_INTERRUPTS
mdefine_line|#define NUM_OPENPIC_INTERRUPTS&t;20
DECL|macro|is_8259_irq
mdefine_line|#define is_8259_irq(n)&t;&t;((n) &lt; NUM_8259_INTERRUPTS)
DECL|macro|openpic_to_irq
mdefine_line|#define openpic_to_irq(n)&t;((n)+NUM_8259_INTERRUPTS)
DECL|macro|irq_to_openpic
mdefine_line|#define irq_to_openpic(n)&t;((n)-NUM_8259_INTERRUPTS)
DECL|macro|IRQ_8259_CASCADE
mdefine_line|#define IRQ_8259_CASCADE&t;NUM_8259_INTERRUPTS
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
