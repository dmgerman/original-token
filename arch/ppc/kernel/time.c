multiline_comment|/*&n; *  linux/arch/i386/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * Adapted for PowerPC (PreP) by Gary Thomas&n; *&n; * This file contains the PC-specific time handling details:&n; * reading the RTC at bootup, etc..&n; * 1994-07-02    Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1995-03-26    Markus Kuhn&n; *      fixed 500 ms bug at call to set_rtc_mmss, fixed DS12887&n; *      precision CMOS clock update&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_int
id|isBeBox
(braket
)braket
suffix:semicolon
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
multiline_comment|/* Cycle counter value at the previous timer interrupt.. */
DECL|variable|last_timer_cc
r_static
r_int
r_int
r_int
id|last_timer_cc
op_assign
l_int|0
suffix:semicolon
DECL|variable|init_timer_cc
r_static
r_int
r_int
r_int
id|init_timer_cc
op_assign
l_int|0
suffix:semicolon
DECL|function|CMOS_READ
r_static
r_inline
r_int
id|CMOS_READ
c_func
(paren
r_int
id|addr
)paren
(brace
id|outb
c_func
(paren
id|addr
op_rshift
l_int|8
comma
id|NVRAM_AS1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|addr
comma
id|NVRAM_AS0
)paren
suffix:semicolon
r_return
(paren
id|inb
c_func
(paren
id|NVRAM_DATA
)paren
)paren
suffix:semicolon
)brace
DECL|function|CMOS_WRITE
r_static
r_inline
r_int
id|CMOS_WRITE
c_func
(paren
r_int
id|addr
comma
r_int
id|val
)paren
(brace
id|outb
c_func
(paren
id|addr
op_rshift
l_int|8
comma
id|NVRAM_AS1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|addr
comma
id|NVRAM_AS0
)paren
suffix:semicolon
r_return
(paren
id|outb
c_func
(paren
id|val
comma
id|NVRAM_DATA
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This function must be called with interrupts disabled &n; * It was inspired by Steve McCanne&squot;s microtime-i386 for BSD.  -- jrs&n; * &n; * However, the pc-audio speaker driver changes the divisor so that&n; * it gets interrupted rather more often - it loads 64 into the&n; * counter rather than 11932! This has an adverse impact on&n; * do_gettimeoffset() -- it stops working! What is also not&n; * good is that the interval that our timer function gets called&n; * is no longer 10.0002 ms, but 9.9767 ms. To get around this&n; * would require using a different timing source. Maybe someone&n; * could use the RTC - I know that this can interrupt at frequencies&n; * ranging from 8192Hz to 2Hz. If I had the energy, I&squot;d somehow fix&n; * it so that at startup, the timer code in sched.c would select&n; * using either the RTC or the 8253 timer. The decision would be&n; * based on whether there was any other device around that needed&n; * to trample on the 8253. I&squot;d set up the RTC to interrupt at 1024 Hz,&n; * and then do some jiggery to have a version of do_timer that &n; * advanced the clock by 1/1024 s. Every time that reached over 1/100&n; * of a second, then do all the old code. If the time was kept correct&n; * then do_gettimeoffset could just return 0 - there is no low order&n; * divider that can be accessed.&n; *&n; * Ideally, you would be able to use the RTC for the speaker driver,&n; * but it appears that the speaker driver really needs interrupt more&n; * often than every 120 us or so.&n; *&n; * Anyway, this needs more thought....&t;&t;pjsg (1993-08-28)&n; * &n; * If you are really that interested, you should be reading&n; * comp.protocols.time.ntp!&n; */
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|function|do_slow_gettimeoffset
r_static
r_int
r_int
id|do_slow_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
id|count
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|count
op_or_assign
id|inb
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* we know probability of underflow is always MUCH less than 1% */
r_if
c_cond
(paren
id|count
OG
(paren
id|LATCH
op_minus
id|LATCH
op_div
l_int|100
)paren
)paren
(brace
multiline_comment|/* check for pending timer interrupt */
id|outb_p
c_func
(paren
l_int|0x0a
comma
l_int|0x20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|1
)paren
id|offset
op_assign
id|TICK_SIZE
suffix:semicolon
)brace
id|count
op_assign
(paren
(paren
id|LATCH
op_minus
l_int|1
)paren
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|offset
op_plus
id|count
suffix:semicolon
)brace
DECL|variable|do_gettimeoffset
r_static
r_int
r_int
(paren
op_star
id|do_gettimeoffset
)paren
(paren
r_void
)paren
op_assign
id|do_slow_gettimeoffset
suffix:semicolon
multiline_comment|/*&n; * This version of gettimeofday has near microsecond resolution.&n; */
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
id|tv-&gt;tv_usec
op_add_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tv-&gt;tv_usec
op_ge
l_int|1000000
)paren
(brace
id|tv-&gt;tv_usec
op_sub_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_increment
suffix:semicolon
)brace
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
multiline_comment|/* This is revolting. We need to set the xtime.tv_usec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
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
id|set_rtc
c_func
(paren
id|xtime.tv_sec
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
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
DECL|struct|_tm
r_struct
id|_tm
(brace
DECL|member|tm_sec
r_int
id|tm_sec
suffix:semicolon
DECL|member|tm_min
r_int
id|tm_min
suffix:semicolon
DECL|member|tm_hour
r_int
id|tm_hour
suffix:semicolon
DECL|member|tm_day
r_int
id|tm_day
suffix:semicolon
DECL|member|tm_month
r_int
id|tm_month
suffix:semicolon
DECL|member|tm_year
r_int
id|tm_year
suffix:semicolon
)brace
suffix:semicolon
DECL|function|_to_tm
r_static
id|_to_tm
c_func
(paren
r_int
id|tim
comma
r_struct
id|_tm
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
id|tm-&gt;tm_month
op_assign
id|i
suffix:semicolon
multiline_comment|/* Days are what is left over (+1) from all that. */
id|tm-&gt;tm_day
op_assign
id|day
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the time into the CMOS&n; */
DECL|function|set_rtc
r_static
r_void
id|set_rtc
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
r_struct
id|_tm
id|tm
suffix:semicolon
r_int
r_char
id|save_control
comma
id|save_freq_select
suffix:semicolon
multiline_comment|/*if (_Processor != _PROC_IBM) return;*/
id|_to_tm
c_func
(paren
id|nowtime
comma
op_amp
id|tm
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
id|save_control
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_CONTROL
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
(paren
id|save_control
op_or
id|MCRTC_SET
)paren
comma
id|MCRTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
id|save_freq_select
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_FREQ_SELECT
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
(paren
id|save_freq_select
op_or
id|MCRTC_DIV_RESET2
)paren
comma
id|MCRTC_FREQ_SELECT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Set RTC H:M:S M/D/Y %d:%02d:%02d %d/%d/%d&bslash;n&quot;
comma
id|tm.tm_hour
comma
id|tm.tm_min
comma
id|tm.tm_sec
comma
id|tm.tm_month
comma
id|tm.tm_day
comma
id|tm.tm_year
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|MCRTC_DM_BINARY
)paren
op_logical_or
id|MCRTC_ALWAYS_BCD
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_month
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_day
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_year
)paren
suffix:semicolon
)brace
id|CMOS_MCRTC_WRITE
c_func
(paren
id|tm.tm_sec
comma
id|MCRTC_SECONDS
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|tm.tm_min
comma
id|MCRTC_MINUTES
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|tm.tm_hour
comma
id|MCRTC_HOURS
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|tm.tm_month
comma
id|MCRTC_MONTH
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|tm.tm_day
comma
id|MCRTC_MINUTES
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|tm.tm_year
op_minus
l_int|1900
comma
id|MCRTC_MINUTES
)paren
suffix:semicolon
multiline_comment|/* The following flags have to be released exactly in this order,&n;&t; * otherwise the DS12887 (popular MC146818A clone with integrated&n;&t; * battery and quartz) will not reset the oscillator and will not&n;&t; * update precisely 500 ms later. You won&squot;t find this mentioned in&n;&t; * the Dallas Semiconductor data sheets, but who believes data&n;&t; * sheets anyway ...                           -- Markus Kuhn&n;&t; */
id|CMOS_MCRTC_WRITE
c_func
(paren
id|save_control
comma
id|MCRTC_CONTROL
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|save_freq_select
comma
id|MCRTC_FREQ_SELECT
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
macro_line|#ifdef __powerpc__
id|printk
c_func
(paren
l_string|&quot;%s: %d - set TOD&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Not implemented */
macro_line|#else&t;
id|printk
c_func
(paren
l_string|&quot;%s: %d - set TOD&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
)paren
suffix:semicolon
id|save_control
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
id|CMOS_MCRTC_WRITE
c_func
(paren
(paren
id|save_control
op_or
id|MCRTC_SET
)paren
comma
id|MCRTC_CONTROL
)paren
suffix:semicolon
id|save_freq_select
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_FREQ_SELECT
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
id|CMOS_MCRTC_WRITE
c_func
(paren
(paren
id|save_freq_select
op_or
id|MCRTC_DIV_RESET2
)paren
comma
id|MCRTC_FREQ_SELECT
)paren
suffix:semicolon
id|cmos_minutes
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_MINUTES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|MCRTC_DM_BINARY
)paren
op_logical_or
id|MCRTC_ALWAYS_BCD
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
id|MCRTC_DM_BINARY
)paren
op_logical_or
id|MCRTC_ALWAYS_BCD
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
id|CMOS_MCRTC_WRITE
c_func
(paren
id|real_seconds
comma
id|MCRTC_SECONDS
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|real_minutes
comma
id|MCRTC_MINUTES
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
id|CMOS_MCRTC_WRITE
c_func
(paren
id|save_control
comma
id|MCRTC_CONTROL
)paren
suffix:semicolon
id|CMOS_MCRTC_WRITE
c_func
(paren
id|save_freq_select
comma
id|MCRTC_FREQ_SELECT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
macro_line|#endif&t;
)brace
multiline_comment|/* last time the cmos clock got updated */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|timer_interrupt
r_static
r_inline
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
r_static
r_int
id|timeints
op_assign
l_int|0
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;   * If we have an externally synchronized Linux clock, then update&n;   * CMOS clock accordingly every ~11 minutes. Set_rtc_mmss() has to be&n;   * called as close as possible to 500 ms before the new second starts.&n;   */
r_if
c_cond
(paren
id|time_state
op_ne
id|TIME_BAD
op_logical_and
id|xtime.tv_sec
OG
id|last_rtc_update
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
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
r_else
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
multiline_comment|/* do it again in 60 s */
multiline_comment|/* use hard disk LED as a heartbeat instead -- much more useful&n;     -- Cort */
r_switch
c_cond
(paren
id|timeints
)paren
(brace
multiline_comment|/* act like an actual heart beat -- ie thump-thump-pause... */
r_case
l_int|0
suffix:colon
r_case
l_int|20
suffix:colon
id|hard_disk_LED
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
r_case
l_int|27
suffix:colon
id|hard_disk_LED
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|100
suffix:colon
id|timeints
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|timeints
op_increment
suffix:semicolon
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
DECL|function|get_cmos_time
r_int
r_int
id|get_cmos_time
c_func
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
id|_Processor
op_eq
id|_PROC_IBM
)paren
(brace
r_do
(brace
multiline_comment|/* Isn&squot;t this overkill ? UIP above should guarantee consistency */
id|sec
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_YEAR
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_SECONDS
)paren
)paren
suffix:semicolon
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
r_else
r_if
c_cond
(paren
id|_Processor
op_eq
id|_PROC_Be
)paren
(brace
r_do
(brace
multiline_comment|/* Isn&squot;t this overkill ? UIP above should guarantee consistency */
id|sec
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_YEAR
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|CMOS_MCRTC_READ
c_func
(paren
id|MCRTC_SECONDS
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Motorola PowerStack etc. */
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
macro_line|#if 0&t;
id|printk
c_func
(paren
l_string|&quot;CMOS TOD - M/D/Y H:M:S = %d/%d/%d %d:%02d:%02d&bslash;n&quot;
comma
id|mon
comma
id|day
comma
id|year
comma
id|hour
comma
id|min
comma
id|sec
)paren
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
r_return
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
)brace
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|get_cmos_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If we have the CPU hardware time counters, use them */
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
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Could not allocate timer IRQ!&quot;
)paren
suffix:semicolon
)brace
eof
