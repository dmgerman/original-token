multiline_comment|/*&n; * linux/arch/sparc/sys_solaris.c&n; *&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* CHECKME: this stuff looks rather bogus */
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
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|put_exec_domain
c_func
(paren
id|current-&gt;exec_domain
)paren
suffix:semicolon
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
l_int|0
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* What is going on here?  Why do we do this? */
multiline_comment|/* XXX current-&gt;exec_domain-&gt;use_count = 0; XXX */
id|ret
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
suffix:semicolon
)brace
r_else
(brace
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
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_SUNOS_EMUL
id|asmlinkage
r_int
DECL|function|do_sunos_syscall
id|do_sunos_syscall
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
OL
l_int|10
)paren
id|printk
(paren
l_string|&quot;SunOS binary emulation not compiled in&bslash;n&quot;
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|force_sig
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
