macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
multiline_comment|/*&n; * Software interrupts..&n; */
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(x)&t;atomic_clear_mask((x),&amp;bh_active)
macro_line|#ifdef __SMP__
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|function|softirq_trylock
r_static
r_inline
r_int
id|softirq_trylock
c_func
(paren
r_void
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|intr_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_count
op_ne
l_int|1
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|intr_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock()&t;atomic_dec(&amp;intr_count)
macro_line|#else
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock()&t;(intr_count ? 0 : ((intr_count=1),1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock()&t;(intr_count = 0)
macro_line|#endif
macro_line|#endif
eof
