macro_line|#ifndef __ASM_SH_IRQ_H
DECL|macro|__ASM_SH_IRQ_H
mdefine_line|#define __ASM_SH_IRQ_H
multiline_comment|/*&n; *&n; * linux/include/asm-sh/irq.h&n; *&n; * Copyright (C) 1999  Niibe Yutaka&n; *&n; */
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;&t;16&t;/* Hard-wired */
DECL|macro|TIMER_IRP_OFFSET
mdefine_line|#define TIMER_IRP_OFFSET&t;12
DECL|macro|TIMER_PRIORITY
mdefine_line|#define TIMER_PRIORITY&t;&t; 1
multiline_comment|/*&n; * 40 = 24+16&n; *&n; * 24 for on chip support modules.&n; * 16 for external interrupts.&n; *&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;40
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
id|disable_irq_nosync
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
multiline_comment|/*&n; * Function for &quot;on chip support modules&quot;.&n; */
r_extern
r_void
id|set_ipr_data
c_func
(paren
r_int
r_int
id|irq
comma
r_int
id|offset
comma
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|make_onChip_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_IRQ_H */
eof
