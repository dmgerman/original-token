multiline_comment|/*&n; *&t;linux/arch/mips/kernel/irq.c&n; *&n; *&t;Copyright (C) 1992 Linus Torvalds&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
multiline_comment|/*&n; * Mips support by Ralf Baechle and Andreas Busse&n; *&n; * The Deskstation Tyne is almost completely like an IBM compatible PC with&n; * another type of microprocessor. Therefore this code is almost completely&n; * the same. More work needs to be done to support Acer PICA and other&n; * machines.&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0                     /* Keep this in sync with time.c */
DECL|variable|cache_21
r_int
r_char
id|cache_21
op_assign
l_int|0xff
suffix:semicolon
DECL|variable|cache_A1
r_int
r_char
id|cache_A1
op_assign
l_int|0xff
suffix:semicolon
DECL|variable|spurious_count
r_int
r_int
id|spurious_count
op_assign
l_int|0
suffix:semicolon
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq_nr
op_amp
l_int|7
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
OL
l_int|8
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cache_21
op_or_assign
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|cache_21
comma
l_int|0x21
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cache_A1
op_or_assign
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|cache_A1
comma
l_int|0xA1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|mask
suffix:semicolon
id|mask
op_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
OL
l_int|8
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cache_21
op_and_assign
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|cache_21
comma
l_int|0x21
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cache_A1
op_and_assign
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|cache_A1
comma
l_int|0xA1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pointers to the low-level handlers: first the general ones, then the&n; * fast ones, then the bad ones.&n; */
r_extern
r_void
id|interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fast_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|bad_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Initial irq handlers.&n; */
DECL|variable|timer_irq
r_static
r_struct
id|irqaction
id|timer_irq
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|cascade_irq
r_static
r_struct
id|irqaction
id|cascade_irq
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|math_irq
r_static
r_struct
id|irqaction
id|math_irq
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|irq_action
r_static
r_struct
id|irqaction
op_star
id|irq_action
(braket
l_int|16
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|get_irq_list
r_int
id|get_irq_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
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
(brace
id|action
op_assign
op_star
(paren
id|i
op_plus
id|irq_action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%2d: %8d %c %s&quot;
comma
id|i
comma
id|kstat.interrupts
(braket
id|i
)braket
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|action-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;,%s %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * do_IRQ handles IRQ&squot;s that have been installed without the&n; * SA_INTERRUPT flag: it uses the full signal-handling return&n; * and runs with other interrupts enabled. All relatively slow&n; * IRQ&squot;s should use this format: notably the keyboard/timer&n; * routines.&n; */
DECL|function|do_IRQ
id|asmlinkage
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
id|irqaction
op_star
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
r_while
c_loop
(paren
id|action
)paren
(brace
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * do_fast_IRQ handles IRQ&squot;s that don&squot;t need the fancy interrupt return&n; * stuff - the handler is also running with interrupts disabled unless&n; * it explicitly enables them later.&n; */
DECL|function|do_fast_IRQ
id|asmlinkage
r_void
id|do_fast_IRQ
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
r_while
c_loop
(paren
id|action
)paren
(brace
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
l_int|NULL
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
)brace
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE SA_ONESHOT
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
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
comma
op_star
id|tmp
op_assign
l_int|NULL
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
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_if
c_cond
(paren
(paren
id|action-&gt;flags
op_amp
id|SA_SHIRQ
)paren
op_logical_and
(paren
id|irqflags
op_amp
id|SA_SHIRQ
)paren
)paren
(brace
r_for
c_loop
(paren
id|tmp
op_assign
id|action
suffix:semicolon
id|tmp-&gt;next
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
op_xor
(paren
id|irqflags
op_amp
id|SA_INTERRUPT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Attempt to mix fast and slow interrupts on IRQ%d denied&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
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
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
id|action
op_assign
op_amp
id|cascade_irq
suffix:semicolon
r_else
r_if
c_cond
(paren
id|irq
op_eq
l_int|13
)paren
id|action
op_assign
op_amp
id|math_irq
suffix:semicolon
r_else
r_if
c_cond
(paren
id|irq
op_eq
id|TIMER_IRQ
)paren
id|action
op_assign
op_amp
id|timer_irq
suffix:semicolon
r_else
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
id|devname
suffix:semicolon
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|tmp-&gt;next
op_assign
id|action
suffix:semicolon
)brace
r_else
(brace
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
op_assign
id|action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|SA_PROBE
)paren
)paren
(brace
multiline_comment|/* SA_ONESHOT used by probing */
multiline_comment|/*&n;&t;&t; * FIXME: Does the SA_INTERRUPT flag make any sense on MIPS???&n;&t;&t; */
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
id|set_int_vector
c_func
(paren
id|irq
comma
id|fast_interrupt
)paren
suffix:semicolon
r_else
id|set_int_vector
c_func
(paren
id|irq
comma
id|interrupt
)paren
suffix:semicolon
)brace
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
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
r_struct
id|irqaction
op_star
id|tmp
op_assign
l_int|NULL
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
id|action-&gt;handler
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
r_if
c_cond
(paren
id|dev_id
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_eq
id|dev_id
)paren
r_break
suffix:semicolon
id|tmp
op_assign
id|action
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free shared IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SHIRQ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free shared IRQ%d with NULL device ID&bslash;n&quot;
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
id|action
op_logical_and
id|tmp
)paren
(brace
id|tmp-&gt;next
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_else
(brace
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|irq
op_eq
l_int|2
)paren
op_logical_or
(paren
id|irq
op_eq
l_int|13
)paren
op_or
(paren
id|irq
op_eq
id|TIMER_IRQ
)paren
)paren
id|memset
c_func
(paren
id|action
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irqaction
)paren
)paren
suffix:semicolon
r_else
id|kfree_s
c_func
(paren
id|action
comma
r_sizeof
(paren
r_struct
id|irqaction
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
)paren
)paren
(brace
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
id|set_int_vector
c_func
(paren
id|irq
comma
id|bad_interrupt
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
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
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
)brace
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|irqs
op_assign
l_int|0
comma
id|irqmask
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
multiline_comment|/* first, snaffle up any unassigned irqs */
r_for
c_loop
(paren
id|i
op_assign
l_int|15
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_irq
c_func
(paren
id|i
comma
id|no_action
comma
id|SA_PROBE
comma
l_string|&quot;probe&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|enable_irq
c_func
(paren
id|i
)paren
suffix:semicolon
id|irqs
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* wait for spurious interrupts to mask themselves out again */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
l_int|2
suffix:semicolon
id|delay
OG
id|jiffies
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* min 10ms delay */
multiline_comment|/* now filter out any obviously spurious interrupts */
id|irqmask
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|cache_A1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
r_int
r_int
)paren
id|cache_21
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|15
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|irqs
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
op_amp
id|irqmask
)paren
(brace
id|irqs
op_xor_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|i
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;probe_irq_on:  irqs=0x%04x irqmask=0x%04x&bslash;n&quot;
comma
id|irqs
comma
id|irqmask
)paren
suffix:semicolon
macro_line|#endif
r_return
id|irqs
suffix:semicolon
)brace
DECL|function|probe_irq_off
r_int
id|probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
(brace
r_int
r_int
id|i
comma
id|irqmask
suffix:semicolon
id|irqmask
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|cache_A1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
r_int
r_int
)paren
id|cache_21
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|15
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|irqs
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|i
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;probe_irq_off: irqs=0x%04x irqmask=0x%04x&bslash;n&quot;
comma
id|irqs
comma
id|irqmask
)paren
suffix:semicolon
macro_line|#endif
id|irqs
op_and_assign
id|irqmask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irqs
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|irqs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqs
op_ne
(paren
id|irqs
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|i
op_assign
op_minus
id|i
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|boot_info.machtype
)paren
(brace
r_case
id|MACH_MIPS_MAGNUM_4000
suffix:colon
r_case
id|MACH_ACER_PICA_61
suffix:colon
id|r4030_write_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
comma
id|JAZZ_IE_ETHERNET
op_or
id|JAZZ_IE_SERIAL1
op_or
id|JAZZ_IE_SERIAL2
op_or
id|JAZZ_IE_PARALLEL
op_or
id|JAZZ_IE_FLOPPY
)paren
suffix:semicolon
id|r4030_read_reg16
c_func
(paren
id|JAZZ_IO_IRQ_SOURCE
)paren
suffix:semicolon
multiline_comment|/* clear pending IRQs */
id|set_cp0_status
c_func
(paren
id|ST0_IM
comma
id|IE_IRQ4
op_or
id|IE_IRQ1
)paren
suffix:semicolon
multiline_comment|/* set the clock to 100 Hz */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_TIMER_INTERVAL
comma
l_int|9
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_DESKSTATION_TYNE
suffix:colon
multiline_comment|/* set the clock to 100 Hz */
id|outb_p
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
l_int|2
comma
id|no_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Unable to get IRQ2 for cascade&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown machtype in init_IRQ&quot;
)paren
suffix:semicolon
)brace
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
id|set_int_vector
c_func
(paren
id|i
comma
id|bad_interrupt
)paren
suffix:semicolon
multiline_comment|/* initialize the bottom half routines. */
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
