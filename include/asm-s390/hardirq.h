multiline_comment|/*&n; *  include/asm-s390/hardirq.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  Derived from &quot;include/asm-i386/hardirq.h&quot;&n; */
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ((atomic_read(&amp;S390_lowcore.local_irq_count) + atomic_read(&amp;S390_lowcore.local_bh_count)) != 0)
DECL|macro|in_irq
mdefine_line|#define in_irq() (atomic_read(&amp;S390_lowcore.local_irq_count) != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(atomic_read(&amp;S390_lowcore.local_irq_count) == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(atomic_inc(&amp;S390_lowcore.local_irq_count))
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(atomic_dec(&amp;S390_lowcore.local_irq_count))
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;do { } while (0)
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
id|atomic_t
id|global_irq_holder
suffix:semicolon
r_extern
id|atomic_t
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
id|atomic_read
c_func
(paren
op_amp
id|global_irq_holder
)paren
op_eq
id|cpu
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|global_irq_holder
comma
id|NO_PROC_ID
)paren
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
id|atomic_inc
c_func
(paren
op_amp
id|safe_get_cpu_lowcore
c_func
(paren
id|cpu
)paren
dot
id|local_irq_count
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
id|atomic_dec
c_func
(paren
op_amp
id|safe_get_cpu_lowcore
c_func
(paren
id|cpu
)paren
dot
id|local_irq_count
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
id|atomic_read
c_func
(paren
op_amp
id|global_irq_count
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
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
