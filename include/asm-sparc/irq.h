multiline_comment|/* $Id: irq.h,v 1.8 1995/11/25 02:31:54 davem Exp $&n; * irq.h: IRQ registers on the Sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_IRQ_H
DECL|macro|_SPARC_IRQ_H
mdefine_line|#define _SPARC_IRQ_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/system.h&gt;     /* For NCPUS */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS    15
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
id|request_fast_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
)paren
suffix:semicolon
multiline_comment|/* On the sun4m, just like the timers, we have both per-cpu and master&n; * interrupt registers.&n; */
multiline_comment|/* These registers are used for sending/receiving irqs from/to&n; * different cpu&squot;s.   &n; */
DECL|struct|sun4m_intreg_percpu
r_struct
id|sun4m_intreg_percpu
(brace
DECL|member|tbt
r_int
r_int
id|tbt
suffix:semicolon
multiline_comment|/* Interrupts still pending for this cpu. */
multiline_comment|/* These next two registers are WRITE-ONLY and are only&n;&t; * &quot;on bit&quot; sensitive, &quot;off bits&quot; written have NO affect.&n;&t; */
DECL|member|clear
r_int
r_int
id|clear
suffix:semicolon
multiline_comment|/* Clear this cpus irqs here. */
DECL|member|set
r_int
r_int
id|set
suffix:semicolon
multiline_comment|/* Set this cpus irqs here. */
DECL|member|space
r_int
r_char
id|space
(braket
id|PAGE_SIZE
op_minus
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sun4m_intregs
r_struct
id|sun4m_intregs
(brace
DECL|member|cpu_intregs
r_struct
id|sun4m_intreg_percpu
id|cpu_intregs
(braket
id|NCPUS
)braket
suffix:semicolon
DECL|member|tbt
r_int
r_int
id|tbt
suffix:semicolon
multiline_comment|/* IRQ&squot;s that are still pending. */
DECL|member|irqs
r_int
r_int
id|irqs
suffix:semicolon
multiline_comment|/* Master IRQ bits. */
multiline_comment|/* Again, like the above, two these registers are WRITE-ONLY. */
DECL|member|clear
r_int
r_int
id|clear
suffix:semicolon
multiline_comment|/* Clear master IRQ&squot;s by setting bits here. */
DECL|member|set
r_int
r_int
id|set
suffix:semicolon
multiline_comment|/* Set master IRQ&squot;s by setting bits here. */
multiline_comment|/* This register is both READ and WRITE. */
DECL|member|undirected_target
r_int
r_int
id|undirected_target
suffix:semicolon
multiline_comment|/* Which cpu gets undirected irqs. */
)brace
suffix:semicolon
r_extern
r_struct
id|sun4m_intregs
op_star
id|sun4m_interrupts
suffix:semicolon
multiline_comment|/* Bit field defines for the interrupt registers on various&n; * Sparc machines.&n; */
multiline_comment|/* The sun4c interrupt register. */
DECL|macro|SUN4C_INT_ENABLE
mdefine_line|#define SUN4C_INT_ENABLE  0x01     /* Allow interrupts. */
DECL|macro|SUN4C_INT_E14
mdefine_line|#define SUN4C_INT_E14     0x80     /* Enable level 14 IRQ. */
DECL|macro|SUN4C_INT_E10
mdefine_line|#define SUN4C_INT_E10     0x20     /* Enable level 10 IRQ. */
DECL|macro|SUN4C_INT_E8
mdefine_line|#define SUN4C_INT_E8      0x10     /* Enable level 8 IRQ. */
DECL|macro|SUN4C_INT_E6
mdefine_line|#define SUN4C_INT_E6      0x08     /* Enable level 6 IRQ. */
DECL|macro|SUN4C_INT_E4
mdefine_line|#define SUN4C_INT_E4      0x04     /* Enable level 4 IRQ. */
DECL|macro|SUN4C_INT_E1
mdefine_line|#define SUN4C_INT_E1      0x02     /* Enable level 1 IRQ. */
multiline_comment|/* The sun4m interrupt registers.  MUST RESEARCH THESE SOME MORE XXX */
DECL|macro|SUN4M_INT_ENABLE
mdefine_line|#define SUN4M_INT_ENABLE  0x80000000
DECL|macro|SUN4M_INT_E14
mdefine_line|#define SUN4M_INT_E14     0x00000080
DECL|macro|SUN4M_INT_E10
mdefine_line|#define SUN4M_INT_E10     0x00080000
macro_line|#endif
eof
