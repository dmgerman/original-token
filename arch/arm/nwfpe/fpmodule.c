multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Corel Computer Corporation, 1998&n;    (c) Philip Blundell, 1998-1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@corelcomputer.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &quot;config.h&quot;
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT
macro_line|#endif
multiline_comment|/* XXX */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
r_int
id|fp_printk
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
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
l_string|&quot;Scott Bambrough &lt;scottb@corelcomputer.com&gt;&quot;
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
DECL|macro|fp_printk
mdefine_line|#define fp_printk&t;printk
DECL|macro|fp_send_sig
mdefine_line|#define fp_send_sig&t;send_sig
DECL|macro|kern_fp_enter
mdefine_line|#define kern_fp_enter&t;fp_enter
macro_line|#endif
multiline_comment|/* kernel function prototypes required */
r_void
id|C_SYMBOL_NAME
c_func
(paren
id|fp_setup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* external declarations for saved kernel symbols */
r_extern
r_int
r_int
id|C_SYMBOL_NAME
c_func
(paren
id|kern_fp_enter
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
multiline_comment|/* Original value of fp_enter from kernel before patched by fpe_init. */
DECL|variable|orig_fp_enter
r_static
r_int
r_int
id|orig_fp_enter
suffix:semicolon
multiline_comment|/* Address of user registers on the kernel stack. */
DECL|variable|userRegisters
r_int
r_int
op_star
id|userRegisters
suffix:semicolon
DECL|function|fpe_version
r_void
id|__init
id|C_SYMBOL_NAME
c_func
(paren
id|fpe_version
)paren
(paren
r_void
)paren
(brace
r_static
r_const
r_char
id|szTitle
(braket
)braket
op_assign
l_string|&quot;&lt;4&gt;NetWinder Floating Point Emulator &quot;
suffix:semicolon
r_static
r_const
r_char
id|szVersion
(braket
)braket
op_assign
l_string|&quot;V0.94.1 &quot;
suffix:semicolon
r_static
r_const
r_char
id|szCopyright
(braket
)braket
op_assign
l_string|&quot;(c) 1998 Corel Computer Corp.&bslash;n&quot;
suffix:semicolon
id|C_SYMBOL_NAME
c_func
(paren
id|fp_printk
)paren
(paren
id|szTitle
)paren
suffix:semicolon
id|C_SYMBOL_NAME
c_func
(paren
id|fp_printk
)paren
(paren
id|szVersion
)paren
suffix:semicolon
id|C_SYMBOL_NAME
c_func
(paren
id|fp_printk
)paren
(paren
id|szCopyright
)paren
suffix:semicolon
)brace
DECL|function|fpe_init
r_int
id|__init
id|fpe_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Display title, version and copyright information. */
id|C_SYMBOL_NAME
c_func
(paren
id|fpe_version
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* Save pointer to the old FP handler and then patch ourselves in */
id|orig_fp_enter
op_assign
id|C_SYMBOL_NAME
c_func
(paren
id|kern_fp_enter
)paren
suffix:semicolon
id|C_SYMBOL_NAME
c_func
(paren
id|kern_fp_enter
)paren
op_assign
(paren
r_int
r_int
)paren
id|C_SYMBOL_NAME
c_func
(paren
id|nwfpe_enter
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|fpe_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Restore the values we saved earlier. */
id|C_SYMBOL_NAME
c_func
(paren
id|kern_fp_enter
)paren
op_assign
id|orig_fp_enter
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|_ARM_pc
mdefine_line|#define _ARM_pc 60
DECL|macro|_ARM_cpsr
mdefine_line|#define _ARM_cpsr 64
multiline_comment|/*&n;ScottB:  November 4, 1998&n;&n;Moved this function out of softfloat-specialize into fpmodule.c.&n;This effectively isolates all the changes required for integrating with the&n;Linux kernel into fpmodule.c.  Porting to NetBSD should only require modifying&n;fpmodule.c to integrate with the NetBSD kernel (I hope!).&n;&n;[1/1/99: Not quite true any more unfortunately.  There is Linux-specific&n;code to access data in user space in some other source files at the &n;moment.  --philb]&n;&n;float_exception_flags is a global variable in SoftFloat.&n;&n;This function is called by the SoftFloat routines to raise a floating&n;point exception.  We check the trap enable byte in the FPSR, and raise&n;a SIGFPE exception if necessary.  If not the relevant bits in the &n;cumulative exceptions flag byte are set and we return.&n;*/
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
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;NWFPE: exception %08x at %08x from %08x&bslash;n&quot;
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
id|float_exception_flags
op_or_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|readFPSR
c_func
(paren
)paren
op_amp
(paren
id|flags
op_lshift
l_int|16
)paren
)paren
(brace
multiline_comment|/* raise exception */
id|C_SYMBOL_NAME
c_func
(paren
id|fp_send_sig
)paren
(paren
id|SIGFPE
comma
id|C_SYMBOL_NAME
c_func
(paren
id|current
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* set the cumulative exceptions flags */
id|writeFPSR
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
eof
