macro_line|#ifndef _ALPHA_IRQ_H
DECL|macro|_ALPHA_IRQ_H
mdefine_line|#define _ALPHA_IRQ_H
multiline_comment|/*&n; *&t;linux/include/alpha/irq.h&n; *&n; *&t;(C) 1994 Linus Torvalds&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if   defined(CONFIG_ALPHA_GENERIC)
multiline_comment|/* Here NR_IRQS is not exact, but rather an upper bound.  This is used&n;   many places throughout the kernel to size static arrays.  That&squot;s ok,&n;   we&squot;ll use alpha_mv.nr_irqs when we want the real thing.  */
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;64
macro_line|#elif defined(CONFIG_ALPHA_CABRIOLET) || &bslash;&n;      defined(CONFIG_ALPHA_EB66P)     || &bslash;&n;      defined(CONFIG_ALPHA_EB164)     || &bslash;&n;      defined(CONFIG_ALPHA_PC164)     || &bslash;&n;      defined(CONFIG_ALPHA_LX164)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;35
macro_line|#elif defined(CONFIG_ALPHA_EB66)      || &bslash;&n;      defined(CONFIG_ALPHA_EB64P)     || &bslash;&n;      defined(CONFIG_ALPHA_MIKASA)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;32
macro_line|#elif defined(CONFIG_ALPHA_ALCOR)     || &bslash;&n;      defined(CONFIG_ALPHA_XLT)       || &bslash;&n;      defined(CONFIG_ALPHA_MIATA)     || &bslash;&n;      defined(CONFIG_ALPHA_RUFFIAN)   || &bslash;&n;      defined(CONFIG_ALPHA_NORITAKE)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;48
macro_line|#elif defined(CONFIG_ALPHA_SABLE)     || &bslash;&n;      defined(CONFIG_ALPHA_SX164)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;40
macro_line|#elif defined(CONFIG_ALPHA_DP264) || &bslash;&n;      defined(CONFIG_ALPHA_RAWHIDE)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;64
macro_line|#elif defined(CONFIG_ALPHA_TAKARA)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;20
macro_line|#else /* everyone else */
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;16
macro_line|#endif
multiline_comment|/*&n; * PROBE_MASK is the bitset of irqs that we consider for autoprobing.&n; */
multiline_comment|/* The normal mask includes all the IRQs except the timer.  */
DECL|macro|_PROBE_MASK
mdefine_line|#define _PROBE_MASK(nr_irqs)&t;(((1UL &lt;&lt; (nr_irqs &amp; 63)) - 1) &amp; ~1UL)
multiline_comment|/* Mask out unused timer irq 0 and RTC irq 8. */
DECL|macro|P2K_PROBE_MASK
mdefine_line|#define P2K_PROBE_MASK&t;&t;(_PROBE_MASK(16) &amp; ~0x101UL)
multiline_comment|/* Mask out unused timer irq 0, &quot;irqs&quot; 20-30, and the EISA cascade. */
DECL|macro|ALCOR_PROBE_MASK
mdefine_line|#define ALCOR_PROBE_MASK&t;(_PROBE_MASK(48) &amp; ~0xfff000000001UL)
multiline_comment|/* Leave timer irq 0 in the mask.  */
DECL|macro|RUFFIAN_PROBE_MASK
mdefine_line|#define RUFFIAN_PROBE_MASK&t;(_PROBE_MASK(48) | 1UL)
macro_line|#if defined(CONFIG_ALPHA_GENERIC)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;alpha_mv.irq_probe_mask
macro_line|#elif defined(CONFIG_ALPHA_P2K)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;P2K_PROBE_MASK
macro_line|#elif defined(CONFIG_ALPHA_ALCOR) || defined(CONFIG_ALPHA_XLT)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;ALCOR_PROBE_MASK
macro_line|#elif defined(CONFIG_ALPHA_RUFFIAN)
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;RUFFIAN_PROBE_MASK
macro_line|#else
DECL|macro|PROBE_MASK
macro_line|# define PROBE_MASK&t;_PROBE_MASK(NR_IRQS)
macro_line|#endif
DECL|function|irq_cannonicalize
r_static
id|__inline__
r_int
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; * XXX is this true for all Alpha&squot;s?  The old serial driver&n;&t; * did it this way for years without any complaints, so....&n;&t; */
r_return
(paren
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
)paren
suffix:semicolon
)brace
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
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
(paren
op_star
id|perf_irq
)paren
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ALPHA_IRQ_H */
eof
