macro_line|#ifndef _ALPHA_IRQ_H
DECL|macro|_ALPHA_IRQ_H
mdefine_line|#define _ALPHA_IRQ_H
multiline_comment|/*&n; *&t;linux/include/alpha/irq.h&n; *&n; *&t;(C) 1994 Linus Torvalds&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ALPHA_CABRIOLET) || defined(CONFIG_ALPHA_EB66P) || &bslash;&n;&t;defined(CONFIG_ALPHA_EB164) || defined(CONFIG_ALPHA_PC164) || &bslash;&n;&t;defined(CONFIG_ALPHA_LX164)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;33
macro_line|#elif defined(CONFIG_ALPHA_EB66) || defined(CONFIG_ALPHA_EB64P) || &bslash;&n;&t;defined(CONFIG_ALPHA_MIKASA)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;32
macro_line|#elif defined(CONFIG_ALPHA_ALCOR) || defined(CONFIG_ALPHA_XLT) || &bslash;&n;&t;defined(CONFIG_ALPHA_MIATA) || defined(CONFIG_ALPHA_NORITAKE) || &bslash;&n;&t;defined(CONFIG_ALPHA_RUFFIAN)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;48
macro_line|#elif defined(CONFIG_ALPHA_SABLE) || defined(CONFIG_ALPHA_SX164)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;40
macro_line|#else
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;16
macro_line|#endif
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
