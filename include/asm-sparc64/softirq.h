multiline_comment|/* softirq.h: 64-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SOFTIRQ_H
DECL|macro|__SPARC64_SOFTIRQ_H
mdefine_line|#define __SPARC64_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/* The locking mechanism for base handlers, to prevent re-entrancy,&n; * is entirely private to an implementation, it should not be&n; * referenced at all outside of this file.&n; */
r_extern
id|atomic_t
id|__sparc64_bh_counter
suffix:semicolon
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
macro_line|#ifdef __SMP__
macro_line|#error SMP not supported on sparc64 yet
macro_line|#else
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock()&t;(atomic_read(&amp;__sparc64_bh_counter) ? &bslash;&n;&t;&t;&t;&t;0 : &bslash;&n;&t;&t;&t;&t;((atomic_set(&amp;__sparc64_bh_counter,1)),1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock()&t;(atomic_set(&amp;__sparc64_bh_counter, 0))
DECL|macro|clear_active_bhs
mdefine_line|#define clear_active_bhs(x)&t;(bh_active &amp;= ~(x))
DECL|macro|init_bh
mdefine_line|#define init_bh(nr, routine)&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&bslash;&n;&t;bh_base[ent] = routine;&t;&bslash;&n;&t;bh_mask_count[ent] = 0;&t;&bslash;&n;&t;bh_mask |= 1 &lt;&lt; ent;&t;&bslash;&n;} while(0)
DECL|macro|mark_bh
mdefine_line|#define mark_bh(nr)&t;&t;(bh_active |= (1 &lt;&lt; (nr)))
DECL|macro|disable_bh
mdefine_line|#define disable_bh(nr)&t;&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&bslash;&n;&t;bh_mask &amp;= ~(1 &lt;&lt; ent);&t;&bslash;&n;&t;bh_mask_count[ent]++;&t;&bslash;&n;} while(0)
DECL|macro|enable_bh
mdefine_line|#define enable_bh(nr)&t;&t;&t;&bslash;&n;do {&t;int ent = nr;&t;&t;&t;&bslash;&n;&t;if (!--bh_mask_count[ent])&t;&bslash;&n;&t;&t;bh_mask |= 1 &lt;&lt; ent;&t;&bslash;&n;} while(0)
DECL|macro|start_bh_atomic
mdefine_line|#define start_bh_atomic() &bslash;&n;&t;do { atomic_inc(&amp;__sparc64_bh_counter); synchronize_irq(); } while(0)
DECL|macro|end_bh_atomic
mdefine_line|#define end_bh_atomic()&t;  do { atomic_dec(&amp;__sparc64_bh_counter); } while(0)
macro_line|#endif /* !(__SMP__) */
macro_line|#endif /* !(__SPARC64_SOFTIRQ_H) */
eof
