multiline_comment|/*&n; *  linux/arch/m68k/hp300/ints.c&n; *&n; *  Copyright (C) 1998 Philip Blundell &lt;philb@gnu.org&gt;&n; *&n; *  This file contains the HP300-specific interrupt handling.  There&n; *  isn&squot;t much here -- we only use the autovector interrupts and at the&n; *  moment everything difficult is handled by the generic code.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &quot;ints.h&quot;
DECL|function|hp300_nmi_handler
r_static
r_void
id|hp300_nmi_handler
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
id|fp
)paren
(brace
r_extern
r_void
id|hp300_reset
c_func
(paren
r_void
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RESET pressed - self destruct sequence initiated.&bslash;n&quot;
)paren
suffix:semicolon
id|hp300_reset
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|hp300_request_irq
r_int
id|hp300_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_return
id|sys_request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|flags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
)brace
DECL|function|hp300_free_irq
r_void
id|hp300_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|sys_free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|hp300_init_IRQ
c_func
(paren
r_void
)paren
)paren
(brace
multiline_comment|/* IPL6 - NMI (keyboard reset) */
id|sys_request_irq
c_func
(paren
l_int|7
comma
id|hp300_nmi_handler
comma
id|IRQ_FLG_STD
comma
l_string|&quot;NMI&quot;
comma
id|hp300_nmi_handler
)paren
suffix:semicolon
)brace
eof