multiline_comment|/*&n; *  linux/fs/fcntl.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
r_extern
r_int
id|sys_close
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
DECL|function|dupfd
r_static
r_int
id|dupfd
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|arg
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
id|current-&gt;filp
(braket
id|fd
)braket
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ge
id|NR_OPEN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_while
c_loop
(paren
id|arg
OL
id|NR_OPEN
)paren
r_if
c_cond
(paren
id|current-&gt;filp
(braket
id|arg
)braket
)paren
id|arg
op_increment
suffix:semicolon
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ge
id|NR_OPEN
)paren
r_return
op_minus
id|EMFILE
suffix:semicolon
id|current-&gt;close_on_exec
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|arg
)paren
suffix:semicolon
(paren
id|current-&gt;filp
(braket
id|arg
)braket
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
op_member_access_from_pointer
id|f_count
op_increment
suffix:semicolon
r_return
id|arg
suffix:semicolon
)brace
DECL|function|sys_dup2
r_int
id|sys_dup2
c_func
(paren
r_int
r_int
id|oldfd
comma
r_int
r_int
id|newfd
)paren
(brace
r_if
c_cond
(paren
id|oldfd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
id|current-&gt;filp
(braket
id|oldfd
)braket
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|newfd
op_eq
id|oldfd
)paren
r_return
id|newfd
suffix:semicolon
id|sys_close
c_func
(paren
id|newfd
)paren
suffix:semicolon
r_return
id|dupfd
c_func
(paren
id|oldfd
comma
id|newfd
)paren
suffix:semicolon
)brace
DECL|function|sys_dup
r_int
id|sys_dup
c_func
(paren
r_int
r_int
id|fildes
)paren
(brace
r_return
id|dupfd
c_func
(paren
id|fildes
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sys_fcntl
r_int
id|sys_fcntl
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
(brace
r_struct
id|file
op_star
id|filp
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
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|F_DUPFD
suffix:colon
r_return
id|dupfd
c_func
(paren
id|fd
comma
id|arg
)paren
suffix:semicolon
r_case
id|F_GETFD
suffix:colon
r_return
(paren
id|current-&gt;close_on_exec
op_rshift
id|fd
)paren
op_amp
l_int|1
suffix:semicolon
r_case
id|F_SETFD
suffix:colon
r_if
c_cond
(paren
id|arg
op_amp
l_int|1
)paren
id|current-&gt;close_on_exec
op_or_assign
(paren
l_int|1
op_lshift
id|fd
)paren
suffix:semicolon
r_else
id|current-&gt;close_on_exec
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|F_GETFL
suffix:colon
r_return
id|filp-&gt;f_flags
suffix:semicolon
r_case
id|F_SETFL
suffix:colon
id|filp-&gt;f_flags
op_and_assign
op_complement
(paren
id|O_APPEND
op_or
id|O_NONBLOCK
)paren
suffix:semicolon
id|filp-&gt;f_flags
op_or_assign
id|arg
op_amp
(paren
id|O_APPEND
op_or
id|O_NONBLOCK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|F_GETLK
suffix:colon
r_case
id|F_SETLK
suffix:colon
r_case
id|F_SETLKW
suffix:colon
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
eof
