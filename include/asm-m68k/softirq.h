macro_line|#ifndef __M68K_SOFTIRQ_H
DECL|macro|__M68K_SOFTIRQ_H
mdefine_line|#define __M68K_SOFTIRQ_H
multiline_comment|/*&n; * Software interrupts.. no SMP here either.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;(local_bh_count(smp_processor_id())++)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;(local_bh_count(smp_processor_id())--)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count != 0)
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock(cpu)  (local_bh_count(cpu) ? 0 : (local_bh_count(cpu)=1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock(cpu)  (local_bh_count(cpu) = 0)
DECL|macro|synchronize_bh
mdefine_line|#define synchronize_bh()&t;barrier()
macro_line|#endif
eof
