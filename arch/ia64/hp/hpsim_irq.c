multiline_comment|/*&n; * Platform dependent support for HP simulator.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
r_static
r_int
DECL|function|irq_hp_sim_handle_irq
id|irq_hp_sim_handle_irq
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
l_int|0
suffix:semicolon
r_struct
id|irq_desc
op_star
id|id
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
(brace
id|status
op_assign
id|id-&gt;status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|IRQ_INPROGRESS
)paren
op_eq
l_int|0
op_logical_and
(paren
id|status
op_amp
id|IRQ_ENABLED
)paren
op_ne
l_int|0
)paren
(brace
id|action
op_assign
id|id-&gt;action
suffix:semicolon
id|status
op_or_assign
id|IRQ_INPROGRESS
suffix:semicolon
)brace
id|id-&gt;status
op_assign
id|status
op_amp
op_complement
(paren
id|IRQ_REPLAY
op_or
id|IRQ_WAITING
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|id-&gt;status
op_amp
id|IRQ_AUTODETECT
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;irq_hpsim_handle_irq: unexpected interrupt %u&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|retval
op_assign
id|invoke_irq_handlers
c_func
(paren
id|irq
comma
id|regs
comma
id|action
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
(brace
id|id-&gt;status
op_and_assign
op_complement
id|IRQ_INPROGRESS
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_void
DECL|function|irq_hp_sim_noop
id|irq_hp_sim_noop
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|variable|irq_type_hp_sim
r_static
r_struct
id|hw_interrupt_type
id|irq_type_hp_sim
op_assign
(brace
l_string|&quot;hp_sim&quot;
comma
(paren
r_void
(paren
op_star
)paren
(paren
r_int
r_int
)paren
)paren
id|irq_hp_sim_noop
comma
multiline_comment|/* init */
id|irq_hp_sim_noop
comma
multiline_comment|/* startup */
id|irq_hp_sim_noop
comma
multiline_comment|/* shutdown */
id|irq_hp_sim_handle_irq
comma
multiline_comment|/* handle */
id|irq_hp_sim_noop
comma
multiline_comment|/* enable */
id|irq_hp_sim_noop
comma
multiline_comment|/* disable */
)brace
suffix:semicolon
r_void
DECL|function|hpsim_irq_init
id|hpsim_irq_init
(paren
r_struct
id|irq_desc
id|desc
(braket
id|NR_IRQS
)braket
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
id|IA64_MIN_VECTORED_IRQ
suffix:semicolon
id|i
op_le
id|IA64_MAX_VECTORED_IRQ
suffix:semicolon
op_increment
id|i
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
id|irq_type_hp_sim
suffix:semicolon
)brace
)brace
eof
