macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
r_int
DECL|function|ia32_exception
id|ia32_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|isr
)paren
(brace
r_struct
id|siginfo
id|siginfo
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|isr
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|isr
op_eq
l_int|0
)paren
id|siginfo.si_code
op_assign
id|TRAP_TRACE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x4
)paren
id|siginfo.si_code
op_assign
id|TRAP_BRANCH
suffix:semicolon
r_else
id|siginfo.si_code
op_assign
id|TRAP_BRKPT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|siginfo.si_code
op_assign
id|TRAP_BRKPT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* Divide fault */
r_case
l_int|4
suffix:colon
multiline_comment|/* Overflow */
r_case
l_int|5
suffix:colon
multiline_comment|/* Bounds fault */
r_case
l_int|6
suffix:colon
multiline_comment|/* Invalid Op-code */
r_case
l_int|7
suffix:colon
multiline_comment|/* FP DNA */
r_case
l_int|8
suffix:colon
multiline_comment|/* Double Fault */
r_case
l_int|9
suffix:colon
multiline_comment|/* Invalid TSS */
r_case
l_int|11
suffix:colon
multiline_comment|/* Segment not present */
r_case
l_int|12
suffix:colon
multiline_comment|/* Stack fault */
r_case
l_int|13
suffix:colon
multiline_comment|/* General Protection Fault */
r_case
l_int|16
suffix:colon
multiline_comment|/* Pending FP error */
r_case
l_int|17
suffix:colon
multiline_comment|/* Alignment check */
r_case
l_int|19
suffix:colon
multiline_comment|/* SSE Numeric error */
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|siginfo.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
