multiline_comment|/* softirq.h: 32-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998-99 Anton Blanchard (anton@progsoc.uts.edu.au)&n; */
macro_line|#ifndef __SPARC_SOFTIRQ_H
DECL|macro|__SPARC_SOFTIRQ_H
mdefine_line|#define __SPARC_SOFTIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;&t;/* For NR_CPUS */
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
r_int
id|__local_bh_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;__local_bh_count[cpu]
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;(local_bh_count(smp_processor_id())++)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;(local_bh_count(smp_processor_id())--)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#else
r_extern
r_int
r_int
id|__local_bh_count
suffix:semicolon
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;__local_bh_count
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;(__local_bh_count++)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;(__local_bh_count--)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (__local_bh_count != 0)
macro_line|#endif&t;/* SMP */
macro_line|#endif&t;/* __SPARC_SOFTIRQ_H */
eof
