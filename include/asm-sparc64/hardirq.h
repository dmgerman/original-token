multiline_comment|/* hardirq.h: 64-bit Sparc hard IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_HARDIRQ_H
DECL|macro|__SPARC64_HARDIRQ_H
mdefine_line|#define __SPARC64_HARDIRQ_H
macro_line|#include &lt;linux/tasks.h&gt;
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()&t;(local_irq_count[smp_processor_id()] != 0)
DECL|macro|hardirq_depth
mdefine_line|#define hardirq_depth()&t;(local_irq_count[smp_processor_id()])
macro_line|#ifdef __SMP__
macro_line|#error SMP not supported on sparc64
macro_line|#else /* !(__SMP__) */
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(++local_irq_count[cpu], (cpu)==0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;(--local_irq_count[cpu])
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count[cpu]++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count[cpu]--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;do { } while(0)
macro_line|#endif /* __SMP__ */
macro_line|#endif /* !(__SPARC64_HARDIRQ_H) */
eof
