macro_line|#ifndef _ASM_IA64_IRQ_H
DECL|macro|_ASM_IA64_IRQ_H
mdefine_line|#define _ASM_IA64_IRQ_H
multiline_comment|/*&n; * Copyright (C) 1999-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1998 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * 11/24/98&t;S.Eranian &t;updated TIMER_IRQ and irq_cannonicalize&n; * 01/20/99&t;S.Eranian&t;added keyboard interrupt&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;256
DECL|macro|NR_ISA_IRQS
mdefine_line|#define NR_ISA_IRQS&t; 16
multiline_comment|/*&n; * 0 special&n; *&n; * 1,3-14 are reserved from firmware&n; *&n; * 16-255 (vectored external interrupts) are available&n; *&n; * 15 spurious interrupt (see IVR)&n; *&n; * 16 lowest priority, 255 highest priority&n; *&n; * 15 classes of 16 interrupts each.&n; */
DECL|macro|IA64_MIN_VECTORED_IRQ
mdefine_line|#define IA64_MIN_VECTORED_IRQ&t; 16
DECL|macro|IA64_MAX_VECTORED_IRQ
mdefine_line|#define IA64_MAX_VECTORED_IRQ&t;255
DECL|macro|IA64_SPURIOUS_INT
mdefine_line|#define IA64_SPURIOUS_INT&t;0x0f
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;&t;0xef&t;/* use highest-prio group 15 interrupt for timer */
DECL|macro|IPI_IRQ
mdefine_line|#define IPI_IRQ&t;&t;&t;0xfe&t;/* inter-processor interrupt vector */
DECL|macro|PERFMON_IRQ
mdefine_line|#define PERFMON_IRQ&t;&t;0x28&t;/* performanc monitor interrupt vector */
DECL|macro|IA64_MIN_VECTORED_IRQ
mdefine_line|#define IA64_MIN_VECTORED_IRQ&t; 16
DECL|macro|IA64_MAX_VECTORED_IRQ
mdefine_line|#define IA64_MAX_VECTORED_IRQ&t;255
r_extern
id|__u8
id|irq_to_vector_map
(braket
id|IA64_MIN_VECTORED_IRQ
)braket
suffix:semicolon
DECL|macro|map_legacy_irq
mdefine_line|#define map_legacy_irq(x) (((x) &lt; IA64_MIN_VECTORED_IRQ) ? irq_to_vector_map[(x)] : (x))
DECL|macro|IRQ_INPROGRESS
mdefine_line|#define IRQ_INPROGRESS&t;(1 &lt;&lt; 0)&t;/* irq handler active */
DECL|macro|IRQ_ENABLED
mdefine_line|#define IRQ_ENABLED&t;(1 &lt;&lt; 1)&t;/* irq enabled */
DECL|macro|IRQ_PENDING
mdefine_line|#define IRQ_PENDING&t;(1 &lt;&lt; 2)&t;/* irq pending */
DECL|macro|IRQ_REPLAY
mdefine_line|#define IRQ_REPLAY&t;(1 &lt;&lt; 3)&t;/* irq has been replayed but not acked yet */
DECL|macro|IRQ_AUTODETECT
mdefine_line|#define IRQ_AUTODETECT&t;(1 &lt;&lt; 4)&t;/* irq is being autodetected */
DECL|macro|IRQ_WAITING
mdefine_line|#define IRQ_WAITING&t;(1 &lt;&lt; 5)&t;/* used for autodetection: irq not yet seen yet */
DECL|struct|hw_interrupt_type
r_struct
id|hw_interrupt_type
(brace
DECL|member|typename
r_const
r_char
op_star
r_typename
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|member|startup
r_void
(paren
op_star
id|startup
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|handle
r_int
(paren
op_star
id|handle
)paren
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|enable
r_void
(paren
op_star
id|enable
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|disable
r_void
(paren
op_star
id|disable
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|hw_interrupt_type
id|irq_type_default
suffix:semicolon
multiline_comment|/* dummy interrupt controller */
r_extern
r_struct
id|hw_interrupt_type
id|irq_type_ia64_internal
suffix:semicolon
multiline_comment|/* CPU-internal interrupt controller */
DECL|struct|irq_desc
r_struct
id|irq_desc
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* type of interrupt (level vs. edge triggered) */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* see above */
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
multiline_comment|/* disable depth for nested irq disables */
DECL|member|handler
r_struct
id|hw_interrupt_type
op_star
id|handler
suffix:semicolon
DECL|member|action
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
multiline_comment|/* irq action list */
)brace
suffix:semicolon
r_extern
r_struct
id|irq_desc
id|irq_desc
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_extern
id|spinlock_t
id|irq_controller_lock
suffix:semicolon
multiline_comment|/* IA64 inter-cpu interrupt related definitions */
multiline_comment|/* Delivery modes for inter-cpu interrupts */
r_enum
(brace
DECL|enumerator|IA64_IPI_DM_INT
id|IA64_IPI_DM_INT
op_assign
l_int|0x0
comma
multiline_comment|/* pend an external interrupt */
DECL|enumerator|IA64_IPI_DM_PMI
id|IA64_IPI_DM_PMI
op_assign
l_int|0x2
comma
multiline_comment|/* pend a PMI */
DECL|enumerator|IA64_IPI_DM_NMI
id|IA64_IPI_DM_NMI
op_assign
l_int|0x4
comma
multiline_comment|/* pend an NMI (vector 2) */
DECL|enumerator|IA64_IPI_DM_INIT
id|IA64_IPI_DM_INIT
op_assign
l_int|0x5
comma
multiline_comment|/* pend an INIT interrupt */
DECL|enumerator|IA64_IPI_DM_EXTINT
id|IA64_IPI_DM_EXTINT
op_assign
l_int|0x7
comma
multiline_comment|/* pend an 8259-compatible interrupt. */
)brace
suffix:semicolon
DECL|macro|IA64_BUS_ID
mdefine_line|#define IA64_BUS_ID(cpu)        (cpu &gt;&gt; 8)
DECL|macro|IA64_LOCAL_ID
mdefine_line|#define IA64_LOCAL_ID(cpu)      (cpu &amp; 0xff)
r_static
id|__inline__
r_int
DECL|function|irq_cannonicalize
id|irq_cannonicalize
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; * We do the legacy thing here of pretending that irqs &lt; 16&n;&t; * are 8259 irqs.&n;&t; */
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
r_int
id|invoke_irq_handlers
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|irqaction
op_star
id|action
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ipi_send
(paren
r_int
id|cpu
comma
r_int
id|vector
comma
r_int
id|delivery_mode
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|irq_enter
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|irq_exit
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|handle_IPI
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
DECL|macro|irq_enter
macro_line|# define irq_enter(cpu, irq)&t;(++local_irq_count[cpu])
DECL|macro|irq_exit
macro_line|# define irq_exit(cpu, irq)&t;(--local_irq_count[cpu])
macro_line|#endif
macro_line|#endif /* _ASM_IA64_IRQ_H */
eof
