macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;asm/machdep.h&gt;&t;&t;/* ppc_md */
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
id|disable_irq_nosync
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
macro_line|#if defined(CONFIG_4xx)
multiline_comment|/*&n; * The PowerPC 403 cores&squot; Asynchronous Interrupt Controller (AIC) has&n; * 32 possible interrupts, a majority of which are not implemented on&n; * all cores. There are six configurable, external interrupt pins and&n; * there are eight internal interrupts for the on-chip serial port&n; * (SPU), DMA controller, and JTAG controller.&n; *&n; * The PowerPC 405 cores&squot; Universal Interrupt Controller (UIC) has 32&n; * possible interrupts as well. There are seven, configurable external&n; * interrupt pins and there are 17 internal interrupts for the on-chip&n; * serial port, DMA controller, on-chip Ethernet controller, PCI, etc.&n; *&n; */
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t;&t;32
DECL|macro|AIC_INT0
mdefine_line|#define&t;AIC_INT0&t;(0)
DECL|macro|AIC_INT4
mdefine_line|#define&t;AIC_INT4&t;(4)
DECL|macro|AIC_INT5
mdefine_line|#define&t;AIC_INT5&t;(5)
DECL|macro|AIC_INT6
mdefine_line|#define&t;AIC_INT6&t;(6)
DECL|macro|AIC_INT7
mdefine_line|#define&t;AIC_INT7&t;(7)
DECL|macro|AIC_INT8
mdefine_line|#define&t;AIC_INT8&t;(8)
DECL|macro|AIC_INT9
mdefine_line|#define&t;AIC_INT9&t;(9)
DECL|macro|AIC_INT10
mdefine_line|#define&t;AIC_INT10&t;(10)
DECL|macro|AIC_INT11
mdefine_line|#define&t;AIC_INT11&t;(11)
DECL|macro|AIC_INT27
mdefine_line|#define&t;AIC_INT27&t;(27)
DECL|macro|AIC_INT28
mdefine_line|#define&t;AIC_INT28&t;(28)
DECL|macro|AIC_INT29
mdefine_line|#define&t;AIC_INT29&t;(29)
DECL|macro|AIC_INT30
mdefine_line|#define&t;AIC_INT30&t;(30)
DECL|macro|AIC_INT31
mdefine_line|#define&t;AIC_INT31&t;(31)
r_static
id|__inline__
r_int
DECL|function|irq_cannonicalize
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_8xx)
multiline_comment|/* The MPC8xx cores have 16 possible interrupts.  There are eight&n; * possible level sensitive interrupts assigned and generated internally&n; * from such devices as CPM, PCMCIA, RTC, PIT, TimeBase and Decrementer.&n; * There are eight external interrupts (IRQs) that can be configured&n; * as either level or edge sensitive. &n; *&n; * The 82xx can have up to 64 interrupts on the internal controller.&n; *&n; * On some implementations, there is also the possibility of an 8259&n; * through the PCI and PCI-ISA bridges.&n; */
macro_line|#ifdef CONFIG_82xx
DECL|macro|NR_SIU_INTS
mdefine_line|#define NR_SIU_INTS&t;64
macro_line|#else
DECL|macro|NR_SIU_INTS
mdefine_line|#define NR_SIU_INTS&t;16
macro_line|#endif
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;(NR_SIU_INTS + NR_8259_INTS)
multiline_comment|/* These values must be zero-based and map 1:1 with the SIU configuration.&n; * They are used throughout the 8xx/82xx I/O subsystem to generate&n; * interrupt masks, flags, and other control patterns.  This is why the&n; * current kernel assumption of the 8259 as the base controller is such&n; * a pain in the butt.&n; */
DECL|macro|SIU_IRQ0
mdefine_line|#define&t;SIU_IRQ0&t;(0)&t;/* Highest priority */
DECL|macro|SIU_LEVEL0
mdefine_line|#define&t;SIU_LEVEL0&t;(1)
DECL|macro|SIU_IRQ1
mdefine_line|#define&t;SIU_IRQ1&t;(2)
DECL|macro|SIU_LEVEL1
mdefine_line|#define&t;SIU_LEVEL1&t;(3)
DECL|macro|SIU_IRQ2
mdefine_line|#define&t;SIU_IRQ2&t;(4)
DECL|macro|SIU_LEVEL2
mdefine_line|#define&t;SIU_LEVEL2&t;(5)
DECL|macro|SIU_IRQ3
mdefine_line|#define&t;SIU_IRQ3&t;(6)
DECL|macro|SIU_LEVEL3
mdefine_line|#define&t;SIU_LEVEL3&t;(7)
DECL|macro|SIU_IRQ4
mdefine_line|#define&t;SIU_IRQ4&t;(8)
DECL|macro|SIU_LEVEL4
mdefine_line|#define&t;SIU_LEVEL4&t;(9)
DECL|macro|SIU_IRQ5
mdefine_line|#define&t;SIU_IRQ5&t;(10)
DECL|macro|SIU_LEVEL5
mdefine_line|#define&t;SIU_LEVEL5&t;(11)
DECL|macro|SIU_IRQ6
mdefine_line|#define&t;SIU_IRQ6&t;(12)
DECL|macro|SIU_LEVEL6
mdefine_line|#define&t;SIU_LEVEL6&t;(13)
DECL|macro|SIU_IRQ7
mdefine_line|#define&t;SIU_IRQ7&t;(14)
DECL|macro|SIU_LEVEL7
mdefine_line|#define&t;SIU_LEVEL7&t;(15)
multiline_comment|/* The internal interrupts we can configure as we see fit.&n; * My personal preference is CPM at level 2, which puts it above the&n; * MBX PCI/ISA/IDE interrupts.&n; */
DECL|macro|PIT_INTERRUPT
mdefine_line|#define PIT_INTERRUPT&t;&t;SIU_LEVEL0
DECL|macro|CPM_INTERRUPT
mdefine_line|#define CPM_INTERRUPT&t;&t;SIU_LEVEL2
DECL|macro|PCMCIA_INTERRUPT
mdefine_line|#define PCMCIA_INTERRUPT&t;SIU_LEVEL6
DECL|macro|DEC_INTERRUPT
mdefine_line|#define DEC_INTERRUPT&t;&t;SIU_LEVEL7
multiline_comment|/* Some internal interrupt registers use an 8-bit mask for the interrupt&n; * level instead of a number.&n; */
DECL|macro|mk_int_int_mask
mdefine_line|#define&t;mk_int_int_mask(IL) (1 &lt;&lt; (7 - (IL/2)))
multiline_comment|/* Now include the board configuration specific associations.&n;*/
macro_line|#include &lt;asm/mpc8xx.h&gt;
multiline_comment|/* always the same on 8xx -- Cort */
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
macro_line|#else
macro_line|#ifdef CONFIG_APUS
DECL|macro|enable_irq
mdefine_line|#define enable_irq m68k_enable_irq
DECL|macro|disable_irq
mdefine_line|#define disable_irq m68k_disable_irq
macro_line|#include &lt;asm-m68k/irq.h&gt;
DECL|macro|enable_irq
macro_line|#undef enable_irq
DECL|macro|disable_irq
macro_line|#undef disable_irq
macro_line|#else /* CONFIG_APUS */
multiline_comment|/*&n; * this is the # irq&squot;s for all ppc arch&squot;s (pmac/chrp/prep)&n; * so it is the max of them all&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;256
macro_line|#endif /* CONFIG_APUS */
DECL|macro|NUM_8259_INTERRUPTS
mdefine_line|#define NUM_8259_INTERRUPTS&t;16
DECL|macro|IRQ_8259_CASCADE
mdefine_line|#define IRQ_8259_CASCADE&t;16
DECL|macro|openpic_to_irq
mdefine_line|#define openpic_to_irq(n)&t;((n)+NUM_8259_INTERRUPTS)
DECL|macro|irq_to_openpic
mdefine_line|#define irq_to_openpic(n)&t;((n)-NUM_8259_INTERRUPTS)
macro_line|#ifndef CONFIG_APUS
multiline_comment|/*&n; * This gets called from serial.c, which is now used on&n; * powermacs as well as prep/chrp boxes.&n; * Prep and chrp both have cascaded 8259 PICs.&n; */
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
r_if
c_cond
(paren
id|ppc_md.irq_cannonicalize
)paren
(brace
r_return
id|ppc_md
dot
id|irq_cannonicalize
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|irq
suffix:semicolon
)brace
)brace
macro_line|#endif /* !CONFIG_APUS */
macro_line|#endif
macro_line|#endif /* _ASM_IRQ_H */
eof
