macro_line|#ifndef __ASM_SH_HARDIRQ_H
DECL|macro|__ASM_SH_HARDIRQ_H
mdefine_line|#define __ASM_SH_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
r_extern
r_int
r_int
id|__local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|__local_bh_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu) (__local_irq_count[(cpu)])
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu) (__local_bh_count[(cpu)])
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ({ int __cpu = smp_processor_id(); &bslash;&n;&t;(__local_irq_count[__cpu] + __local_bh_count[__cpu] != 0); })
DECL|macro|in_irq
mdefine_line|#define in_irq() (__local_irq_count[smp_processor_id()] != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(__local_irq_count[cpu] == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)&t;(__local_irq_count[cpu]++)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)&t;(__local_irq_count[cpu]--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier()
macro_line|#else
macro_line|#error Super-H SMP is not available
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_SH_HARDIRQ_H */
eof
