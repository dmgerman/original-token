multiline_comment|/* softirq.h: 32-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC_SOFTIRQ_H
DECL|macro|__SPARC_SOFTIRQ_H
mdefine_line|#define __SPARC_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/* The locking mechanism for base handlers, to prevent re-entrancy,&n; * is entirely private to an implementation, it should not be&n; * referenced at all outside of this file.&n; */
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
macro_line|#ifdef __SMP__
r_extern
id|atomic_t
id|__sparc_bh_counter
suffix:semicolon
DECL|macro|start_bh_atomic
mdefine_line|#define start_bh_atomic() &bslash;&n;&t;do { atomic_inc(&amp;__sparc_bh_counter); synchronize_irq(); } while(0)
DECL|macro|end_bh_atomic
mdefine_line|#define end_bh_atomic()&t;&t;atomic_dec(&amp;__sparc_bh_counter)
macro_line|#include &lt;asm/spinlock.h&gt;
r_extern
id|spinlock_t
id|global_bh_lock
suffix:semicolon
DECL|macro|init_bh
mdefine_line|#define init_bh(nr, routine)&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;int ent = nr;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;bh_base[ent] = routine;&t;&t;&t;&t;&bslash;&n;&t;bh_mask_count[ent] = 0;&t;&t;&t;&t;&bslash;&n;&t;bh_mask |= 1 &lt;&lt; ent;&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
DECL|macro|remove_bh
mdefine_line|#define remove_bh(nr)&t;&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;int ent = nr;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;bh_base[ent] = NULL;&t;&t;&t;&t;&bslash;&n;&t;bh_mask &amp;= ~(1 &lt;&lt; ent);&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
DECL|macro|mark_bh
mdefine_line|#define mark_bh(nr)&t;&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;bh_active |= (1 &lt;&lt; nr);&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
DECL|macro|disable_bh
mdefine_line|#define disable_bh(nr)&t;&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;int ent = nr;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;bh_mask &amp;= ~(1 &lt;&lt; ent);&t;&t;&t;&t;&bslash;&n;&t;bh_mask_count[ent]++;&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
DECL|macro|enable_bh
mdefine_line|#define enable_bh(nr)&t;&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;int ent = nr;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;if (!--bh_mask_count[ent])&t;&t;&t;&bslash;&n;&t;&t;bh_mask |= 1 &lt;&lt; ent;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock(cpu)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret = 1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(atomic_add_return(1, &amp;__sparc_bh_counter) != 1) {&t;&bslash;&n;&t;&t;atomic_dec(&amp;__sparc_bh_counter);&t;&t;&bslash;&n;&t;&t;ret = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock(cpu)&t;atomic_dec(&amp;__sparc_bh_counter)
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(mask)&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;bh_active &amp;= ~(mask);&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
macro_line|#else /* !(__SMP__) */
r_extern
r_int
id|__sparc_bh_counter
suffix:semicolon
DECL|macro|start_bh_atomic
mdefine_line|#define start_bh_atomic()&t;do { __sparc_bh_counter++; barrier(); } while(0)
DECL|macro|end_bh_atomic
mdefine_line|#define end_bh_atomic()&t;&t;do { barrier(); __sparc_bh_counter--; } while(0)
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock(cpu) (__sparc_bh_counter ? 0 : (__sparc_bh_counter=1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock(cpu) (__sparc_bh_counter = 0)
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(x)&t;(bh_active &amp;= ~(x))
DECL|macro|synchronize_bh
mdefine_line|#define synchronize_bh()&t;barrier() /* XXX implement SMP version -DaveM */
DECL|macro|init_bh
mdefine_line|#define init_bh(nr, routine)&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&bslash;&n;&t;bh_base[ent] = routine;&t;&bslash;&n;&t;bh_mask_count[ent] = 0;&t;&bslash;&n;&t;bh_mask |= 1 &lt;&lt; ent;&t;&bslash;&n;} while(0)
DECL|macro|remove_bh
mdefine_line|#define remove_bh(nr)&t;&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&bslash;&n;&t;bh_base[ent] = NULL;&t;&bslash;&n;&t;bh_mask &amp;= ~(1 &lt;&lt; ent);&t;&bslash;&n;} while(0)
DECL|macro|mark_bh
mdefine_line|#define mark_bh(nr)&t;&t;(bh_active |= (1 &lt;&lt; (nr)))
DECL|macro|disable_bh
mdefine_line|#define disable_bh(nr)&t;&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&bslash;&n;&t;bh_mask &amp;= ~(1 &lt;&lt; ent);&t;&bslash;&n;&t;bh_mask_count[ent]++;&t;&bslash;&n;} while(0)
DECL|macro|enable_bh
mdefine_line|#define enable_bh(nr)&t;&t;&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&t;&bslash;&n;&t;if (!--bh_mask_count[ent])&t;&bslash;&n;&t;&t;bh_mask |= 1 &lt;&lt; ent;&t;&bslash;&n;} while(0)
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __SPARC_SOFTIRQ_H */
eof
