macro_line|#ifndef _ASM_IA64_HARDIRQ_H
DECL|macro|_ASM_IA64_HARDIRQ_H
mdefine_line|#define _ASM_IA64_HARDIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|hardirq_no
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __cpu = smp_processor_id();&t;&t;&t;&t;&bslash;&n;&t;(local_irq_count[__cpu] + local_bh_count[__cpu]) != 0;&t;&bslash;&n;})
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
macro_line|# define hardirq_trylock(cpu)&t;&t;(local_irq_count[cpu] == 0)
DECL|macro|hardirq_endlock
macro_line|# define hardirq_endlock(cpu)&t;&t;((void) 0)
DECL|macro|hardirq_enter
macro_line|# define hardirq_enter(cpu, irq)&t;(local_irq_count[cpu]++)
DECL|macro|hardirq_exit
macro_line|# define hardirq_exit(cpu, irq)&t;&t;(local_irq_count[cpu]--)
DECL|macro|synchronize_irq
macro_line|# define synchronize_irq()&t;&t;barrier()
macro_line|#else
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_int
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
id|spin_unlock
c_func
(paren
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|hardirq_enter
r_static
r_inline
r_void
id|hardirq_enter
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
(braket
id|cpu
)braket
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|global_irq_count
)paren
suffix:semicolon
)brace
DECL|function|hardirq_exit
r_static
r_inline
r_void
id|hardirq_exit
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|global_irq_count
)paren
suffix:semicolon
op_decrement
id|local_irq_count
(braket
id|cpu
)braket
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
(braket
id|cpu
)braket
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
mdefine_line|#define hardirq_endlock(cpu)  ((void)0)
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
