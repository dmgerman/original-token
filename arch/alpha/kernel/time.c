multiline_comment|/*&n; *  linux/arch/alpha/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * This file contains the PC-specific time handling details:&n; * reading the RTC at bootup, etc..&n; * 1994-07-02    Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1995-03-26    Markus Kuhn&n; *      fixed 500 ms bug at call to set_rtc_mmss, fixed DS12887&n; *      precision CMOS clock update&n; * 1997-01-09    Adrian Sun&n; *      use interval timer if CONFIG_RTC=y&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#ifdef CONFIG_RTC 
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0  /* using pit for timer */
macro_line|#else 
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 8  /* using rtc for timer */
macro_line|#endif
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Shift amount by which scaled_ticks_per_cycle is scaled.  Shifting&n; * by 48 gives us 16 bits for HZ while keeping the accuracy good even&n; * for large CPU clock rates.&n; */
DECL|macro|FIX_SHIFT
mdefine_line|#define FIX_SHIFT&t;48
multiline_comment|/* lump static variables together for more efficient access: */
r_static
r_struct
(brace
DECL|member|last_time
id|__u32
id|last_time
suffix:semicolon
multiline_comment|/* cycle counter last time it got invoked */
DECL|member|max_cycles_per_tick
id|__u32
id|max_cycles_per_tick
suffix:semicolon
multiline_comment|/* more makes us think we lost an interrupt */
DECL|member|scaled_ticks_per_cycle
r_int
r_int
id|scaled_ticks_per_cycle
suffix:semicolon
multiline_comment|/* ticks/cycle * 2^48 */
DECL|member|last_rtc_update
r_int
id|last_rtc_update
suffix:semicolon
multiline_comment|/* last time the cmos clock got updated */
DECL|variable|state
)brace
id|state
suffix:semicolon
DECL|function|rpcc
r_static
r_inline
id|__u32
id|rpcc
c_func
(paren
r_void
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;rpcc %0&quot;
suffix:colon
l_string|&quot;r=&quot;
(paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|timer_interrupt
r_void
id|timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|__u32
id|delta
comma
id|now
suffix:semicolon
id|now
op_assign
id|rpcc
c_func
(paren
)paren
suffix:semicolon
id|delta
op_assign
id|now
op_minus
id|state.last_time
suffix:semicolon
id|state.last_time
op_assign
id|now
suffix:semicolon
r_if
c_cond
(paren
id|delta
OG
id|state.max_cycles_per_tick
)paren
(brace
r_int
id|i
comma
id|missed_ticks
suffix:semicolon
id|missed_ticks
op_assign
(paren
(paren
id|delta
op_star
id|state.scaled_ticks_per_cycle
)paren
op_rshift
id|FIX_SHIFT
)paren
op_minus
l_int|1
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
id|missed_ticks
suffix:semicolon
op_increment
id|i
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * CMOS clock accordingly every ~11 minutes. Set_rtc_mmss() has to be&n;&t; * called as close as possible to 500 ms before the new second starts.&n;&t; */
r_if
c_cond
(paren
id|time_state
op_ne
id|TIME_BAD
op_logical_and
id|xtime.tv_sec
OG
id|state.last_rtc_update
op_plus
l_int|660
op_logical_and
id|xtime.tv_usec
OG
l_int|500000
op_minus
(paren
id|tick
op_rshift
l_int|1
)paren
op_logical_and
id|xtime.tv_usec
OL
l_int|500000
op_plus
(paren
id|tick
op_rshift
l_int|1
)paren
)paren
r_if
c_cond
(paren
id|set_rtc_mmss
c_func
(paren
id|xtime.tv_sec
)paren
op_eq
l_int|0
)paren
id|state.last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
r_else
id|state.last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
multiline_comment|/* do it again in 60 s */
)brace
multiline_comment|/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.&n; * Assumes input in normal date format, i.e. 1980-12-31 23:59:59&n; * =&gt; year=1980, mon=12, day=31, hour=23, min=59, sec=59.&n; *&n; * [For the Julian calendar (which was used in Russia before 1917,&n; * Britain &amp; colonies before 1752, anywhere else before 1582,&n; * and is still in use by some communities) leave out the&n; * -year/100+year/400 terms, and add 10.]&n; *&n; * This algorithm was first published by Gauss (I think).&n; *&n; * WARNING: this function will overflow on 2106-02-07 06:28:16 on&n; * machines were long is 32-bit! (However, as time_t is signed, we&n; * will already get problems at other places on 2038-01-19 03:14:08)&n; */
DECL|function|mktime
r_static
r_inline
r_int
r_int
id|mktime
c_func
(paren
r_int
r_int
id|year
comma
r_int
r_int
id|mon
comma
r_int
r_int
id|day
comma
r_int
r_int
id|hour
comma
r_int
r_int
id|min
comma
r_int
r_int
id|sec
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ge
(paren
r_int
)paren
(paren
id|mon
op_sub_assign
l_int|2
)paren
)paren
(brace
multiline_comment|/* 1..12 -&gt; 11,12,1..10 */
id|mon
op_add_assign
l_int|12
suffix:semicolon
multiline_comment|/* Puts Feb last since it has leap day */
id|year
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_return
(paren
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|year
op_div
l_int|4
op_minus
id|year
op_div
l_int|100
op_plus
id|year
op_div
l_int|400
op_plus
l_int|367
op_star
id|mon
op_div
l_int|12
op_plus
id|day
)paren
op_plus
id|year
op_star
l_int|365
op_minus
l_int|719499
)paren
op_star
l_int|24
op_plus
id|hour
multiline_comment|/* now have hours */
)paren
op_star
l_int|60
op_plus
id|min
multiline_comment|/* now have minutes */
)paren
op_star
l_int|60
op_plus
id|sec
suffix:semicolon
multiline_comment|/* finally seconds */
)brace
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_RTC
r_int
r_char
id|save_control
suffix:semicolon
macro_line|#endif
r_void
(paren
op_star
id|irq_handler
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
suffix:semicolon
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* The Linux interpretation of the CMOS clock register contents:&n;&t; * When the Update-In-Progress (UIP) flag goes from 1 to 0, the&n;&t; * RTC registers show the second which has precisely just started.&n;&t; * Let&squot;s hope other operating systems interpret the RTC the same way.&n;&t; */
multiline_comment|/* read RTC exactly on falling edge of update flag */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* may take up to 1 second... */
r_if
c_cond
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
r_break
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
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* must try at least 2.228 ms */
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
)paren
r_break
suffix:semicolon
r_do
(brace
multiline_comment|/* Isn&squot;t this overkill ? UIP above should guarantee consistency */
id|sec
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
)paren
suffix:semicolon
)brace
macro_line|#ifdef ALPHA_PRE_V1_2_SRM_CONSOLE
multiline_comment|/*&n;&t; * The meaning of life, the universe, and everything. Plus&n;&t; * this makes the year come out right on SRM consoles earlier&n;&t; * than v1.2.&n;&t; */
id|year
op_sub_assign
l_int|42
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|year
op_add_assign
l_int|1900
)paren
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|HZ
OG
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
(brace
r_extern
r_void
id|__you_loose
(paren
r_void
)paren
suffix:semicolon
id|__you_loose
c_func
(paren
)paren
suffix:semicolon
)brace
id|state.last_time
op_assign
id|rpcc
c_func
(paren
)paren
suffix:semicolon
id|state.scaled_ticks_per_cycle
op_assign
(paren
(paren
r_int
r_int
)paren
id|HZ
op_lshift
id|FIX_SHIFT
)paren
op_div
id|hwrpb-&gt;cycle_freq
suffix:semicolon
id|state.max_cycles_per_tick
op_assign
(paren
l_int|2
op_star
id|hwrpb-&gt;cycle_freq
)paren
op_div
id|HZ
suffix:semicolon
id|state.last_rtc_update
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_RTC 
multiline_comment|/* turn off RTC interrupts before /dev/rtc is initialized */
id|save_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
id|save_control
op_and_assign
op_complement
id|RTC_PIE
suffix:semicolon
id|save_control
op_and_assign
op_complement
id|RTC_AIE
suffix:semicolon
id|save_control
op_and_assign
op_complement
id|RTC_UIE
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|save_control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_READ
c_func
(paren
id|RTC_INTR_FLAGS
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* setup timer */
id|irq_handler
op_assign
id|timer_interrupt
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|TIMER_IRQ
comma
id|irq_handler
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
)brace
multiline_comment|/*&n; * We could get better timer accuracy by using the alpha&n; * time counters or something.  Now this is limited to&n; * the HZ clock frequency.&n; */
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
id|tv
op_assign
id|xtime
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|xtime
op_assign
op_star
id|tv
suffix:semicolon
id|time_state
op_assign
id|TIME_BAD
suffix:semicolon
id|time_maxerror
op_assign
l_int|0x70000000
suffix:semicolon
id|time_esterror
op_assign
l_int|0x70000000
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be&n; * called 500 ms after the second nowtime has started, because when&n; * nowtime is written into the registers of the CMOS clock, it will&n; * jump to the next second precisely 500 ms later. Check the Motorola&n; * MC146818A or Dallas DS12887 data sheet for details.&n; */
DECL|function|set_rtc_mmss
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
r_int
r_char
id|save_control
comma
id|save_freq_select
suffix:semicolon
id|save_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
id|CMOS_WRITE
c_func
(paren
(paren
id|save_control
op_or
id|RTC_SET
)paren
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|save_freq_select
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
id|CMOS_WRITE
c_func
(paren
(paren
id|save_freq_select
op_or
id|RTC_DIV_RESET2
)paren
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|cmos_minutes
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
id|BCD_TO_BIN
c_func
(paren
id|cmos_minutes
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * since we&squot;re only adjusting minutes and seconds,&n;&t; * don&squot;t interfere with hour overflow. This avoids&n;&t; * messing with unknown time zones but requires your&n;&t; * RTC not to be off by more than 15 minutes&n;&t; */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
OL
l_int|30
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
)brace
id|CMOS_WRITE
c_func
(paren
id|real_seconds
comma
id|RTC_SECONDS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|real_minutes
comma
id|RTC_MINUTES
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* The following flags have to be released exactly in this order,&n;&t; * otherwise the DS12887 (popular MC146818A clone with integrated&n;&t; * battery and quartz) will not reset the oscillator and will not&n;&t; * update precisely 500 ms later. You won&squot;t find this mentioned in&n;&t; * the Dallas Semiconductor data sheets, but who believes data&n;&t; * sheets anyway ...                           -- Markus Kuhn&n;&t; */
id|CMOS_WRITE
c_func
(paren
id|save_control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|save_freq_select
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
