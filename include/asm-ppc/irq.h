macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#ifndef CONFIG_8xx
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
id|irq
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
macro_line|#else /* CONFIG_8xx */
multiline_comment|/* The MPC8xx cores have 16 possible interrupts.  There are eight&n; * possible level sensitive interrupts assigned and generated internally&n; * from such devices as CPM, PCMCIA, RTC, PIT, TimeBase and Decrementer.&n; * There are eight external interrupts (IRQs) that can be configured&n; * as either level or edge sensitive. &n; * On the MBX implementation, there is also the possibility of an 8259&n; * through the PCI and PCI-ISA bridges.  All 8259 interrupts appear&n; * on the 8xx as IRQ3, but I may eventually add some of the 8259 code&n; * back into this port to handle that controller.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;16
DECL|macro|SIU_IRQ0
mdefine_line|#define&t;SIU_IRQ0&t;0&t;/* Highest priority */
DECL|macro|SIU_LEVEL0
mdefine_line|#define&t;SIU_LEVEL0&t;1
DECL|macro|SIU_IRQ1
mdefine_line|#define&t;SIU_IRQ1&t;2
DECL|macro|SIU_LEVEL1
mdefine_line|#define&t;SIU_LEVEL1&t;3
DECL|macro|SIU_IRQ2
mdefine_line|#define&t;SIU_IRQ2&t;4
DECL|macro|SIU_LEVEL2
mdefine_line|#define&t;SIU_LEVEL2&t;5
DECL|macro|SIU_IRQ3
mdefine_line|#define&t;SIU_IRQ3&t;6
DECL|macro|SIU_LEVEL3
mdefine_line|#define&t;SIU_LEVEL3&t;7
DECL|macro|SIU_IRQ4
mdefine_line|#define&t;SIU_IRQ4&t;8
DECL|macro|SIU_LEVEL4
mdefine_line|#define&t;SIU_LEVEL4&t;9
DECL|macro|SIU_IRQ5
mdefine_line|#define&t;SIU_IRQ5&t;10
DECL|macro|SIU_LEVEL5
mdefine_line|#define&t;SIU_LEVEL5&t;11
DECL|macro|SIU_IRQ6
mdefine_line|#define&t;SIU_IRQ6&t;12
DECL|macro|SIU_LEVEL6
mdefine_line|#define&t;SIU_LEVEL6&t;13
DECL|macro|SIU_IRQ7
mdefine_line|#define&t;SIU_IRQ7&t;14
DECL|macro|SIU_LEVEL7
mdefine_line|#define&t;SIU_LEVEL7&t;15
multiline_comment|/* The internal interrupts we can configure as we see fit.&n; * My personal preference is CPM at level 2, which puts it above the&n; * MBX PCI/ISA/IDE interrupts.&n; */
DECL|macro|PIT_INTERRUPT
mdefine_line|#define PIT_INTERRUPT&t;SIU_LEVEL0
DECL|macro|CPM_INTERRUPT
mdefine_line|#define CPM_INTERRUPT&t;SIU_LEVEL2
DECL|macro|DEC_INTERRUPT
mdefine_line|#define DEC_INTERRUPT&t;SIU_LEVEL7
multiline_comment|/* Some internal interrupt registers use an 8-bit mask for the interrupt&n; * level instead of a number.&n; */
DECL|macro|mk_int_int_mask
mdefine_line|#define&t;mk_int_int_mask(IL) (1 &lt;&lt; (7 - (IL/2)))
macro_line|#ifdef CONFIG_MBX
multiline_comment|/* These are defined (and fixed) by the MBX hardware implementation.*/
DECL|macro|POWER_FAIL_INT
mdefine_line|#define POWER_FAIL_INT&t;SIU_IRQ0&t;/* Power fail */
DECL|macro|TEMP_HILO_INT
mdefine_line|#define TEMP_HILO_INT&t;SIU_IRQ1&t;/* Temperature sensor */
DECL|macro|QSPAN_INT
mdefine_line|#define QSPAN_INT&t;SIU_IRQ2&t;/* PCI Bridge (DMA CTLR?) */
DECL|macro|ISA_BRIDGE_INT
mdefine_line|#define ISA_BRIDGE_INT&t;SIU_IRQ3&t;/* All those PC things */
DECL|macro|COMM_L_INT
mdefine_line|#define COMM_L_INT&t;SIU_IRQ6&t;/* MBX Comm expansion connector pin */
DECL|macro|STOP_ABRT_INT
mdefine_line|#define STOP_ABRT_INT&t;SIU_IRQ7&t;/* Stop/Abort header pin */
macro_line|#endif /* CONFIG_MBX */
macro_line|#endif /* CONFIG_8xx */
macro_line|#endif
eof
