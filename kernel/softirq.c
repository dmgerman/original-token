multiline_comment|/*&n; *&t;linux/kernel/softirq.c&n; *&n; *&t;Copyright (C) 1992 Linus Torvalds&n; *&n; * do_bottom_half() runs at normal kernel priority: all interrupts&n; * enabled.  do_bottom_half() is atomic with respect to itself: a&n; * bottom_half handler need not be re-entrant.&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
DECL|variable|intr_count
id|atomic_t
id|intr_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|bh_mask_count
r_int
id|bh_mask_count
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|bh_active
r_int
r_int
id|bh_active
op_assign
l_int|0
suffix:semicolon
DECL|variable|bh_mask
r_int
r_int
id|bh_mask
op_assign
l_int|0
suffix:semicolon
DECL|variable|bh_base
r_void
(paren
op_star
id|bh_base
(braket
l_int|32
)braket
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * This needs to make sure that only one bottom half handler&n; * is ever active at a time. We do this without locking by&n; * doing an atomic increment on the intr_count, and checking&n; * (nonatomically) against 1. Only if it&squot;s 1 do we schedule&n; * the bottom half.&n; *&n; * Note that the non-atomicity of the test (as opposed to the&n; * actual update) means that the test may fail, and _nobody_&n; * runs the handlers if there is a race that makes multiple&n; * CPU&squot;s get here at the same time. That&squot;s ok, we&squot;ll run them&n; * next time around.&n; */
DECL|function|run_bottom_halves
r_static
r_inline
r_void
id|run_bottom_halves
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|active
suffix:semicolon
r_void
(paren
op_star
op_star
id|bh
)paren
(paren
r_void
)paren
suffix:semicolon
id|active
op_assign
id|get_active_bhs
c_func
(paren
)paren
suffix:semicolon
id|clear_active_bhs
c_func
(paren
id|active
)paren
suffix:semicolon
id|bh
op_assign
id|bh_base
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|active
op_amp
l_int|1
)paren
(paren
op_star
id|bh
)paren
(paren
)paren
suffix:semicolon
id|bh
op_increment
suffix:semicolon
id|active
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|active
)paren
suffix:semicolon
)brace
DECL|function|do_bottom_half
id|asmlinkage
r_void
id|do_bottom_half
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hardirq_trylock
c_func
(paren
id|cpu
)paren
)paren
(brace
r_if
c_cond
(paren
id|softirq_trylock
c_func
(paren
)paren
)paren
(brace
id|run_bottom_halves
c_func
(paren
)paren
suffix:semicolon
id|softirq_endlock
c_func
(paren
)paren
suffix:semicolon
)brace
id|hardirq_endlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
)brace
eof
