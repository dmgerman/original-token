multiline_comment|/*&n; *&t;linux/arch/i386/kernel/irq.c&n; *&n; *&t;Copyright (C) 1992 Linus Torvalds&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|CR0_NE
mdefine_line|#define CR0_NE 32
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
macro_line|#ifdef __SMP_PROF__
DECL|variable|int_count
r_static
r_int
r_int
id|int_count
(braket
id|NR_CPUS
)braket
(braket
id|NR_IRQS
)braket
op_assign
(brace
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|irq_nr
OL
l_int|8
)paren
(brace
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
)brace
r_else
(brace
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
)brace
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
r_if
c_cond
(paren
id|irq_nr
OL
l_int|8
)paren
(brace
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
)brace
r_else
(brace
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
)brace
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
multiline_comment|/*&n; * This builds up the IRQ handler stubs using some ugly macros in irq.h&n; *&n; * These macros create the low-level assembly IRQ routines that do all&n; * the operations that are needed to keep the AT interrupt-controller&n; * happy. They are also written to be fast - and to disable interrupts&n; * as little as humanly possible.&n; *&n; * NOTE! These macros expand to three different handlers for each line: one&n; * complete handler that does all the fancy stuff (including signal handling),&n; * and one fast handler that is meant for simple IRQ&squot;s that want to be&n; * atomic. The specific handler is chosen depending on the SA_INTERRUPT&n; * flag when installing a handler. Finally, one &quot;bad interrupt&quot; handler, that&n; * is used when no handler is present.&n; *&n; * The timer interrupt is handled specially to insure that the jiffies&n; * variable is updated at all times.  Specifically, the timer interrupt is&n; * just like the complete handlers except that it is invoked with interrupts&n; * disabled and should never re-enable them.  If other interrupts were&n; * allowed to be processed while the timer interrupt is active, then the&n; * other interrupts would have to avoid using the jiffies variable for delay&n; * and interval timing operations to avoid hanging the system.&n; */
id|BUILD_TIMER_IRQ
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
macro_line|#ifdef __SMP__
id|BUILD_SMP_INTERRUPT
c_func
(paren
id|reschedule_interrupt
)paren
id|BUILD_SMP_INTERRUPT
c_func
(paren
id|invalidate_interrupt
)paren
id|BUILD_SMP_INTERRUPT
c_func
(paren
id|stop_cpu_interrupt
)paren
macro_line|#endif
multiline_comment|/*&n; * Pointers to the low-level handlers: first the general ones, then the&n; * fast ones, then the bad ones.&n; */
DECL|variable|interrupt
r_static
r_void
(paren
op_star
id|interrupt
(braket
l_int|17
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
multiline_comment|/*&n; * Initial irq handlers.&n; */
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
multiline_comment|/*&n; * Note that on a 486, we don&squot;t want to do a SIGFPE on an irq13&n; * as the irq is unreliable, and exception 16 works correctly&n; * (ie as explained in the intel literature). On a 386, you&n; * can&squot;t use exception 16 due to bad IBM design, so we have to&n; * rely on the less exact irq13.&n; *&n; * Careful.. Not only is IRQ13 unreliable, but it is also&n; * leads to races. IBM designers who came up with it should&n; * be shot.&n; */
DECL|function|math_error_irq
r_static
r_void
id|math_error_irq
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
op_logical_or
op_logical_neg
id|hard_math
)paren
r_return
suffix:semicolon
id|math_error
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|irq13
r_static
r_struct
id|irqaction
id|irq13
op_assign
(brace
id|math_error_irq
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;math error&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * IRQ2 is cascade interrupt to second interrupt controller&n; */
DECL|variable|irq2
r_static
r_struct
id|irqaction
id|irq2
op_assign
(brace
id|no_action
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;cascade&quot;
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
l_string|&quot;%2d: %10u %c %s&quot;
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
multiline_comment|/*&n; *&t;Linus - should you add NMI counts here ?????&n; */
macro_line|#ifdef __SMP_PROF__
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;IPI: %8lu received&bslash;n&quot;
comma
id|ipi_count
)paren
suffix:semicolon
macro_line|#endif&t;&t;
r_return
id|len
suffix:semicolon
)brace
macro_line|#ifdef __SMP_PROF__
DECL|function|get_smp_prof_list
r_int
id|get_smp_prof_list
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
id|j
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
r_int
r_int
id|sum_spins
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sum_spins_syscall
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sum_spins_sys_idle
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sum_smp_idle_count
op_assign
l_int|0
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
(brace
r_int
id|cpunum
op_assign
id|cpu_logical_map
(braket
id|i
)braket
suffix:semicolon
id|sum_spins
op_add_assign
id|smp_spins
(braket
id|cpunum
)braket
suffix:semicolon
id|sum_spins_syscall
op_add_assign
id|smp_spins_syscall
(braket
id|cpunum
)braket
suffix:semicolon
id|sum_spins_sys_idle
op_add_assign
id|smp_spins_sys_idle
(braket
id|cpunum
)braket
suffix:semicolon
id|sum_smp_idle_count
op_add_assign
id|smp_idle_count
(braket
id|cpunum
)braket
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
l_string|&quot;CPUS: %10i &bslash;n&quot;
comma
id|smp_num_cpus
)paren
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
l_string|&quot;            SUM &quot;
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;        P%1d &quot;
comma
id|cpu_logical_map
(braket
id|i
)braket
)paren
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
l_string|&quot;&bslash;n&quot;
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
id|NR_IRQS
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
op_logical_or
op_logical_neg
id|action-&gt;handler
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
l_string|&quot;%3d: %10d &quot;
comma
id|i
comma
id|kstat.interrupts
(braket
id|i
)braket
)paren
suffix:semicolon
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
l_string|&quot;%10d &quot;
comma
id|int_count
(braket
id|cpu_logical_map
(braket
id|j
)braket
)braket
(braket
id|i
)braket
)paren
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
l_string|&quot;%c %s&quot;
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;LCK: %10lu&quot;
comma
id|sum_spins
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; %10lu&quot;
comma
id|smp_spins
(braket
id|cpu_logical_map
(braket
id|i
)braket
)braket
)paren
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
l_string|&quot;   spins from int&bslash;n&quot;
)paren
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
l_string|&quot;LCK: %10lu&quot;
comma
id|sum_spins_syscall
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; %10lu&quot;
comma
id|smp_spins_syscall
(braket
id|cpu_logical_map
(braket
id|i
)braket
)braket
)paren
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
l_string|&quot;   spins from syscall&bslash;n&quot;
)paren
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
l_string|&quot;LCK: %10lu&quot;
comma
id|sum_spins_sys_idle
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; %10lu&quot;
comma
id|smp_spins_sys_idle
(braket
id|cpu_logical_map
(braket
id|i
)braket
)braket
)paren
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
l_string|&quot;   spins from sysidle&bslash;n&quot;
)paren
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
l_string|&quot;IDLE %10lu&quot;
comma
id|sum_smp_idle_count
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot; %10lu&quot;
comma
id|smp_idle_count
(braket
id|cpu_logical_map
(braket
id|i
)braket
)braket
)paren
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
l_string|&quot;   idle ticks&bslash;n&quot;
)paren
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
l_string|&quot;IPI: %10lu   received&bslash;n&quot;
comma
id|ipi_count
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif 
multiline_comment|/*&n; * Global interrupt locks for SMP. Allow interrupts to come in on any&n; * CPU, yet make cli/sti act globally to protect critical regions..&n; */
macro_line|#ifdef __SMP__
DECL|variable|global_irq_holder
r_int
r_char
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
DECL|variable|global_irq_lock
r_int
r_volatile
r_int
id|global_irq_lock
suffix:semicolon
DECL|variable|global_irq_count
r_int
r_volatile
r_int
id|global_irq_count
suffix:semicolon
DECL|variable|local_irq_count
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|irq_active
mdefine_line|#define irq_active(cpu) &bslash;&n;&t;(global_irq_count != local_irq_count[cpu])
DECL|macro|INIT_STUCK
mdefine_line|#define INIT_STUCK 10000000
DECL|macro|STUCK
mdefine_line|#define STUCK(x) &bslash;&n;if (!--stuck) {printk(#x &quot; stuck at %08lx, waiting for %08lx&bslash;n&quot;, where, previous); stuck = INIT_STUCK;}
multiline_comment|/*&n; * &quot;global_cli()&quot; is a special case, in that it can hold the&n; * interrupts disabled for a longish time, and also because&n; * we may be doing TLB invalidates when holding the global&n; * IRQ lock for historical reasons. Thus we may need to check&n; * SMP invalidate events specially by hand here (but not in&n; * any normal spinlocks)&n; */
DECL|function|check_smp_invalidate
r_static
r_inline
r_void
id|check_smp_invalidate
c_func
(paren
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|cpu
comma
op_amp
id|smp_invalidate_needed
)paren
)paren
(brace
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|smp_invalidate_needed
)paren
suffix:semicolon
id|local_flush_tlb
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
comma
r_int
r_int
id|where
)paren
(brace
r_static
r_int
r_int
id|previous
suffix:semicolon
r_int
id|local_count
suffix:semicolon
r_int
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
r_if
c_cond
(paren
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
multiline_comment|/* do we already hold the lock? */
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
multiline_comment|/* Uhhuh.. Somebody else got it. Wait.. */
r_do
(brace
r_do
(brace
id|STUCK
c_func
(paren
id|irqlock1
)paren
suffix:semicolon
id|check_smp_invalidate
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ok, we got the lock bit.&n;&t; * But that&squot;s actually just the easy part.. Now&n;&t; * we need to make sure that nobody else is running&n;&t; * in an interrupt context. &n;&t; */
id|local_count
op_assign
id|local_irq_count
(braket
id|cpu
)braket
suffix:semicolon
multiline_comment|/* Are we the only one in an interrupt context? */
r_while
c_loop
(paren
id|local_count
op_ne
id|global_irq_count
)paren
(brace
multiline_comment|/*&n;&t;&t; * No such luck. Now we need to release the lock,&n;&t;&t; * _and_ release our interrupt context, because&n;&t;&t; * otherwise we&squot;d have dead-locks and live-locks&n;&t;&t; * and other fun things.&n;&t;&t; */
id|atomic_sub
c_func
(paren
id|local_count
comma
op_amp
id|global_irq_count
)paren
suffix:semicolon
id|global_irq_lock
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Wait for everybody else to go away and release&n;&t;&t; * their things before trying to get the lock again.&n;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|STUCK
c_func
(paren
id|irqlock2
)paren
suffix:semicolon
id|check_smp_invalidate
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|global_irq_count
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|global_irq_lock
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
r_break
suffix:semicolon
)brace
id|atomic_add
c_func
(paren
id|local_count
comma
op_amp
id|global_irq_count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Finally.&n;&t; */
id|global_irq_holder
op_assign
id|cpu
suffix:semicolon
id|previous
op_assign
id|where
suffix:semicolon
)brace
DECL|function|__global_cli
r_void
id|__global_cli
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
r_int
r_int
id|where
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl 12(%%esp),%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|where
)paren
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|get_irqlock
c_func
(paren
id|cpu
comma
id|where
)paren
suffix:semicolon
)brace
DECL|function|__global_sti
r_void
id|__global_sti
c_func
(paren
r_void
)paren
(brace
id|release_irqlock
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__global_save_flags
r_int
r_int
id|__global_save_flags
c_func
(paren
r_void
)paren
(brace
r_return
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
id|__global_sti
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__global_cli
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;global_restore_flags: %08lx (%08lx)&bslash;n&quot;
comma
id|flags
comma
(paren
op_amp
id|flags
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|macro|INIT_STUCK
macro_line|#undef INIT_STUCK
DECL|macro|INIT_STUCK
mdefine_line|#define INIT_STUCK 200000000
DECL|macro|STUCK
macro_line|#undef STUCK
DECL|macro|STUCK
mdefine_line|#define STUCK &bslash;&n;if (!--stuck) {printk(&quot;irq_enter stuck (irq=%d, cpu=%d, global=%d)&bslash;n&quot;,irq,cpu,global_irq_holder); stuck = INIT_STUCK;}
DECL|function|irq_enter
r_static
r_inline
r_void
id|irq_enter
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
r_int
id|stuck
op_assign
id|INIT_STUCK
suffix:semicolon
id|hardirq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
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
(brace
id|printk
c_func
(paren
l_string|&quot;BAD! Local interrupts enabled, global disabled&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|STUCK
suffix:semicolon
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|intr_count
)paren
suffix:semicolon
)brace
DECL|function|irq_exit
r_static
r_inline
r_void
id|irq_exit
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|intr_count
)paren
suffix:semicolon
id|hardirq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|release_irqlock
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)&t;do { } while (0)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)&t;do { } while (0)
macro_line|#endif
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
multiline_comment|/* slow interrupts run with interrupts enabled */
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
r_while
c_loop
(paren
id|action
)paren
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
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
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
suffix:semicolon
r_int
id|do_random
comma
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
r_while
c_loop
(paren
id|action
)paren
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
l_int|NULL
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
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
id|irq_exit
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|setup_x86_irq
r_int
id|setup_x86_irq
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
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
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
id|setup_x86_irq
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
(brace
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
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
)brace
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
multiline_comment|/* first, enable any unassigned irqs */
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
id|HZ
op_div
l_int|10
suffix:semicolon
id|delay
OG
id|jiffies
suffix:semicolon
)paren
multiline_comment|/* about 100ms delay */
suffix:semicolon
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
r_return
id|irqs
op_amp
op_complement
id|irqmask
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
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;probe_irq_off: irqs=0x%04lx irqmask=0x%04x&bslash;n&quot;
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
r_static
r_int
r_char
id|smptrap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|smptrap
)paren
(brace
r_return
suffix:semicolon
)brace
id|smptrap
op_assign
l_int|1
suffix:semicolon
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
multiline_comment|/* This bit is a hack because we don&squot;t send timer messages to all processors yet */
multiline_comment|/* It has to be here .. it doesn&squot;t work if you put it down the bottom - assembler explodes 8) */
macro_line|#ifdef __SMP__&t;
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|i
comma
id|reschedule_interrupt
)paren
suffix:semicolon
multiline_comment|/* IRQ &squot;16&squot; - IPI for rescheduling */
id|set_intr_gate
c_func
(paren
l_int|0x21
op_plus
id|i
comma
id|invalidate_interrupt
)paren
suffix:semicolon
multiline_comment|/* IRQ &squot;17&squot; - IPI for invalidation */
id|set_intr_gate
c_func
(paren
l_int|0x22
op_plus
id|i
comma
id|stop_cpu_interrupt
)paren
suffix:semicolon
multiline_comment|/* IRQ &squot;18&squot; - IPI for CPU halt */
macro_line|#endif&t;
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|setup_x86_irq
c_func
(paren
l_int|2
comma
op_amp
id|irq2
)paren
suffix:semicolon
id|setup_x86_irq
c_func
(paren
l_int|13
comma
op_amp
id|irq13
)paren
suffix:semicolon
)brace
eof
