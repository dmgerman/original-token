macro_line|#ifndef _ALPHA_HARDIRQ_H
DECL|macro|_ALPHA_HARDIRQ_H
mdefine_line|#define _ALPHA_HARDIRQ_H
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()  (local_irq_count[smp_processor_id()] != 0)
macro_line|#ifndef __SMP__
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;((cpu) == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count[cpu]++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count[cpu]--)
macro_line|#else
macro_line|#error FIXME
macro_line|#endif /* __SMP__ */
macro_line|#endif /* _ALPHA_HARDIRQ_H */
eof
