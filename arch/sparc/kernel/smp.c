multiline_comment|/* smp.c: Sparc SMP support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
suffix:semicolon
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
suffix:semicolon
DECL|variable|smp_msg_data
r_volatile
r_int
r_int
id|smp_msg_data
suffix:semicolon
DECL|variable|smp_src_cpu
r_volatile
r_int
id|smp_src_cpu
suffix:semicolon
DECL|variable|smp_msg_id
r_volatile
r_int
id|smp_msg_id
suffix:semicolon
DECL|variable|smp_commenced
r_static
r_volatile
r_int
id|smp_commenced
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The only guarenteed locking primitive available on all Sparc&n; * processors is &squot;ldstub [%addr_reg + imm], %dest_reg&squot; which atomicly&n; * places the current byte at the effective address into dest_reg and&n; * places 0xff there afterwards.  Pretty lame locking primitive&n; * compared to the Alpha and the intel no?  Most Sparcs have &squot;swap&squot;&n; * instruction which is muct better...&n; */
DECL|variable|kernel_lock
id|klock_t
id|kernel_lock
suffix:semicolon
DECL|function|smp_commence
r_void
id|smp_commence
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Lets the callin&squot;s below out of their loop.&n;&t; */
id|smp_commenced
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|smp_callin
r_void
id|smp_callin
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
op_assign
id|smp_get_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX Clear the software interrupts _HERE_. */
id|sti
c_func
(paren
)paren
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|cpuid
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|cpu_callin_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|local_invalidate_all
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
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_number_map
(braket
id|cpuid
)braket
op_eq
op_minus
l_int|1
)paren
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
id|local_invalidate_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_boot_cpus
r_void
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
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
r_struct
id|sparc_ipimsg
op_star
id|msg
op_assign
(paren
r_struct
id|sparc_ipimsg
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|target_map
suffix:semicolon
r_int
id|p
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_static
r_volatile
r_int
id|message_cpu
op_assign
id|NO_PROC_ID
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smp_activated
op_logical_or
op_logical_neg
id|smp_commenced
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|msg
op_eq
id|MSG_RESCHEDULE
)paren
(brace
r_if
c_cond
(paren
id|smp_cpu_in_msg
(braket
id|p
)braket
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|message_cpu
op_ne
id|NO_PROC_ID
op_logical_and
id|msg
op_ne
id|MSG_STOP_CPU
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;CPU #%d: Message pass %d but pass in progress by %d of %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|msg
comma
id|message_cpu
comma
id|smp_msg_id
)paren
suffix:semicolon
)brace
id|message_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|smp_cpu_in_msg
(braket
id|p
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_ne
id|MSG_RESCHEDULE
)paren
(brace
id|smp_src_cpu
op_assign
id|p
suffix:semicolon
id|smp_msg_id
op_assign
id|msg
suffix:semicolon
id|smp_msg_data
op_assign
id|data
suffix:semicolon
)brace
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL_BUT_SELF
)paren
(brace
id|target_map
op_assign
id|cpu_present_map
suffix:semicolon
id|cpu_callin_map
(braket
l_int|0
)braket
op_assign
(paren
l_int|1
op_lshift
id|smp_src_cpu
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|target
op_eq
id|MSG_ALL
)paren
(brace
id|target_map
op_assign
id|cpu_present_map
suffix:semicolon
id|cpu_callin_map
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|target_map
op_assign
(paren
l_int|1
op_lshift
id|target
)paren
suffix:semicolon
id|cpu_callin_map
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* XXX Send lvl15 soft interrupt to cpus here XXX */
r_switch
c_cond
(paren
id|wait
)paren
(brace
r_case
l_int|1
suffix:colon
r_while
c_loop
(paren
id|cpu_callin_map
(braket
l_int|0
)braket
op_ne
id|target_map
)paren
(brace
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_while
c_loop
(paren
id|smp_invalidate_needed
)paren
(brace
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|smp_cpu_in_msg
(braket
id|p
)braket
op_decrement
suffix:semicolon
id|message_cpu
op_assign
id|NO_PROC_ID
suffix:semicolon
)brace
DECL|function|smp_invalidate
r_inline
r_void
id|smp_invalidate
c_func
(paren
r_int
id|type
comma
r_int
r_int
id|a
comma
r_int
r_int
id|b
comma
r_int
r_int
id|c
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|smp_invalidate_needed
op_assign
id|cpu_present_map
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
id|smp_message_pass
c_func
(paren
id|MSG_ALL_BUT_SELF
comma
id|MSG_INVALIDATE_TLB
comma
l_int|0L
comma
l_int|2
)paren
suffix:semicolon
id|local_invalidate
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|smp_invalidate_all
r_void
id|smp_invalidate_all
c_func
(paren
r_void
)paren
(brace
id|smp_invalidate
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_invalidate_mm
r_void
id|smp_invalidate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|smp_invalidate
c_func
(paren
l_int|1
comma
(paren
r_int
r_int
)paren
id|mm
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_invalidate_range
r_void
id|smp_invalidate_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|smp_invalidate
c_func
(paren
l_int|2
comma
(paren
r_int
r_int
)paren
id|mm
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
DECL|function|smp_invalidate_page
r_void
id|smp_invalidate_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vmap
comma
r_int
r_int
id|page
)paren
(brace
id|smp_invalidate
c_func
(paren
l_int|3
comma
(paren
r_int
r_int
)paren
id|vmap-&gt;vm_mm
comma
id|page
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|smp_reschedule_irq
r_void
id|smp_reschedule_irq
c_func
(paren
r_int
id|cpl
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|active_kernel_processor
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;SMP Reschedule on CPU #%d, but #%d is active.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|active_kernel_processor
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|current-&gt;utime
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;priority
OL
l_int|15
)paren
id|kstat.cpu_nice
op_increment
suffix:semicolon
r_else
id|kstat.cpu_user
op_increment
suffix:semicolon
)brace
multiline_comment|/* Update ITIMER_VIRT for current task if not in a system call */
r_if
c_cond
(paren
id|current-&gt;it_virt_value
op_logical_and
op_logical_neg
(paren
op_decrement
id|current-&gt;it_virt_value
)paren
)paren
(brace
id|current-&gt;it_virt_value
op_assign
id|current-&gt;it_virt_incr
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGVTALRM
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|current-&gt;stime
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
)paren
(brace
id|kstat.cpu_system
op_increment
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROFILE
r_if
c_cond
(paren
id|prof_buffer
op_logical_and
id|current-&gt;pid
)paren
(brace
r_extern
r_int
id|_stext
suffix:semicolon
r_int
r_int
id|eip
op_assign
id|regs-&gt;eip
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|eip
op_rshift_assign
id|CONFIG_PROFILE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|eip
OL
id|prof_len
)paren
id|prof_buffer
(braket
id|eip
)braket
op_increment
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n;&t; * check the cpu time limit on the process.&n;&t; */
r_if
c_cond
(paren
(paren
id|current-&gt;rlim
(braket
id|RLIMIT_CPU
)braket
dot
id|rlim_max
op_ne
id|RLIM_INFINITY
)paren
op_logical_and
(paren
(paren
(paren
id|current-&gt;stime
op_plus
id|current-&gt;utime
)paren
op_div
id|HZ
)paren
op_ge
id|current-&gt;rlim
(braket
id|RLIMIT_CPU
)braket
dot
id|rlim_max
)paren
)paren
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;rlim
(braket
id|RLIMIT_CPU
)braket
dot
id|rlim_cur
op_ne
id|RLIM_INFINITY
)paren
op_logical_and
(paren
(paren
(paren
id|current-&gt;stime
op_plus
id|current-&gt;utime
)paren
op_mod
id|HZ
)paren
op_eq
l_int|0
)paren
)paren
(brace
r_int
r_int
id|psecs
op_assign
(paren
id|current-&gt;stime
op_plus
id|current-&gt;utime
)paren
op_div
id|HZ
suffix:semicolon
multiline_comment|/* send when equal */
r_if
c_cond
(paren
id|psecs
op_eq
id|current-&gt;rlim
(braket
id|RLIMIT_CPU
)braket
dot
id|rlim_cur
)paren
id|send_sig
c_func
(paren
id|SIGXCPU
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* and every five seconds thereafter. */
r_else
r_if
c_cond
(paren
(paren
id|psecs
OG
id|current-&gt;rlim
(braket
id|RLIMIT_CPU
)braket
dot
id|rlim_cur
)paren
op_logical_and
(paren
(paren
id|psecs
op_minus
id|current-&gt;rlim
(braket
id|RLIMIT_CPU
)braket
dot
id|rlim_cur
)paren
op_mod
l_int|5
)paren
op_eq
l_int|0
)paren
id|send_sig
c_func
(paren
id|SIGXCPU
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Update ITIMER_PROF for the current task */
r_if
c_cond
(paren
id|current-&gt;it_prof_value
op_logical_and
op_logical_neg
(paren
op_decrement
id|current-&gt;it_prof_value
)paren
)paren
(brace
id|current-&gt;it_prof_value
op_assign
id|current-&gt;it_prof_incr
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGPROF
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
OG
op_decrement
id|current-&gt;counter
op_logical_or
id|current-&gt;pid
op_eq
l_int|0
)paren
(brace
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|smp_message_irq
r_void
id|smp_message_irq
c_func
(paren
r_int
id|cpl
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&t;static int n=0;&n;&t;if(n++&lt;NR_CPUS)&n;&t;&t;printk(&quot;IPI %d-&gt;%d(%d,%ld)&bslash;n&quot;,smp_src_cpu,i,smp_msg_id,smp_msg_data);*/
r_switch
c_cond
(paren
id|smp_msg_id
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* IRQ 13 testing - boring */
r_return
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;A TLB flush is needed.&n;&t;&t; */
r_case
id|MSG_INVALIDATE_TLB
suffix:colon
r_if
c_cond
(paren
id|clear_bit
c_func
(paren
id|i
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|smp_invalidate_needed
)paren
)paren
(brace
id|local_invalidate
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|i
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|cpu_callin_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|cpu_callin_map
(braket
l_int|0
)braket
op_or_assign
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Halt other CPU&squot;s for a panic or reboot&n;&t;&t; */
r_case
id|MSG_STOP_CPU
suffix:colon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|cpu_data
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|hlt_works_ok
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;hlt&quot;
)paren
suffix:semicolon
)brace
)brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;CPU #%d sent invalid cross CPU message to CPU #%d: %X(%lX).&bslash;n&quot;
comma
id|smp_src_cpu
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|smp_msg_id
comma
id|smp_msg_data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Clear the IPI, so we can receive future IPI&squot;s&n;&t; */
id|apic_read
c_func
(paren
id|APIC_SPIV
)paren
suffix:semicolon
multiline_comment|/* Dummy read */
id|apic_write
c_func
(paren
id|APIC_EOI
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Docs say use 0 for future compatibility */
)brace
eof