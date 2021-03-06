multiline_comment|/* $Id: indy_timer.c,v 1.17 2000/01/21 22:34:03 ralf Exp $&n; *&n; * indy_timer.c: Setting up the clock on the INDY 8254 controller.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copytight (C) 1997, 1998 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/sgi.h&gt;
macro_line|#include &lt;asm/sgi/sgihpc.h&gt;
macro_line|#include &lt;asm/sgi/sgint23.h&gt;
multiline_comment|/* Because of a bug in the i8254 timer we need to use the onchip r4k&n; * counter as our system wide timer interrupt running at 100HZ.&n; */
DECL|variable|r4k_offset
r_static
r_int
r_int
id|r4k_offset
suffix:semicolon
multiline_comment|/* Amount to increment compare reg each time */
DECL|variable|r4k_cur
r_static
r_int
r_int
id|r4k_cur
suffix:semicolon
multiline_comment|/* What counter should be at next timer irq */
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
DECL|function|ack_r4ktimer
r_static
r_inline
r_void
id|ack_r4ktimer
c_func
(paren
r_int
r_int
id|newval
)paren
(brace
id|write_32bit_cp0_register
c_func
(paren
id|CP0_COMPARE
comma
id|newval
)paren
suffix:semicolon
)brace
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
r_struct
id|indy_clock
op_star
id|clock
op_assign
(paren
r_struct
id|indy_clock
op_star
)paren
id|INDY_CLOCK_REGS
suffix:semicolon
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
id|clock_minutes
suffix:semicolon
DECL|macro|FROB_FROM_CLOCK
mdefine_line|#define FROB_FROM_CLOCK(x) (((x) &amp; 0xf) | ((((x) &amp; 0xf0) &gt;&gt; 4) * 10));
DECL|macro|FROB_TO_CLOCK
mdefine_line|#define FROB_TO_CLOCK(x)  ((((((x) &amp; 0xff) / 10)&lt;&lt;4) | (((x) &amp; 0xff) % 10)) &amp; 0xff)
id|clock-&gt;cmd
op_and_assign
op_complement
(paren
l_int|0x80
)paren
suffix:semicolon
id|clock_minutes
op_assign
id|clock-&gt;min
suffix:semicolon
id|clock-&gt;cmd
op_or_assign
(paren
l_int|0x80
)paren
suffix:semicolon
id|clock_minutes
op_assign
id|FROB_FROM_CLOCK
c_func
(paren
id|clock_minutes
)paren
suffix:semicolon
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
id|clock_minutes
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
(brace
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
)brace
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
id|clock_minutes
)paren
OL
l_int|30
)paren
(brace
multiline_comment|/* Force clock oscillator to be on. */
id|clock-&gt;month
op_and_assign
op_complement
(paren
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Write real_seconds and real_minutes into the Dallas. */
id|clock-&gt;cmd
op_and_assign
op_complement
(paren
l_int|0x80
)paren
suffix:semicolon
id|clock-&gt;sec
op_assign
id|real_seconds
suffix:semicolon
id|clock-&gt;min
op_assign
id|real_minutes
suffix:semicolon
id|clock-&gt;cmd
op_or_assign
(paren
l_int|0x80
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
l_int|1
suffix:semicolon
DECL|macro|FROB_FROM_CLOCK
macro_line|#undef FROB_FROM_CLOCK
DECL|macro|FROB_TO_CLOCK
macro_line|#undef FROB_TO_CLOCK
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
suffix:semicolon
DECL|variable|missed_heart_beats
r_int
r_int
id|missed_heart_beats
suffix:semicolon
DECL|function|indy_timer_interrupt
r_void
id|indy_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
r_int
id|irq
op_assign
l_int|7
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* Ack timer and compute new compare. */
id|count
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
)paren
suffix:semicolon
multiline_comment|/* This has races.  */
r_if
c_cond
(paren
(paren
id|count
op_minus
id|r4k_cur
)paren
op_ge
id|r4k_offset
)paren
(brace
multiline_comment|/* If this happens to often we&squot;ll need to compensate.  */
id|missed_heart_beats
op_increment
suffix:semicolon
id|r4k_cur
op_assign
id|count
op_plus
id|r4k_offset
suffix:semicolon
)brace
r_else
id|r4k_cur
op_add_assign
id|r4k_offset
suffix:semicolon
id|ack_r4ktimer
c_func
(paren
id|r4k_cur
)paren
suffix:semicolon
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* We update the Dallas time of day approx. every 11 minutes,&n;&t; * because of how the numbers work out we need to make&n;&t; * absolutely sure we do this update within 500ms before the&n;&t; * next second starts, thus the following code.&n;&t; */
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
id|tick
op_rshift
l_int|1
)paren
op_logical_and
id|xtime.tv_usec
op_le
l_int|500000
op_plus
(paren
id|tick
op_rshift
l_int|1
)paren
)paren
(brace
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
multiline_comment|/* do it again in 60 s */
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
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
DECL|function|dosample
r_static
r_int
r_int
id|dosample
c_func
(paren
r_volatile
r_int
r_char
op_star
id|tcwp
comma
r_volatile
r_int
r_char
op_star
id|tc2p
)paren
(brace
r_int
r_int
id|ct0
comma
id|ct1
suffix:semicolon
r_int
r_char
id|msb
comma
id|lsb
suffix:semicolon
multiline_comment|/* Start the counter. */
op_star
id|tcwp
op_assign
(paren
id|SGINT_TCWORD_CNT2
op_or
id|SGINT_TCWORD_CALL
op_or
id|SGINT_TCWORD_MRGEN
)paren
suffix:semicolon
op_star
id|tc2p
op_assign
(paren
id|SGINT_TCSAMP_COUNTER
op_amp
l_int|0xff
)paren
suffix:semicolon
op_star
id|tc2p
op_assign
(paren
id|SGINT_TCSAMP_COUNTER
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Get initial counter invariant */
id|ct0
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
)paren
suffix:semicolon
multiline_comment|/* Latch and spin until top byte of counter2 is zero */
r_do
(brace
op_star
id|tcwp
op_assign
(paren
id|SGINT_TCWORD_CNT2
op_or
id|SGINT_TCWORD_CLAT
)paren
suffix:semicolon
id|lsb
op_assign
op_star
id|tc2p
suffix:semicolon
id|msb
op_assign
op_star
id|tc2p
suffix:semicolon
id|ct1
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|msb
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Stop the counter. */
op_star
id|tcwp
op_assign
(paren
id|SGINT_TCWORD_CNT2
op_or
id|SGINT_TCWORD_CALL
op_or
id|SGINT_TCWORD_MSWST
)paren
suffix:semicolon
multiline_comment|/* Return the difference, this is how far the r4k counter increments&n;&t; * for every one HZ.&n;&t; */
r_return
id|ct1
op_minus
id|ct0
suffix:semicolon
)brace
DECL|function|get_indy_time
r_static
r_int
r_int
id|__init
id|get_indy_time
c_func
(paren
r_void
)paren
(brace
r_struct
id|indy_clock
op_star
id|clock
op_assign
(paren
r_struct
id|indy_clock
op_star
)paren
id|INDY_CLOCK_REGS
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
multiline_comment|/* Freeze it. */
id|clock-&gt;cmd
op_and_assign
op_complement
(paren
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Read regs. */
id|sec
op_assign
id|clock-&gt;sec
suffix:semicolon
id|min
op_assign
id|clock-&gt;min
suffix:semicolon
id|hour
op_assign
(paren
id|clock-&gt;hr
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|day
op_assign
(paren
id|clock-&gt;date
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|mon
op_assign
(paren
id|clock-&gt;month
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|year
op_assign
id|clock-&gt;year
suffix:semicolon
multiline_comment|/* Unfreeze clock. */
id|clock-&gt;cmd
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* Frob the bits. */
DECL|macro|FROB1
mdefine_line|#define FROB1(x)  (((x) &amp; 0xf) + ((((x) &amp; 0xf0) &gt;&gt; 4) * 10));
DECL|macro|FROB2
mdefine_line|#define FROB2(x)  (((x) &amp; 0xf) + (((((x) &amp; 0xf0) &gt;&gt; 4) &amp; 0x3) * 10));
multiline_comment|/* XXX Should really check that secs register is the same&n;&t; * XXX as when we first read it and if not go back and&n;&t; * XXX read the regs above again.&n;&t; */
id|sec
op_assign
id|FROB1
c_func
(paren
id|sec
)paren
suffix:semicolon
id|min
op_assign
id|FROB1
c_func
(paren
id|min
)paren
suffix:semicolon
id|day
op_assign
id|FROB1
c_func
(paren
id|day
)paren
suffix:semicolon
id|mon
op_assign
id|FROB1
c_func
(paren
id|mon
)paren
suffix:semicolon
id|year
op_assign
id|FROB1
c_func
(paren
id|year
)paren
suffix:semicolon
id|hour
op_assign
id|FROB2
c_func
(paren
id|hour
)paren
suffix:semicolon
DECL|macro|FROB1
macro_line|#undef FROB1
DECL|macro|FROB2
macro_line|#undef FROB2
multiline_comment|/* Wheee... */
r_if
c_cond
(paren
id|year
OL
l_int|45
)paren
(brace
id|year
op_add_assign
l_int|30
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|year
op_add_assign
l_int|1940
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
DECL|macro|ALLINTS
mdefine_line|#define ALLINTS (IE_IRQ0 | IE_IRQ1 | IE_IRQ2 | IE_IRQ3 | IE_IRQ4 | IE_IRQ5)
DECL|function|indy_timer_init
r_void
id|__init
id|indy_timer_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sgi_ioc_timers
op_star
id|p
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|tcwp
comma
op_star
id|tc2p
suffix:semicolon
multiline_comment|/* Figure out the r4k offset, the algorithm is very simple&n;&t; * and works in _all_ cases as long as the 8254 counter&n;&t; * register itself works ok (as an interrupt driving timer&n;&t; * it does not because of bug, this is why we are using&n;&t; * the onchip r4k counter/compare register to serve this&n;&t; * purpose, but for r4k_offset calculation it will work&n;&t; * ok for us).  There are other very complicated ways&n;&t; * of performing this calculation but this one works just&n;&t; * fine so I am not going to futz around. ;-)&n;&t; */
id|p
op_assign
id|ioc_timers
suffix:semicolon
id|tcwp
op_assign
op_amp
id|p-&gt;tcword
suffix:semicolon
id|tc2p
op_assign
op_amp
id|p-&gt;tcnt2
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;calculating r4koff... &quot;
)paren
suffix:semicolon
id|dosample
c_func
(paren
id|tcwp
comma
id|tc2p
)paren
suffix:semicolon
multiline_comment|/* First sample. */
id|dosample
c_func
(paren
id|tcwp
comma
id|tc2p
)paren
suffix:semicolon
multiline_comment|/* Eat one.&t;*/
id|r4k_offset
op_assign
id|dosample
c_func
(paren
id|tcwp
comma
id|tc2p
)paren
suffix:semicolon
multiline_comment|/* Second sample. */
id|printk
c_func
(paren
l_string|&quot;%08lx(%d)&bslash;n&quot;
comma
id|r4k_offset
comma
(paren
r_int
)paren
id|r4k_offset
)paren
suffix:semicolon
id|r4k_cur
op_assign
(paren
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
)paren
op_plus
id|r4k_offset
)paren
suffix:semicolon
id|write_32bit_cp0_register
c_func
(paren
id|CP0_COMPARE
comma
id|r4k_cur
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_IM
comma
id|ALLINTS
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|get_indy_time
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Read time from RTC. */
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
DECL|function|indy_8254timer_irq
r_void
id|indy_8254timer_irq
c_func
(paren
r_void
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
r_int
id|irq
op_assign
l_int|4
suffix:semicolon
id|irq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;indy_8254timer_irq: Whoops, should not have gotten this IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|prom_imode
c_func
(paren
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
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
id|read_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|tv
op_assign
id|xtime
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
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
eof
