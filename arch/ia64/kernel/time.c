multiline_comment|/*&n; * linux/arch/ia64/kernel/time.c&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 1999-2000 David Mosberger &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; * Copyright (C) 1999-2000 VA Linux Systems&n; * Copyright (C) 1999-2000 Walt Drummond &lt;drummond@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|lost_ticks
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_DEBUG_IRQ
DECL|variable|last_cli_ip
r_int
r_int
id|last_cli_ip
suffix:semicolon
macro_line|#endif
r_static
r_struct
(brace
DECL|member|delta
r_int
r_int
id|delta
suffix:semicolon
DECL|member|next
r_int
r_int
id|next
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|itm
)brace
id|itm
suffix:semicolon
r_static
r_void
DECL|function|do_profile
id|do_profile
(paren
r_int
r_int
id|ip
)paren
(brace
r_extern
r_char
id|_stext
suffix:semicolon
r_if
c_cond
(paren
id|prof_buffer
op_logical_and
id|current-&gt;pid
)paren
(brace
id|ip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|ip
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t ignore out-of-bounds IP values silently,&n;&t;&t; * put them into the last histogram slot, so if&n;&t;&t; * present, they will show up as a sharp peak.&n;&t;&t; */
r_if
c_cond
(paren
id|ip
OG
id|prof_len
op_minus
l_int|1
)paren
id|ip
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|ip
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Return the number of micro-seconds that elapsed since the last&n; * update to jiffy.  The xtime_lock must be at least read-locked when&n; * calling this routine.&n; */
r_static
r_inline
r_int
r_int
DECL|function|gettimeoffset
id|gettimeoffset
(paren
r_void
)paren
(brace
r_int
r_int
id|now
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|elapsed_cycles
comma
id|lost
suffix:semicolon
id|elapsed_cycles
op_assign
id|now
op_minus
(paren
id|itm.next
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_minus
id|itm.delta
)paren
suffix:semicolon
id|lost
op_assign
id|lost_ticks
suffix:semicolon
r_if
c_cond
(paren
id|lost
)paren
id|elapsed_cycles
op_add_assign
id|lost
op_star
id|itm.delta
suffix:semicolon
r_return
(paren
id|elapsed_cycles
op_star
id|my_cpu_data.usec_per_cyc
)paren
op_rshift
id|IA64_USEC_PER_CYC_SHIFT
suffix:semicolon
)brace
r_void
DECL|function|do_settimeofday
id|do_settimeofday
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
(brace
multiline_comment|/*&n;&t;&t; * This is revolting. We need to set the xtime.tv_usec&n;&t;&t; * correctly. However, the value in this location is&n;&t;&t; * is value at the last tick.  Discover what&n;&t;&t; * correction gettimeofday would have done, and then&n;&t;&t; * undo it!&n;&t;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tv-&gt;tv_usec
OL
l_int|0
)paren
(brace
id|tv-&gt;tv_usec
op_add_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_decrement
suffix:semicolon
)brace
id|xtime
op_assign
op_star
id|tv
suffix:semicolon
id|time_adjust
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* stop active adjtime() */
id|time_status
op_or_assign
id|STA_UNSYNC
suffix:semicolon
id|time_maxerror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|time_esterror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
)brace
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
r_void
DECL|function|do_gettimeofday
id|do_gettimeofday
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
r_int
id|flags
comma
id|usec
comma
id|sec
suffix:semicolon
id|read_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
(brace
id|usec
op_assign
id|gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_add_assign
id|xtime.tv_usec
suffix:semicolon
)brace
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|usec
op_ge
l_int|1000000
)paren
(brace
id|usec
op_sub_assign
l_int|1000000
suffix:semicolon
op_increment
id|sec
suffix:semicolon
)brace
id|tv-&gt;tv_sec
op_assign
id|sec
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|usec
suffix:semicolon
)brace
r_static
r_void
DECL|function|timer_interrupt
id|timer_interrupt
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
r_static
r_int
r_int
id|last_time
suffix:semicolon
r_static
r_int
r_char
id|count
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Here we are in the timer irq handler. We have irqs locally&n;&t; * disabled, but we don&squot;t know if the timer_bh is running on&n;&t; * another CPU. We need to avoid to SMP race by acquiring the&n;&t; * xtime_lock.&n;&t; */
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* do kernel PC profiling here.  */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|do_profile
c_func
(paren
id|regs-&gt;cr_iip
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|bootstrap_processor
)paren
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#else
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|itm.next
(braket
id|cpu
)braket
op_add_assign
id|itm.delta
suffix:semicolon
multiline_comment|/*&n;&t;&t; * There is a race condition here: to be on the &quot;safe&quot;&n;&t;&t; * side, we process timer ticks until itm.next is&n;&t;&t; * ahead of the itc by at least half the timer&n;&t;&t; * interval.  This should give us enough time to set&n;&t;&t; * the new itm value without losing a timer tick.&n;&t;&t; */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|itm.next
(braket
id|cpu
)braket
comma
id|ia64_get_itc
c_func
(paren
)paren
op_plus
id|itm.delta
op_div
l_int|2
)paren
)paren
(brace
id|ia64_set_itm
c_func
(paren
id|itm.next
(braket
id|cpu
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if !(defined(CONFIG_IA64_SOFTSDV_HACKS) &amp;&amp; defined(CONFIG_SMP))
multiline_comment|/*&n;&t;&t; * SoftSDV in SMP mode is _slow_, so we do &quot;loose&quot; ticks, &n;&t;&t; * but it&squot;s really OK...&n;&t;&t; */
r_if
c_cond
(paren
id|count
OG
l_int|0
op_logical_and
id|jiffies
op_minus
id|last_time
OG
l_int|5
op_star
id|HZ
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_increment
op_eq
l_int|0
)paren
(brace
id|last_time
op_assign
id|jiffies
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Lost clock tick on CPU %d (now=%lx, next=%lx)!!&bslash;n&quot;
comma
id|cpu
comma
id|ia64_get_itc
c_func
(paren
)paren
comma
id|itm.next
(braket
id|cpu
)braket
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_IA64_DEBUG_IRQ
id|printk
c_func
(paren
l_string|&quot;last_cli_ip=%lx&bslash;n&quot;
comma
id|last_cli_ip
)paren
suffix:semicolon
macro_line|# endif
)brace
macro_line|#endif
)brace
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Encapsulate access to the itm structure for SMP.&n; */
r_void
id|__init
DECL|function|ia64_cpu_local_tick
id|ia64_cpu_local_tick
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* arrange for the cycle counter to generate a timer interrupt: */
id|ia64_set_itv
c_func
(paren
id|TIMER_IRQ
comma
l_int|0
)paren
suffix:semicolon
id|ia64_set_itc
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|itm.next
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
id|ia64_get_itc
c_func
(paren
)paren
op_plus
id|itm.delta
suffix:semicolon
id|ia64_set_itm
c_func
(paren
id|itm.next
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|ia64_init_itm
id|ia64_init_itm
(paren
r_void
)paren
(brace
r_int
r_int
id|platform_base_freq
comma
id|itc_freq
comma
id|drift
suffix:semicolon
r_struct
id|pal_freq_ratio
id|itc_ratio
comma
id|proc_ratio
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * According to SAL v2.6, we need to use a SAL call to determine the&n;&t; * platform base frequency and then a PAL call to determine the&n;&t; * frequency ratio between the ITC and the base frequency.&n;&t; */
id|status
op_assign
id|ia64_sal_freq_base
c_func
(paren
id|SAL_FREQ_BASE_PLATFORM
comma
op_amp
id|platform_base_freq
comma
op_amp
id|drift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SAL_FREQ_BASE_PLATFORM failed: %s&bslash;n&quot;
comma
id|ia64_sal_strerror
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|ia64_pal_freq_ratios
c_func
(paren
op_amp
id|proc_ratio
comma
l_int|0
comma
op_amp
id|itc_ratio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;PAL_FREQ_RATIOS failed with status=%ld&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
multiline_comment|/* invent &quot;random&quot; values */
id|printk
c_func
(paren
l_string|&quot;SAL/PAL failed to obtain frequency info---inventing reasonably values&bslash;n&quot;
)paren
suffix:semicolon
id|platform_base_freq
op_assign
l_int|100000000
suffix:semicolon
id|itc_ratio.num
op_assign
l_int|3
suffix:semicolon
id|itc_ratio.den
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_IA64_LION_HACKS)
multiline_comment|/* Our Lion currently returns base freq 104.857MHz, which&n;&t;   ain&squot;t right (it really is 100MHz).  */
id|printk
c_func
(paren
l_string|&quot;SAL/PAL returned: base-freq=%lu, itc-ratio=%lu/%lu, proc-ratio=%lu/%lu&bslash;n&quot;
comma
id|platform_base_freq
comma
id|itc_ratio.num
comma
id|itc_ratio.den
comma
id|proc_ratio.num
comma
id|proc_ratio.den
)paren
suffix:semicolon
id|platform_base_freq
op_assign
l_int|100000000
suffix:semicolon
macro_line|#elif 0 &amp;&amp; defined(CONFIG_IA64_BIGSUR_HACKS)
multiline_comment|/* BigSur with 991020 firmware returned itc-ratio=9/2 and base&n;&t;   freq 75MHz, which wasn&squot;t right.  The 991119 firmware seems&n;&t;   to return the right values, so this isn&squot;t necessary&n;&t;   anymore... */
id|printk
c_func
(paren
l_string|&quot;SAL/PAL returned: base-freq=%lu, itc-ratio=%lu/%lu, proc-ratio=%lu/%lu&bslash;n&quot;
comma
id|platform_base_freq
comma
id|itc_ratio.num
comma
id|itc_ratio.den
comma
id|proc_ratio.num
comma
id|proc_ratio.den
)paren
suffix:semicolon
id|platform_base_freq
op_assign
l_int|100000000
suffix:semicolon
id|proc_ratio.num
op_assign
l_int|5
suffix:semicolon
id|proc_ratio.den
op_assign
l_int|1
suffix:semicolon
id|itc_ratio.num
op_assign
l_int|5
suffix:semicolon
id|itc_ratio.den
op_assign
l_int|1
suffix:semicolon
macro_line|#elif defined(CONFIG_IA64_SOFTSDV_HACKS)
id|platform_base_freq
op_assign
l_int|10000000
suffix:semicolon
id|proc_ratio.num
op_assign
l_int|4
suffix:semicolon
id|proc_ratio.den
op_assign
l_int|1
suffix:semicolon
id|itc_ratio.num
op_assign
l_int|4
suffix:semicolon
id|itc_ratio.den
op_assign
l_int|1
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|platform_base_freq
OL
l_int|40000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Platform base frequency %lu bogus---resetting to 75MHz!&bslash;n&quot;
comma
id|platform_base_freq
)paren
suffix:semicolon
id|platform_base_freq
op_assign
l_int|75000000
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|proc_ratio.den
)paren
id|proc_ratio.num
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* avoid division by zero */
r_if
c_cond
(paren
op_logical_neg
id|itc_ratio.den
)paren
id|itc_ratio.num
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* avoid division by zero */
id|itc_freq
op_assign
(paren
id|platform_base_freq
op_star
id|itc_ratio.num
)paren
op_div
id|itc_ratio.den
suffix:semicolon
id|itm.delta
op_assign
id|itc_freq
op_div
id|HZ
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;timer: base freq=%lu.%03luMHz, ITC ratio=%lu/%lu, ITC freq=%lu.%03luMHz&bslash;n&quot;
comma
id|platform_base_freq
op_div
l_int|1000000
comma
(paren
id|platform_base_freq
op_div
l_int|1000
)paren
op_mod
l_int|1000
comma
id|itc_ratio.num
comma
id|itc_ratio.den
comma
id|itc_freq
op_div
l_int|1000000
comma
(paren
id|itc_freq
op_div
l_int|1000
)paren
op_mod
l_int|1000
)paren
suffix:semicolon
id|my_cpu_data.proc_freq
op_assign
(paren
id|platform_base_freq
op_star
id|proc_ratio.num
)paren
op_div
id|proc_ratio.den
suffix:semicolon
id|my_cpu_data.itc_freq
op_assign
id|itc_freq
suffix:semicolon
id|my_cpu_data.cyc_per_usec
op_assign
id|itc_freq
op_div
l_int|1000000
suffix:semicolon
id|my_cpu_data.usec_per_cyc
op_assign
(paren
l_int|1000000UL
op_lshift
id|IA64_USEC_PER_CYC_SHIFT
)paren
op_div
id|itc_freq
suffix:semicolon
multiline_comment|/* Setup the CPU local timer tick */
id|ia64_cpu_local_tick
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|time_init
id|time_init
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Request the IRQ _before_ doing anything to cause that&n;&t; * interrupt to be posted.&n;&t; */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|TIMER_IRQ
comma
id|timer_interrupt
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Could not allocate timer IRQ!&quot;
)paren
suffix:semicolon
id|efi_gettimeofday
c_func
(paren
op_amp
id|xtime
)paren
suffix:semicolon
id|ia64_init_itm
c_func
(paren
)paren
suffix:semicolon
)brace
eof
