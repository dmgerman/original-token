multiline_comment|/*&n; *  linux/arch/arm/kernel/irq.c&n; *&n; *  Copyright (C) 1992 Linus Torvalds&n; *  Modifications for ARM processor Copyright (C) 1995, 1996 Russell King.&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_DEBUG_ERRORS */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq-no.h&gt;
macro_line|#include &lt;asm/arch/irq.h&gt;
DECL|variable|local_irq_count
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifdef __SMP__
DECL|variable|__arm_bh_counter
id|atomic_t
id|__arm_bh_counter
suffix:semicolon
macro_line|#else
DECL|variable|__arm_bh_counter
r_int
id|__arm_bh_counter
suffix:semicolon
macro_line|#endif
DECL|variable|irq_controller_lock
id|spinlock_t
id|irq_controller_lock
suffix:semicolon
macro_line|#ifndef SMP
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)&t;(++local_irq_count[cpu])
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)&t;(--local_irq_count[cpu])
macro_line|#else
macro_line|#error SMP not supported
macro_line|#endif
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef cliIF
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cliIF
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|mask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef cliIF
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cliIF
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|unmask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|irq_action
r_struct
id|irqaction
op_star
id|irq_action
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/*&n; * Bitmask indicating valid interrupt numbers&n; */
DECL|variable|validirqs
r_int
r_int
id|validirqs
(braket
id|NR_IRQS
op_div
l_int|32
)braket
op_assign
(brace
l_int|0x003fffff
comma
l_int|0x000001ff
comma
l_int|0x000000ff
comma
l_int|0x00000000
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
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
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
id|NR_IRQS
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
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%3d: %10u   %s&quot;
comma
id|i
comma
id|kstat.interrupts
(braket
id|i
)braket
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
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;, %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; * do_IRQ handles all normal device IRQ&squot;s&n; */
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
id|status
comma
id|cpu
suffix:semicolon
macro_line|#if defined(HAS_IOMD) || defined(HAS_IOC)
r_if
c_cond
(paren
id|irq
op_ne
id|IRQ_EXPANSIONCARD
)paren
macro_line|#endif
(brace
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|mask_and_ack_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
)brace
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
comma
id|irq
)paren
suffix:semicolon
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
multiline_comment|/* Return with this interrupt masked if no action */
id|status
op_assign
l_int|0
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
r_do
(brace
id|status
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
id|status
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
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
macro_line|#if defined(HAS_IOMD) || defined(HAS_IOC)
r_if
c_cond
(paren
id|irq
op_ne
id|IRQ_KEYBOARDTX
op_logical_and
id|irq
op_ne
id|IRQ_EXPANSIONCARD
)paren
macro_line|#endif
(brace
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
)brace
)brace
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This should be conditional: we should really get&n;&t; * a return code from the irq handler to tell us&n;&t; * whether the handler wants us to do software bottom&n;&t; * half handling or not..&n;&t; *&n;&t; * ** IMPORTANT NOTE: do_bottom_half() ENABLES IRQS!!! **&n;&t; * **  WE MUST DISABLE THEM AGAIN, ELSE IDE DISKS GO   **&n;&t; * **                       AWOL                       **&n;&t; */
r_if
c_cond
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|bh_active
op_amp
id|bh_mask
)paren
id|do_bottom_half
c_func
(paren
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#if defined(HAS_IOMD) || defined(HAS_IOC)
DECL|function|do_ecard_IRQ
r_void
id|do_ecard_IRQ
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
r_do
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
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|mask_irq
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|setup_arm_irq
r_int
id|setup_arm_irq
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
id|save_flags_cli
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
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
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
multiline_comment|/*&n; * Using &quot;struct sigaction&quot; is slightly silly, but there&n; * are historical reasons and it works well, so..&n; */
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
id|irq_flags
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
id|NR_IRQS
op_logical_or
op_logical_neg
(paren
id|validirqs
(braket
id|irq
op_rshift
l_int|5
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|31
)paren
)paren
)paren
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
id|irq_flags
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
id|setup_arm_irq
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
op_ge
id|NR_IRQS
op_logical_or
op_logical_neg
(paren
id|validirqs
(braket
id|irq
op_rshift
l_int|5
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|31
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
id|save_flags_cli
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
id|restore_flags
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
id|KERN_ERR
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
multiline_comment|/* first snaffle up any unassigned irqs */
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
id|irq_action
(braket
id|i
)braket
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
l_int|1
op_lshift
id|i
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
id|HZ
op_div
l_int|10
suffix:semicolon
id|delay
OG
id|jiffies
suffix:semicolon
)paren
multiline_comment|/* min 100ms delay */
suffix:semicolon
multiline_comment|/* now filter out any obviously spurious interrupts */
r_return
id|irqs
op_amp
id|get_enabled_irqs
c_func
(paren
)paren
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
suffix:semicolon
id|irqs
op_and_assign
op_complement
id|get_enabled_irqs
c_func
(paren
)paren
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
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
)paren
(brace
id|irq_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
eof
