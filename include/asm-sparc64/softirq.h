multiline_comment|/* softirq.h: 64-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997, 1998 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SOFTIRQ_H
DECL|macro|__SPARC64_SOFTIRQ_H
mdefine_line|#define __SPARC64_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for membar() */
macro_line|#ifndef __SMP__
r_extern
r_int
r_int
id|local_bh_count
suffix:semicolon
macro_line|#else
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count&t;&t;(cpu_data[smp_processor_id()].bh_count)
macro_line|#endif
multiline_comment|/* The locking mechanism for base handlers, to prevent re-entrancy,&n; * is entirely private to an implementation, it should not be&n; * referenced at all outside of this file.&n; */
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(mask)&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&quot;1:&t;ldx&t;[%1], %%g7&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;andn&t;%%g7, %0, %%g5&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;casx&t;[%1], %%g7, %%g5&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;cmp&t;%%g7, %%g5&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne,pn&t;%%xcc, 1b&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t; nop&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no outputs */&t;&t;&t;&bslash;&n;&t;: &quot;HIr&quot; (mask), &quot;r&quot; (&amp;bh_active)&t;&bslash;&n;&t;: &quot;g5&quot;, &quot;g7&quot;, &quot;cc&quot;, &quot;memory&quot;)
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
id|bh_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|nr
)paren
suffix:semicolon
id|membar
c_func
(paren
l_string|&quot;#StoreStore&quot;
)paren
suffix:semicolon
id|bh_base
(braket
id|nr
)braket
op_assign
l_int|NULL
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
macro_line|#ifndef __SMP__
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
op_decrement
suffix:semicolon
)brace
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock(cpu)&t;(local_bh_count ? 0 : (local_bh_count=1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock(cpu)&t;(local_bh_count = 0)
DECL|macro|synchronize_bh
mdefine_line|#define synchronize_bh()&t;barrier()
macro_line|#else /* (__SMP__) */
r_extern
id|atomic_t
id|global_bh_lock
suffix:semicolon
r_extern
id|spinlock_t
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
multiline_comment|/* These are for the IRQs testing the lock */
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
id|spin_trylock
c_func
(paren
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
op_logical_and
id|cpu_data
(braket
id|cpu
)braket
dot
id|bh_count
op_eq
l_int|0
)paren
(brace
op_increment
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|bh_count
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
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
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|bh_count
)paren
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|global_bh_count
)paren
suffix:semicolon
)brace
macro_line|#endif /* (__SMP__) */
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
id|synchronize_bh
c_func
(paren
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
macro_line|#endif /* !(__SPARC64_SOFTIRQ_H) */
eof
