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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
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
macro_line|#ifdef __SMP__
id|BUILD_MSGIRQ
c_func
(paren
id|SECOND
comma
l_int|13
comma
l_int|0x20
)paren
macro_line|#else
id|BUILD_IRQ
c_func
(paren
id|SECOND
comma
l_int|13
comma
l_int|0x20
)paren
macro_line|#endif
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
id|BUILD_RESCHEDIRQ
c_func
(paren
l_int|16
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
macro_line|#ifdef __SMP__&t;
comma
id|IRQ16_interrupt
macro_line|#endif
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
op_le
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sum_spins
op_add_assign
id|smp_spins
(braket
id|i
)braket
suffix:semicolon
id|sum_spins_syscall
op_add_assign
id|smp_spins_syscall
(braket
id|i
)braket
suffix:semicolon
id|sum_spins_sys_idle
op_add_assign
id|smp_spins_sys_idle
(braket
id|i
)braket
suffix:semicolon
id|sum_smp_idle_count
op_add_assign
id|smp_idle_count
(braket
id|i
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
l_int|0
op_eq
id|smp_num_cpus
ques
c_cond
l_int|1
suffix:colon
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
id|i
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
id|j
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
l_string|&quot;%c %s&bslash;n&quot;
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
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|smp_threads_ready
op_logical_and
id|active_kernel_processor
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;IRQ %d: active processor set wrongly(%d not %d).&bslash;n&quot;
comma
id|irq
comma
id|active_kernel_processor
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
macro_line|#ifdef __SMP_PROF__
id|int_count
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|action
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
(brace
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef __SMP__
multiline_comment|/* IRQ 13 is allowed - thats an invalidate */
r_if
c_cond
(paren
id|smp_threads_ready
op_logical_and
id|active_kernel_processor
op_ne
id|smp_processor_id
c_func
(paren
)paren
op_logical_and
id|irq
op_ne
l_int|13
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;fast_IRQ %d: active processor set wrongly(%d not %d).&bslash;n&quot;
comma
id|irq
comma
id|active_kernel_processor
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|kstat.interrupts
(braket
id|irq
)braket
op_increment
suffix:semicolon
macro_line|#ifdef __SMP_PROF__
id|int_count
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|action
)paren
(brace
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
r_if
c_cond
(paren
id|action-&gt;flags
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
)brace
macro_line|#ifndef __SMP__
multiline_comment|/*&n; * Note that on a 486, we don&squot;t want to do a SIGFPE on a irq13&n; * as the irq is unreliable, and exception 16 works correctly&n; * (ie as explained in the intel literature). On a 386, you&n; * can&squot;t use exception 16 due to bad IBM design, so we have to&n; * rely on the less exact irq13.&n; *&n; * Careful.. Not only is IRQ13 unreliable, but it is also&n; * leads to races. IBM designers who came up with it should&n; * be shot.&n; */
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
macro_line|#endif
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
multiline_comment|/* It has to here .. it doesnt work if you put it down the bottom - assembler explodes 8) */
macro_line|#ifdef __SMP__&t;
id|set_intr_gate
c_func
(paren
l_int|0x20
op_plus
id|i
comma
id|interrupt
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* IRQ &squot;16&squot; - IPI for rescheduling */
macro_line|#endif&t;
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
l_string|&quot;Unable to get IRQ2 for cascade.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifndef __SMP__&t;&t;
r_if
c_cond
(paren
id|request_irq
c_func
(paren
l_int|13
comma
id|math_error_irq
comma
l_int|0
comma
l_string|&quot;math error&quot;
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Unable to get IRQ13 for math-error handler.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|request_irq
c_func
(paren
l_int|13
comma
id|smp_message_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;IPI&quot;
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Unable to get IRQ13 for IPI.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
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
)brace
eof
