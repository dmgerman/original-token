multiline_comment|/*&n; *  linux/arch/m68k/hp300/time.c&n; *&n; *  Copyright (C) 1998 Philip Blundell &lt;philb@gnu.org&gt;&n; *&n; *  This file contains the HP300-specific time handling code.&n; */
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
multiline_comment|/* Clock hardware definitions */
DECL|macro|CLOCKBASE
mdefine_line|#define CLOCKBASE&t;0xf05f8000
DECL|macro|CLKCR1
mdefine_line|#define&t;CLKCR1&t;&t;0x1
DECL|macro|CLKCR2
mdefine_line|#define&t;CLKCR2&t;&t;0x3
DECL|macro|CLKCR3
mdefine_line|#define&t;CLKCR3&t;&t;CLKCR1
DECL|macro|CLKSR
mdefine_line|#define&t;CLKSR&t;&t;CLKCR2
DECL|macro|CLKMSB1
mdefine_line|#define&t;CLKMSB1&t;&t;0x5
DECL|macro|CLKMSB2
mdefine_line|#define&t;CLKMSB2&t;&t;0x9
DECL|macro|CLKMSB3
mdefine_line|#define&t;CLKMSB3&t;&t;0xD
DECL|function|hp300_gettimeoffset
r_int
r_int
id|hp300_gettimeoffset
(paren
r_void
)paren
(brace
r_return
l_int|0L
suffix:semicolon
)brace
DECL|function|hp300_tick
r_static
r_void
id|hp300_tick
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
r_int
id|tmp
suffix:semicolon
r_void
(paren
op_star
id|vector
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
op_assign
id|dev_id
suffix:semicolon
id|readb
c_func
(paren
id|CLOCKBASE
op_plus
id|CLKSR
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movpw %1@(5),%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|CLOCKBASE
)paren
)paren
suffix:semicolon
id|vector
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|hp300_sched_init
c_func
(paren
r_void
(paren
op_star
id|vector
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
)paren
)paren
(brace
r_int
r_int
id|intval
op_assign
(paren
l_int|10000
op_div
l_int|4
)paren
op_minus
l_int|1
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x1
comma
id|CLOCKBASE
op_plus
id|CLKCR2
)paren
suffix:semicolon
multiline_comment|/* select CR1 */
id|writeb
c_func
(paren
l_int|0x1
comma
id|CLOCKBASE
op_plus
id|CLKCR1
)paren
suffix:semicolon
multiline_comment|/* reset */
id|asm
r_volatile
(paren
l_string|&quot; movpw %0,%1@(5)&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|intval
)paren
comma
l_string|&quot;a&quot;
(paren
id|CLOCKBASE
)paren
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
l_int|6
comma
id|hp300_tick
comma
id|IRQ_FLG_STD
comma
l_string|&quot;timer tick&quot;
comma
id|vector
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x1
comma
id|CLOCKBASE
op_plus
id|CLKCR2
)paren
suffix:semicolon
multiline_comment|/* select CR1 */
id|writeb
c_func
(paren
l_int|0x40
comma
id|CLOCKBASE
op_plus
id|CLKCR1
)paren
suffix:semicolon
multiline_comment|/* enable irq */
)brace
eof
