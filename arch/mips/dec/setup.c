multiline_comment|/*&n; * Setup pointers to hardware dependand routines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
r_extern
r_struct
id|feature
id|decstation_feature
suffix:semicolon
r_static
r_void
DECL|function|dec_irq_setup
id|dec_irq_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* FIXME: should set up the clock as per above? */
id|pmax_printf
c_func
(paren
l_string|&quot;Please write the IRQ setup code for the DECStation!&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|board_time_init
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
DECL|function|dec_time_init
r_static
r_void
id|dec_time_init
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|pmax_printf
c_func
(paren
l_string|&quot;Please write the time init code for the DECStation!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_extern
r_void
id|dec_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|dec_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dec_machine_power_off
c_func
(paren
r_void
)paren
dot
r_void
DECL|function|decstation_setup
id|decstation_setup
c_func
(paren
r_void
)paren
(brace
id|irq_setup
op_assign
id|dec_irq_setup
suffix:semicolon
id|board_time_init
op_assign
id|dec_time_init
suffix:semicolon
multiline_comment|/* FIXME: Setup fd_cacheflush */
id|feature
op_assign
op_amp
id|decstation_feature
suffix:semicolon
multiline_comment|/* FIXME: Will go away */
id|_machine_restart
op_assign
id|dec_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|dec_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|dec_machine_power_off
suffix:semicolon
)brace
eof
