multiline_comment|/*&n; *  linux/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|_S
mdefine_line|#define _S(nr) (1&lt;&lt;((nr)-1))
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(_S(SIGKILL) | _S(SIGSTOP)))
DECL|function|sys_sigprocmask
id|asmlinkage
r_int
id|sys_sigprocmask
c_func
(paren
r_int
id|how
comma
id|sigset_t
op_star
id|set
comma
id|sigset_t
op_star
id|oset
)paren
(brace
id|sigset_t
id|new_set
comma
id|old_set
op_assign
id|current-&gt;blocked
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|set
comma
r_sizeof
(paren
id|sigset_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|new_set
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|set
)paren
op_amp
id|_BLOCKABLE
suffix:semicolon
r_switch
c_cond
(paren
id|how
)paren
(brace
r_case
id|SIG_BLOCK
suffix:colon
id|current-&gt;blocked
op_or_assign
id|new_set
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG_UNBLOCK
suffix:colon
id|current-&gt;blocked
op_and_assign
op_complement
id|new_set
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG_SETMASK
suffix:colon
id|current-&gt;blocked
op_assign
id|new_set
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|oset
)paren
(brace
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oset
comma
r_sizeof
(paren
id|sigset_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|put_fs_long
c_func
(paren
id|old_set
comma
(paren
r_int
r_int
op_star
)paren
id|oset
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_sgetmask
id|asmlinkage
r_int
id|sys_sgetmask
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;blocked
suffix:semicolon
)brace
DECL|function|sys_ssetmask
id|asmlinkage
r_int
id|sys_ssetmask
c_func
(paren
r_int
id|newmask
)paren
(brace
r_int
id|old
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_assign
id|newmask
op_amp
id|_BLOCKABLE
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
DECL|function|sys_sigpending
id|asmlinkage
r_int
id|sys_sigpending
c_func
(paren
id|sigset_t
op_star
id|set
)paren
(brace
r_int
id|error
suffix:semicolon
multiline_comment|/* fill in &quot;set&quot; with signals pending but blocked. */
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|set
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|put_fs_long
c_func
(paren
id|current-&gt;blocked
op_amp
id|current-&gt;signal
comma
(paren
r_int
r_int
op_star
)paren
id|set
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * POSIX 3.3.1.3:&n; *  &quot;Setting a signal action to SIG_IGN for a signal that is pending&n; *   shall cause the pending signal to be discarded, whether or not&n; *   it is blocked&quot; (but SIGCHLD is unspecified: linux leaves it alone).&n; *&n; *  &quot;Setting a signal action to SIG_DFL for a signal that is pending&n; *   and whose default action is to ignore the signal (for example,&n; *   SIGCHLD), shall cause the pending signal to be discarded, whether&n; *   or not it is blocked&quot;&n; *&n; * Note the silly behaviour of SIGCHLD: SIG_IGN means that the signal&n; * isn&squot;t actually ignored, but does automatic child reaping, while&n; * SIG_DFL is explicitly said by POSIX to force the signal to be ignored..&n; */
DECL|function|check_pending
r_static
r_void
id|check_pending
c_func
(paren
r_int
id|signum
)paren
(brace
r_struct
id|sigaction
op_star
id|p
suffix:semicolon
id|p
op_assign
id|signum
op_minus
l_int|1
op_plus
id|current-&gt;sigaction
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;sa_handler
op_eq
id|SIG_IGN
)paren
(brace
r_if
c_cond
(paren
id|signum
op_eq
id|SIGCHLD
)paren
r_return
suffix:semicolon
id|current-&gt;signal
op_and_assign
op_complement
id|_S
c_func
(paren
id|signum
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;sa_handler
op_eq
id|SIG_DFL
)paren
(brace
r_if
c_cond
(paren
id|signum
op_ne
id|SIGCONT
op_logical_and
id|signum
op_ne
id|SIGCHLD
op_logical_and
id|signum
op_ne
id|SIGWINCH
)paren
r_return
suffix:semicolon
id|current-&gt;signal
op_and_assign
op_complement
id|_S
c_func
(paren
id|signum
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|sys_signal
id|asmlinkage
r_int
r_int
id|sys_signal
c_func
(paren
r_int
id|signum
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
)paren
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|sigaction
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|signum
l_int|32
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|signum
op_eq
id|SIGKILL
op_logical_or
id|signum
op_eq
id|SIGSTOP
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|handler
op_ne
id|SIG_DFL
op_logical_and
id|handler
op_ne
id|SIG_IGN
)paren
(brace
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|handler
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
id|tmp.sa_handler
op_assign
id|handler
suffix:semicolon
id|tmp.sa_mask
op_assign
l_int|0
suffix:semicolon
id|tmp.sa_flags
op_assign
id|SA_ONESHOT
op_or
id|SA_NOMASK
suffix:semicolon
id|tmp.sa_restorer
op_assign
l_int|NULL
suffix:semicolon
id|handler
op_assign
id|current-&gt;sigaction
(braket
id|signum
op_minus
l_int|1
)braket
dot
id|sa_handler
suffix:semicolon
id|current-&gt;sigaction
(braket
id|signum
op_minus
l_int|1
)braket
op_assign
id|tmp
suffix:semicolon
id|check_pending
c_func
(paren
id|signum
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|handler
suffix:semicolon
)brace
DECL|function|sys_sigaction
id|asmlinkage
r_int
id|sys_sigaction
c_func
(paren
r_int
id|signum
comma
r_const
r_struct
id|sigaction
op_star
id|action
comma
r_struct
id|sigaction
op_star
id|oldaction
)paren
(brace
r_struct
id|sigaction
id|new_sa
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|signum
l_int|32
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|signum
op_eq
id|SIGKILL
op_logical_or
id|signum
op_eq
id|SIGSTOP
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p
op_assign
id|signum
op_minus
l_int|1
op_plus
id|current-&gt;sigaction
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_int
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|action
comma
r_sizeof
(paren
op_star
id|action
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|new_sa
comma
id|action
comma
r_sizeof
(paren
r_struct
id|sigaction
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_sa.sa_flags
op_amp
id|SA_NOMASK
)paren
id|new_sa.sa_mask
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|new_sa.sa_mask
op_or_assign
id|_S
c_func
(paren
id|signum
)paren
suffix:semicolon
id|new_sa.sa_mask
op_and_assign
id|_BLOCKABLE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_sa.sa_handler
op_ne
id|SIG_DFL
op_logical_and
id|new_sa.sa_handler
op_ne
id|SIG_IGN
)paren
(brace
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|new_sa.sa_handler
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|oldaction
)paren
(brace
r_int
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oldaction
comma
r_sizeof
(paren
op_star
id|oldaction
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|oldaction
comma
id|p
comma
r_sizeof
(paren
r_struct
id|sigaction
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action
)paren
(brace
op_star
id|p
op_assign
id|new_sa
suffix:semicolon
id|check_pending
c_func
(paren
id|signum
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
