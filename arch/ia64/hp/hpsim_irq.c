multiline_comment|/*&n; * Platform dependent support for HP simulator.&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
r_static
r_int
r_int
DECL|function|hpsim_irq_startup
id|hpsim_irq_startup
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|hpsim_irq_noop
id|hpsim_irq_noop
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
r_typename
suffix:colon
l_string|&quot;hpsim&quot;
comma
id|startup
suffix:colon
id|hpsim_irq_startup
comma
id|shutdown
suffix:colon
id|hpsim_irq_noop
comma
id|enable
suffix:colon
id|hpsim_irq_noop
comma
id|disable
suffix:colon
id|hpsim_irq_noop
comma
id|ack
suffix:colon
id|hpsim_irq_noop
comma
id|end
suffix:colon
id|hpsim_irq_noop
comma
id|set_affinity
suffix:colon
(paren
r_void
(paren
op_star
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
)paren
id|hpsim_irq_noop
comma
)brace
suffix:semicolon
r_void
id|__init
DECL|function|hpsim_irq_init
id|hpsim_irq_init
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
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_eq
op_amp
id|no_irq_type
)paren
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
