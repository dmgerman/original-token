macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
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
macro_line|#else /* __SMP__ */
r_extern
r_int
r_char
id|global_irq_holder
suffix:semicolon
r_extern
id|spinlock_t
id|global_irq_lock
suffix:semicolon
r_extern
id|atomic_t
id|global_irq_count
suffix:semicolon
DECL|macro|release_irqlock
mdefine_line|#define release_irqlock(cpu)&t;&t;&t;&t;&bslash;&n;do {&t;if(global_irq_holder == (unsigned char) cpu) {&t;&bslash;&n;&t;&t;global_irq_holder = NO_PROC_ID;&t;&t;&bslash;&n;&t;&t;spin_unlock(&amp;global_irq_lock);&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* Ordering of the counter bumps is _deadly_ important. */
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu) &bslash;&n;&t;do { ++local_irq_count[cpu]; atomic_inc(&amp;global_irq_count); } while(0)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu) &bslash;&n;&t;do { atomic_dec(&amp;global_irq_count); --local_irq_count[cpu]; } while(0)
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;&t;&t;&t;&t;&bslash;&n;({&t;unsigned long flags; int ret = 1;&t;&t;&t;&bslash;&n;&t;__save_flags(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;__cli();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(atomic_add_return(1, &amp;global_irq_count) != 1 ||&t;&bslash;&n;&t;   *(((unsigned char *)(&amp;global_irq_lock)))) {&t;&t;&bslash;&n;&t;&t;atomic_dec(&amp;global_irq_count);&t;&t;&t;&bslash;&n;&t;&t;__restore_flags(flags);&t;&t;&t;&t;&bslash;&n;&t;&t;ret = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;++local_irq_count[cpu];&t;&t;&t;&t;&bslash;&n;&t;&t;__sti();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu) do { __cli(); hardirq_exit(cpu); __sti(); } while(0)
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
