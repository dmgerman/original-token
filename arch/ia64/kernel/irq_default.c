macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
r_static
r_int
DECL|function|irq_default_handle_irq
id|irq_default_handle_irq
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unexpected irq vector 0x%x on CPU %u!&bslash;n&quot;
comma
id|irq
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t call do_bottom_half() for spurious interrupts */
)brace
r_static
r_void
DECL|function|irq_default_noop
id|irq_default_noop
(paren
r_int
r_int
id|irq
)paren
(brace
multiline_comment|/* nuthing to do... */
)brace
DECL|variable|irq_type_default
r_struct
id|hw_interrupt_type
id|irq_type_default
op_assign
(brace
l_string|&quot;default&quot;
comma
(paren
r_void
(paren
op_star
)paren
(paren
r_int
r_int
)paren
)paren
id|irq_default_noop
comma
multiline_comment|/* init */
id|irq_default_noop
comma
multiline_comment|/* startup */
id|irq_default_noop
comma
multiline_comment|/* shutdown */
id|irq_default_handle_irq
comma
multiline_comment|/* handle */
id|irq_default_noop
comma
multiline_comment|/* enable */
id|irq_default_noop
multiline_comment|/* disable */
)brace
suffix:semicolon
eof
