multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;    (c) Philip Blundell, 1998-1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* XXX */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* XXX */
macro_line|#include &quot;softfloat.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
macro_line|#include &quot;fpmodule.h&quot;
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;fpa11.inl&quot;
multiline_comment|/* external data */
r_extern
id|FPA11
op_star
id|fpa11
suffix:semicolon
multiline_comment|/* kernel symbols required for signal handling */
DECL|typedef|PTASK
r_typedef
r_struct
id|task_struct
op_star
id|PTASK
suffix:semicolon
macro_line|#ifdef MODULE
r_void
id|fp_send_sig
c_func
(paren
r_int
r_int
id|sig
comma
id|PTASK
id|p
comma
r_int
id|priv
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; 0x20115
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Scott Bambrough &lt;scottb@rebel.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NWFPE floating point emulator&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
DECL|macro|fp_send_sig
mdefine_line|#define fp_send_sig&t;send_sig
DECL|macro|kern_fp_enter
mdefine_line|#define kern_fp_enter&t;fp_enter
macro_line|#endif
multiline_comment|/* kernel function prototypes required */
r_void
id|fp_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* external declarations for saved kernel symbols */
r_extern
r_void
(paren
op_star
id|kern_fp_enter
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Original value of fp_enter from kernel before patched by fpe_init. */
DECL|variable|orig_fp_enter
r_static
r_void
(paren
op_star
id|orig_fp_enter
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* forward declarations */
r_extern
r_void
id|nwfpe_enter
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Address of user registers on the kernel stack. */
DECL|variable|userRegisters
r_int
r_int
op_star
id|userRegisters
suffix:semicolon
DECL|function|fpe_init
r_int
id|__init
id|fpe_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
r_sizeof
(paren
id|FPA11
)paren
OG
r_sizeof
(paren
r_union
id|fp_state
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nwfpe: bad structure size&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Display title, version and copyright information. */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NetWinder Floating Point Emulator V0.95 &quot;
l_string|&quot;(c) 1998-1999 Rebel.com&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Save pointer to the old FP handler and then patch ourselves in */
id|orig_fp_enter
op_assign
id|kern_fp_enter
suffix:semicolon
id|kern_fp_enter
op_assign
id|nwfpe_enter
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fpe_exit
r_void
id|__exit
id|fpe_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Restore the values we saved earlier. */
id|kern_fp_enter
op_assign
id|orig_fp_enter
suffix:semicolon
)brace
multiline_comment|/*&n;ScottB:  November 4, 1998&n;&n;Moved this function out of softfloat-specialize into fpmodule.c.&n;This effectively isolates all the changes required for integrating with the&n;Linux kernel into fpmodule.c.  Porting to NetBSD should only require modifying&n;fpmodule.c to integrate with the NetBSD kernel (I hope!).&n;&n;[1/1/99: Not quite true any more unfortunately.  There is Linux-specific&n;code to access data in user space in some other source files at the &n;moment (grep for get_user / put_user calls).  --philb]&n;&n;float_exception_flags is a global variable in SoftFloat.&n;&n;This function is called by the SoftFloat routines to raise a floating&n;point exception.  We check the trap enable byte in the FPSR, and raise&n;a SIGFPE exception if necessary.  If not the relevant bits in the &n;cumulative exceptions flag byte are set and we return.&n;*/
DECL|function|float_raise
r_void
id|float_raise
c_func
(paren
r_int
r_char
id|flags
)paren
(brace
r_register
r_int
r_int
id|fpsr
comma
id|cumulativeTraps
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;NWFPE: %s[%d] takes exception %08x at %p from %08x&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|flags
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|userRegisters
(braket
l_int|15
)braket
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Keep SoftFloat exception flags up to date.  */
id|float_exception_flags
op_or_assign
id|flags
suffix:semicolon
multiline_comment|/* Read fpsr and initialize the cumulativeTraps.  */
id|fpsr
op_assign
id|readFPSR
c_func
(paren
)paren
suffix:semicolon
id|cumulativeTraps
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* For each type of exception, the cumulative trap exception bit is only&n;     set if the corresponding trap enable bit is not set.  */
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|fpsr
op_amp
id|BIT_IXE
)paren
)paren
op_logical_and
(paren
id|flags
op_amp
id|BIT_IXC
)paren
)paren
id|cumulativeTraps
op_or_assign
id|BIT_IXC
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|fpsr
op_amp
id|BIT_UFE
)paren
)paren
op_logical_and
(paren
id|flags
op_amp
id|BIT_UFC
)paren
)paren
id|cumulativeTraps
op_or_assign
id|BIT_UFC
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|fpsr
op_amp
id|BIT_OFE
)paren
)paren
op_logical_and
(paren
id|flags
op_amp
id|BIT_OFC
)paren
)paren
id|cumulativeTraps
op_or_assign
id|BIT_OFC
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|fpsr
op_amp
id|BIT_DZE
)paren
)paren
op_logical_and
(paren
id|flags
op_amp
id|BIT_DZC
)paren
)paren
id|cumulativeTraps
op_or_assign
id|BIT_DZC
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|fpsr
op_amp
id|BIT_IOE
)paren
)paren
op_logical_and
(paren
id|flags
op_amp
id|BIT_IOC
)paren
)paren
id|cumulativeTraps
op_or_assign
id|BIT_IOC
suffix:semicolon
multiline_comment|/* Set the cumulative exceptions flags.  */
r_if
c_cond
(paren
id|cumulativeTraps
)paren
id|writeFPSR
c_func
(paren
id|fpsr
op_or
id|cumulativeTraps
)paren
suffix:semicolon
multiline_comment|/* Raise an exception if necessary.  */
r_if
c_cond
(paren
id|fpsr
op_amp
(paren
id|flags
op_lshift
l_int|16
)paren
)paren
id|fp_send_sig
c_func
(paren
id|SIGFPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|fpe_init
id|module_init
c_func
(paren
id|fpe_init
)paren
suffix:semicolon
DECL|variable|fpe_exit
id|module_exit
c_func
(paren
id|fpe_exit
)paren
suffix:semicolon
eof
