macro_line|#ifndef __ASM_MIPS_HARDIRQ_H
DECL|macro|__ASM_MIPS_HARDIRQ_H
mdefine_line|#define __ASM_MIPS_HARDIRQ_H
macro_line|#include &lt;linux/tasks.h&gt;
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifndef __SMP__
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count[cpu] == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count[cpu]++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count[cpu]--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;do { } while (0)
macro_line|#else
macro_line|#error No habla MIPS SMP
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __ASM_MIPS_HARDIRQ_H */
eof
