multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *      refclock.c  --  Linux soundcard HF FSK driver,&n; *                      Reference clock routines.&n; *&n; *      Copyright (C) 1997  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *        Swiss Federal Institute of Technology (ETH), Electronics Lab&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&n; */
multiline_comment|/*****************************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/hfmodem.h&gt;
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * currently this module is supposed to support both module styles, i.e.&n; * the old one present up to about 2.1.9, and the new one functioning&n; * starting with 2.1.21. The reason is I have a kit allowing to compile&n; * this module also under 2.0.x which was requested by several people.&n; * This will go in 2.2&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20123
macro_line|#include &lt;linux/init.h&gt;
macro_line|#else
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(x) x
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * command line params&n; */
DECL|variable|scale_tvusec
r_static
r_int
r_int
id|scale_tvusec
op_assign
l_int|1UL
op_lshift
l_int|24
suffix:semicolon
macro_line|#ifdef __i386__
DECL|variable|scale_rdtsc
r_static
r_int
r_int
id|scale_rdtsc
op_assign
l_int|0
suffix:semicolon
DECL|variable|rdtsc_ok
r_static
r_int
id|rdtsc_ok
op_assign
l_int|1
suffix:semicolon
macro_line|#endif /* __i386__ */
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#ifdef __i386__
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|i386_capability
c_func
(paren
r_void
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|fl1
suffix:semicolon
r_union
(brace
r_struct
(brace
r_int
r_int
id|ebx
comma
id|edx
comma
id|ecx
suffix:semicolon
)brace
id|r
suffix:semicolon
r_int
r_char
id|s
(braket
l_int|13
)braket
suffix:semicolon
)brace
id|id
suffix:semicolon
r_int
r_int
id|eax
suffix:semicolon
r_int
r_int
id|x86_capability
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|flags
op_or_assign
l_int|0x200000
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|fl1
op_assign
id|flags
suffix:semicolon
id|flags
op_and_assign
op_complement
l_int|0x200000
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fl1
op_amp
l_int|0x200000
)paren
op_logical_or
(paren
id|flags
op_amp
l_int|0x200000
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: cpu does not support CPUID&bslash;n&quot;
comma
id|hfmodem_drvname
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__asm__
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
id|id.r.ebx
)paren
comma
l_string|&quot;=c&quot;
(paren
id|id.r.ecx
)paren
comma
l_string|&quot;=d&quot;
(paren
id|id.r.edx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|id.s
(braket
l_int|12
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|eax
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: cpu (vendor string %s) does not support capability &quot;
l_string|&quot;list&bslash;n&quot;
comma
id|hfmodem_drvname
comma
id|id.s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: cpu: vendor string %s &quot;
comma
id|hfmodem_drvname
comma
id|id.s
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|x86_capability
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;ebx&quot;
comma
l_string|&quot;ecx&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fam %d mdl %d step %d cap 0x%x&bslash;n&quot;
comma
(paren
id|eax
op_rshift
l_int|8
)paren
op_amp
l_int|15
comma
(paren
id|eax
op_rshift
l_int|4
)paren
op_amp
l_int|15
comma
id|eax
op_amp
l_int|15
comma
id|x86_capability
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x86_capability
op_amp
l_int|0x10
)paren
id|rdtsc_ok
op_assign
l_int|1
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: cpu does not support the rdtsc instruction&bslash;n&quot;
comma
id|hfmodem_drvname
)paren
suffix:semicolon
)brace
macro_line|#endif /* __i386__ */   
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|hfmodem_refclock_probe
c_func
(paren
r_void
)paren
)paren
(brace
macro_line|#ifdef __i386__
r_if
c_cond
(paren
id|rdtsc_ok
)paren
(brace
id|rdtsc_ok
op_assign
l_int|0
suffix:semicolon
id|i386_capability
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdtsc_ok
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
comma
id|tmp2
comma
id|tmp3
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rdtsc&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp1
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rdtsc&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp0
op_eq
id|tmp2
op_logical_and
id|tmp1
op_eq
id|tmp3
)paren
(brace
id|rdtsc_ok
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: rdtsc unusable, does not change&bslash;n&quot;
comma
id|hfmodem_drvname
)paren
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: using %s as timing source&bslash;n&quot;
comma
id|hfmodem_drvname
comma
id|rdtsc_ok
ques
c_cond
l_string|&quot;rdtsc&quot;
suffix:colon
l_string|&quot;gettimeofday&quot;
)paren
suffix:semicolon
macro_line|#endif /* __i386__ */
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|hfmodem_refclock_init
r_void
id|hfmodem_refclock_init
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|dev-&gt;clk.lasttime
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __i386__
r_if
c_cond
(paren
id|rdtsc_ok
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;rdtsc;&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|dev-&gt;clk.starttime_hi
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|dev-&gt;clk.starttime_lo
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* __i386__ */
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|dev-&gt;clk.last_tvusec
op_assign
id|tv.tv_usec
suffix:semicolon
id|dev-&gt;clk.time_cnt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|hfmodem_refclock_current
id|hfmodem_time_t
id|hfmodem_refclock_current
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
comma
id|hfmodem_time_t
id|expected
comma
r_int
id|exp_valid
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|hfmodem_time_t
id|curtime
suffix:semicolon
r_int
id|diff
suffix:semicolon
macro_line|#ifdef __i386__
r_if
c_cond
(paren
id|rdtsc_ok
)paren
(brace
r_int
r_int
id|tmp0
comma
id|tmp1
suffix:semicolon
r_int
r_int
id|tmp2
comma
id|tmp3
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rdtsc;&bslash;n&bslash;t&quot;
l_string|&quot;subl %2,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;sbbl %3,%%edx&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|tmp0
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp1
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|dev-&gt;clk.starttime_lo
)paren
comma
l_string|&quot;m&quot;
(paren
id|dev-&gt;clk.starttime_hi
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mull %1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|scale_rdtsc
)paren
comma
l_string|&quot;a&quot;
(paren
id|tmp0
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mull %1&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|tmp3
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|scale_rdtsc
)paren
comma
l_string|&quot;a&quot;
(paren
id|tmp1
)paren
suffix:colon
l_string|&quot;dx&quot;
)paren
suffix:semicolon
id|curtime
op_assign
id|tmp2
op_plus
id|tmp3
suffix:semicolon
r_goto
id|time_known
suffix:semicolon
)brace
macro_line|#endif /* __i386__ */
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|dev-&gt;clk.time_cnt
op_add_assign
(paren
r_int
)paren
(paren
l_int|1000000
op_plus
id|tv.tv_usec
op_minus
id|dev-&gt;clk.last_tvusec
)paren
op_mod
l_int|1000000
suffix:semicolon
id|dev-&gt;clk.last_tvusec
op_assign
id|tv.tv_usec
suffix:semicolon
id|curtime
op_assign
(paren
id|dev-&gt;clk.time_cnt
op_star
id|scale_tvusec
)paren
op_rshift
l_int|24
suffix:semicolon
id|time_known
suffix:colon
r_if
c_cond
(paren
id|exp_valid
op_logical_and
id|abs
c_func
(paren
id|diff
op_assign
(paren
id|curtime
op_minus
id|dev-&gt;clk.lasttime
op_minus
id|expected
)paren
)paren
op_ge
l_int|1000
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: refclock adjustment %ld more than 1ms&bslash;n&quot;
comma
id|hfmodem_drvname
comma
id|diff
)paren
suffix:semicolon
r_return
(paren
id|dev-&gt;clk.lasttime
op_assign
id|curtime
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
eof