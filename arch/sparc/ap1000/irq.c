multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ap1000/apreg.h&gt;
r_extern
r_void
id|ap_clear_clock_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ap_init_timers
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ap_enable_irq
r_static
r_void
id|ap_enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
multiline_comment|/* printk(&quot;ENABLE IRQ %d IGNORED&bslash;n&quot;,irq_nr); */
)brace
DECL|function|ap_disable_irq
r_static
r_void
id|ap_disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DISABLE IRQ %d IGNORED&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
)brace
DECL|function|ap_clear_profile_irq
r_static
r_void
id|ap_clear_profile_irq
c_func
(paren
r_void
)paren
(brace
id|MC_OUT
c_func
(paren
id|MC_INTR
comma
id|AP_CLR_INTR_REQ
op_lshift
id|MC_INTR_ITIM0_SH
)paren
suffix:semicolon
)brace
DECL|function|ap_load_profile_irq
r_static
r_void
id|ap_load_profile_irq
c_func
(paren
r_int
id|limit
)paren
(brace
id|MC_OUT
c_func
(paren
id|MC_ITIMER0
comma
id|limit
)paren
suffix:semicolon
)brace
DECL|function|ap_init_IRQ
r_void
id|ap_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|enable_irq
op_assign
id|ap_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|ap_disable_irq
suffix:semicolon
id|clear_clock_irq
op_assign
id|ap_clear_clock_irq
suffix:semicolon
id|clear_profile_irq
op_assign
id|ap_clear_profile_irq
suffix:semicolon
id|load_profile_irq
op_assign
id|ap_load_profile_irq
suffix:semicolon
id|init_timers
op_assign
id|ap_init_timers
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* the sun4m code does this, so we do too */
)brace
eof
