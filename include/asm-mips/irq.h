multiline_comment|/*&n; * include/asm-mips/irq.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf GMBH&n; * written by Ralf Baechle&n; *&n; */
macro_line|#ifndef __ASM_MIPS_IRQ_H
DECL|macro|__ASM_MIPS_IRQ_H
mdefine_line|#define __ASM_MIPS_IRQ_H
multiline_comment|/*&n; * Actually this is a lie but we hide the local device&squot;s interrupts ...&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 64
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
r_struct
id|irqaction
suffix:semicolon
r_extern
r_int
id|setup_x86_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|local_irq_count
(braket
)braket
suffix:semicolon
macro_line|#ifdef __SMP__
macro_line|#error Send superfluous SMP boxes to ralf@uni-koblenz.de
macro_line|#else
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)     (++local_irq_count[cpu])
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)      (--local_irq_count[cpu])
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_IRQ_H */
eof
