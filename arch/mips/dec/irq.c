multiline_comment|/*&n; * Code to handle DECstation IRQs plus some generic interrupt stuff.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994, 1995, 1996, 1997 Ralf Baechle&n; *&n; * $Id: irq.c,v 1.6 2000/02/04 07:40:23 ralf Exp $&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dec/interrupts.h&gt;
r_extern
r_volatile
r_int
r_int
op_star
id|isr
suffix:semicolon
multiline_comment|/* address of the interrupt status register     */
r_extern
r_volatile
r_int
r_int
op_star
id|imr
suffix:semicolon
multiline_comment|/* address of the interrupt mask register       */
r_extern
id|decint_t
id|dec_interrupt
(braket
id|NR_INTS
)braket
suffix:semicolon
DECL|variable|spurious_count
r_int
r_int
id|spurious_count
op_assign
l_int|0
suffix:semicolon
DECL|function|mask_irq
r_static
r_inline
r_void
id|mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|dec_interrupt
(braket
id|irq_nr
)braket
dot
id|iemask
)paren
(brace
multiline_comment|/* This is an ASIC interrupt    */
op_star
id|imr
op_and_assign
op_complement
id|dec_interrupt
(braket
id|irq_nr
)braket
dot
id|iemask
suffix:semicolon
id|dummy
op_assign
op_star
id|imr
suffix:semicolon
id|dummy
op_assign
op_star
id|imr
suffix:semicolon
)brace
r_else
multiline_comment|/* This is a cpu interrupt        */
id|set_cp0_status
c_func
(paren
id|ST0_IM
comma
id|read_32bit_cp0_register
c_func
(paren
id|CP0_STATUS
)paren
op_amp
op_complement
id|dec_interrupt
(braket
id|irq_nr
)braket
dot
id|cpu_mask
)paren
suffix:semicolon
)brace
DECL|function|unmask_irq
r_static
r_inline
r_void
id|unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|dec_interrupt
(braket
id|irq_nr
)braket
dot
id|iemask
)paren
(brace
multiline_comment|/* This is an ASIC interrupt    */
op_star
id|imr
op_or_assign
id|dec_interrupt
(braket
id|irq_nr
)braket
dot
id|iemask
suffix:semicolon
id|dummy
op_assign
op_star
id|imr
suffix:semicolon
id|dummy
op_assign
op_star
id|imr
suffix:semicolon
)brace
id|set_cp0_status
c_func
(paren
id|ST0_IM
comma
id|read_32bit_cp0_register
c_func
(paren
id|CP0_STATUS
)paren
op_or
id|dec_interrupt
(braket
id|irq_nr
)braket
dot
id|cpu_mask
)paren
suffix:semicolon
)brace
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq_nr
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq_nr
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
DECL|variable|irq_action
r_static
r_struct
id|irqaction
op_star
id|irq_action
(braket
l_int|32
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|action
op_assign
id|irq_action
(braket
id|i
)braket
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
id|kstat.irqs
(braket
l_int|0
)braket
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
suffix:semicolon
r_int
id|do_random
comma
id|cpu
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq
)paren
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
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
)paren
id|__sti
c_func
(paren
)paren
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
id|do_random
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|do_random
op_or_assign
id|action-&gt;flags
suffix:semicolon
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
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_random
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|irq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/* unmasking and bottom half handling is done magically for us. */
)brace
multiline_comment|/*&n; * Idea is to put all interrupts&n; * in a single table and differenciate them just by number.&n; */
DECL|function|setup_dec_irq
r_int
id|setup_dec_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
(brace
r_int
id|shared
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|p
op_assign
id|irq_action
op_plus
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Can&squot;t share interrupts unless both agree to */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old-&gt;flags
op_amp
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SHIRQ
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Can&squot;t share interrupts unless both are same type */
r_if
c_cond
(paren
(paren
id|old-&gt;flags
op_xor
r_new
op_member_access_from_pointer
id|flags
)paren
op_amp
id|SA_INTERRUPT
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* add new interrupt at end of irq queue */
r_do
(brace
id|p
op_assign
op_amp
id|old-&gt;next
suffix:semicolon
id|old
op_assign
op_star
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old
)paren
suffix:semicolon
id|shared
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared
)paren
(brace
id|unmask_irq
c_func
(paren
id|irq
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
r_int
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|32
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|retval
op_assign
id|setup_dec_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
id|retval
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
comma
op_star
op_star
id|p
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
l_int|39
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
r_for
c_loop
(paren
id|p
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
(paren
id|action
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now free it */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq
(braket
id|irq_action
)braket
)paren
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* TODO */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_off
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|irqs
)paren
(brace
multiline_comment|/* TODO */
r_return
l_int|0
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
id|irq_setup
c_func
(paren
)paren
suffix:semicolon
)brace
eof
