multiline_comment|/*&n; *  linux/arch/i386/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * This file contains the PC-specific time handling details:&n; * reading the RTC at bootup, etc..&n; * 1994-07-02    Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1995-03-26    Markus Kuhn&n; *      fixed 500 ms bug at call to set_rtc_mmss, fixed DS12887&n; *      precision CMOS clock update&n; * 1996-05-03    Ingo Molnar&n; *      fixed time warps in do_[slow|fast]_gettimeoffset()&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_int
id|setup_x86_irq
c_func
(paren
r_int
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
macro_line|#ifndef&t;CONFIG_APM&t;/* cycle counter may be unreliable */
multiline_comment|/* Cycle counter value at the previous timer interrupt.. */
r_static
r_struct
(brace
DECL|member|low
r_int
r_int
id|low
suffix:semicolon
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|variable|init_timer_cc
DECL|variable|last_timer_cc
)brace
id|init_timer_cc
comma
id|last_timer_cc
suffix:semicolon
multiline_comment|/*&n; * This is more assembly than C, but it&squot;s also rather&n; * timing-critical and we have to use assembler to get&n; * reasonable 64-bit arithmetic&n; */
DECL|function|do_fast_gettimeoffset
r_static
r_int
r_int
id|do_fast_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|eax
id|asm
c_func
(paren
l_string|&quot;ax&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|edx
id|asm
c_func
(paren
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_int
r_int
id|tmp
comma
id|quotient
comma
id|low_timer
comma
id|missing_time
suffix:semicolon
multiline_comment|/* Last jiffy when do_fast_gettimeoffset() was called.. */
r_static
r_int
r_int
id|last_jiffies
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Cached &quot;clocks per usec&quot; value.. */
r_static
r_int
r_int
id|cached_quotient
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The &quot;clocks per usec&quot; value is calculated once each jiffy */
id|tmp
op_assign
id|jiffies
suffix:semicolon
id|quotient
op_assign
id|cached_quotient
suffix:semicolon
id|low_timer
op_assign
id|last_timer_cc.low
suffix:semicolon
id|missing_time
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|last_jiffies
op_ne
id|tmp
)paren
(brace
id|last_jiffies
op_assign
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t;&t; * test for hanging bottom handler (this means xtime is not &n;&t;&t; * updated yet)&n;&t;&t; */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|TIMER_BH
comma
op_amp
id|bh_active
)paren
)paren
(brace
id|missing_time
op_assign
l_int|1000020
op_div
id|HZ
suffix:semicolon
)brace
multiline_comment|/* Get last timer tick in absolute kernel time */
id|eax
op_assign
id|low_timer
suffix:semicolon
id|edx
op_assign
id|last_timer_cc.high
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;subl &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|init_timer_cc
)paren
l_string|&quot;,%0&bslash;n&bslash;t&quot;
l_string|&quot;sbbl &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|init_timer_cc
)paren
l_string|&quot;+4,%1&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|eax
)paren
comma
l_string|&quot;1&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Divide the 64-bit time with the 32-bit jiffy counter,&n;&t;&t; * getting the quotient in clocks.&n;&t;&t; *&n;&t;&t; * Giving quotient = &quot;average internal clocks per usec&quot;&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
comma
l_string|&quot;1&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
id|edx
op_assign
l_int|1000020
op_div
id|HZ
suffix:semicolon
id|tmp
op_assign
id|eax
suffix:semicolon
id|eax
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
comma
l_string|&quot;1&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
id|cached_quotient
op_assign
id|eax
suffix:semicolon
id|quotient
op_assign
id|eax
suffix:semicolon
)brace
multiline_comment|/* Read the time counter */
id|__asm__
c_func
(paren
l_string|&quot;.byte 0x0f,0x31&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|edx
op_assign
l_int|0
suffix:semicolon
id|eax
op_sub_assign
id|low_timer
suffix:semicolon
multiline_comment|/*&n;&t; * Time offset = (1000020/HZ * time_low) / quotient.&n;&t; */
id|__asm__
c_func
(paren
l_string|&quot;mull %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|quotient
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
comma
l_string|&quot;1&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * Due to rounding errors (and jiffies inconsistencies),&n;&t; * we need to check the result so that we&squot;ll get a timer&n;&t; * that is monotonic.&n;&t; */
r_if
c_cond
(paren
id|edx
op_ge
l_int|1000020
op_div
id|HZ
)paren
id|edx
op_assign
l_int|1000020
op_div
id|HZ
op_minus
l_int|1
suffix:semicolon
id|eax
op_assign
id|edx
op_plus
id|missing_time
suffix:semicolon
r_return
id|eax
suffix:semicolon
)brace
macro_line|#endif
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
r_static
r_int
id|count_p
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|jiffies_p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * cache volatile jiffies temporarily; we have IRQs turned off. &n;&t; */
r_int
r_int
id|jiffies_t
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
id|jiffies_t
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; * avoiding timer inconsistencies (they are rare, but they happen)...&n;&t; * there are three kinds of problems that must be avoided here:&n;&t; *  1. the timer counter underflows&n;&t; *  2. hardware problem with the timer, not giving us continuous time,&n;&t; *     the counter does small &quot;jumps&quot; upwards on some Pentium systems,&n;&t; *     thus causes time warps&n;&t; *  3. we are after the timer interrupt, but the bottom half handler&n;&t; *     hasn&squot;t executed yet.&n;&t; */
r_if
c_cond
(paren
id|count
OG
id|count_p
)paren
(brace
r_if
c_cond
(paren
id|jiffies_t
op_eq
id|jiffies_p
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|LATCH
op_minus
id|LATCH
op_div
l_int|100
)paren
(brace
id|offset
op_assign
id|TICK_SIZE
suffix:semicolon
)brace
r_else
multiline_comment|/*&n;&t;&t;&t;&t; * argh, the timer is bugging we cant do nothing &n;&t;&t;&t;&t; * but to give the previous clock value.&n;&t;&t;&t;&t; */
id|count
op_assign
id|count_p
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|TIMER_BH
comma
op_amp
id|bh_active
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * we have detected a counter underflow.&n;&t;&t;&t; &t; */
id|offset
op_assign
id|TICK_SIZE
suffix:semicolon
id|count_p
op_assign
id|count
suffix:semicolon
)brace
r_else
(brace
id|count_p
op_assign
id|count
suffix:semicolon
id|jiffies_p
op_assign
id|jiffies_t
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|count_p
op_assign
id|count
suffix:semicolon
id|jiffies_p
op_assign
id|jiffies_t
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
multiline_comment|/*&n; * this is only used if we have fast gettimeoffset:&n; */
DECL|function|do_x86_get_fast_time
r_void
id|do_x86_get_fast_time
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|do_gettimeofday
c_func
(paren
id|tv
)paren
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
id|MAXPHASE
suffix:semicolon
id|time_esterror
op_assign
id|MAXPHASE
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
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
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
multiline_comment|/* As we return to user mode fire off the other CPU schedulers.. this is &n;&t;   basically because we don&squot;t yet share IRQ&squot;s around. This message is&n;&t;   rigged to be safe on the 386 - basically it&squot;s a hack, so don&squot;t look&n;&t;   closely for now.. */
multiline_comment|/*smp_message_pass(MSG_ALL_BUT_SELF, MSG_RESCHEDULE, 0L, 0); */
)brace
macro_line|#ifndef&t;CONFIG_APM&t;/* cycle counter may be unreliable */
multiline_comment|/*&n; * This is the same as the above, except we _also_ save the current&n; * cycle counter value at the time of the timer interrupt, so that&n; * we later on can estimate the time of day more exactly.&n; */
DECL|function|pentium_timer_interrupt
r_static
r_void
id|pentium_timer_interrupt
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
multiline_comment|/* read Pentium cycle counter */
id|__asm__
c_func
(paren
l_string|&quot;.byte 0x0f,0x31&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|last_timer_cc.low
)paren
comma
l_string|&quot;=d&quot;
(paren
id|last_timer_cc.high
)paren
)paren
suffix:semicolon
id|timer_interrupt
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
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
DECL|variable|irq0
r_static
r_struct
id|irqaction
id|irq0
op_assign
(brace
id|timer_interrupt
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
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
macro_line|#ifndef CONFIG_APM
multiline_comment|/* Don&squot;t use them if a suspend/resume could&n;                                   corrupt the timer value.  This problem&n;                                   needs more debugging. */
r_if
c_cond
(paren
id|x86_capability
op_amp
l_int|16
)paren
(brace
id|do_gettimeoffset
op_assign
id|do_fast_gettimeoffset
suffix:semicolon
id|do_get_fast_time
op_assign
id|do_x86_get_fast_time
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|x86_vendor_id
comma
l_string|&quot;AuthenticAMD&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|x86
op_eq
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|x86_model
op_eq
l_int|0
)paren
(brace
multiline_comment|/* turn on cycle counters during power down */
id|__asm__
id|__volatile__
(paren
l_string|&quot; movl $0x83, %%ecx &bslash;n &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;.byte 0x0f,0x32 &bslash;n &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;orl $1,%%eax &bslash;n &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;.byte 0x0f,0x30 &bslash;n &quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* read Pentium cycle counter */
id|__asm__
c_func
(paren
l_string|&quot;.byte 0x0f,0x31&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|init_timer_cc.low
)paren
comma
l_string|&quot;=d&quot;
(paren
id|init_timer_cc.high
)paren
)paren
suffix:semicolon
id|irq0.handler
op_assign
id|pentium_timer_interrupt
suffix:semicolon
)brace
macro_line|#endif
id|setup_x86_irq
c_func
(paren
l_int|0
comma
op_amp
id|irq0
)paren
suffix:semicolon
)brace
eof
