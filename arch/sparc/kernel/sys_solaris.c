multiline_comment|/*&n; * linux/arch/sparc/sys_solaris.c&n; *&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
id|asmlinkage
r_int
DECL|function|do_solaris_syscall
id|do_solaris_syscall
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|current-&gt;personality
op_assign
id|PER_SVR4
suffix:semicolon
id|current-&gt;exec_domain
op_assign
id|lookup_exec_domain
c_func
(paren
id|PER_SVR4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;exec_domain
op_logical_and
id|current-&gt;exec_domain-&gt;handler
)paren
(brace
id|current-&gt;exec_domain-&gt;handler
(paren
id|regs
)paren
suffix:semicolon
id|current-&gt;exec_domain-&gt;use_count
op_assign
l_int|0
suffix:semicolon
r_return
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;No solaris handler&bslash;n&quot;
)paren
suffix:semicolon
id|send_sig
(paren
id|SIGSEGV
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
