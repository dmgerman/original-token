macro_line|#ifndef _ALPHA_SOFTIRQ_H
DECL|macro|_ALPHA_SOFTIRQ_H
mdefine_line|#define _ALPHA_SOFTIRQ_H
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
r_extern
r_int
r_int
id|local_bh_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
DECL|function|clear_active_bhs
r_static
r_inline
r_void
id|clear_active_bhs
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%1&bslash;n&quot;
l_string|&quot;&t;bic %0,%2,%0&bslash;n&quot;
l_string|&quot;&t;stq_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_active
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
id|bh_active
)paren
)paren
suffix:semicolon
)brace
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
id|atomic_set
c_func
(paren
op_amp
id|bh_mask_count
(braket
id|nr
)braket
comma
l_int|0
)paren
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
macro_line|#ifdef __SMP__
multiline_comment|/*&n; * The locking mechanism for base handlers, to prevent re-entrancy,&n; * is entirely private to an implementation, it should not be&n; * referenced at all outside of this file.&n; */
r_extern
id|atomic_t
id|global_bh_lock
suffix:semicolon
r_extern
id|atomic_t
id|global_bh_count
suffix:semicolon
r_extern
r_void
id|synchronize_bh
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|start_bh_atomic
r_static
r_inline
r_void
id|start_bh_atomic
c_func
(paren
r_void
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|global_bh_lock
)paren
suffix:semicolon
id|synchronize_bh
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|end_bh_atomic
r_static
r_inline
r_void
id|end_bh_atomic
c_func
(paren
r_void
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|global_bh_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|function|softirq_trylock
r_static
r_inline
r_int
id|softirq_trylock
c_func
(paren
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_bh_count
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|global_bh_lock
)paren
op_eq
l_int|0
)paren
(brace
op_increment
id|local_bh_count
(braket
id|cpu
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_bh_count
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|softirq_endlock
r_static
r_inline
r_void
id|softirq_endlock
c_func
(paren
r_int
id|cpu
)paren
(brace
id|local_bh_count
(braket
id|cpu
)braket
op_decrement
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_bh_count
)paren
suffix:semicolon
)brace
macro_line|#else
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
id|local_bh_count
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
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
id|local_bh_count
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_decrement
suffix:semicolon
)brace
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock(cpu) &bslash;&n;  (local_bh_count[cpu] ? 0 : (local_bh_count[cpu] = 1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock(cpu) &bslash;&n;  (local_bh_count[cpu] = 0)
DECL|macro|synchronize_bh
mdefine_line|#define synchronize_bh()&t;do { } while (0)
macro_line|#endif&t;/* SMP */
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
id|atomic_inc
c_func
(paren
op_amp
id|bh_mask_count
(braket
id|nr
)braket
)paren
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
id|atomic_dec_and_test
c_func
(paren
op_amp
id|bh_mask_count
(braket
id|nr
)braket
)paren
)paren
id|bh_mask
op_or_assign
l_int|1
op_lshift
id|nr
suffix:semicolon
)brace
macro_line|#endif /* _ALPHA_SOFTIRQ_H */
eof
