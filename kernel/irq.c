multiline_comment|/*&n; *&t;linux/kernel/irq.c&n; *&n; *&t;Copyright (C) 1992 Linus Torvalds&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * The same sigaction struct is used, and with similar semantics (ie there&n; * is a SA_INTERRUPT flag etc). Naturally it&squot;s not a 1:1 relation, but there&n; * are similarities.&n; *&n; * sa_handler(int irq_NR) is the default function called.&n; * sa_mask is 0 if nothing uses this IRQ&n; * sa_flags contains various info: SA_INTERRUPT etc&n; * sa_restorer is the unused&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|CR0_NE
mdefine_line|#define CR0_NE 32
DECL|variable|intr_count
r_static
r_int
r_int
id|intr_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|cache_21
r_static
r_int
r_char
id|cache_21
op_assign
l_int|0xff
suffix:semicolon
DECL|variable|cache_A1
r_static
r_int
r_char
id|cache_A1
op_assign
l_int|0xff
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
l_int|0xFFFFFFFF
suffix:semicolon
DECL|variable|bh_base
r_struct
id|bh_struct
id|bh_base
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/*&n; * do_bottom_half() runs at normal kernel priority: all interrupts&n; * enabled.  do_bottom_half() is atomic with respect to itself: a&n; * bottom_half handler need not be re-entrant.  This function is&n; * called only when bh_active is non-zero and when there aren&squot;t any&n; * nested irq&squot;s active.&n; */
DECL|function|do_bottom_half
r_void
id|do_bottom_half
c_func
(paren
r_int
id|nr
)paren
(brace
r_struct
id|bh_struct
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|bh_base
op_plus
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;routine
op_ne
l_int|NULL
)paren
id|bh
op_member_access_from_pointer
id|routine
c_func
(paren
id|bh-&gt;data
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;irq.c:bad bottom half entry (%d).&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This builds up the IRQ handler stubs using some ugly macros in irq.h&n; *&n; * These macros create the low-level assembly IRQ routines that do all&n; * the operations that are needed to keep the AT interrupt-controller&n; * happy. They are also written to be fast - and to disable interrupts&n; * as little as humanly possible.&n; *&n; * NOTE! These macros expand to three different handlers for each line: one&n; * complete handler that does all the fancy stuff (including signal handling),&n; * and one fast handler that is meant for simple IRQ&squot;s that want to be&n; * atomic. The specific handler is chosen depending on the SA_INTERRUPT&n; * flag when installing a handler. Finally, one &quot;bad interrupt&quot; handler, that&n; * is used when no handler is present.&n; */
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|0
comma
l_int|0x01
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|1
comma
l_int|0x02
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|2
comma
l_int|0x04
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|3
comma
l_int|0x08
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|4
comma
l_int|0x10
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|5
comma
l_int|0x20
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|6
comma
l_int|0x40
)paren
id|BUILD_IRQ
c_func
(paren
id|FIRST
comma
l_int|7
comma
l_int|0x80
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|8
comma
l_int|0x01
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|9
comma
l_int|0x02
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|10
comma
l_int|0x04
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|11
comma
l_int|0x08
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|12
comma
l_int|0x10
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|13
comma
l_int|0x20
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|14
comma
l_int|0x40
)paren
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|15
comma
l_int|0x80
)paren
multiline_comment|/*&n; * Pointers to the low-level handlers: first the general ones, then the&n; * fast ones, then the bad ones.&n; */
DECL|variable|interrupt
r_static
r_void
(paren
op_star
id|interrupt
(braket
l_int|16
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
id|IRQ0_interrupt
comma
id|IRQ1_interrupt
comma
id|IRQ2_interrupt
comma
id|IRQ3_interrupt
comma
id|IRQ4_interrupt
comma
id|IRQ5_interrupt
comma
id|IRQ6_interrupt
comma
id|IRQ7_interrupt
comma
id|IRQ8_interrupt
comma
id|IRQ9_interrupt
comma
id|IRQ10_interrupt
comma
id|IRQ11_interrupt
comma
id|IRQ12_interrupt
comma
id|IRQ13_interrupt
comma
id|IRQ14_interrupt
comma
id|IRQ15_interrupt
)brace
suffix:semicolon
DECL|variable|fast_interrupt
r_static
r_void
(paren
op_star
id|fast_interrupt
(braket
l_int|16
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
id|fast_IRQ0_interrupt
comma
id|fast_IRQ1_interrupt
comma
id|fast_IRQ2_interrupt
comma
id|fast_IRQ3_interrupt
comma
id|fast_IRQ4_interrupt
comma
id|fast_IRQ5_interrupt
comma
id|fast_IRQ6_interrupt
comma
id|fast_IRQ7_interrupt
comma
id|fast_IRQ8_interrupt
comma
id|fast_IRQ9_interrupt
comma
id|fast_IRQ10_interrupt
comma
id|fast_IRQ11_interrupt
comma
id|fast_IRQ12_interrupt
comma
id|fast_IRQ13_interrupt
comma
id|fast_IRQ14_interrupt
comma
id|fast_IRQ15_interrupt
)brace
suffix:semicolon
DECL|variable|bad_interrupt
r_static
r_void
(paren
op_star
id|bad_interrupt
(braket
l_int|16
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
id|bad_IRQ0_interrupt
comma
id|bad_IRQ1_interrupt
comma
id|bad_IRQ2_interrupt
comma
id|bad_IRQ3_interrupt
comma
id|bad_IRQ4_interrupt
comma
id|bad_IRQ5_interrupt
comma
id|bad_IRQ6_interrupt
comma
id|bad_IRQ7_interrupt
comma
id|bad_IRQ8_interrupt
comma
id|bad_IRQ9_interrupt
comma
id|bad_IRQ10_interrupt
comma
id|bad_IRQ11_interrupt
comma
id|bad_IRQ12_interrupt
comma
id|bad_IRQ13_interrupt
comma
id|bad_IRQ14_interrupt
comma
id|bad_IRQ15_interrupt
)brace
suffix:semicolon
DECL|function|fake_keyboard_interrupt
r_void
id|fake_keyboard_interrupt
c_func
(paren
r_void
)paren
(brace
id|IRQ1_interrupt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initial irq handlers.&n; */
DECL|variable|irq_sigaction
r_static
r_struct
id|sigaction
id|irq_sigaction
(braket
l_int|16
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * do_IRQ handles IRQ&squot;s that have been installed without the&n; * SA_INTERRUPT flag: it uses the full signal-handling return&n; * and runs with other interrupts enabled. All relatively slow&n; * IRQ&squot;s should use this format: notably the keyboard/timer&n; * routines.&n; */
DECL|function|do_IRQ
r_void
id|do_IRQ
c_func
(paren
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
id|sigaction
op_star
id|sa
op_assign
id|irq
op_plus
id|irq_sigaction
suffix:semicolon
id|sa
op_member_access_from_pointer
id|sa_handler
c_func
(paren
(paren
r_int
)paren
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * do_fast_IRQ handles IRQ&squot;s that don&squot;t need the fancy interrupt return&n; * stuff - the handler is also running with interrupts disabled unless&n; * it explicitly enables them later.&n; */
DECL|function|do_fast_IRQ
r_void
id|do_fast_IRQ
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|sigaction
op_star
id|sa
op_assign
id|irq
op_plus
id|irq_sigaction
suffix:semicolon
id|sa
op_member_access_from_pointer
id|sa_handler
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|irqaction
r_int
id|irqaction
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|sigaction
op_star
r_new
)paren
(brace
r_struct
id|sigaction
op_star
id|sa
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|15
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sa
op_assign
id|irq
op_plus
id|irq_sigaction
suffix:semicolon
r_if
c_cond
(paren
id|sa-&gt;sa_mask
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_member_access_from_pointer
id|sa_handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|sa
op_assign
op_star
r_new
suffix:semicolon
id|sa-&gt;sa_mask
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_INTERRUPT
)paren
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|irq
comma
id|fast_interrupt
(braket
id|irq
)braket
)paren
suffix:semicolon
r_else
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|irq
comma
id|interrupt
(braket
id|irq
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|8
)paren
(brace
id|cache_21
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cache_21
comma
l_int|0x21
)paren
suffix:semicolon
)brace
r_else
(brace
id|cache_21
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
id|cache_A1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cache_21
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cache_A1
comma
l_int|0xA1
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
)paren
)paren
(brace
r_struct
id|sigaction
id|sa
suffix:semicolon
id|sa.sa_handler
op_assign
id|handler
suffix:semicolon
id|sa.sa_flags
op_assign
l_int|0
suffix:semicolon
id|sa.sa_mask
op_assign
l_int|0
suffix:semicolon
id|sa.sa_restorer
op_assign
l_int|NULL
suffix:semicolon
r_return
id|irqaction
c_func
(paren
id|irq
comma
op_amp
id|sa
)paren
suffix:semicolon
)brace
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|sigaction
op_star
id|sa
op_assign
id|irq
op_plus
id|irq_sigaction
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|15
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sa-&gt;sa_mask
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|8
)paren
(brace
id|cache_21
op_or_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|outb
c_func
(paren
id|cache_21
comma
l_int|0x21
)paren
suffix:semicolon
)brace
r_else
(brace
id|cache_A1
op_or_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|8
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cache_A1
comma
l_int|0xA1
)paren
suffix:semicolon
)brace
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|irq
comma
id|bad_interrupt
(braket
id|irq
)braket
)paren
suffix:semicolon
id|sa-&gt;sa_handler
op_assign
l_int|NULL
suffix:semicolon
id|sa-&gt;sa_flags
op_assign
l_int|0
suffix:semicolon
id|sa-&gt;sa_mask
op_assign
l_int|0
suffix:semicolon
id|sa-&gt;sa_restorer
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that on a 486, we don&squot;t want to do a SIGFPE on a irq13&n; * as the irq is unreliable, and exception 16 works correctly&n; * (ie as explained in the intel litterature). On a 386, you&n; * can&squot;t use exception 16 due to bad IBM design, so we have to&n; * rely on the less exact irq13.&n; */
DECL|function|math_error_irq
r_static
r_void
id|math_error_irq
c_func
(paren
r_int
id|cpl
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
l_int|0xF0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ignore_irq13
)paren
r_return
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|last_task_used_math
comma
l_int|1
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fninit&quot;
)paren
suffix:semicolon
)brace
DECL|function|no_action
r_static
r_void
id|no_action
c_func
(paren
r_int
id|cpl
)paren
(brace
)brace
DECL|variable|ignore_IRQ
r_static
r_struct
id|sigaction
id|ignore_IRQ
op_assign
(brace
id|no_action
comma
l_int|0
comma
id|SA_INTERRUPT
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_IRQ
r_void
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
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|i
comma
id|bad_interrupt
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqaction
c_func
(paren
l_int|2
comma
op_amp
id|ignore_IRQ
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Unable to get IRQ2 for cascade&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
l_int|13
comma
id|math_error_irq
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Unable to get IRQ13 for math-error handler&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* intialize the bottom half routines. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh_base
(braket
id|i
)braket
dot
id|routine
op_assign
l_int|NULL
suffix:semicolon
id|bh_base
(braket
id|i
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|bh_active
op_assign
l_int|0
suffix:semicolon
id|intr_count
op_assign
l_int|0
suffix:semicolon
)brace
eof
