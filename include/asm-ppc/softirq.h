multiline_comment|/*&n; * Software interrupts..&n; */
macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/*&n; * The locking mechanism for base handlers, to prevent re-entrancy,&n; * is entirely private to an implementation, it should not be&n; * referenced at all outside of this file.&n; */
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
macro_line|#ifndef __SMP__
r_extern
r_int
id|__ppc_bh_counter
suffix:semicolon
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(x)&t;atomic_clear_mask((x),&amp;bh_active)
DECL|function|init_bh
r_extern
r_inline
r_void
id|init_bh
c_func
(paren
r_int
id|nr
comma
r_void
(paren
op_star
id|routine
)paren
(paren
r_void
)paren
)paren
(brace
id|bh_base
(braket
id|nr
)braket
op_assign
id|routine
suffix:semicolon
id|bh_mask_count
(braket
id|nr
)braket
op_assign
l_int|0
suffix:semicolon
id|bh_mask
op_or_assign
l_int|1
op_lshift
id|nr
suffix:semicolon
)brace
DECL|function|remove_bh
r_extern
r_inline
r_void
id|remove_bh
c_func
(paren
r_int
id|nr
)paren
(brace
id|bh_base
(braket
id|nr
)braket
op_assign
l_int|NULL
suffix:semicolon
id|bh_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|nr
)paren
suffix:semicolon
)brace
DECL|function|mark_bh
r_extern
r_inline
r_void
id|mark_bh
c_func
(paren
r_int
id|nr
)paren
(brace
id|set_bit
c_func
(paren
id|nr
comma
op_amp
id|bh_active
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These use a mask count to correctly handle&n; * nested disable/enable calls&n; */
DECL|function|disable_bh
r_extern
r_inline
r_void
id|disable_bh
c_func
(paren
r_int
id|nr
)paren
(brace
id|bh_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|nr
)paren
suffix:semicolon
id|bh_mask_count
(braket
id|nr
)braket
op_increment
suffix:semicolon
)brace
DECL|function|enable_bh
r_extern
r_inline
r_void
id|enable_bh
c_func
(paren
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|bh_mask_count
(braket
id|nr
)braket
)paren
id|bh_mask
op_or_assign
l_int|1
op_lshift
id|nr
suffix:semicolon
)brace
DECL|function|start_bh_atomic
r_extern
r_inline
r_void
id|start_bh_atomic
c_func
(paren
r_void
)paren
(brace
id|__ppc_bh_counter
op_increment
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|end_bh_atomic
r_extern
r_inline
r_void
id|end_bh_atomic
c_func
(paren
r_void
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|__ppc_bh_counter
op_decrement
suffix:semicolon
)brace
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock()&t;(__ppc_bh_counter? 0: ((__ppc_bh_counter=1),1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock()&t;(__ppc_bh_counter = 0)
macro_line|#else /* __SMP__ */
r_extern
id|atomic_t
id|__ppc_bh_counter
suffix:semicolon
DECL|macro|start_bh_atomic
mdefine_line|#define start_bh_atomic() &bslash;&n;&t;do { atomic_inc(&amp;__ppc_bh_counter); synchronize_irq(); } while(0)
DECL|macro|end_bh_atomic
mdefine_line|#define end_bh_atomic()&t;&t;atomic_dec(&amp;__ppc_bh_counter)
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
mdefine_line|#define softirq_trylock()&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret = 1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(atomic_add_return(1, &amp;__ppc_bh_counter) != 1) {&t;&bslash;&n;&t;&t;atomic_dec(&amp;__ppc_bh_counter);&t;&t;&bslash;&n;&t;&t;ret = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock()&t;atomic_dec(&amp;__ppc_bh_counter)
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(mask)&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irqsave(&amp;global_bh_lock, flags);&t;&bslash;&n;&t;bh_active &amp;= ~(mask);&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irqrestore(&amp;global_bh_lock, flags);&t;&bslash;&n;} while(0)
macro_line|#endif /* __SMP__ */
macro_line|#endif
eof
