macro_line|#ifndef _ALPHA_IRQ_H
DECL|macro|_ALPHA_IRQ_H
mdefine_line|#define _ALPHA_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm-sparc/irq.h&n; *&n; *&t;Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/system.h&gt;     /* For NCPUS */
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
macro_line|#if 0 /* These aren&squot;t used on the Sparc (yet), but kept for&n;       * future reference, they could come in handy.&n;       */
mdefine_line|#define __STR(x) #x
mdefine_line|#define STR(x) __STR(x)
mdefine_line|#define SAVE_ALL &quot;xx&quot;
mdefine_line|#define SAVE_MOST &quot;yy&quot;
mdefine_line|#define RESTORE_MOST &quot;zz&quot;
mdefine_line|#define ACK_FIRST(mask) &quot;aa&quot;
mdefine_line|#define ACK_SECOND(mask) &quot;dummy&quot;
mdefine_line|#define UNBLK_FIRST(mask) &quot;dummy&quot;
mdefine_line|#define UNBLK_SECOND(mask) &quot;dummy&quot;
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
mdefine_line|#define FAST_IRQ_NAME(nr) IRQ_NAME2(fast_IRQ##nr)
mdefine_line|#define BAD_IRQ_NAME(nr) IRQ_NAME2(bad_IRQ##nr)
mdefine_line|#define BUILD_IRQ(chip,nr,mask) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;asmlinkage void FAST_IRQ_NAME(nr); &bslash;&n;asmlinkage void BAD_IRQ_NAME(nr); &bslash;&n;asm code comes here
macro_line|#endif
macro_line|#endif
eof
