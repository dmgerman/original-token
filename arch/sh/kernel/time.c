multiline_comment|/* $Id: time.c,v 1.20 2000/02/28 12:42:51 gniibe Exp $&n; *&n; *  linux/arch/sh/kernel/time.c&n; *&n; *  Copyright (C) 1999  Tetsuya Okada &amp; Niibe Yutaka&n; *&n; *  Some code taken from i386 version.&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
DECL|macro|TMU_TOCR_INIT
mdefine_line|#define TMU_TOCR_INIT&t;0x00
DECL|macro|TMU0_TCR_INIT
mdefine_line|#define TMU0_TCR_INIT&t;0x0020
DECL|macro|TMU_TSTR_INIT
mdefine_line|#define TMU_TSTR_INIT&t;1
multiline_comment|/* RCR1 Bits */
DECL|macro|RCR1_CF
mdefine_line|#define RCR1_CF&t;&t;0x80&t;/* Carry Flag             */
DECL|macro|RCR1_CIE
mdefine_line|#define RCR1_CIE&t;0x10&t;/* Carry Interrupt Enable */
DECL|macro|RCR1_AIE
mdefine_line|#define RCR1_AIE&t;0x08&t;/* Alarm Interrupt Enable */
DECL|macro|RCR1_AF
mdefine_line|#define RCR1_AF&t;&t;0x01&t;/* Alarm Flag             */
multiline_comment|/* RCR2 Bits */
DECL|macro|RCR2_PEF
mdefine_line|#define RCR2_PEF&t;0x80&t;/* PEriodic interrupt Flag */
DECL|macro|RCR2_PESMASK
mdefine_line|#define RCR2_PESMASK&t;0x70&t;/* Periodic interrupt Set  */
DECL|macro|RCR2_RTCEN
mdefine_line|#define RCR2_RTCEN&t;0x08&t;/* ENable RTC              */
DECL|macro|RCR2_ADJ
mdefine_line|#define RCR2_ADJ&t;0x04&t;/* ADJustment (30-second)  */
DECL|macro|RCR2_RESET
mdefine_line|#define RCR2_RESET&t;0x02&t;/* Reset bit               */
DECL|macro|RCR2_START
mdefine_line|#define RCR2_START&t;0x01&t;/* Start bit               */
macro_line|#if defined(__sh3__)
DECL|macro|TMU_TOCR
mdefine_line|#define TMU_TOCR&t;0xfffffe90&t;/* Byte access */
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR&t;0xfffffe92&t;/* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR&t;0xfffffe94&t;/* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT&t;0xfffffe98&t;/* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR&t;0xfffffe9c&t;/* Word access */
DECL|macro|FRQCR
mdefine_line|#define FRQCR&t;&t;0xffffff80
multiline_comment|/* SH-3 RTC */
DECL|macro|R64CNT
mdefine_line|#define R64CNT  &t;0xfffffec0
DECL|macro|RSECCNT
mdefine_line|#define RSECCNT &t;0xfffffec2
DECL|macro|RMINCNT
mdefine_line|#define RMINCNT &t;0xfffffec4
DECL|macro|RHRCNT
mdefine_line|#define RHRCNT  &t;0xfffffec6
DECL|macro|RWKCNT
mdefine_line|#define RWKCNT  &t;0xfffffec8
DECL|macro|RDAYCNT
mdefine_line|#define RDAYCNT &t;0xfffffeca
DECL|macro|RMONCNT
mdefine_line|#define RMONCNT &t;0xfffffecc
DECL|macro|RYRCNT
mdefine_line|#define RYRCNT  &t;0xfffffece
DECL|macro|RSECAR
mdefine_line|#define RSECAR  &t;0xfffffed0
DECL|macro|RMINAR
mdefine_line|#define RMINAR  &t;0xfffffed2
DECL|macro|RHRAR
mdefine_line|#define RHRAR   &t;0xfffffed4
DECL|macro|RWKAR
mdefine_line|#define RWKAR   &t;0xfffffed6
DECL|macro|RDAYAR
mdefine_line|#define RDAYAR  &t;0xfffffed8
DECL|macro|RMONAR
mdefine_line|#define RMONAR  &t;0xfffffeda
DECL|macro|RCR1
mdefine_line|#define RCR1    &t;0xfffffedc
DECL|macro|RCR2
mdefine_line|#define RCR2    &t;0xfffffede
macro_line|#elif defined(__SH4__)
DECL|macro|TMU_TOCR
mdefine_line|#define TMU_TOCR&t;0xffd80000&t;/* Byte access */
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR&t;0xffd80004&t;/* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR&t;0xffd80008&t;/* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT&t;0xffd8000c&t;/* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR&t;0xffd80010&t;/* Word access */
DECL|macro|FRQCR
mdefine_line|#define FRQCR&t;&t;0xffc00000
multiline_comment|/* SH-4 RTC */
DECL|macro|R64CNT
mdefine_line|#define R64CNT  &t;0xffc80000
DECL|macro|RSECCNT
mdefine_line|#define RSECCNT &t;0xffc80004
DECL|macro|RMINCNT
mdefine_line|#define RMINCNT &t;0xffc80008
DECL|macro|RHRCNT
mdefine_line|#define RHRCNT  &t;0xffc8000c
DECL|macro|RWKCNT
mdefine_line|#define RWKCNT  &t;0xffc80010
DECL|macro|RDAYCNT
mdefine_line|#define RDAYCNT &t;0xffc80014
DECL|macro|RMONCNT
mdefine_line|#define RMONCNT &t;0xffc80018
DECL|macro|RYRCNT
mdefine_line|#define RYRCNT  &t;0xffc8001c  /* 16bit */
DECL|macro|RSECAR
mdefine_line|#define RSECAR  &t;0xffc80020
DECL|macro|RMINAR
mdefine_line|#define RMINAR  &t;0xffc80024
DECL|macro|RHRAR
mdefine_line|#define RHRAR   &t;0xffc80028
DECL|macro|RWKAR
mdefine_line|#define RWKAR   &t;0xffc8002c
DECL|macro|RDAYAR
mdefine_line|#define RDAYAR  &t;0xffc80030
DECL|macro|RMONAR
mdefine_line|#define RMONAR  &t;0xffc80034
DECL|macro|RCR1
mdefine_line|#define RCR1    &t;0xffc80038
DECL|macro|RCR2
mdefine_line|#define RCR2    &t;0xffc8003c
macro_line|#endif
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
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
r_extern
r_volatile
r_int
r_int
id|lost_ticks
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
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
id|usec
op_assign
l_int|0
suffix:semicolon
(brace
r_int
r_int
id|lost
op_assign
id|lost_ticks
suffix:semicolon
r_if
c_cond
(paren
id|lost
)paren
id|usec
op_add_assign
id|lost
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
)brace
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_add_assign
id|xtime.tv_usec
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
id|sec
op_increment
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
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
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
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
DECL|function|set_rtc_time
r_static
r_int
id|set_rtc_time
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
id|ctrl_outb
c_func
(paren
id|RCR2_RESET
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Reset pre-scaler &amp; stop RTC */
id|cmos_minutes
op_assign
id|ctrl_inb
c_func
(paren
id|RMINCNT
)paren
suffix:semicolon
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
id|ctrl_outb
c_func
(paren
id|real_seconds
comma
id|RSECCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|real_minutes
comma
id|RMINCNT
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_time: can&squot;t update from %d to %d&bslash;n&quot;
comma
id|cmos_minutes
comma
id|real_minutes
)paren
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|ctrl_outb
c_func
(paren
id|RCR2_RTCEN
op_or
id|RCR2_START
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Start RTC */
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* last time the RTC clock got updated */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|do_timer_interrupt
r_static
r_inline
r_void
id|do_timer_interrupt
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
macro_line|#if 0
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
id|sh_do_profile
c_func
(paren
id|regs-&gt;pc
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * RTC clock accordingly every ~11 minutes. Set_rtc_mmss() has to be&n;&t; * called as close as possible to 500 ms before the new second starts.&n;&t; */
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
OG
id|last_rtc_update
op_plus
l_int|660
op_logical_and
id|xtime.tv_usec
op_ge
l_int|500000
op_minus
(paren
(paren
r_int
)paren
id|tick
)paren
op_div
l_int|2
op_logical_and
id|xtime.tv_usec
op_le
l_int|500000
op_plus
(paren
(paren
r_int
)paren
id|tick
)paren
op_div
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|set_rtc_time
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
)brace
)brace
multiline_comment|/*&n; * This is the same as the above, except we _also_ save the current&n; * Time Stamp Counter value at the time of the timer interrupt, so that&n; * we later on can estimate the time of day more exactly.&n; */
DECL|function|timer_interrupt
r_static
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
r_int
r_int
id|timer_status
suffix:semicolon
multiline_comment|/* Clear UNF bit */
id|timer_status
op_assign
id|ctrl_inw
c_func
(paren
id|TMU0_TCR
)paren
suffix:semicolon
id|timer_status
op_and_assign
op_complement
l_int|0x100
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|timer_status
comma
id|TMU0_TCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Here we are in the timer irq handler. We just have irqs locally&n;&t; * disabled but we don&squot;t know if the timer_bh is running on the other&n;&t; * CPU. We need to avoid to SMP race with it. NOTE: we don&squot; t need&n;&t; * the irq version of write_lock because as just said we have irq&n;&t; * locally disabled. -arca&n;&t; */
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|do_timer_interrupt
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
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
DECL|function|get_rtc_time
r_static
r_int
r_int
id|get_rtc_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sec
comma
id|min
comma
id|hr
comma
id|wk
comma
id|day
comma
id|mon
comma
id|yr
comma
id|yr100
suffix:semicolon
id|again
suffix:colon
r_do
(brace
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RCR1
)paren
suffix:semicolon
multiline_comment|/* Clear CF-bit */
id|sec
op_assign
id|ctrl_inb
c_func
(paren
id|RSECCNT
)paren
suffix:semicolon
id|min
op_assign
id|ctrl_inb
c_func
(paren
id|RMINCNT
)paren
suffix:semicolon
id|hr
op_assign
id|ctrl_inb
c_func
(paren
id|RHRCNT
)paren
suffix:semicolon
id|wk
op_assign
id|ctrl_inb
c_func
(paren
id|RWKCNT
)paren
suffix:semicolon
id|day
op_assign
id|ctrl_inb
c_func
(paren
id|RDAYCNT
)paren
suffix:semicolon
id|mon
op_assign
id|ctrl_inb
c_func
(paren
id|RMONCNT
)paren
suffix:semicolon
macro_line|#if defined(__SH4__)
id|yr
op_assign
id|ctrl_inw
c_func
(paren
id|RYRCNT
)paren
suffix:semicolon
id|yr100
op_assign
(paren
id|yr
op_rshift
l_int|8
)paren
suffix:semicolon
id|yr
op_and_assign
l_int|0xff
suffix:semicolon
macro_line|#else
id|yr
op_assign
id|ctrl_inb
c_func
(paren
id|RYRCNT
)paren
suffix:semicolon
id|yr100
op_assign
(paren
id|yr
op_eq
l_int|0x99
)paren
ques
c_cond
l_int|0x19
suffix:colon
l_int|0x20
suffix:semicolon
macro_line|#endif
)brace
r_while
c_loop
(paren
(paren
id|ctrl_inb
c_func
(paren
id|RCR1
)paren
op_amp
id|RCR1_CF
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|yr100
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|yr
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
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hr
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
id|sec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|yr
OG
l_int|99
op_logical_or
id|mon
template_param
l_int|12
op_logical_or
id|day
OG
l_int|31
op_logical_or
id|day
template_param
l_int|23
op_logical_or
id|min
OG
l_int|59
op_logical_or
id|sec
OG
l_int|59
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SH RTC: invalid value, resetting to 1 Jan 2000&bslash;n&quot;
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|RCR2_RESET
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Reset &amp; Stop */
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RSECCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RMINCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RHRCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|6
comma
id|RWKCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|RDAYCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|RMONCNT
)paren
suffix:semicolon
macro_line|#if defined(__SH4__)
id|ctrl_outw
c_func
(paren
l_int|0x2000
comma
id|RYRCNT
)paren
suffix:semicolon
macro_line|#else
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RYRCNT
)paren
suffix:semicolon
macro_line|#endif
id|ctrl_outb
c_func
(paren
id|RCR2_RTCEN
op_or
id|RCR2_START
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Start */
r_goto
id|again
suffix:semicolon
)brace
r_return
id|mktime
c_func
(paren
id|yr100
op_star
l_int|100
op_plus
id|yr
comma
id|mon
comma
id|day
comma
id|hr
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
DECL|function|get_cpu_mhz
r_static
id|__init
r_int
r_int
id|get_cpu_mhz
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|__dummy
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
id|ctrl_inb
c_func
(paren
id|R64CNT
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|RCR1_CIE
comma
id|RCR1
)paren
suffix:semicolon
multiline_comment|/* Enable carry interrupt */
id|asm
r_volatile
(paren
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;tst&t;%1,%1&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|count
)paren
comma
l_string|&quot;=z&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;1&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SH-3:&n;&t; * CPU clock = 4 stages * loop&n;&t; * tst    rm,rm      if id ex&n;&t; * bt/s   1b            if id ex&n;&t; * add    #1,rd            if id ex&n;         *                            (if) pipe line stole&n;&t; * tst    rm,rm                  if id ex&n;         * ....&n;&t; *&n;&t; *&n;&t; * SH-4:&n;&t; * CPU clock = 6 stages * loop&n;&t; * I don&squot;t know why.&n;         * ....&n;&t; */
macro_line|#if defined(__SH4__)
r_return
id|count
op_star
l_int|6
suffix:semicolon
macro_line|#else
r_return
id|count
op_star
l_int|4
suffix:semicolon
macro_line|#endif
)brace
DECL|function|rtc_interrupt
r_static
r_void
id|rtc_interrupt
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
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RCR1
)paren
suffix:semicolon
multiline_comment|/* Disable Carry Interrupts */
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
l_int|1
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
id|SA_INTERRUPT
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
DECL|variable|irq1
r_static
r_struct
id|irqaction
id|irq1
op_assign
(brace
id|rtc_interrupt
comma
id|SA_INTERRUPT
comma
l_int|0
comma
l_string|&quot;rtc&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cpu_clock
comma
id|master_clock
comma
id|bus_clock
comma
id|module_clock
suffix:semicolon
r_int
r_int
id|frqcr
comma
id|ifc
comma
id|pfc
suffix:semicolon
r_int
r_int
id|interval
suffix:semicolon
macro_line|#if defined(__sh3__)
r_static
r_int
id|ifc_table
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|1
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|pfc_table
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|1
comma
l_int|3
comma
l_int|6
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|stc_table
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
macro_line|#elif defined(__SH4__)
r_static
r_int
id|ifc_table
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
mdefine_line|#define bfc_table ifc_table&t;/* Same */
r_static
r_int
id|pfc_table
(braket
)braket
op_assign
(brace
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|2
comma
l_int|2
comma
l_int|2
)brace
suffix:semicolon
macro_line|#endif
id|xtime.tv_sec
op_assign
id|get_rtc_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
id|setup_irq
c_func
(paren
id|TIMER_IRQ
comma
op_amp
id|irq0
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|RTC_IRQ
comma
op_amp
id|irq1
)paren
suffix:semicolon
multiline_comment|/* Check how fast it is.. */
id|cpu_clock
op_assign
id|get_cpu_mhz
c_func
(paren
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|RTC_IRQ
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|cpu_clock
op_div
l_int|1000000
)paren
comma
(paren
id|cpu_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
macro_line|#if defined(__sh3__)
(brace
r_int
r_int
id|tmp
comma
id|stc
suffix:semicolon
id|frqcr
op_assign
id|ctrl_inw
c_func
(paren
id|FRQCR
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|frqcr
op_amp
l_int|0x8000
)paren
op_rshift
l_int|13
suffix:semicolon
id|tmp
op_or_assign
(paren
id|frqcr
op_amp
l_int|0x0030
)paren
op_rshift
l_int|4
suffix:semicolon
id|stc
op_assign
id|stc_table
(braket
id|tmp
)braket
suffix:semicolon
id|tmp
op_assign
(paren
id|frqcr
op_amp
l_int|0x4000
)paren
op_rshift
l_int|12
suffix:semicolon
id|tmp
op_or_assign
(paren
id|frqcr
op_amp
l_int|0x000c
)paren
op_rshift
l_int|2
suffix:semicolon
id|ifc
op_assign
id|ifc_table
(braket
id|tmp
)braket
suffix:semicolon
id|tmp
op_assign
(paren
id|frqcr
op_amp
l_int|0x2000
)paren
op_rshift
l_int|11
suffix:semicolon
id|tmp
op_or_assign
id|frqcr
op_amp
l_int|0x0003
suffix:semicolon
id|pfc
op_assign
id|pfc_table
(braket
id|tmp
)braket
suffix:semicolon
id|master_clock
op_assign
id|cpu_clock
suffix:semicolon
id|bus_clock
op_assign
id|master_clock
op_div
id|pfc
suffix:semicolon
)brace
macro_line|#elif defined(__SH4__)
(brace
r_int
r_int
id|bfc
suffix:semicolon
id|frqcr
op_assign
id|ctrl_inw
c_func
(paren
id|FRQCR
)paren
suffix:semicolon
id|ifc
op_assign
id|ifc_table
(braket
(paren
id|frqcr
op_rshift
l_int|6
)paren
op_amp
l_int|0x0007
)braket
suffix:semicolon
id|bfc
op_assign
id|bfc_table
(braket
(paren
id|frqcr
op_rshift
l_int|3
)paren
op_amp
l_int|0x0007
)braket
suffix:semicolon
id|pfc
op_assign
id|pfc_table
(braket
id|frqcr
op_amp
l_int|0x0007
)braket
suffix:semicolon
id|master_clock
op_assign
id|cpu_clock
op_star
id|ifc
suffix:semicolon
id|bus_clock
op_assign
id|master_clock
op_div
id|bfc
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Bus clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|bus_clock
op_div
l_int|1000000
)paren
comma
(paren
id|bus_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
id|module_clock
op_assign
id|master_clock
op_div
id|pfc
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Module clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|module_clock
op_div
l_int|1000000
)paren
comma
(paren
id|module_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
id|interval
op_assign
(paren
id|module_clock
op_div
(paren
id|HZ
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Interval = %ld&bslash;n&quot;
comma
id|interval
)paren
suffix:semicolon
multiline_comment|/* Start TMU0 */
id|ctrl_outb
c_func
(paren
id|TMU_TOCR_INIT
comma
id|TMU_TOCR
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|TMU0_TCR_INIT
comma
id|TMU0_TCR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|interval
comma
id|TMU0_TCOR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|interval
comma
id|TMU0_TCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|TMU_TSTR_INIT
comma
id|TMU_TSTR
)paren
suffix:semicolon
)brace
eof
