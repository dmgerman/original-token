multiline_comment|/*&n; * $Id: irq_control.h,v 1.2 1999/07/17 20:23:58 cort Exp $&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; */
macro_line|#ifndef _PPC_IRQ_CONTROL_H
DECL|macro|_PPC_IRQ_CONTROL_H
mdefine_line|#define _PPC_IRQ_CONTROL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_void
id|do_lost_interrupts
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
id|atomic_t
id|ppc_n_lost_interrupts
suffix:semicolon
DECL|macro|__no_use_save_flags
mdefine_line|#define __no_use_save_flags(flags) &bslash;&n;&t;({__asm__ __volatile__ (&quot;mfmsr %0&quot; : &quot;=r&quot; ((flags)) : : &quot;memory&quot;); })
DECL|function|__no_use_restore_flags
r_extern
id|__inline__
r_void
id|__no_use_restore_flags
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|MSR_EE
)paren
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|ppc_n_lost_interrupts
)paren
op_ne
l_int|0
)paren
(brace
id|do_lost_interrupts
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync; mtmsr %0; isync&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|__no_use_sti
r_extern
id|__inline__
r_void
id|__no_use_sti
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mfmsr %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
id|flags
op_or_assign
id|MSR_EE
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ppc_n_lost_interrupts
)paren
)paren
id|do_lost_interrupts
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync; mtmsr %0; isync&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
DECL|function|__no_use_cli
r_extern
id|__inline__
r_void
id|__no_use_cli
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mfmsr %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
id|flags
op_and_assign
op_complement
id|MSR_EE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync; mtmsr %0; isync&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__no_use_mask_irq
mdefine_line|#define __no_use_mask_irq(irq) ({if (irq_desc[irq].ctl &amp;&amp; irq_desc[irq].ctl-&gt;disable) irq_desc[irq].ctl-&gt;disable(irq);})
DECL|macro|__no_use_unmask_irq
mdefine_line|#define __no_use_unmask_irq(irq) ({if (irq_desc[irq].ctl &amp;&amp; irq_desc[irq].ctl-&gt;enable) irq_desc[irq].ctl-&gt;enable(irq);})
DECL|macro|__no_use_mask_and_ack_irq
mdefine_line|#define __no_use_mask_and_ack_irq(irq) ({if (irq_desc[irq].ctl &amp;&amp; irq_desc[irq].ctl-&gt;mask_and_ack) irq_desc[irq].ctl-&gt;mask_and_ack(irq);})
macro_line|#ifdef CONFIG_RTL
multiline_comment|/* the rtl system provides these -- Cort */
r_extern
r_void
id|__sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__restore_flags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__return_flags
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags) (flags = __return_flags())
DECL|macro|rtl_hard_cli
mdefine_line|#define rtl_hard_cli __no_use_cli
DECL|macro|rtl_hard_sti
mdefine_line|#define rtl_hard_sti __no_use_sti
DECL|macro|rtl_hard_save_flags
mdefine_line|#define rtl_hard_save_flags(flags) __no_use_save_flags(flags)
DECL|macro|rtl_hard_restore_flags
mdefine_line|#define rtl_hard_restore_flags(flags) __no_use_restore_flags(flags)
DECL|macro|rtl_hard_mask_irq
mdefine_line|#define rtl_hard_mask_irq(irq) __no_use_mask_irq(irq)
DECL|macro|rtl_hard_unmask_irq
mdefine_line|#define rtl_hard_unmask_irq(irq) __no_use_unmask_irq(irq)
DECL|macro|rtl_hard_mask_and_ack_irq
mdefine_line|#define rtl_hard_mask_and_ack_irq(irq) __no_use_mask_and_ack_irq(irq)
macro_line|#else /* CONFIG_RTL */
DECL|macro|__cli
mdefine_line|#define __cli __no_use_cli
DECL|macro|__sti
mdefine_line|#define __sti __no_use_sti
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags) __no_use_save_flags(flags)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags) __no_use_restore_flags(flags)
DECL|macro|mask_irq
mdefine_line|#define mask_irq(irq) __no_use_mask_irq(irq)
DECL|macro|unmask_irq
mdefine_line|#define unmask_irq(irq) __no_use_unmask_irq(irq)
DECL|macro|mask_and_ack_irq
mdefine_line|#define mask_and_ack_irq(irq) __no_use_mask_and_ack_irq(irq)
macro_line|#endif /* CONFIG_RTL */
macro_line|#endif /* _PPC_IRQ_CONTROL_H */
eof
