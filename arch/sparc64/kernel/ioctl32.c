multiline_comment|/* $Id: ioctl32.c,v 1.3 1997/05/27 19:30:13 jj Exp $&n; * ioctl32.c: Conversion between 32bit and 64bit native ioctls.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * These routines maintain argument size conversion between 32bit and 64bit&n; * ioctls.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* As gcc will warn about casting u32 to some ptr, we have to cast it to unsigned long first, and that&squot;s what is A() for.&n; * You just do (void *)A(x), instead of having to type (void *)((unsigned long)x) or instead of just (void *)x, which will&n; * produce warnings */
DECL|macro|A
mdefine_line|#define A(x) ((unsigned long)x)
r_extern
id|asmlinkage
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|function|sys32_ioctl
id|asmlinkage
r_int
id|sys32_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
id|u32
id|arg
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|filp
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_op
op_logical_or
op_logical_neg
id|filp-&gt;f_op-&gt;ioctl
)paren
(brace
id|error
op_assign
id|sys_ioctl
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
id|error
op_assign
id|sys_ioctl
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|EINVAL
)paren
(brace
id|printk
(paren
l_string|&quot;sys32_ioctl on %016lx&squot;s %08x returns EINVAL&bslash;n&quot;
comma
id|filp-&gt;f_op
ques
c_cond
(paren
r_int
)paren
id|filp-&gt;f_op-&gt;ioctl
suffix:colon
l_int|0UL
comma
id|cmd
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof