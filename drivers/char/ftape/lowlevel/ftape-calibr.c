multiline_comment|/*&n; *      Copyright (C) 1993-1996 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-calibr.c,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:08 $&n; *&n; *      GP calibration routine for processor speed dependent&n; *      functions.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if defined(__alpha__)
macro_line|# include &lt;asm/hwrpb.h&gt;
macro_line|#elif defined(__i386__)
macro_line|# include &lt;linux/timex.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &quot;../lowlevel/ftape-tracing.h&quot;
macro_line|#include &quot;../lowlevel/ftape-calibr.h&quot;
macro_line|#include &quot;../lowlevel/fdc-io.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__i386__)
macro_line|# error Ftape is not implemented for this architecture!
macro_line|#endif
macro_line|#if defined(__alpha__)
DECL|variable|ps_per_cycle
r_static
r_int
r_int
id|ps_per_cycle
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Note: On Intel PCs, the clock ticks at 100 Hz (HZ==100) which is&n; * too slow for certain timeouts (and that clock doesn&squot;t even tick&n; * when interrupts are disabled).  For that reason, the 8254 timer is&n; * used directly to implement fine-grained timeouts.  However, on&n; * Alpha PCs, the 8254 is *not* used to implement the clock tick&n; * (which is 1024 Hz, normally) and the 8254 timer runs at some&n; * &quot;random&quot; frequency (it seems to run at 18Hz, but its not safe to&n; * rely on this value).  Instead, we use the Alpha&squot;s &quot;rpcc&quot;&n; * instruction to read cycle counts.  As this is a 32 bit counter,&n; * it will overflow only once per 30 seconds (on a 200MHz machine),&n; * which is plenty.&n; */
DECL|function|ftape_timestamp
r_int
r_int
id|ftape_timestamp
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(__alpha__)
r_int
r_int
id|r
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;rpcc %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
macro_line|#elif defined(__i386__)
r_int
r_int
id|flags
suffix:semicolon
id|__u16
id|lo
suffix:semicolon
id|__u16
id|hi
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
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|lo
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|lo
op_or_assign
id|inb
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
id|hi
op_assign
id|jiffies
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
(paren
id|hi
op_plus
l_int|1
)paren
op_star
(paren
r_int
r_int
)paren
id|LATCH
)paren
op_minus
id|lo
suffix:semicolon
multiline_comment|/* downcounter ! */
macro_line|#endif
)brace
DECL|function|short_ftape_timestamp
r_static
r_int
r_int
id|short_ftape_timestamp
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(__alpha__)
r_return
id|ftape_timestamp
c_func
(paren
)paren
suffix:semicolon
macro_line|#elif defined(__i386__)
r_int
r_int
id|count
suffix:semicolon
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
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|LATCH
op_minus
id|count
)paren
suffix:semicolon
multiline_comment|/* normal: downcounter */
macro_line|#endif
)brace
DECL|function|diff
r_static
r_int
r_int
id|diff
c_func
(paren
r_int
r_int
id|t0
comma
r_int
r_int
id|t1
)paren
(brace
macro_line|#if defined(__alpha__)
r_return
(paren
id|t1
op_le
id|t0
)paren
ques
c_cond
id|t1
op_plus
(paren
l_int|1UL
op_lshift
l_int|32
)paren
op_minus
id|t0
suffix:colon
id|t1
op_minus
id|t0
suffix:semicolon
macro_line|#elif defined(__i386__)
multiline_comment|/*&n;&t; * This is tricky: to work for both short and full ftape_timestamps&n;&t; * we&squot;ll have to discriminate between these.&n;&t; * If it _looks_ like short stamps with wrapping around we&squot;ll&n;&t; * asume it are. This will generate a small error if it really&n;&t; * was a (very large) delta from full ftape_timestamps.&n;&t; */
r_return
(paren
id|t1
op_le
id|t0
op_logical_and
id|t0
op_le
id|LATCH
)paren
ques
c_cond
id|t1
op_plus
id|LATCH
op_minus
id|t0
suffix:colon
id|t1
op_minus
id|t0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|usecs
r_static
r_int
r_int
id|usecs
c_func
(paren
r_int
r_int
id|count
)paren
(brace
macro_line|#if defined(__alpha__)
r_return
(paren
id|ps_per_cycle
op_star
id|count
)paren
op_div
l_int|1000000UL
suffix:semicolon
macro_line|#elif defined(__i386__)
r_return
(paren
l_int|10000
op_star
id|count
)paren
op_div
(paren
(paren
id|CLOCK_TICK_RATE
op_plus
l_int|50
)paren
op_div
l_int|100
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ftape_timediff
r_int
r_int
id|ftape_timediff
c_func
(paren
r_int
r_int
id|t0
comma
r_int
r_int
id|t1
)paren
(brace
multiline_comment|/*&n;&t; *  Calculate difference in usec for ftape_timestamp results t0 &amp; t1.&n;&t; *  Note that on the i386 platform with short time-stamps, the&n;&t; *  maximum allowed timespan is 1/HZ or we&squot;ll lose ticks!&n;&t; */
r_return
id|usecs
c_func
(paren
id|diff
c_func
(paren
id|t0
comma
id|t1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*      To get an indication of the I/O performance,&n; *      measure the duration of the inb() function.&n; */
DECL|function|time_inb
r_static
r_void
id|time_inb
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|t0
comma
id|t1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_any
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
id|t0
op_assign
id|short_ftape_timestamp
c_func
(paren
)paren
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
l_int|1000
suffix:semicolon
op_increment
id|i
)paren
(brace
id|status
op_assign
id|inb
c_func
(paren
id|fdc.msr
)paren
suffix:semicolon
)brace
id|t1
op_assign
id|short_ftape_timestamp
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
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;inb() duration: %d nsec&quot;
comma
id|ftape_timediff
c_func
(paren
id|t0
comma
id|t1
)paren
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
)brace
DECL|function|init_clock
r_static
r_void
id|init_clock
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(__i386__)
r_int
r_int
id|t
suffix:semicolon
r_int
id|i
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_any
)paren
suffix:semicolon
multiline_comment|/*  Haven&squot;t studied on why, but there sometimes is a problem&n;&t; *  with the tick timer readout. The two bytes get swapped.&n;&t; *  This hack solves that problem by doing one extra input.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000
suffix:semicolon
op_increment
id|i
)paren
(brace
id|t
op_assign
id|short_ftape_timestamp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
id|LATCH
)paren
(brace
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* get in sync again */
id|TRACE
c_func
(paren
id|ft_t_warn
comma
l_string|&quot;clock counter fixed&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#elif defined(__alpha__)
macro_line|#if CONFIG_FT_ALPHA_CLOCK == 0
macro_line|#error You must define and set CONFIG_FT_ALPHA_CLOCK in the Makefile !
macro_line|#endif
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
id|TRACE_FUN
c_func
(paren
id|ft_t_any
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwrpb-&gt;cycle_freq
op_ne
l_int|0
)paren
(brace
id|ps_per_cycle
op_assign
(paren
l_int|1000
op_star
l_int|1000
op_star
l_int|1000
op_star
l_int|1000UL
)paren
op_div
id|hwrpb-&gt;cycle_freq
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * HELP:  Linux 2.0.x doesn&squot;t set cycle_freq on my noname !&n;&t;&t; */
id|ps_per_cycle
op_assign
(paren
l_int|1000
op_star
l_int|1000
op_star
l_int|1000
op_star
l_int|1000UL
)paren
op_div
id|CONFIG_FT_ALPHA_CLOCK
suffix:semicolon
)brace
macro_line|#endif
id|TRACE_EXIT
suffix:semicolon
)brace
multiline_comment|/*&n; *      Input:  function taking int count as parameter.&n; *              pointers to calculated calibration variables.&n; */
DECL|function|ftape_calibrate
r_void
id|ftape_calibrate
c_func
(paren
r_char
op_star
id|name
comma
r_void
(paren
op_star
id|fun
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
op_star
id|calibr_count
comma
r_int
r_int
op_star
id|calibr_time
)paren
(brace
r_static
r_int
id|first_time
op_assign
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|tc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|time
suffix:semicolon
macro_line|#if defined(__i386__)
r_int
r_int
id|old_tc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|old_count
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|old_time
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_time
)paren
(brace
multiline_comment|/* get idea of I/O performance */
id|init_clock
c_func
(paren
)paren
suffix:semicolon
id|time_inb
c_func
(paren
)paren
suffix:semicolon
id|first_time
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*    value of timeout must be set so that on very slow systems&n;&t; *    it will give a time less than one jiffy, and on&n;&t; *    very fast systems it&squot;ll give reasonable precision.&n;&t; */
id|count
op_assign
l_int|40
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
l_int|15
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
r_int
id|t0
suffix:semicolon
r_int
r_int
id|t1
suffix:semicolon
r_int
r_int
id|once
suffix:semicolon
r_int
r_int
id|multiple
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
op_star
id|calibr_count
op_assign
op_star
id|calibr_time
op_assign
id|count
suffix:semicolon
multiline_comment|/* set TC to 1 */
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
id|fun
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* dummy, get code into cache */
id|t0
op_assign
id|short_ftape_timestamp
c_func
(paren
)paren
suffix:semicolon
id|fun
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* overhead + one test */
id|t1
op_assign
id|short_ftape_timestamp
c_func
(paren
)paren
suffix:semicolon
id|once
op_assign
id|diff
c_func
(paren
id|t0
comma
id|t1
)paren
suffix:semicolon
id|t0
op_assign
id|short_ftape_timestamp
c_func
(paren
)paren
suffix:semicolon
id|fun
c_func
(paren
id|count
)paren
suffix:semicolon
multiline_comment|/* overhead + count tests */
id|t1
op_assign
id|short_ftape_timestamp
c_func
(paren
)paren
suffix:semicolon
id|multiple
op_assign
id|diff
c_func
(paren
id|t0
comma
id|t1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|time
op_assign
id|ftape_timediff
c_func
(paren
l_int|0
comma
id|multiple
op_minus
id|once
)paren
suffix:semicolon
id|tc
op_assign
(paren
l_int|1000
op_star
id|time
)paren
op_div
(paren
id|count
op_minus
l_int|1
)paren
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_any
comma
l_string|&quot;once:%3d us,%6d times:%6d us, TC:%5d ns&quot;
comma
id|usecs
c_func
(paren
id|once
)paren
comma
id|count
op_minus
l_int|1
comma
id|usecs
c_func
(paren
id|multiple
)paren
comma
id|tc
)paren
suffix:semicolon
macro_line|#if defined(__alpha__)
multiline_comment|/*&n;&t;&t; * Increase the calibration count exponentially until the&n;&t;&t; * calibration time exceeds 100 ms.&n;&t;&t; */
r_if
c_cond
(paren
id|time
op_ge
l_int|100
op_star
l_int|1000
)paren
(brace
r_break
suffix:semicolon
)brace
macro_line|#elif defined(__i386__)
multiline_comment|/*&n;&t;&t; * increase the count until the resulting time nears 2/HZ,&n;&t;&t; * then the tc will drop sharply because we lose LATCH counts.&n;&t;&t; */
r_if
c_cond
(paren
id|tc
op_le
id|old_tc
op_div
l_int|2
)paren
(brace
id|time
op_assign
id|old_time
suffix:semicolon
id|count
op_assign
id|old_count
suffix:semicolon
r_break
suffix:semicolon
)brace
id|old_tc
op_assign
id|tc
suffix:semicolon
id|old_count
op_assign
id|count
suffix:semicolon
id|old_time
op_assign
id|time
suffix:semicolon
macro_line|#endif
id|count
op_mul_assign
l_int|2
suffix:semicolon
)brace
op_star
id|calibr_count
op_assign
id|count
op_minus
l_int|1
suffix:semicolon
op_star
id|calibr_time
op_assign
id|time
suffix:semicolon
id|TRACE
c_func
(paren
id|ft_t_info
comma
l_string|&quot;TC for `%s()&squot; = %d nsec (at %d counts)&quot;
comma
id|name
comma
(paren
l_int|1000
op_star
op_star
id|calibr_time
)paren
op_div
op_star
id|calibr_count
comma
op_star
id|calibr_count
)paren
suffix:semicolon
id|TRACE_EXIT
suffix:semicolon
)brace
eof