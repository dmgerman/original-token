multiline_comment|/* Yo, Emacs! we&squot;re -*- Linux-C -*-&n; *&n; *      Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *      GP calibration routine for processor speed dependent&n; *      functions.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;tracing.h&quot;
macro_line|#include &quot;calibr.h&quot;
macro_line|#include &quot;fdc-io.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
DECL|function|timestamp
r_int
id|timestamp
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
)brace
DECL|function|timediff
r_int
id|timediff
c_func
(paren
r_int
id|t0
comma
r_int
id|t1
)paren
(brace
multiline_comment|/*  Calculate difference in usec for timestamp results t0 &amp; t1.&n;&t; *  Note that the maximum timespan allowed is 1/HZ or we&squot;ll lose ticks!&n;&t; */
r_if
c_cond
(paren
id|t1
OL
id|t0
)paren
(brace
id|t1
op_add_assign
id|LATCH
suffix:semicolon
)brace
r_return
(paren
l_int|1000
op_star
(paren
id|t1
op_minus
id|t0
)paren
)paren
op_div
(paren
(paren
id|CLOCK_TICK_RATE
op_plus
l_int|500
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
multiline_comment|/*      To get an indication of the I/O performance,&n; *      measure the duration of the inb() function.&n; */
DECL|function|time_inb
r_void
id|time_inb
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|8
comma
l_string|&quot;time_inb&quot;
)paren
suffix:semicolon
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
id|timestamp
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
id|timestamp
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
r_if
c_cond
(paren
id|t1
op_minus
id|t0
op_le
l_int|0
)paren
(brace
id|t1
op_add_assign
id|LATCH
suffix:semicolon
)brace
id|TRACEx1
c_func
(paren
l_int|4
comma
l_string|&quot;inb() duration: %d nsec&quot;
comma
id|timediff
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
multiline_comment|/*  Haven&squot;t studied on why, but there sometimes is a problem&n; *  with the tick timer readout. The two bytes get swapped.&n; *  This hack solves that problem by doing one extra input.&n; */
DECL|function|fix_clock
r_void
id|fix_clock
c_func
(paren
r_void
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|8
comma
l_string|&quot;fix_clock&quot;
)paren
suffix:semicolon
r_int
id|t
suffix:semicolon
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
l_int|1000
suffix:semicolon
op_increment
id|i
)paren
(brace
id|t
op_assign
id|timestamp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
l_int|0
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
l_int|2
comma
l_string|&quot;clock counter fixed&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|TRACE_EXIT
suffix:semicolon
)brace
multiline_comment|/*&n; *      Input:  function taking int count as parameter.&n; *              pointers to calculated calibration variables.&n; */
DECL|function|calibrate
r_int
id|calibrate
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
)paren
comma
r_int
op_star
id|calibr_count
comma
r_int
op_star
id|calibr_time
)paren
(brace
id|TRACE_FUN
c_func
(paren
l_int|5
comma
l_string|&quot;calibrate&quot;
)paren
suffix:semicolon
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
id|old_tc
op_assign
l_int|0
suffix:semicolon
r_int
id|old_count
op_assign
l_int|1
suffix:semicolon
r_int
id|old_time
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|first_time
)paren
(brace
multiline_comment|/* get idea of I/O performance */
id|fix_clock
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
op_star
id|calibr_count
op_assign
l_int|10
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
id|t0
comma
id|t1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|once
suffix:semicolon
r_int
id|multiple
suffix:semicolon
r_int
id|tc
suffix:semicolon
op_star
id|calibr_time
op_assign
op_star
id|calibr_count
suffix:semicolon
multiline_comment|/* set TC to 1 */
id|fun
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* dummy, get code into cache */
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
id|timestamp
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
id|timestamp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t1
OL
id|t0
)paren
(brace
id|t1
op_add_assign
id|LATCH
suffix:semicolon
)brace
id|once
op_assign
id|t1
op_minus
id|t0
suffix:semicolon
id|t0
op_assign
id|timestamp
c_func
(paren
)paren
suffix:semicolon
id|fun
c_func
(paren
op_star
id|calibr_count
)paren
suffix:semicolon
multiline_comment|/* overhead + multiple tests */
id|t1
op_assign
id|timestamp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t1
OL
id|t0
)paren
(brace
id|t1
op_add_assign
id|LATCH
suffix:semicolon
)brace
id|multiple
op_assign
id|t1
op_minus
id|t0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|calibr_time
op_assign
(paren
l_int|10000
op_star
(paren
id|multiple
op_minus
id|once
)paren
)paren
op_div
(paren
id|CLOCK_TICK_RATE
op_div
l_int|100
)paren
suffix:semicolon
op_decrement
op_star
id|calibr_count
suffix:semicolon
multiline_comment|/* because delta corresponds to this count */
id|tc
op_assign
(paren
l_int|1000
op_star
op_star
id|calibr_time
)paren
op_div
op_star
id|calibr_count
suffix:semicolon
id|TRACEx4
c_func
(paren
l_int|8
comma
l_string|&quot;once:%4d us,%5d times:%6d us, TC:%5d ns&quot;
comma
(paren
l_int|10000
op_star
id|once
)paren
op_div
(paren
id|CLOCK_TICK_RATE
op_div
l_int|100
)paren
comma
op_star
id|calibr_count
comma
(paren
l_int|10000
op_star
id|multiple
)paren
op_div
(paren
id|CLOCK_TICK_RATE
op_div
l_int|100
)paren
comma
id|tc
)paren
suffix:semicolon
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
op_star
id|calibr_time
op_assign
id|old_time
suffix:semicolon
op_star
id|calibr_count
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
op_star
id|calibr_count
suffix:semicolon
id|old_time
op_assign
op_star
id|calibr_time
suffix:semicolon
op_star
id|calibr_count
op_mul_assign
l_int|2
suffix:semicolon
)brace
id|TRACEx3
c_func
(paren
l_int|4
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
r_return
l_int|0
suffix:semicolon
)brace
eof