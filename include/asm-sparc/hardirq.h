multiline_comment|/* hardirq.h: 32-bit Sparc hard IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998-99 Anton Blanchard (anton@progsoc.uts.edu.au)&n; */
macro_line|#ifndef __SPARC_HARDIRQ_H
DECL|macro|__SPARC_HARDIRQ_H
mdefine_line|#define __SPARC_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#ifndef CONFIG_SMP
r_extern
r_int
r_int
id|__local_irq_count
suffix:semicolon
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;__local_irq_count
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()  ((__local_irq_count + __local_bh_count) != 0)
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;((void)(cpu), __local_irq_count == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { (void)(cpu); } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(__local_irq_count++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(__local_irq_count--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier()
DECL|macro|in_irq
mdefine_line|#define in_irq() (__local_irq_count != 0)
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_int
r_int
id|__local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;__local_irq_count[cpu]
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
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ({ int __cpu = smp_processor_id(); &bslash;&n;&t;(local_irq_count(__cpu) + local_bh_count(__cpu) != 0); })
DECL|macro|in_irq
mdefine_line|#define in_irq() ({ int __cpu = smp_processor_id(); &bslash;&n;&t;(local_irq_count(__cpu) != 0); })
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
(paren
r_int
r_char
)paren
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
)paren
(brace
op_increment
id|local_irq_count
c_func
(paren
id|cpu
)paren
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
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|global_irq_count
)paren
op_logical_and
op_logical_neg
id|spin_is_locked
(paren
op_amp
id|global_irq_lock
)paren
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
macro_line|#endif /* __SPARC_HARDIRQ_H */
eof
