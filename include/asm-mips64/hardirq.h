multiline_comment|/* $Id: hardirq.h,v 1.4 2000/02/23 00:41:38 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_HARDIRQ_H
DECL|macro|_ASM_HARDIRQ_H
mdefine_line|#define _ASM_HARDIRQ_H
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
DECL|macro|in_irq
mdefine_line|#define in_irq() (local_irq_count[smp_processor_id()] != 0)
macro_line|#ifndef __SMP__
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count[cpu] == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu)&t;&t;(local_irq_count[cpu]++)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu)&t;&t;(local_irq_count[cpu]--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier();
macro_line|#else
macro_line|#error No habla MIPS SMP
macro_line|#endif /* __SMP__ */
macro_line|#endif /* _ASM_HARDIRQ_H */
eof
