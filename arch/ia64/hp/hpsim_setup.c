multiline_comment|/*&n; * Platform dependent support for HP simulator.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &quot;hpsim_ssc.h&quot;
r_extern
r_struct
id|console
id|hpsim_cons
suffix:semicolon
multiline_comment|/*&n; * Simulator system call.&n; */
r_inline
r_int
DECL|function|ia64_ssc
id|ia64_ssc
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|nr
)paren
(brace
macro_line|#ifdef __GCC_DOESNT_KNOW_IN_REGS__
r_register
r_int
id|in0
id|asm
(paren
l_string|&quot;r32&quot;
)paren
op_assign
id|arg0
suffix:semicolon
r_register
r_int
id|in1
id|asm
(paren
l_string|&quot;r33&quot;
)paren
op_assign
id|arg1
suffix:semicolon
r_register
r_int
id|in2
id|asm
(paren
l_string|&quot;r34&quot;
)paren
op_assign
id|arg2
suffix:semicolon
r_register
r_int
id|in3
id|asm
(paren
l_string|&quot;r35&quot;
)paren
op_assign
id|arg3
suffix:semicolon
macro_line|#else
r_register
r_int
id|in0
id|asm
(paren
l_string|&quot;in0&quot;
)paren
op_assign
id|arg0
suffix:semicolon
r_register
r_int
id|in1
id|asm
(paren
l_string|&quot;in1&quot;
)paren
op_assign
id|arg1
suffix:semicolon
r_register
r_int
id|in2
id|asm
(paren
l_string|&quot;in2&quot;
)paren
op_assign
id|arg2
suffix:semicolon
r_register
r_int
id|in3
id|asm
(paren
l_string|&quot;in3&quot;
)paren
op_assign
id|arg3
suffix:semicolon
macro_line|#endif
r_register
r_int
id|r8
id|asm
(paren
l_string|&quot;r8&quot;
)paren
suffix:semicolon
r_register
r_int
id|r15
id|asm
(paren
l_string|&quot;r15&quot;
)paren
op_assign
id|nr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;break 0x80001&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r8
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|r15
)paren
comma
l_string|&quot;r&quot;
(paren
id|in0
)paren
comma
l_string|&quot;r&quot;
(paren
id|in1
)paren
comma
l_string|&quot;r&quot;
(paren
id|in2
)paren
comma
l_string|&quot;r&quot;
(paren
id|in3
)paren
)paren
suffix:semicolon
r_return
id|r8
suffix:semicolon
)brace
r_void
DECL|function|ia64_ssc_connect_irq
id|ia64_ssc_connect_irq
(paren
r_int
id|intr
comma
r_int
id|irq
)paren
(brace
id|ia64_ssc
c_func
(paren
id|intr
comma
id|irq
comma
l_int|0
comma
l_int|0
comma
id|SSC_CONNECT_INTERRUPT
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_ctl_trace
id|ia64_ctl_trace
(paren
r_int
id|on
)paren
(brace
id|ia64_ssc
c_func
(paren
id|on
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_CTL_TRACE
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|hpsim_setup
id|hpsim_setup
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0801
)paren
suffix:semicolon
multiline_comment|/* default to first SCSI drive */
id|register_console
(paren
op_amp
id|hpsim_cons
)paren
suffix:semicolon
)brace
eof
