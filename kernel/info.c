multiline_comment|/*&n; * linux/kernel/info.c&n; *&n; * Copyright (C) 1992 Darren Senn&n; */
multiline_comment|/* This implements the sysinfo() system call */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|sys_sysinfo
id|asmlinkage
r_int
id|sys_sysinfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|info
)paren
(brace
r_struct
id|sysinfo
id|val
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|val
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sysinfo
)paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|val.uptime
op_assign
id|jiffies
op_div
id|HZ
suffix:semicolon
id|val.loads
(braket
l_int|0
)braket
op_assign
id|avenrun
(braket
l_int|0
)braket
op_lshift
(paren
id|SI_LOAD_SHIFT
op_minus
id|FSHIFT
)paren
suffix:semicolon
id|val.loads
(braket
l_int|1
)braket
op_assign
id|avenrun
(braket
l_int|1
)braket
op_lshift
(paren
id|SI_LOAD_SHIFT
op_minus
id|FSHIFT
)paren
suffix:semicolon
id|val.loads
(braket
l_int|2
)braket
op_assign
id|avenrun
(braket
l_int|2
)braket
op_lshift
(paren
id|SI_LOAD_SHIFT
op_minus
id|FSHIFT
)paren
suffix:semicolon
id|val.procs
op_assign
id|nr_tasks
op_minus
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|si_meminfo
c_func
(paren
op_amp
id|val
)paren
suffix:semicolon
id|si_swapinfo
c_func
(paren
op_amp
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|info
comma
op_amp
id|val
comma
r_sizeof
(paren
r_struct
id|sysinfo
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
