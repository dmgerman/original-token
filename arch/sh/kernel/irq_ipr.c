multiline_comment|/* $Id: irq_ipr.c,v 1.6 2000/05/14 08:41:25 gniibe Exp $&n; *&n; * linux/arch/sh/kernel/irq_ipr.c&n; *&n; * Copyright (C) 1999  Niibe Yutaka &amp; Takeshi Yaegashi&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * Interrupt handling for IPR-based IRQ.&n; *&n; * Supported system:&n; *&t;On-chip supporting modules (TMU, RTC, etc.).&n; *&t;On-chip supporting modules for SH7709/SH7709A/SH7729.&n; *&t;Hitachi SolutionEngine external I/O:&n; *&t;&t;MS7709SE01, MS7709ASE01, and MS7750SE01&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|struct|ipr_data
r_struct
id|ipr_data
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* Address of Interrupt Priority Register */
DECL|member|shift
r_int
id|shift
suffix:semicolon
multiline_comment|/* Shifts of the 16-bit data */
DECL|member|priority
r_int
id|priority
suffix:semicolon
multiline_comment|/* The priority */
)brace
suffix:semicolon
DECL|variable|ipr_data
r_static
r_struct
id|ipr_data
id|ipr_data
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|function|set_ipr_data
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
(brace
id|ipr_data
(braket
id|irq
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
id|ipr_data
(braket
id|irq
)braket
dot
id|shift
op_assign
id|pos
op_star
l_int|4
suffix:semicolon
multiline_comment|/* POSition (0-3) x 4 means shift */
id|ipr_data
(braket
id|irq
)braket
dot
id|priority
op_assign
id|priority
suffix:semicolon
)brace
r_static
r_void
id|enable_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_void
id|disable_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* shutdown is same as &quot;disable&quot; */
DECL|macro|shutdown_ipr_irq
mdefine_line|#define shutdown_ipr_irq disable_ipr_irq
r_static
r_void
id|mask_and_ack_ipr
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|end_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|function|startup_ipr_irq
r_static
r_int
r_int
id|startup_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_ipr_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
DECL|variable|ipr_irq_type
r_static
r_struct
id|hw_interrupt_type
id|ipr_irq_type
op_assign
(brace
l_string|&quot;IPR-based-IRQ&quot;
comma
id|startup_ipr_irq
comma
id|shutdown_ipr_irq
comma
id|enable_ipr_irq
comma
id|disable_ipr_irq
comma
id|mask_and_ack_ipr
comma
id|end_ipr_irq
)brace
suffix:semicolon
DECL|function|disable_ipr_irq
r_void
id|disable_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|flags
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|ipr_data
(braket
id|irq
)braket
dot
id|addr
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0xffff
op_xor
(paren
l_int|0x0f
op_lshift
id|ipr_data
(braket
id|irq
)braket
dot
id|shift
)paren
suffix:semicolon
multiline_comment|/* Set the priority in IPR to 0 */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|ctrl_inw
c_func
(paren
id|addr
)paren
suffix:semicolon
id|val
op_and_assign
id|mask
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_ipr_irq
r_static
r_void
id|enable_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|flags
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|ipr_data
(braket
id|irq
)braket
dot
id|addr
suffix:semicolon
r_int
id|priority
op_assign
id|ipr_data
(braket
id|irq
)braket
dot
id|priority
suffix:semicolon
r_int
r_int
id|value
op_assign
(paren
id|priority
op_lshift
id|ipr_data
(braket
id|irq
)braket
dot
id|shift
)paren
suffix:semicolon
multiline_comment|/* Set priority in IPR back to original value */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|ctrl_inw
c_func
(paren
id|addr
)paren
suffix:semicolon
id|val
op_or_assign
id|value
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|make_ipr_irq
r_void
id|make_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_irq_nosync
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_assign
op_amp
id|ipr_irq_type
suffix:semicolon
id|disable_ipr_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|mask_and_ack_ipr
r_static
r_void
id|mask_and_ack_ipr
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_ipr_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_SUBTYPE_SH7709
multiline_comment|/* This is needed when we use edge triggered setting */
multiline_comment|/* XXX: Is it really needed? */
r_if
c_cond
(paren
id|IRQ0_IRQ
op_le
id|irq
op_logical_and
id|irq
op_le
id|IRQ5_IRQ
)paren
(brace
multiline_comment|/* Clear external interrupt request */
r_int
id|a
op_assign
id|ctrl_inb
c_func
(paren
id|INTC_IRR0
)paren
suffix:semicolon
id|a
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IRQ0_IRQ
)paren
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|a
comma
id|INTC_IRR0
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|end_ipr_irq
r_static
r_void
id|end_ipr_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_ipr_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|TIMER_IRQ
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|ipr_irq_type
suffix:semicolon
)brace
id|set_ipr_data
c_func
(paren
id|TIMER_IRQ
comma
id|TIMER_IPR_ADDR
comma
id|TIMER_IPR_POS
comma
id|TIMER_PRIORITY
)paren
suffix:semicolon
id|set_ipr_data
c_func
(paren
id|RTC_IRQ
comma
id|RTC_IPR_ADDR
comma
id|RTC_IPR_POS
comma
id|RTC_PRIORITY
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_SUBTYPE_SH7709
multiline_comment|/*&n;&t; * Initialize the Interrupt Controller (INTC)&n;&t; * registers to their power on values&n;&t; */
macro_line|#if 0
multiline_comment|/*&n;&t; * XXX: I think that this is the job of boot loader. -- gniibe&n;&t; *&n;&t; * When Takeshi released new boot loader following setting&n;&t; * will be removed shortly.&n;&t; */
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|INTC_IRR0
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|INTC_IRR1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|INTC_IRR2
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_ICR0
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_ICR1
)paren
suffix:semicolon
multiline_comment|/* Really? 0x4000?*/
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_ICR2
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_INTER
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_IPRA
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_IPRB
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_IPRC
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_IPRD
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|INTC_IPRE
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Enable external irq (INTC IRQ mode).&n;&t; * You should set corresponding bits of PFC to &quot;00&quot;&n;&t; * to enable these interrupts.&n;&t; */
id|set_ipr_data
c_func
(paren
id|IRQ0_IRQ
comma
id|IRQ0_IRP_ADDR
comma
id|IRQ0_IRP_POS
comma
id|IRQ0_PRIORITY
)paren
suffix:semicolon
id|set_ipr_data
c_func
(paren
id|IRQ1_IRQ
comma
id|IRQ1_IRP_ADDR
comma
id|IRQ1_IRP_POS
comma
id|IRQ1_PRIORITY
)paren
suffix:semicolon
id|set_ipr_data
c_func
(paren
id|IRQ2_IRQ
comma
id|IRQ2_IRP_ADDR
comma
id|IRQ2_IRP_POS
comma
id|IRQ2_PRIORITY
)paren
suffix:semicolon
id|set_ipr_data
c_func
(paren
id|IRQ3_IRQ
comma
id|IRQ3_IRP_ADDR
comma
id|IRQ3_IRP_POS
comma
id|IRQ3_PRIORITY
)paren
suffix:semicolon
id|set_ipr_data
c_func
(paren
id|IRQ4_IRQ
comma
id|IRQ4_IRP_ADDR
comma
id|IRQ4_IRP_POS
comma
id|IRQ4_PRIORITY
)paren
suffix:semicolon
id|set_ipr_data
c_func
(paren
id|IRQ5_IRQ
comma
id|IRQ5_IRP_ADDR
comma
id|IRQ5_IRP_POS
comma
id|IRQ5_PRIORITY
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_CPU_SUBTYPE_SH7709 */
)brace
eof
