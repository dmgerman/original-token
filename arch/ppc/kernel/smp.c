multiline_comment|/*&n; * $Id: smp.c,v 1.68 1999/09/17 19:38:05 cort Exp $&n; *&n; * Smp support for ppc.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great&n; * deal of code from the sparc and intel versions.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; * Support for PReP (Motorola MTX/MVME) SMP by Troy Benjegerdes&n; * (troy@microux.com, hozer@drgw.net)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/gemini.h&gt;
macro_line|#include &quot;time.h&quot;
macro_line|#include &quot;open_pic.h&quot;
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
op_assign
l_int|0
suffix:semicolon
DECL|variable|smp_commenced
r_volatile
r_int
id|smp_commenced
op_assign
l_int|0
suffix:semicolon
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
DECL|variable|cpu_data
r_struct
id|cpuinfo_PPC
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|klock_info
r_struct
id|klock_info_struct
id|klock_info
op_assign
(brace
id|KLOCK_CLEAR
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|active_kernel_processor
r_volatile
r_int
r_char
id|active_kernel_processor
op_assign
id|NO_PROC_ID
suffix:semicolon
multiline_comment|/* Processor holding kernel spinlock&t;&t;*/
DECL|variable|ipi_count
r_volatile
r_int
r_int
id|ipi_count
suffix:semicolon
DECL|variable|kernel_flag
id|spinlock_t
id|kernel_flag
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|prof_multiplier
r_int
r_int
id|prof_multiplier
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|prof_counter
r_int
r_int
id|prof_counter
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cacheflush_time
id|cycles_t
id|cacheflush_time
suffix:semicolon
multiline_comment|/* all cpu mappings are 1-1 -- Cort */
DECL|variable|cpu_number_map
r_int
id|cpu_number_map
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
)brace
suffix:semicolon
DECL|variable|cpu_callin_map
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
r_int
id|start_secondary
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
suffix:semicolon
id|u_int
id|openpic_read
c_func
(paren
r_volatile
id|u_int
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* register for interrupting the secondary processor on the powersurge */
DECL|macro|PSURGE_INTR
mdefine_line|#define PSURGE_INTR&t;((volatile unsigned *)0xf80000c0)
DECL|function|smp_local_timer_interrupt
r_void
id|smp_local_timer_interrupt
c_func
(paren
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
r_extern
r_void
id|update_one_process
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|prof_counter
(braket
id|cpu
)braket
)paren
(brace
r_int
id|user
op_assign
l_int|0
comma
id|system
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
op_assign
id|current
suffix:semicolon
multiline_comment|/*&n;&t;&t; * After doing the above, we need to make like&n;&t;&t; * a normal interrupt - otherwise timer interrupts&n;&t;&t; * ignore the global interrupt lock, which is the&n;&t;&t; * WrongThing (tm) to do.&n;&t;&t; */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|user
op_assign
l_int|1
suffix:semicolon
r_else
id|system
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pid
)paren
(brace
id|update_one_process
c_func
(paren
id|p
comma
l_int|1
comma
id|user
comma
id|system
comma
id|cpu
)paren
suffix:semicolon
id|p-&gt;counter
op_sub_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;counter
op_le
l_int|0
)paren
(brace
id|p-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|current-&gt;need_resched
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;priority
OL
id|DEF_PRIORITY
)paren
(brace
id|kstat.cpu_nice
op_add_assign
id|user
suffix:semicolon
id|kstat.per_cpu_nice
(braket
id|cpu
)braket
op_add_assign
id|user
suffix:semicolon
)brace
r_else
(brace
id|kstat.cpu_user
op_add_assign
id|user
suffix:semicolon
id|kstat.per_cpu_user
(braket
id|cpu
)braket
op_add_assign
id|user
suffix:semicolon
)brace
id|kstat.cpu_system
op_add_assign
id|system
suffix:semicolon
id|kstat.per_cpu_system
(braket
id|cpu
)braket
op_add_assign
id|system
suffix:semicolon
)brace
id|prof_counter
(braket
id|cpu
)braket
op_assign
id|prof_multiplier
(braket
id|cpu
)braket
suffix:semicolon
)brace
)brace
DECL|function|smp_message_recv
r_void
id|smp_message_recv
c_func
(paren
r_int
id|msg
)paren
(brace
id|ipi_count
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|msg
)paren
(brace
r_case
id|MSG_STOP_CPU
suffix:colon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MSG_RESCHEDULE
suffix:colon
id|current-&gt;need_resched
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MSG_INVALIDATE_TLB
suffix:colon
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
r_case
l_int|0xf0f0
suffix:colon
multiline_comment|/* pmac syncing time bases - just return */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SMP %d: smp_message_recv(): unknown msg %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * As it is now, if we&squot;re sending two message at the same time&n; * we have race conditions on Pmac.  The PowerSurge doesn&squot;t easily&n; * allow us to send IPI messages so we put the messages in&n; * smp_message[].&n; *&n; * This is because don&squot;t have several IPI&squot;s on the PowerSurge even though&n; * we do on the chrp.  It would be nice to use actual IPI&squot;s such as with openpic&n; * rather than this.&n; *  -- Cort&n; */
DECL|variable|pmac_smp_message
r_int
id|pmac_smp_message
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|pmac_smp_message_recv
r_void
id|pmac_smp_message_recv
c_func
(paren
r_void
)paren
(brace
r_int
id|msg
op_assign
id|pmac_smp_message
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
multiline_comment|/* clear interrupt */
id|out_be32
c_func
(paren
id|PSURGE_INTR
comma
op_complement
l_int|0
)paren
suffix:semicolon
multiline_comment|/* make sure msg is for us */
r_if
c_cond
(paren
id|msg
op_eq
op_minus
l_int|1
)paren
r_return
suffix:semicolon
id|smp_message_recv
c_func
(paren
id|msg
)paren
suffix:semicolon
multiline_comment|/* reset message */
id|pmac_smp_message
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * 750&squot;s don&squot;t broadcast tlb invalidates so&n; * we have to emulate that behavior.&n; *   -- Cort&n; */
DECL|function|smp_send_tlb_invalidate
r_void
id|smp_send_tlb_invalidate
c_func
(paren
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_eq
l_int|8
)paren
id|smp_message_pass
c_func
(paren
id|MSG_ALL_BUT_SELF
comma
id|MSG_INVALIDATE_TLB
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/*&n;&t; * This is only used if `cpu&squot; is running an idle task,&n;&t; * so it will reschedule itself anyway...&n;&t; *&n;&t; * This isn&squot;t the case anymore since the other CPU could be&n;&t; * sleeping and won&squot;t reschedule until the next interrupt (such&n;&t; * as the timer).&n;&t; *  -- Cort&n;&t; */
multiline_comment|/* This is only used if `cpu&squot; is running an idle task,&n;&t;   so it will reschedule itself anyway... */
id|smp_message_pass
c_func
(paren
id|cpu
comma
id|MSG_RESCHEDULE
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_send_stop
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
id|smp_message_pass
c_func
(paren
id|MSG_ALL_BUT_SELF
comma
id|MSG_STOP_CPU
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_message_pass
r_void
id|smp_message_pass
c_func
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|_machine
op_amp
(paren
id|_MACH_Pmac
op_or
id|_MACH_chrp
op_or
id|_MACH_prep
op_or
id|_MACH_gemini
)paren
)paren
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|_machine
)paren
(brace
r_case
id|_MACH_Pmac
suffix:colon
multiline_comment|/*&n;&t;&t; * IPI&squot;s on the Pmac are a hack but without reasonable&n;&t;&t; * IPI hardware SMP on Pmac is a hack.&n;&t;&t; *&n;&t;&t; * We assume here that the msg is not -1.  If it is,&n;&t;&t; * the recipient won&squot;t know the message was destined&n;&t;&t; * for it. -- Cort&n;&t;&t; */
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
id|pmac_smp_message
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|target
)paren
(brace
r_case
id|MSG_ALL
suffix:colon
id|pmac_smp_message
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
id|msg
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|MSG_ALL_BUT_SELF
suffix:colon
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
r_if
c_cond
(paren
id|i
op_ne
id|smp_processor_id
(paren
)paren
)paren
id|pmac_smp_message
(braket
id|i
)braket
op_assign
id|msg
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pmac_smp_message
(braket
id|target
)braket
op_assign
id|msg
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* interrupt secondary processor */
id|out_be32
c_func
(paren
id|PSURGE_INTR
comma
op_complement
l_int|0
)paren
suffix:semicolon
id|out_be32
c_func
(paren
id|PSURGE_INTR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Assume for now that the secondary doesn&squot;t send&n;&t;&t; * IPI&squot;s -- Cort&n;&t;&t; */
multiline_comment|/* interrupt primary */
multiline_comment|/**(volatile unsigned long *)(0xf3019000);*/
r_break
suffix:semicolon
r_case
id|_MACH_chrp
suffix:colon
r_case
id|_MACH_prep
suffix:colon
r_case
id|_MACH_gemini
suffix:colon
multiline_comment|/* make sure we&squot;re sending something that translates to an IPI */
r_if
c_cond
(paren
id|msg
OG
l_int|0x3
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|target
)paren
(brace
r_case
id|MSG_ALL
suffix:colon
id|openpic_cause_IPI
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
comma
l_int|0xffffffff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MSG_ALL_BUT_SELF
suffix:colon
id|openpic_cause_IPI
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
comma
l_int|0xffffffff
op_amp
op_complement
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|openpic_cause_IPI
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
comma
l_int|1
op_lshift
id|target
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|smp_boot_cpus
r_void
id|__init
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_extern
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|smp_chrp_cpu_nr
suffix:semicolon
r_extern
r_void
id|__secondary_start_psurge
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__secondary_start_chrp
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|i
comma
id|cpu_nr
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|a
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Entering SMP Mode...&bslash;n&quot;
)paren
suffix:semicolon
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * assume for now that the first cpu booted is&n;&t; * cpu 0, the master -- Cort&n;&t; */
id|cpu_callin_map
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|active_kernel_processor
op_assign
l_int|0
suffix:semicolon
id|current-&gt;processor
op_assign
l_int|0
suffix:semicolon
id|init_idle
c_func
(paren
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|prof_counter
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|prof_multiplier
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * XXX very rough, assumes 20 bus cycles to read a cache line,&n;&t; * timebase increments every 4 bus cycles, 32kB L1 data cache.&n;&t; */
id|cacheflush_time
op_assign
l_int|5
op_star
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|_machine
op_amp
(paren
id|_MACH_Pmac
op_or
id|_MACH_chrp
op_or
id|_MACH_gemini
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SMP not supported on this machine.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|_machine
)paren
(brace
r_case
id|_MACH_Pmac
suffix:colon
multiline_comment|/* assume powersurge board - 2 processors -- Cort */
id|cpu_nr
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_chrp
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|openpic_enable_IPI
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpu_nr
op_assign
id|smp_chrp_cpu_nr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_gemini
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|openpic_enable_IPI
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpu_nr
op_assign
(paren
id|readb
c_func
(paren
id|GEMINI_CPUSTAT
)paren
op_amp
id|GEMINI_CPU_COUNT_MASK
)paren
op_rshift
l_int|2
suffix:semicolon
id|cpu_nr
op_assign
(paren
id|cpu_nr
op_eq
l_int|0
)paren
ques
c_cond
l_int|4
suffix:colon
id|cpu_nr
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * only check for cpus we know exist.  We keep the callin map&n;&t; * with cpus at the bottom -- Cort&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|cpu_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|c
suffix:semicolon
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/* create a process for the processor */
multiline_comment|/* we don&squot;t care about the values in regs since we&squot;ll&n;&t;&t;   never reschedule the forked task. */
r_if
c_cond
(paren
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_PID
comma
l_int|0
comma
op_amp
id|regs
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;failed fork for CPU %d&quot;
comma
id|i
)paren
suffix:semicolon
id|p
op_assign
id|init_task.prev_task
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|panic
c_func
(paren
l_string|&quot;No idle task for CPU %d&quot;
comma
id|i
)paren
suffix:semicolon
id|del_from_runqueue
c_func
(paren
id|p
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|p
)paren
suffix:semicolon
id|init_tasks
(braket
id|i
)braket
op_assign
id|p
suffix:semicolon
id|p-&gt;processor
op_assign
id|i
suffix:semicolon
id|p-&gt;has_cpu
op_assign
l_int|1
suffix:semicolon
id|current_set
(braket
id|i
)braket
op_assign
id|p
suffix:semicolon
multiline_comment|/* need to flush here since secondary bats aren&squot;t setup */
r_for
c_loop
(paren
id|a
op_assign
id|KERNELBASE
suffix:semicolon
id|a
OL
id|KERNELBASE
op_plus
l_int|0x800000
suffix:semicolon
id|a
op_add_assign
l_int|32
)paren
id|asm
r_volatile
(paren
l_string|&quot;dcbf 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
multiline_comment|/* wake up cpus */
r_switch
c_cond
(paren
id|_machine
)paren
(brace
r_case
id|_MACH_Pmac
suffix:colon
multiline_comment|/* setup entry point of secondary processor */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
l_int|0xf2800000
)paren
op_assign
(paren
r_int
r_int
)paren
id|__secondary_start_psurge
op_minus
id|KERNELBASE
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* interrupt secondary to begin executing code */
id|out_be32
c_func
(paren
id|PSURGE_INTR
comma
op_complement
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|out_be32
c_func
(paren
id|PSURGE_INTR
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_chrp
suffix:colon
op_star
(paren
r_int
r_int
op_star
)paren
id|KERNELBASE
op_assign
id|i
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcbf 0,%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|KERNELBASE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_gemini
suffix:colon
id|openpic_init_processor
c_func
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|openpic_init_processor
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * wait to see if the cpu made a callin (is actually up).&n;&t;&t; * use this value that I found through experimentation.&n;&t;&t; * -- Cort&n;&t;&t; */
r_for
c_loop
(paren
id|c
op_assign
l_int|1000
suffix:semicolon
id|c
op_logical_and
op_logical_neg
id|cpu_callin_map
(braket
id|i
)braket
suffix:semicolon
id|c
op_decrement
)paren
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_callin_map
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Processor %d found.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* this sync&squot;s the decr&squot;s -- Cort */
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
id|set_dec
c_func
(paren
id|decrementer_count
)paren
suffix:semicolon
id|smp_num_cpus
op_increment
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Processor %d is stuck.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|_machine
op_amp
(paren
id|_MACH_gemini
op_or
id|_MACH_chrp
op_or
id|_MACH_prep
)paren
)paren
id|do_openpic_setup_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
(brace
multiline_comment|/* reset the entry point so if we get another intr we won&squot;t&n;&t;&t; * try to startup again */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
l_int|0xf2800000
)paren
op_assign
l_int|0x100
suffix:semicolon
multiline_comment|/* send interrupt to other processors to start decr&squot;s on all cpus */
id|smp_message_pass
c_func
(paren
l_int|1
comma
l_int|0xf0f0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_commence
r_void
id|__init
id|smp_commence
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Lets the callin&squot;s below out of their loop.&n;&t; */
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|smp_commenced
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* intel needs this */
DECL|function|initialize_secondary
r_void
id|__init
id|initialize_secondary
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Activate a secondary processor. */
DECL|function|start_secondary
r_int
id|__init
id|start_secondary
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|smp_callin
c_func
(paren
)paren
suffix:semicolon
r_return
id|cpu_idle
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|smp_callin
r_void
id|__init
id|smp_callin
c_func
(paren
r_void
)paren
(brace
id|smp_store_cpu_info
c_func
(paren
id|current-&gt;processor
)paren
suffix:semicolon
id|set_dec
c_func
(paren
id|decrementer_count
)paren
suffix:semicolon
id|init_idle
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
id|current-&gt;mm-&gt;mmap-&gt;vm_page_prot
op_assign
id|PAGE_SHARED
suffix:semicolon
id|current-&gt;mm-&gt;mmap-&gt;vm_start
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|current-&gt;mm-&gt;mmap-&gt;vm_end
op_assign
id|init_mm.mmap-&gt;vm_end
suffix:semicolon
macro_line|#endif
id|cpu_callin_map
(braket
id|current-&gt;processor
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Each processor has to do this and this is the best&n;&t; * place to stick it for now.&n;&t; *  -- Cort&n;&t; */
r_if
c_cond
(paren
id|_machine
op_amp
(paren
id|_MACH_gemini
op_or
id|_MACH_chrp
op_or
id|_MACH_prep
)paren
)paren
id|do_openpic_setup_cpu
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|smp_commenced
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_setup
r_void
id|__init
id|smp_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
)brace
DECL|function|setup_profiling_timer
r_int
id|__init
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_store_cpu_info
r_void
id|__init
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
(brace
r_struct
id|cpuinfo_PPC
op_star
id|c
op_assign
op_amp
id|cpu_data
(braket
id|id
)braket
suffix:semicolon
multiline_comment|/* assume bogomips are same for everything */
id|c-&gt;loops_per_sec
op_assign
id|loops_per_sec
suffix:semicolon
id|c-&gt;pvr
op_assign
id|_get_PVR
c_func
(paren
)paren
suffix:semicolon
)brace
eof
