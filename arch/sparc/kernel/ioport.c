multiline_comment|/* ioport.c:  I/O access on the Sparc. Work in progress.. Most of the things&n; *            in this file are for the sole purpose of getting the kernel&n; *&t;      throught the compiler. :-)&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
multiline_comment|/*&n; * this changes the io permissions bitmap in the current task.&n; */
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|turn_on
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
