macro_line|#ifndef _ALPHA_IRQ_H
DECL|macro|_ALPHA_IRQ_H
mdefine_line|#define _ALPHA_IRQ_H
multiline_comment|/*&n; *&t;linux/include/alpha/irq.h&n; *&n; *&t;(C) 1994 Linus Torvalds&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if   defined(CONFIG_ALPHA_CABRIOLET) || &bslash;&n;      defined(CONFIG_ALPHA_EB66P)     || &bslash;&n;      defined(CONFIG_ALPHA_EB164)     || &bslash;&n;      defined(CONFIG_ALPHA_PC164)     || &bslash;&n;&t;defined(CONFIG_ALPHA_LX164)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;35
macro_line|#elif defined(CONFIG_ALPHA_EB66)      || &bslash;&n;      defined(CONFIG_ALPHA_EB64P)     || &bslash;&n;&t;defined(CONFIG_ALPHA_MIKASA)
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
macro_line|#endif
eof
