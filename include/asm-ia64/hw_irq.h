macro_line|#ifndef _ASM_IA64_HW_IRQ_H
DECL|macro|_ASM_IA64_HW_IRQ_H
mdefine_line|#define _ASM_IA64_HW_IRQ_H
multiline_comment|/*&n; * Copyright (C) 2000 Hewlett-Packard Co&n; * Copyright (C) 2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * 0 special&n; *&n; * 1,3-14 are reserved from firmware&n; *&n; * 16-255 (vectored external interrupts) are available&n; *&n; * 15 spurious interrupt (see IVR)&n; *&n; * 16 lowest priority, 255 highest priority&n; *&n; * 15 classes of 16 interrupts each.&n; */
DECL|macro|IA64_MIN_VECTORED_IRQ
mdefine_line|#define IA64_MIN_VECTORED_IRQ&t; 16
DECL|macro|IA64_MAX_VECTORED_IRQ
mdefine_line|#define IA64_MAX_VECTORED_IRQ&t;255
DECL|macro|IA64_SPURIOUS_INT
mdefine_line|#define IA64_SPURIOUS_INT&t;0x0f
DECL|macro|IA64_MIN_VECTORED_IRQ
mdefine_line|#define IA64_MIN_VECTORED_IRQ&t; 16
DECL|macro|IA64_MAX_VECTORED_IRQ
mdefine_line|#define IA64_MAX_VECTORED_IRQ&t;255
DECL|macro|PERFMON_IRQ
mdefine_line|#define PERFMON_IRQ&t;&t;0x28&t;/* performanc monitor interrupt vector */
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;&t;0xef&t;/* use highest-prio group 15 interrupt for timer */
DECL|macro|IPI_IRQ
mdefine_line|#define IPI_IRQ&t;&t;&t;0xfe&t;/* inter-processor interrupt vector */
DECL|macro|CMC_IRQ
mdefine_line|#define CMC_IRQ&t;&t;&t;0xff&t;/* correctable machine-check interrupt vector */
multiline_comment|/* IA64 inter-cpu interrupt related definitions */
DECL|macro|IPI_DEFAULT_BASE_ADDR
mdefine_line|#define IPI_DEFAULT_BASE_ADDR&t;0xfee00000
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
r_extern
id|__u8
id|isa_irq_to_vector_map
(braket
l_int|16
)braket
suffix:semicolon
DECL|macro|isa_irq_to_vector
mdefine_line|#define isa_irq_to_vector(x)&t;isa_irq_to_vector_map[(x)]
r_extern
r_int
r_int
id|ipi_base_addr
suffix:semicolon
r_extern
r_struct
id|hw_interrupt_type
id|irq_type_ia64_sapic
suffix:semicolon
multiline_comment|/* CPU-internal interrupt controller */
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
comma
r_int
id|redirect
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|hw_resend_irq
id|hw_resend_irq
(paren
r_struct
id|hw_interrupt_type
op_star
id|h
comma
r_int
r_int
id|vector
)paren
(brace
r_int
id|my_cpu_id
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|my_cpu_id
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|__u64
id|lid
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=cr.lid&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lid
)paren
)paren
suffix:semicolon
id|my_cpu_id
op_assign
(paren
id|lid
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* extract id (ignore eid) */
macro_line|#endif
id|ipi_send
c_func
(paren
id|my_cpu_id
comma
id|vector
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_HW_IRQ_H */
eof
