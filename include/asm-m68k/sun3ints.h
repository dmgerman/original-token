multiline_comment|/*&n; * sun3ints.h -- Linux/Sun3 interrupt handling code definitions&n; *&n; * Erik Verbruggen (erik@bigmama.xtdnet.nl)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive for&n; * more details.&n; */
macro_line|#ifndef SUN3INTS_H
DECL|macro|SUN3INTS_H
mdefine_line|#define SUN3INTS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/intersil.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
r_void
id|sun3_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_void
id|sun3_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_int
id|sun3_request_irq
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
suffix:semicolon
macro_line|#endif /* SUN3INTS_H */
eof
