multiline_comment|/*&n; *  linux/arch/arm/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *  Modifications for ARM (C) 1994, 1995, 1996,1997 Russell King&n; *  Copyright (C) 1999 SuSE GmbH, (Philipp Rumpf, prumpf@tux.org)&n; *&n; * 1994-07-02  Alan Modra&n; *             fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1998-12-20  Updated NTP code according to technical memorandum Jan &squot;96&n; *             &quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
DECL|variable|timer_value
r_static
r_int
id|timer_value
suffix:semicolon
DECL|variable|timer_delta
r_static
r_int
id|timer_delta
suffix:semicolon
DECL|variable|tod_data
r_static
r_struct
id|pdc_tod
id|tod_data
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
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
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|old
suffix:semicolon
r_int
id|lost
op_assign
l_int|0
suffix:semicolon
r_int
id|cr16
suffix:semicolon
id|old
op_assign
id|timer_value
suffix:semicolon
id|cr16
op_assign
id|mfctl
c_func
(paren
l_int|16
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|timer_value
op_minus
id|cr16
)paren
OL
(paren
id|timer_delta
op_div
l_int|2
)paren
)paren
(brace
id|timer_value
op_add_assign
id|timer_delta
suffix:semicolon
id|lost
op_increment
suffix:semicolon
)brace
id|mtctl
c_func
(paren
id|timer_value
comma
l_int|16
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|led_interrupt_func
c_func
(paren
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
id|tv-&gt;tv_sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
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
id|xtime.tv_sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|xtime.tv_usec
op_assign
id|tv-&gt;tv_usec
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
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
id|timer_delta
op_assign
(paren
l_int|100
op_star
id|PAGE0-&gt;mem_10msec
)paren
op_div
id|HZ
suffix:semicolon
multiline_comment|/* make the first timer interrupt go off in one second */
id|timer_value
op_assign
id|mfctl
c_func
(paren
l_int|16
)paren
op_plus
(paren
id|HZ
op_star
id|timer_delta
)paren
suffix:semicolon
id|mtctl
c_func
(paren
id|timer_value
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdc_tod_read
c_func
(paren
op_amp
id|tod_data
)paren
op_eq
l_int|0
)paren
(brace
id|xtime.tv_sec
op_assign
id|tod_data.tod_sec
suffix:semicolon
id|xtime.tv_usec
op_assign
id|tod_data.tod_usec
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error reading tod clock&bslash;n&quot;
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
l_int|0
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
