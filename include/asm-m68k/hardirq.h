macro_line|#ifndef __M68K_HARDIRQ_H
DECL|macro|__M68K_HARDIRQ_H
mdefine_line|#define __M68K_HARDIRQ_H
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
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;((cpu)==0)&t;/* always true */
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count[cpu]++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count[cpu]--)
macro_line|#endif
eof
