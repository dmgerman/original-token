macro_line|#ifndef _ALPHA_SOFTIRQ_H
DECL|macro|_ALPHA_SOFTIRQ_H
mdefine_line|#define _ALPHA_SOFTIRQ_H
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#ifndef __SMP__
r_extern
r_int
id|__local_bh_count
suffix:semicolon
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;((void)(cpu), __local_bh_count)
macro_line|#else
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;(cpu_data[cpu].bh_count)
macro_line|#endif
DECL|function|cpu_bh_disable
r_extern
r_inline
r_void
id|cpu_bh_disable
c_func
(paren
r_int
id|cpu
)paren
(brace
id|local_bh_count
c_func
(paren
id|cpu
)paren
op_increment
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cpu_bh_enable
r_extern
r_inline
r_void
id|cpu_bh_enable
c_func
(paren
r_int
id|cpu
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|local_bh_count
c_func
(paren
id|cpu
)paren
op_decrement
suffix:semicolon
)brace
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;cpu_bh_enable(smp_processor_id())
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable(smp_processor_id())
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif /* _ALPHA_SOFTIRQ_H */
eof
