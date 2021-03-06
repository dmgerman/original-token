multiline_comment|/*&n; * $Id: time.c,v 1.57 1999/10/21 03:08:16 cort Exp $&n; * Common time routines among all ppc machines.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) to merge&n; * Paul Mackerras&squot; version and mine for PReP and Pmac.&n; * MPC8xx/MBX changes by Dan Malek (dmalek@jlc.net).&n; *&n; * First round of bugfixes by Gabriel Paubert (paubert@iram.es)&n; * to make clock more stable (2.4.0-test5). The only thing&n; * that this code assumes is that the timebases have been synchronized&n; * by firmware on SMP and are never stopped (never do sleep&n; * on SMP then, nap and doze are OK).&n; *&n; * TODO (not necessarily in this file):&n; * - improve precision and reproducibility of timebase frequency&n; * measurement at boot time.&n; * - get rid of xtime_lock for gettimeofday (generic kernel problem&n; * to be implemented on all architectures for SMP scalability and&n; * eventually implementing gettimeofday without entering the kernel).&n; * - put all time/clock related variables in a single structure&n; * to minimize number of cache lines touched by gettimeofday()&n; * - for astronomical applications: add a new function to get&n; * non ambiguous timestamps even around leap seconds. This needs&n; * a new timestamp format and a good name.&n; *&n; *&n; * The following comment is partially obsolete (at least the long wait&n; * is no more a valid reason):&n; * Since the MPC8xx has a programmable interrupt timer, I decided to&n; * use that rather than the decrementer.  Two reasons: 1.) the clock&n; * frequency is low, causing 2.) a long wait in the timer interrupt&n; *&t;&t;while ((d = get_dec()) == dval)&n; * loop.  The MPC8xx can be driven from a variety of input clocks,&n; * so a number of assumptions have been made here because the kernel&n; * parameter HZ is a constant.  We assume (correctly, today :-) that&n; * the MPC8xx on the MBX board is driven from a 32.768 kHz crystal.&n; * This is then divided by 4, providing a 8192 Hz clock into the PIT.&n; * Since it is not possible to get a nice 100 Hz clock out of this, without&n; * creating a software PLL, I have set HZ to 128.  -- Dan&n; *&n; * 1997-09-10  Updated NTP code according to technical memorandum Jan &squot;96&n; *             &quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* keep track of when we need to update the rtc */
DECL|variable|last_rtc_update
id|time_t
id|last_rtc_update
suffix:semicolon
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
multiline_comment|/* The decrementer counts down by 128 every 128ns on a 601. */
DECL|macro|DECREMENTER_COUNT_601
mdefine_line|#define DECREMENTER_COUNT_601&t;(1000000000 / HZ)
DECL|variable|tb_ticks_per_jiffy
r_int
id|tb_ticks_per_jiffy
suffix:semicolon
DECL|variable|tb_to_us
r_int
id|tb_to_us
suffix:semicolon
DECL|variable|tb_last_stamp
r_int
id|tb_last_stamp
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|variable|time_offset
r_static
r_int
id|time_offset
suffix:semicolon
multiline_comment|/* Timer interrupt helper function */
DECL|function|tb_delta
r_static
r_inline
r_int
id|tb_delta
c_func
(paren
r_int
op_star
id|jiffy_stamp
)paren
(brace
r_int
id|delta
suffix:semicolon
r_if
c_cond
(paren
id|__USE_RTC
c_func
(paren
)paren
)paren
(brace
id|delta
op_assign
id|get_rtcl
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
OL
op_star
id|jiffy_stamp
)paren
op_star
id|jiffy_stamp
op_sub_assign
l_int|1000000000
suffix:semicolon
id|delta
op_sub_assign
op_star
id|jiffy_stamp
suffix:semicolon
)brace
r_else
(brace
id|delta
op_assign
id|get_tbl
c_func
(paren
)paren
op_minus
op_star
id|jiffy_stamp
suffix:semicolon
)brace
r_return
id|delta
suffix:semicolon
)brace
multiline_comment|/*&n; * timer_interrupt - gets called when the decrementer overflows,&n; * with interrupts disabled.&n; * We set it up to overflow again in 1/HZ seconds.&n; */
DECL|function|timer_interrupt
r_int
id|timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|next_dec
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
id|jiffy_stamp
op_assign
id|last_jiffy_stamp
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|hardirq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_do
(brace
id|jiffy_stamp
op_add_assign
id|tb_ticks_per_jiffy
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* We are in an interrupt, no need to save/restore flags */
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|tb_last_stamp
op_assign
id|jiffy_stamp
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * update the rtc when needed, this should be performed on the&n;&t;&t; * right fraction of a second. Half or full second ?&n;&t;&t; * Full second works on mk48t59 clocks, others need testing.&n;&t;&t; * Note that this update is basically only used through&n;&t;&t; * the adjtimex system calls. Setting the HW clock in&n;&t;&t; * any other way is a /dev/rtc and userland business.&n;&t;&t; * This is still wrong by -0.5/+1.5 jiffies because of the&n;&t;&t; * timer interrupt resolution and possible delay, but here we&n;&t;&t; * hit a quantization limit which can only be solved by higher&n;&t;&t; * resolution timers and decoupling time management from timer&n;&t;&t; * interrupts. This is also wrong on the clocks&n;&t;&t; * which require being written at the half second boundary.&n;&t;&t; * We should have an rtc call that only sets the minutes and&n;&t;&t; * seconds like on Intel to avoid problems with non UTC clocks.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|time_status
op_amp
id|STA_UNSYNC
)paren
op_eq
l_int|0
op_logical_and
id|xtime.tv_sec
op_minus
id|last_rtc_update
op_ge
l_int|659
op_logical_and
id|abs
c_func
(paren
id|xtime.tv_usec
op_minus
(paren
l_int|1000000
op_minus
l_int|1000000
op_div
id|HZ
)paren
)paren
OL
l_int|500000
op_div
id|HZ
op_logical_and
id|jiffies
op_minus
id|wall_jiffies
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|ppc_md
dot
id|set_rtc_time
c_func
(paren
id|xtime.tv_sec
op_plus
l_int|1
op_plus
id|time_offset
)paren
op_eq
l_int|0
)paren
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_plus
l_int|1
suffix:semicolon
r_else
multiline_comment|/* Try again one minute later */
id|last_rtc_update
op_add_assign
l_int|60
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|next_dec
op_assign
id|tb_ticks_per_jiffy
op_minus
id|tb_delta
c_func
(paren
op_amp
id|jiffy_stamp
)paren
)paren
OL
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|set_dec
c_func
(paren
id|next_dec
)paren
suffix:semicolon
id|last_jiffy_stamp
c_func
(paren
id|cpu
)paren
op_assign
id|jiffy_stamp
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_local_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif&t;&t;
r_if
c_cond
(paren
id|ppc_md.heartbeat
op_logical_and
op_logical_neg
id|ppc_md.heartbeat_count
op_decrement
)paren
id|ppc_md
dot
id|heartbeat
c_func
(paren
)paren
suffix:semicolon
id|hardirq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* lets ret_from_int know we can do checks */
)brace
multiline_comment|/*&n; * This version of gettimeofday has microsecond resolution.&n; */
DECL|function|do_gettimeofday
r_void
id|do_gettimeofday
c_func
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
suffix:semicolon
r_int
id|delta
comma
id|lost_ticks
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
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_assign
id|xtime.tv_usec
suffix:semicolon
id|delta
op_assign
id|tb_ticks_since
c_func
(paren
id|tb_last_stamp
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* As long as timebases are not in sync, gettimeofday can only&n;&t; * have jiffy resolution on SMP.&n;&t; */
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
id|delta
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
id|lost_ticks
op_assign
id|jiffies
op_minus
id|wall_jiffies
suffix:semicolon
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|usec
op_add_assign
id|mulhwu
c_func
(paren
id|tb_to_us
comma
id|tb_ticks_per_jiffy
op_star
id|lost_ticks
op_plus
id|delta
)paren
suffix:semicolon
r_while
c_loop
(paren
id|usec
OG
l_int|1000000
)paren
(brace
id|sec
op_increment
suffix:semicolon
id|usec
op_sub_assign
l_int|1000000
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
DECL|function|do_settimeofday
r_void
id|do_settimeofday
c_func
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
suffix:semicolon
r_int
id|tb_delta
comma
id|new_usec
comma
id|new_sec
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Updating the RTC is not the job of this code. If the time is&n;&t; * stepped under NTP, the RTC will be update after STA_UNSYNC&n;&t; * is cleared. Tool like clock/hwclock either copy the RTC&n;&t; * to the system time, in which case there is no point in writing&n;&t; * to the RTC again, or write to the RTC but then they don&squot;t call&n;&t; * settimeofday to perform this operation. Note also that&n;&t; * we don&squot;t touch the decrementer since:&n;&t; * a) it would lose timer interrupt synchronization on SMP&n;&t; * (if it is working one day)&n;&t; * b) it could make one jiffy spuriously shorter or longer&n;&t; * which would introduce another source of uncertainty potentially&n;&t; * harmful to relatively short timers.&n;&t; */
multiline_comment|/* This works perfectly on SMP only if the tb are in sync but &n;&t; * guarantees an error &lt; 1 jiffy even if they are off by eons,&n;&t; * still reasonable when gettimeofday resolution is 1 jiffy.&n;&t; */
id|tb_delta
op_assign
id|tb_ticks_since
c_func
(paren
id|last_jiffy_stamp
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|tb_delta
op_add_assign
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
id|tb_ticks_per_jiffy
suffix:semicolon
id|new_sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|new_usec
op_assign
id|tv-&gt;tv_usec
op_minus
id|mulhwu
c_func
(paren
id|tb_to_us
comma
id|tb_delta
)paren
suffix:semicolon
r_while
c_loop
(paren
id|new_usec
OL
l_int|0
)paren
(brace
id|new_sec
op_decrement
suffix:semicolon
id|new_usec
op_add_assign
l_int|1000000
suffix:semicolon
)brace
id|xtime.tv_usec
op_assign
id|new_usec
suffix:semicolon
id|xtime.tv_sec
op_assign
id|new_sec
suffix:semicolon
multiline_comment|/* In case of a large backwards jump in time with NTP, we want the &n;&t; * clock to be updated as soon as the PLL is again in lock.&n;&t; */
id|last_rtc_update
op_assign
id|new_sec
op_minus
l_int|658
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
id|time_state
op_assign
id|TIME_ERROR
suffix:semicolon
multiline_comment|/* p. 24, (a) */
id|time_maxerror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|time_esterror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|time_t
id|sec
comma
id|old_sec
suffix:semicolon
r_int
id|old_stamp
comma
id|stamp
comma
id|elapsed
suffix:semicolon
multiline_comment|/* This function is only called on the boot processor */
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.time_init
op_ne
l_int|NULL
)paren
id|time_offset
op_assign
id|ppc_md
dot
id|time_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__USE_RTC
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 601 processor: dec counts down by 128 every 128ns */
id|tb_ticks_per_jiffy
op_assign
id|DECREMENTER_COUNT_601
suffix:semicolon
multiline_comment|/* mulhwu_scale_factor(1000000000, 1000000) is 0x418937 */
id|tb_to_us
op_assign
l_int|0x418937
suffix:semicolon
)brace
r_else
(brace
id|ppc_md
dot
id|calibrate_decr
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Now that the decrementer is calibrated, it can be used in case the &n;&t; * clock is stuck, but the fact that we have to handle the 601&n;&t; * makes things more complex. Repeatedly read the RTC until the&n;&t; * next second boundary to try to achieve some precision...&n;&t; */
id|stamp
op_assign
id|get_native_tbl
c_func
(paren
)paren
suffix:semicolon
id|sec
op_assign
id|ppc_md
dot
id|get_rtc_time
c_func
(paren
)paren
suffix:semicolon
id|elapsed
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|old_stamp
op_assign
id|stamp
suffix:semicolon
id|old_sec
op_assign
id|sec
suffix:semicolon
id|stamp
op_assign
id|get_native_tbl
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__USE_RTC
c_func
(paren
)paren
op_logical_and
id|stamp
OL
id|old_stamp
)paren
id|old_stamp
op_sub_assign
l_int|1000000000
suffix:semicolon
id|elapsed
op_add_assign
id|stamp
op_minus
id|old_stamp
suffix:semicolon
id|sec
op_assign
id|ppc_md
dot
id|get_rtc_time
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_eq
id|old_sec
op_logical_and
id|elapsed
OL
l_int|2
op_star
id|HZ
op_star
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_eq
id|old_sec
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: real time clock seems stuck!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|write_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|sec
suffix:semicolon
id|last_jiffy_stamp
c_func
(paren
l_int|0
)paren
op_assign
id|tb_last_stamp
op_assign
id|stamp
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No update now, we just read the time from the RTC ! */
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Not exact, but the timer interrupt takes care of this */
id|set_dec
c_func
(paren
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
multiline_comment|/* If platform provided a timezone (pmac), we correct the time&n;&t; * using do_sys_settimeofday() which in turn calls warp_clock()&n;&t; */
r_if
c_cond
(paren
id|time_offset
)paren
(brace
r_struct
id|timezone
id|tz
suffix:semicolon
id|tz.tz_minuteswest
op_assign
op_minus
id|time_offset
op_div
l_int|60
suffix:semicolon
id|tz.tz_dsttime
op_assign
l_int|0
suffix:semicolon
id|do_sys_settimeofday
c_func
(paren
l_int|NULL
comma
op_amp
id|tz
)paren
suffix:semicolon
)brace
)brace
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|macro|FEBRUARY
mdefine_line|#define FEBRUARY&t;2
DECL|macro|STARTOFTIME
mdefine_line|#define&t;STARTOFTIME&t;1970
DECL|macro|SECDAY
mdefine_line|#define SECDAY&t;&t;86400L
DECL|macro|SECYR
mdefine_line|#define SECYR&t;&t;(SECDAY * 365)
DECL|macro|leapyear
mdefine_line|#define&t;leapyear(year)&t;&t;((year) % 4 == 0)
DECL|macro|days_in_year
mdefine_line|#define&t;days_in_year(a) &t;(leapyear(a) ? 366 : 365)
DECL|macro|days_in_month
mdefine_line|#define&t;days_in_month(a) &t;(month_days[(a) - 1])
DECL|variable|month_days
r_static
r_int
id|month_days
(braket
l_int|12
)braket
op_assign
(brace
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
multiline_comment|/*&n; * This only works for the Gregorian calendar - i.e. after 1752 (in the UK)&n; */
DECL|function|GregorianDay
r_void
id|GregorianDay
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_int
id|leapsToDate
suffix:semicolon
r_int
id|lastYear
suffix:semicolon
r_int
id|day
suffix:semicolon
r_int
id|MonthOffset
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
)brace
suffix:semicolon
id|lastYear
op_assign
id|tm-&gt;tm_year
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Number of leap corrections to apply up to end of last year&n;&t; */
id|leapsToDate
op_assign
id|lastYear
op_div
l_int|4
op_minus
id|lastYear
op_div
l_int|100
op_plus
id|lastYear
op_div
l_int|400
suffix:semicolon
multiline_comment|/*&n;&t; * This year is a leap year if it is divisible by 4 except when it is&n;&t; * divisible by 100 unless it is divisible by 400&n;&t; *&n;&t; * e.g. 1904 was a leap year, 1900 was not, 1996 is, and 2000 will be&n;&t; */
r_if
c_cond
(paren
(paren
id|tm-&gt;tm_year
op_mod
l_int|4
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
id|tm-&gt;tm_year
op_mod
l_int|100
op_ne
l_int|0
)paren
op_logical_or
(paren
id|tm-&gt;tm_year
op_mod
l_int|400
op_eq
l_int|0
)paren
)paren
op_logical_and
(paren
id|tm-&gt;tm_mon
OG
l_int|2
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We are past Feb. 29 in a leap year&n;&t;&t; */
id|day
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|day
op_assign
l_int|0
suffix:semicolon
)brace
id|day
op_add_assign
id|lastYear
op_star
l_int|365
op_plus
id|leapsToDate
op_plus
id|MonthOffset
(braket
id|tm-&gt;tm_mon
op_minus
l_int|1
)braket
op_plus
id|tm-&gt;tm_mday
suffix:semicolon
id|tm-&gt;tm_wday
op_assign
id|day
op_mod
l_int|7
suffix:semicolon
)brace
DECL|function|to_tm
r_void
id|to_tm
c_func
(paren
r_int
id|tim
comma
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
r_int
id|hms
comma
id|day
suffix:semicolon
id|day
op_assign
id|tim
op_div
id|SECDAY
suffix:semicolon
id|hms
op_assign
id|tim
op_mod
id|SECDAY
suffix:semicolon
multiline_comment|/* Hours, minutes, seconds are easy */
id|tm-&gt;tm_hour
op_assign
id|hms
op_div
l_int|3600
suffix:semicolon
id|tm-&gt;tm_min
op_assign
(paren
id|hms
op_mod
l_int|3600
)paren
op_div
l_int|60
suffix:semicolon
id|tm-&gt;tm_sec
op_assign
(paren
id|hms
op_mod
l_int|3600
)paren
op_mod
l_int|60
suffix:semicolon
multiline_comment|/* Number of years in days */
r_for
c_loop
(paren
id|i
op_assign
id|STARTOFTIME
suffix:semicolon
id|day
op_ge
id|days_in_year
c_func
(paren
id|i
)paren
suffix:semicolon
id|i
op_increment
)paren
id|day
op_sub_assign
id|days_in_year
c_func
(paren
id|i
)paren
suffix:semicolon
id|tm-&gt;tm_year
op_assign
id|i
suffix:semicolon
multiline_comment|/* Number of months in days left */
r_if
c_cond
(paren
id|leapyear
c_func
(paren
id|tm-&gt;tm_year
)paren
)paren
id|days_in_month
c_func
(paren
id|FEBRUARY
)paren
op_assign
l_int|29
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|day
op_ge
id|days_in_month
c_func
(paren
id|i
)paren
suffix:semicolon
id|i
op_increment
)paren
id|day
op_sub_assign
id|days_in_month
c_func
(paren
id|i
)paren
suffix:semicolon
id|days_in_month
c_func
(paren
id|FEBRUARY
)paren
op_assign
l_int|28
suffix:semicolon
id|tm-&gt;tm_mon
op_assign
id|i
suffix:semicolon
multiline_comment|/* Days are what is left over (+1) from all that. */
id|tm-&gt;tm_mday
op_assign
id|day
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Determine the day of week&n;&t; */
id|GregorianDay
c_func
(paren
id|tm
)paren
suffix:semicolon
)brace
multiline_comment|/* Auxiliary function to compute scaling factors */
multiline_comment|/* Actually the choice of a timebase running at 1/4 the of the bus&n; * frequency giving resolution of a few tens of nanoseconds is quite nice.&n; * It makes this computation very precise (27-28 bits typically) which&n; * is optimistic considering the stability of most processor clock&n; * oscillators and the precision with which the timebase frequency&n; * is measured but does not harm.&n; */
DECL|function|mulhwu_scale_factor
r_int
id|mulhwu_scale_factor
c_func
(paren
r_int
id|inscale
comma
r_int
id|outscale
)paren
(brace
r_int
id|mlt
op_assign
l_int|0
comma
id|tmp
comma
id|err
suffix:semicolon
multiline_comment|/* No concern for performance, it&squot;s done once: use a stupid&n;&t; * but safe and compact method to find the multiplier.&n;&t; */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|1U
op_lshift
l_int|31
suffix:semicolon
id|tmp
op_ne
l_int|0
suffix:semicolon
id|tmp
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|mulhwu
c_func
(paren
id|inscale
comma
id|mlt
op_or
id|tmp
)paren
OL
id|outscale
)paren
id|mlt
op_or_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* We might still be off by 1 for the best approximation.&n;&t; * A side effect of this is that if outscale is too large&n;&t; * the returned value will be zero.&n;&t; * Many corner cases have been checked and seem to work,&n;&t; * some might have been forgotten in the test however.&n;&t; */
id|err
op_assign
id|inscale
op_star
(paren
id|mlt
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_le
id|inscale
op_div
l_int|2
)paren
id|mlt
op_increment
suffix:semicolon
r_return
id|mlt
suffix:semicolon
)brace
eof
