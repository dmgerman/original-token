macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#ifdef CONFIG_SGI_IP27
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/agent.h&gt;
macro_line|#include &lt;asm/sn/sn0/ip27.h&gt;
DECL|macro|DORESCHED
mdefine_line|#define DORESCHED&t;0xab
DECL|macro|DOCALL
mdefine_line|#define DOCALL&t;&t;0xbc
DECL|macro|IRQ_TO_SWLEVEL
mdefine_line|#define IRQ_TO_SWLEVEL(i)&t;i + 7&t;/* Delete this from here */
DECL|function|sendintr
r_static
r_void
id|sendintr
c_func
(paren
r_int
id|destid
comma
r_int
r_char
id|status
)paren
(brace
r_int
id|irq
suffix:semicolon
macro_line|#if (CPUS_PER_NODE == 2)
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|DORESCHED
suffix:colon
id|irq
op_assign
id|CPU_RESCHED_A_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DOCALL
suffix:colon
id|irq
op_assign
id|CPU_CALL_A_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;sendintr&quot;
)paren
suffix:semicolon
)brace
id|irq
op_add_assign
id|cputoslice
c_func
(paren
id|destid
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the compact hub number to the NASID to get the correct&n;&t; * part of the address space.  Then set the interrupt bit associated&n;&t; * with the CPU we want to send the interrupt to.&n;&t; */
id|REMOTE_HUB_SEND_INTR
c_func
(paren
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cputocnode
c_func
(paren
id|destid
)paren
)paren
comma
id|IRQ_TO_SWLEVEL
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
macro_line|#else
op_lshift
id|Bomb
op_logical_neg
id|Must
id|redefine
id|this
r_for
c_loop
id|more
id|than
l_int|2
id|CPUS
dot
op_rshift
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_SGI_IP27 */
multiline_comment|/* The &squot;big kernel lock&squot; */
DECL|variable|kernel_flag
id|spinlock_t
id|kernel_flag
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
suffix:semicolon
multiline_comment|/* Not used */
DECL|variable|smp_commenced
id|atomic_t
id|smp_commenced
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|cpu_data
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
suffix:semicolon
multiline_comment|/* Number that came online.  */
DECL|variable|__cpu_number_map
r_int
id|__cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|__cpu_logical_map
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cacheflush_time
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|function|smp_tune_scheduling
r_static
r_void
id|smp_tune_scheduling
(paren
r_void
)paren
(brace
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
r_void
id|allowboot
c_func
(paren
r_void
)paren
suffix:semicolon
id|init_new_context
c_func
(paren
id|current
comma
op_amp
id|init_mm
)paren
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
id|smp_tune_scheduling
c_func
(paren
)paren
suffix:semicolon
id|allowboot
c_func
(paren
)paren
suffix:semicolon
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
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|smp_commenced
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|stop_this_cpu
r_static
r_void
id|stop_this_cpu
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
multiline_comment|/*&n;&t; * Remove this CPU&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
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
id|smp_call_function
c_func
(paren
id|stop_this_cpu
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * this function sends a &squot;reschedule&squot; IPI to another CPU.&n; * it goes straight through and wastes no time serializing&n; * anything. Worst case is that we lose a reschedule ...&n; */
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
id|sendintr
c_func
(paren
id|cpu
comma
id|DORESCHED
)paren
suffix:semicolon
)brace
multiline_comment|/* Not really SMP stuff ... */
DECL|function|setup_profiling_timer
r_int
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
multiline_comment|/*&n; * Run a function on all other CPUs.&n; *  &lt;func&gt;      The function to run. This must be fast and non-blocking.&n; *  &lt;info&gt;      An arbitrary pointer to pass to the function.&n; *  &lt;retry&gt;     If true, keep retrying until ready.&n; *  &lt;wait&gt;      If true, wait until function has completed on other CPUs.&n; *  [RETURNS]   0 on success, else a negative status code.&n; *&n; * Does not return until remote CPUs are nearly ready to execute &lt;func&gt;&n; * or are or have executed.&n; */
DECL|struct|call_data_struct
r_static
r_volatile
r_struct
id|call_data_struct
(brace
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|started
id|atomic_t
id|started
suffix:semicolon
DECL|member|finished
id|atomic_t
id|finished
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
DECL|variable|call_data
)brace
op_star
id|call_data
suffix:semicolon
DECL|function|smp_call_function
r_int
id|smp_call_function
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|retry
comma
r_int
id|wait
)paren
(brace
r_struct
id|call_data_struct
id|data
suffix:semicolon
r_int
id|i
comma
id|cpus
op_assign
id|smp_num_cpus
op_minus
l_int|1
suffix:semicolon
r_static
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_if
c_cond
(paren
id|cpus
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|data.func
op_assign
id|func
suffix:semicolon
id|data.info
op_assign
id|info
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.started
comma
l_int|0
)paren
suffix:semicolon
id|data.wait
op_assign
id|wait
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_set
c_func
(paren
op_amp
id|data.finished
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|call_data
op_assign
op_amp
id|data
suffix:semicolon
multiline_comment|/* Send a message to all other CPUs and wait for them to respond */
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
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
id|sendintr
c_func
(paren
id|i
comma
id|DOCALL
)paren
suffix:semicolon
multiline_comment|/* Wait for response */
multiline_comment|/* FIXME: lock-up detection, backtrace on lock-up */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.started
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.finished
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_call_function_interrupt
r_extern
r_void
id|smp_call_function_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|d
comma
r_struct
id|pt_regs
op_star
id|r
)paren
(brace
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
op_assign
id|call_data-&gt;func
suffix:semicolon
r_void
op_star
id|info
op_assign
id|call_data-&gt;info
suffix:semicolon
r_int
id|wait
op_assign
id|call_data-&gt;wait
suffix:semicolon
multiline_comment|/*&n;&t; * Notify initiating CPU that I&squot;ve grabbed the data and am&n;&t; * about to execute the function.&n;&t; */
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;started
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * At this point the info structure may be out of scope unless wait==1.&n;&t; */
(paren
op_star
id|func
)paren
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;finished
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all_ipi
r_static
r_void
id|flush_tlb_all_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
id|_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|flush_tlb_all_ipi
comma
l_int|0
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm_ipi
r_static
r_void
id|flush_tlb_mm_ipi
c_func
(paren
r_void
op_star
id|mm
)paren
(brace
id|_flush_tlb_mm
c_func
(paren
(paren
r_struct
id|mm_struct
op_star
)paren
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following tlb flush calls are invoked when old translations are &n; * being torn down, or pte attributes are changing. For single threaded&n; * address spaces, a new context is obtained on the current cpu, and tlb&n; * context on other cpus are invalidated to force a new context allocation&n; * at switch_mm time, should the mm ever be used on other cpus. For &n; * multithreaded address spaces, intercpu interrupts have to be sent.&n; * Another case where intercpu interrupts are required is when the target&n; * mm might be active on another cpu (eg debuggers doing the flushes on&n; * behalf of debugees, kswapd stealing pages from another process etc).&n; * Kanoj 07/00.&n; */
DECL|function|flush_tlb_mm
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
op_ne
l_int|1
)paren
op_logical_or
(paren
id|current-&gt;mm
op_ne
id|mm
)paren
)paren
(brace
id|smp_call_function
c_func
(paren
id|flush_tlb_mm_ipi
comma
(paren
r_void
op_star
)paren
id|mm
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
id|CPU_CONTEXT
c_func
(paren
id|i
comma
id|mm
)paren
op_assign
l_int|0
suffix:semicolon
)brace
id|_flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
DECL|struct|flush_tlb_data
r_struct
id|flush_tlb_data
(brace
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
DECL|member|vma
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
DECL|member|addr1
r_int
r_int
id|addr1
suffix:semicolon
DECL|member|addr2
r_int
r_int
id|addr2
suffix:semicolon
)brace
suffix:semicolon
DECL|function|flush_tlb_range_ipi
r_static
r_void
id|flush_tlb_range_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_struct
id|flush_tlb_data
op_star
id|fd
op_assign
(paren
r_struct
id|flush_tlb_data
op_star
)paren
id|info
suffix:semicolon
id|_flush_tlb_range
c_func
(paren
id|fd-&gt;mm
comma
id|fd-&gt;addr1
comma
id|fd-&gt;addr2
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_void
id|flush_tlb_range
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
r_if
c_cond
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
op_ne
l_int|1
)paren
op_logical_or
(paren
id|current-&gt;mm
op_ne
id|mm
)paren
)paren
(brace
r_struct
id|flush_tlb_data
id|fd
suffix:semicolon
id|fd.mm
op_assign
id|mm
suffix:semicolon
id|fd.addr1
op_assign
id|start
suffix:semicolon
id|fd.addr2
op_assign
id|end
suffix:semicolon
id|smp_call_function
c_func
(paren
id|flush_tlb_range_ipi
comma
(paren
r_void
op_star
)paren
op_amp
id|fd
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
id|CPU_CONTEXT
c_func
(paren
id|i
comma
id|mm
)paren
op_assign
l_int|0
suffix:semicolon
)brace
id|_flush_tlb_range
c_func
(paren
id|mm
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page_ipi
r_static
r_void
id|flush_tlb_page_ipi
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_struct
id|flush_tlb_data
op_star
id|fd
op_assign
(paren
r_struct
id|flush_tlb_data
op_star
)paren
id|info
suffix:semicolon
id|_flush_tlb_page
c_func
(paren
id|fd-&gt;vma
comma
id|fd-&gt;addr1
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
r_if
c_cond
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|vma-&gt;vm_mm-&gt;mm_users
)paren
op_ne
l_int|1
)paren
op_logical_or
(paren
id|current-&gt;mm
op_ne
id|vma-&gt;vm_mm
)paren
)paren
(brace
r_struct
id|flush_tlb_data
id|fd
suffix:semicolon
id|fd.vma
op_assign
id|vma
suffix:semicolon
id|fd.addr1
op_assign
id|page
suffix:semicolon
id|smp_call_function
c_func
(paren
id|flush_tlb_page_ipi
comma
(paren
r_void
op_star
)paren
op_amp
id|fd
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
id|CPU_CONTEXT
c_func
(paren
id|i
comma
id|vma-&gt;vm_mm
)paren
op_assign
l_int|0
suffix:semicolon
)brace
id|_flush_tlb_page
c_func
(paren
id|vma
comma
id|page
)paren
suffix:semicolon
)brace
eof
