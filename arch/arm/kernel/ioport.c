multiline_comment|/*&n; * linux/arch/arm/kernel/ioport.c&n; *&n; * IO permission support for ARM.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|sys_iopl
id|asmlinkage
r_int
id|sys_iopl
c_func
(paren
r_int
r_int
id|turn_on
)paren
(brace
r_if
c_cond
(paren
id|turn_on
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*&n;&t; * We only support an on_off approach&n;&t; */
id|modify_domain
c_func
(paren
id|DOMAIN_IO
comma
id|turn_on
ques
c_cond
id|DOMAIN_MANAGER
suffix:colon
id|DOMAIN_CLIENT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
