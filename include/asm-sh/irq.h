macro_line|#ifndef __ASM_SH_IRQ_H
DECL|macro|__ASM_SH_IRQ_H
mdefine_line|#define __ASM_SH_IRQ_H
multiline_comment|/*&n; *&n; * linux/include/asm-sh/irq.h&n; *&n; * Copyright (C) 1999  Niibe Yutaka &amp; Takeshi Yaegashi&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(__sh3__)
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA  &t;0xfffffee2UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB  &t;0xfffffee4UL
macro_line|#elif defined(__SH4__)
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA&t;0xffd00004UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB&t;0xffd00008UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC&t;0xffd0000cUL
macro_line|#endif
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;16
DECL|macro|TIMER_IPR_ADDR
mdefine_line|#define TIMER_IPR_ADDR&t;INTC_IPRA
DECL|macro|TIMER_IPR_POS
mdefine_line|#define TIMER_IPR_POS&t; 3
DECL|macro|TIMER_PRIORITY
mdefine_line|#define TIMER_PRIORITY&t; 2
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;22
DECL|macro|RTC_IPR_ADDR
mdefine_line|#define RTC_IPR_ADDR&t;INTC_IPRA
DECL|macro|RTC_IPR_POS
mdefine_line|#define RTC_IPR_POS&t; 0
DECL|macro|RTC_PRIORITY
mdefine_line|#define RTC_PRIORITY&t;TIMER_PRIORITY
macro_line|#if defined(__SH4__)
multiline_comment|/*&n; * 48 = 32+16&n; *&n; * 32 for on chip support modules.&n; * 16 for external interrupts.&n; *&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;48
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7708)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 32
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7709)
macro_line|#ifdef CONFIG_HD64461
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 80&t;&t;/* HD64461_IRQBASE+16, see hd64461.h */
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 61
macro_line|#endif
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
r_int
id|addr
comma
r_int
id|pos
comma
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|make_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|make_imask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|INTC_IRR0
mdefine_line|#define INTC_IRR0&t;0xa4000004UL
DECL|macro|INTC_IRR1
mdefine_line|#define INTC_IRR1&t;0xa4000006UL
DECL|macro|INTC_IRR2
mdefine_line|#define INTC_IRR2&t;0xa4000008UL
DECL|macro|INTC_ICR0
mdefine_line|#define INTC_ICR0  &t;0xfffffee0UL
DECL|macro|INTC_ICR1
mdefine_line|#define INTC_ICR1  &t;0xa4000010UL
DECL|macro|INTC_ICR2
mdefine_line|#define INTC_ICR2  &t;0xa4000012UL
DECL|macro|INTC_INTER
mdefine_line|#define INTC_INTER &t;0xa4000014UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC  &t;0xa4000016UL
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD  &t;0xa4000018UL
DECL|macro|INTC_IPRE
mdefine_line|#define INTC_IPRE  &t;0xa400001aUL
DECL|macro|IRQ0_IRQ
mdefine_line|#define IRQ0_IRQ&t;32
DECL|macro|IRQ1_IRQ
mdefine_line|#define IRQ1_IRQ&t;33
DECL|macro|IRQ2_IRQ
mdefine_line|#define IRQ2_IRQ&t;34
DECL|macro|IRQ3_IRQ
mdefine_line|#define IRQ3_IRQ&t;35
DECL|macro|IRQ4_IRQ
mdefine_line|#define IRQ4_IRQ&t;36
DECL|macro|IRQ5_IRQ
mdefine_line|#define IRQ5_IRQ&t;37
DECL|macro|IRQ0_IRP_ADDR
mdefine_line|#define IRQ0_IRP_ADDR&t;INTC_IPRC
DECL|macro|IRQ1_IRP_ADDR
mdefine_line|#define IRQ1_IRP_ADDR&t;INTC_IPRC
DECL|macro|IRQ2_IRP_ADDR
mdefine_line|#define IRQ2_IRP_ADDR&t;INTC_IPRC
DECL|macro|IRQ3_IRP_ADDR
mdefine_line|#define IRQ3_IRP_ADDR&t;INTC_IPRC
DECL|macro|IRQ4_IRP_ADDR
mdefine_line|#define IRQ4_IRP_ADDR&t;INTC_IPRD
DECL|macro|IRQ5_IRP_ADDR
mdefine_line|#define IRQ5_IRP_ADDR&t;INTC_IPRD
DECL|macro|IRQ0_IRP_POS
mdefine_line|#define IRQ0_IRP_POS&t;0
DECL|macro|IRQ1_IRP_POS
mdefine_line|#define IRQ1_IRP_POS&t;1
DECL|macro|IRQ2_IRP_POS
mdefine_line|#define IRQ2_IRP_POS&t;2
DECL|macro|IRQ3_IRP_POS
mdefine_line|#define IRQ3_IRP_POS&t;3
DECL|macro|IRQ4_IRP_POS
mdefine_line|#define IRQ4_IRP_POS&t;0
DECL|macro|IRQ5_IRP_POS
mdefine_line|#define IRQ5_IRP_POS&t;1
DECL|macro|IRQ0_PRIORITY
mdefine_line|#define IRQ0_PRIORITY&t;1
DECL|macro|IRQ1_PRIORITY
mdefine_line|#define IRQ1_PRIORITY&t;1
DECL|macro|IRQ2_PRIORITY
mdefine_line|#define IRQ2_PRIORITY&t;1
DECL|macro|IRQ3_PRIORITY
mdefine_line|#define IRQ3_PRIORITY&t;1
DECL|macro|IRQ4_PRIORITY
mdefine_line|#define IRQ4_PRIORITY&t;1
DECL|macro|IRQ5_PRIORITY
mdefine_line|#define IRQ5_PRIORITY&t;1
macro_line|#endif
macro_line|#endif /* __ASM_SH_IRQ_H */
eof
