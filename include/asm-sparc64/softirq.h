multiline_comment|/* softirq.h: 64-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997, 1998 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SOFTIRQ_H
DECL|macro|__SPARC64_SOFTIRQ_H
mdefine_line|#define __SPARC64_SOFTIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for membar() */
macro_line|#ifndef CONFIG_SMP
r_extern
r_int
r_int
id|local_bh_count
suffix:semicolon
macro_line|#else
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count&t;&t;(cpu_data[smp_processor_id()].bh_count)
macro_line|#endif
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;(local_bh_count++)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;(local_bh_count--)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count != 0)
macro_line|#endif /* !(__SPARC64_SOFTIRQ_H) */
eof
