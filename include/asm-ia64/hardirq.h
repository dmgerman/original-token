macro_line|#ifndef _ASM_IA64_HARDIRQ_H
DECL|macro|_ASM_IA64_HARDIRQ_H
mdefine_line|#define _ASM_IA64_HARDIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
r_typedef
r_struct
(brace
DECL|member|__local_irq_count
r_int
r_int
id|__local_irq_count
suffix:semicolon
DECL|member|__local_bh_count
r_int
r_int
id|__local_bh_count
suffix:semicolon
DECL|member|__nmi_counter
id|atomic_t
id|__nmi_counter
suffix:semicolon
macro_line|# if NR_CPUS &gt; 1
DECL|member|__pad
r_int
r_int
id|__pad
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* this assumes 64-byte cache-lines... */
macro_line|# endif
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
r_extern
id|irq_cpustat_t
id|irq_stat
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * Simple wrappers reducing source bloat&n; */
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;(irq_stat[(cpu)].__local_irq_count)
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;(irq_stat[(cpu)].__local_bh_count)
DECL|macro|nmi_counter
mdefine_line|#define nmi_counter(cpu)&t;(irq_stat[(cpu)].__nmi_counter)
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __cpu = smp_processor_id();&t;&t;&t;&t;&bslash;&n;&t;(local_irq_count(__cpu) + local_bh_count(__cpu)) != 0;&t;&bslash;&n;})
DECL|macro|in_irq
mdefine_line|#define in_irq() (local_irq_count(smp_processor_id()) != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
macro_line|# define hardirq_trylock(cpu)&t;&t;(local_irq_count(cpu) == 0)
DECL|macro|hardirq_endlock
macro_line|# define hardirq_endlock(cpu)&t;&t;do { } while (0)
DECL|macro|irq_enter
macro_line|# define irq_enter(cpu, irq)&t;&t;(++local_irq_count(cpu))
DECL|macro|irq_exit
macro_line|# define irq_exit(cpu, irq)&t;&t;(--local_irq_count(cpu))
DECL|macro|synchronize_irq
macro_line|# define synchronize_irq()&t;&t;barrier()
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_int
r_char
id|global_irq_holder
suffix:semicolon
r_extern
r_int
r_volatile
r_int
id|global_irq_lock
suffix:semicolon
DECL|function|irqs_running
r_static
r_inline
r_int
id|irqs_running
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|local_irq_count
c_func
(paren
id|i
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_irqlock
r_static
r_inline
r_void
id|release_irqlock
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* if we didn&squot;t own the irq lock, just ignore.. */
r_if
c_cond
(paren
id|global_irq_holder
op_eq
id|cpu
)paren
(brace
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|irq_enter
r_static
r_inline
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
(brace
op_increment
id|local_irq_count
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
)brace
DECL|function|irq_exit
r_static
r_inline
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
(brace
op_decrement
id|local_irq_count
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|hardirq_trylock
r_static
r_inline
r_int
id|hardirq_trylock
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
op_logical_neg
id|local_irq_count
c_func
(paren
id|cpu
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* _ASM_IA64_HARDIRQ_H */
eof
