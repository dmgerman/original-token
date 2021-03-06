multiline_comment|/*  $Id: irq.c,v 1.109 2000/08/31 10:00:39 anton Exp $&n; *  arch/sparc/kernel/irq.c:  Interrupt request handling routines. On the&n; *                            Sparc the IRQ&squot;s are basically &squot;cast in stone&squot;&n; *                            and you are supposed to probe the prom&squot;s device&n; *                            node trees to find out who&squot;s got which IRQ.&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *  Copyright (C) 1995 Pete A. Zaitcev (zaitcev@metabyte.com)&n; *  Copyright (C) 1996 Dave Redman (djhr@tadpole.co.uk)&n; *  Copyright (C) 1998-2000 Anton Blanchard (anton@linuxcare.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/pcic.h&gt;
multiline_comment|/*&n; * Dave Redman (djhr@tadpole.co.uk)&n; *&n; * IRQ numbers.. These are no longer restricted to 15..&n; *&n; * this is done to enable SBUS cards and onboard IO to be masked&n; * correctly. using the interrupt level isn&squot;t good enough.&n; *&n; * For example:&n; *   A device interrupting at sbus level6 and the Floppy both come in&n; *   at IRQ11, but enabling and disabling them requires writing to&n; *   different bits in the SLAVIO/SEC.&n; *&n; * As a result of these changes sun4m machines could now support&n; * directed CPU interrupts using the existing enable/disable irq code&n; * with tweaks.&n; *&n; */
DECL|function|irq_panic
r_static
r_void
id|irq_panic
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
op_star
id|cputypval
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;machine: %s doesn&squot;t have irq handlers defined!&bslash;n&quot;
comma
id|cputypval
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|init_timers
r_void
(paren
op_star
id|init_timers
)paren
(paren
r_void
(paren
op_star
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
)paren
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_void
(paren
op_star
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
)paren
)paren
id|irq_panic
suffix:semicolon
multiline_comment|/*&n; * Dave Redman (djhr@tadpole.co.uk)&n; *&n; * There used to be extern calls and hard coded values here.. very sucky!&n; * instead, because some of the devices attach very early, I do something&n; * equally sucky but at least we&squot;ll never try to free statically allocated&n; * space or call kmalloc before kmalloc_init :(.&n; * &n; * In fact it&squot;s the timer10 that attaches first.. then timer14&n; * then kmalloc_init is called.. then the tty interrupts attach.&n; * hmmm....&n; *&n; */
DECL|macro|MAX_STATIC_ALLOC
mdefine_line|#define MAX_STATIC_ALLOC&t;4
DECL|variable|static_irqaction
r_struct
id|irqaction
id|static_irqaction
(braket
id|MAX_STATIC_ALLOC
)braket
suffix:semicolon
DECL|variable|static_irq_count
r_int
id|static_irq_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|irq_action
r_struct
id|irqaction
op_star
id|irq_action
(braket
id|NR_IRQS
op_plus
l_int|1
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
macro_line|#ifdef CONFIG_SMP
r_int
id|j
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
r_extern
r_int
id|sun4d_get_irq_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_return
id|sun4d_get_irq_list
c_func
(paren
id|buf
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
(paren
id|NR_IRQS
op_plus
l_int|1
)paren
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
l_string|&quot;%3d: &quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%10u &quot;
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
macro_line|#else
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|smp_num_cpus
suffix:semicolon
id|j
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%10u &quot;
comma
id|kstat.irqs
(braket
id|cpu_logical_map
c_func
(paren
id|j
)paren
)braket
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; %c %s&quot;
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
r_int
r_int
id|cpu_irq
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
r_extern
r_void
id|sun4d_free_irq
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_return
id|sun4d_free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
)brace
id|cpu_irq
op_assign
id|irq
op_amp
id|NR_IRQS
suffix:semicolon
id|action
op_assign
op_star
(paren
id|cpu_irq
op_plus
id|irq_action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_irq
OG
l_int|14
)paren
(brace
multiline_comment|/* 14 irq levels on the sparc */
id|printk
c_func
(paren
l_string|&quot;Trying to free bogus IRQ %d&bslash;n&quot;
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
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_STATIC_ALLOC
)paren
(brace
multiline_comment|/* This interrupt is marked as specially allocated&n;&t;     * so it is a bad idea to free it.&n;&t;     */
id|printk
c_func
(paren
l_string|&quot;Attempt to free statically allocated IRQ%d (%s)&bslash;n&quot;
comma
id|irq
comma
id|action-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_logical_and
id|tmp
)paren
id|tmp-&gt;next
op_assign
id|action-&gt;next
suffix:semicolon
r_else
op_star
(paren
id|cpu_irq
op_plus
id|irq_action
)paren
op_assign
id|action-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
(paren
id|cpu_irq
op_plus
id|irq_action
)paren
)paren
)paren
id|disable_irq
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
)brace
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Who has the global irq brlock */
DECL|variable|global_irq_holder
r_int
r_char
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
r_void
id|smp_show_backtrace_all_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|show_backtrace
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|VERBOSE_DEBUG_IRQLOCK
mdefine_line|#define VERBOSE_DEBUG_IRQLOCK
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 100000000
DECL|function|show
r_static
r_void
id|show
c_func
(paren
r_char
op_star
id|str
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
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s, CPU %d:&bslash;n&quot;
comma
id|str
comma
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irq:  %d [ &quot;
comma
id|irqs_running
c_func
(paren
)paren
)paren
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%u &quot;
comma
id|__brlock_array
(braket
id|i
)braket
(braket
id|BR_GLOBALIRQ_LOCK
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;]&bslash;nbh:   %d [ &quot;
comma
(paren
id|spin_is_locked
c_func
(paren
op_amp
id|global_bh_lock
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%u &quot;
comma
id|local_bh_count
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;]&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef VERBOSE_DEBUG_IRQLOCK
id|smp_show_backtrace_all_cpus
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|show_backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * We have to allow irqs to arrive between __sti and __cli&n; */
DECL|macro|SYNC_OTHER_CORES
mdefine_line|#define SYNC_OTHER_CORES(x) barrier()
multiline_comment|/*&n; * This is called when we want to synchronize with&n; * interrupts. We may for example tell a device to&n; * stop sending interrupts: but to make sure there&n; * are no interrupts that are executing on another&n; * CPU we need to call this function.&n; */
DECL|function|synchronize_irq
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|irqs_running
c_func
(paren
)paren
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_irqlock
r_static
r_inline
r_void
id|get_irqlock
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|cpu
op_eq
id|global_irq_holder
)paren
r_return
suffix:semicolon
id|count
op_assign
id|MAXCOUNT
suffix:semicolon
id|again
suffix:colon
id|br_write_lock
c_func
(paren
id|BR_GLOBALIRQ_LOCK
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|spinlock_t
op_star
id|lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irqs_running
c_func
(paren
)paren
op_logical_and
(paren
id|local_bh_count
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_logical_or
op_logical_neg
id|spin_is_locked
c_func
(paren
op_amp
id|global_bh_lock
)paren
)paren
)paren
r_break
suffix:semicolon
id|br_write_unlock
c_func
(paren
id|BR_GLOBALIRQ_LOCK
)paren
suffix:semicolon
id|lock
op_assign
op_amp
id|__br_write_locks
(braket
id|BR_GLOBALIRQ_LOCK
)braket
dot
id|lock
suffix:semicolon
r_while
c_loop
(paren
id|irqs_running
c_func
(paren
)paren
op_logical_or
id|spin_is_locked
c_func
(paren
id|lock
)paren
op_logical_or
(paren
op_logical_neg
id|local_bh_count
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_logical_and
id|spin_is_locked
c_func
(paren
op_amp
id|global_bh_lock
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
(brace
id|show
c_func
(paren
l_string|&quot;get_irqlock&quot;
)paren
suffix:semicolon
id|count
op_assign
(paren
op_complement
l_int|0
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
id|__sti
c_func
(paren
)paren
suffix:semicolon
id|SYNC_OTHER_CORES
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
)brace
r_goto
id|again
suffix:semicolon
)brace
id|global_irq_holder
op_assign
id|cpu
suffix:semicolon
)brace
multiline_comment|/*&n; * A global &quot;cli()&quot; while in an interrupt context&n; * turns into just a local cli(). Interrupts&n; * should use spinlocks for the (very unlikely)&n; * case that they ever want to protect against&n; * each other.&n; *&n; * If we already have local interrupts disabled,&n; * this will not turn a local disable into a&n; * global one (problems with spinlocks: this makes&n; * save_flags+cli+sti usable inside a spinlock).&n; */
DECL|function|__global_cli
r_void
id|__global_cli
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|PSR_PIL
)paren
op_ne
id|PSR_PIL
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
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local_irq_count
c_func
(paren
id|cpu
)paren
)paren
id|get_irqlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
)brace
DECL|function|__global_sti
r_void
id|__global_sti
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
op_logical_neg
id|local_irq_count
c_func
(paren
id|cpu
)paren
)paren
id|release_irqlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP flags value to restore to:&n; * 0 - global cli&n; * 1 - global sti&n; * 2 - local cli&n; * 3 - local sti&n; */
DECL|function|__global_save_flags
r_int
r_int
id|__global_save_flags
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
comma
id|retval
suffix:semicolon
r_int
r_int
id|local_enabled
op_assign
l_int|0
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|PSR_PIL
)paren
op_ne
id|PSR_PIL
)paren
id|local_enabled
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* default to local */
id|retval
op_assign
l_int|2
op_plus
id|local_enabled
suffix:semicolon
multiline_comment|/* check for global flags if we&squot;re not in an interrupt */
r_if
c_cond
(paren
op_logical_neg
id|local_irq_count
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|local_enabled
)paren
id|retval
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|global_irq_holder
op_eq
(paren
r_int
r_char
)paren
id|smp_processor_id
c_func
(paren
)paren
)paren
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__global_restore_flags
r_void
id|__global_restore_flags
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_switch
c_cond
(paren
id|flags
)paren
(brace
r_case
l_int|0
suffix:colon
id|__global_cli
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__global_sti
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
(brace
r_int
r_int
id|pc
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %%i7, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pc
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;global_restore_flags: Bogon flags(%08lx) caller %08lx&bslash;n&quot;
comma
id|flags
comma
id|pc
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* CONFIG_SMP */
DECL|function|unexpected_irq
r_void
id|unexpected_irq
c_func
(paren
r_int
id|irq
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
r_int
id|i
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|cpu_irq
suffix:semicolon
id|cpu_irq
op_assign
id|irq
op_amp
id|NR_IRQS
suffix:semicolon
id|action
op_assign
op_star
(paren
id|cpu_irq
op_plus
id|irq_action
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IO device interrupt, irq = %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC = %08lx NPC = %08lx FP=%08lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
comma
id|regs-&gt;u_regs
(braket
l_int|14
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Expecting: &quot;
)paren
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
r_if
c_cond
(paren
id|action-&gt;handler
)paren
id|prom_printf
c_func
(paren
l_string|&quot;[%s:%d:0x%x] &quot;
comma
id|action-&gt;name
comma
(paren
r_int
)paren
id|i
comma
(paren
r_int
r_int
)paren
id|action-&gt;handler
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;AIEEE&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;bogus interrupt received&quot;
)paren
suffix:semicolon
)brace
DECL|function|handler_irq
r_void
id|handler_irq
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
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp4m_irq_rotate
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif
id|irq_enter
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
id|disable_pil_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Only rotate on lower priority IRQ&squot;s (scsi, ethernet, etc.). */
r_if
c_cond
(paren
id|irq
OL
l_int|10
)paren
(brace
id|smp4m_irq_rotate
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#endif
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
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
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|action
op_logical_or
op_logical_neg
id|action-&gt;handler
)paren
id|unexpected_irq
c_func
(paren
id|irq
comma
l_int|0
comma
id|regs
)paren
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
id|enable_pil_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_FD
r_extern
r_void
id|floppy_interrupt
c_func
(paren
r_int
id|irq
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
suffix:semicolon
DECL|function|sparc_floppy_irq
r_void
id|sparc_floppy_irq
c_func
(paren
r_int
id|irq
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
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|disable_pil_irq
c_func
(paren
id|irq
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
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|floppy_interrupt
c_func
(paren
id|irq
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
id|enable_pil_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Fast IRQ&squot;s on the Sparc can only have one routine attached to them,&n; * thus no sharing possible.&n; */
DECL|function|request_fast_irq
r_int
id|request_fast_irq
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
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|cpu_irq
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_struct
id|tt_entry
op_star
id|trap_table
suffix:semicolon
r_extern
r_struct
id|tt_entry
id|trapbase_cpu1
comma
id|trapbase_cpu2
comma
id|trapbase_cpu3
suffix:semicolon
macro_line|#endif
id|cpu_irq
op_assign
id|irq
op_amp
id|NR_IRQS
suffix:semicolon
r_if
c_cond
(paren
id|cpu_irq
OG
l_int|14
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|action
op_assign
op_star
(paren
id|cpu_irq
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
id|action-&gt;flags
op_amp
id|SA_SHIRQ
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Trying to register fast irq when already shared.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_SHIRQ
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Trying to register fast irq as shared.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Anyway, someone already owns it so cannot be made fast. */
id|printk
c_func
(paren
l_string|&quot;request_fast_irq: Trying to register yet already owned.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* If this is flagged as statically allocated then we use our&n;&t; * private struct which is never freed.&n;&t; */
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_STATIC_ALLOC
)paren
(brace
r_if
c_cond
(paren
id|static_irq_count
OL
id|MAX_STATIC_ALLOC
)paren
id|action
op_assign
op_amp
id|static_irqaction
(braket
id|static_irq_count
op_increment
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;Fast IRQ%d (%s) SA_STATIC_ALLOC failed using kmalloc&bslash;n&quot;
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action
op_eq
l_int|NULL
)paren
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
multiline_comment|/* Dork with trap table if we get this far. */
DECL|macro|INSTANTIATE
mdefine_line|#define INSTANTIATE(table) &bslash;&n;&t;table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_one = SPARC_RD_PSR_L0; &bslash;&n;&t;table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_two = &bslash;&n;&t;&t;SPARC_BRANCH((unsigned long) handler, &bslash;&n;&t;&t;&t;     (unsigned long) &amp;table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_two);&bslash;&n;&t;table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_three = SPARC_RD_WIM_L3; &bslash;&n;&t;table[SP_TRAP_IRQ1+(cpu_irq-1)].inst_four = SPARC_NOP;
id|INSTANTIATE
c_func
(paren
id|sparc_ttable
)paren
macro_line|#ifdef CONFIG_SMP
id|trap_table
op_assign
op_amp
id|trapbase_cpu1
suffix:semicolon
id|INSTANTIATE
c_func
(paren
id|trap_table
)paren
id|trap_table
op_assign
op_amp
id|trapbase_cpu2
suffix:semicolon
id|INSTANTIATE
c_func
(paren
id|trap_table
)paren
id|trap_table
op_assign
op_amp
id|trapbase_cpu3
suffix:semicolon
id|INSTANTIATE
c_func
(paren
id|trap_table
)paren
macro_line|#endif
DECL|macro|INSTANTIATE
macro_line|#undef INSTANTIATE
multiline_comment|/*&n;&t; * XXX Correct thing whould be to flush only I- and D-cache lines&n;&t; * which contain the handler in question. But as of time of the&n;&t; * writing we have no CPU-neutral interface to fine-grained flushes.&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
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
id|action-&gt;dev_id
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
(paren
id|cpu_irq
op_plus
id|irq_action
)paren
op_assign
id|action
suffix:semicolon
id|enable_irq
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
r_int
r_int
id|cpu_irq
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
r_extern
r_int
id|sun4d_request_irq
c_func
(paren
r_int
r_int
comma
r_void
(paren
op_star
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
comma
r_const
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_return
id|sun4d_request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
)brace
id|cpu_irq
op_assign
id|irq
op_amp
id|NR_IRQS
suffix:semicolon
r_if
c_cond
(paren
id|cpu_irq
OG
l_int|14
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|cpu_irq
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
id|action
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Or else! */
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* If this is flagged as statically allocated then we use our&n;&t; * private struct which is never freed.&n;&t; */
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_STATIC_ALLOC
)paren
(brace
r_if
c_cond
(paren
id|static_irq_count
OL
id|MAX_STATIC_ALLOC
)paren
id|action
op_assign
op_amp
id|static_irqaction
(braket
id|static_irq_count
op_increment
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;Request for IRQ%d (%s) SA_STATIC_ALLOC failed using kmalloc&bslash;n&quot;
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action
op_eq
l_int|NULL
)paren
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
id|tmp-&gt;next
op_assign
id|action
suffix:semicolon
r_else
op_star
(paren
id|cpu_irq
op_plus
id|irq_action
)paren
op_assign
id|action
suffix:semicolon
id|enable_irq
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We really don&squot;t need these at all on the Sparc.  We only have&n; * stubs here because they are exported to modules.&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
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
id|mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* djhr&n; * This could probably be made indirect too and assigned in the CPU&n; * bits of the code. That would be much nicer I think and would also&n; * fit in with the idea of being able to tune your kernel for your machine&n; * by removing unrequired machine and device support.&n; *&n; */
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|sun4c_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun4m_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun4d_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_case
id|sun4
suffix:colon
id|sun4c_init_IRQ
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
macro_line|#ifdef CONFIG_PCI
id|pcic_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcic_present
c_func
(paren
)paren
)paren
(brace
id|sun4m_pci_init_IRQ
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
id|sun4m_init_IRQ
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4d
suffix:colon
id|sun4d_init_IRQ
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;Cannot initialize IRQ&squot;s on this Sun machine...&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|btfixup
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* For now, nothing... */
)brace
eof
