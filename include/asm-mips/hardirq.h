multiline_comment|/* $Id: hardirq.h,v 1.5 1998/08/29 21:20:21 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_HARDIRQ_H
DECL|macro|__ASM_MIPS_HARDIRQ_H
mdefine_line|#define __ASM_MIPS_HARDIRQ_H
macro_line|#include &lt;linux/threads.h&gt;
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ({ int __cpu = smp_processor_id(); &bslash;&n;&t;(local_irq_count[__cpu] + local_bh_count[__cpu] != 0); })
macro_line|#ifndef __SMP__
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count[cpu] == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count[cpu]++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count[cpu]--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier();
macro_line|#else
macro_line|#error No habla MIPS SMP
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __ASM_MIPS_HARDIRQ_H */
eof
