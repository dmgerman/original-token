macro_line|#ifndef __M68K_HARDIRQ_H
DECL|macro|__M68K_HARDIRQ_H
mdefine_line|#define __M68K_HARDIRQ_H
macro_line|#include &lt;linux/threads.h&gt;
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() (local_irq_count[smp_processor_id()] + local_bh_count[smp_processor_id()] != 0)
DECL|macro|in_irq
mdefine_line|#define in_irq() (local_irq_count[smp_processor_id()] != 0)
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count[cpu] == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu)&t;&t;(local_irq_count[cpu]++)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu)&t;&t;(local_irq_count[cpu]--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier()
macro_line|#endif
eof
