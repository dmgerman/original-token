multiline_comment|/*&n; *  linux/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
r_extern
r_int
id|core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|sys_sgetmask
r_int
id|sys_sgetmask
c_func
(paren
)paren
(brace
r_return
id|current-&gt;blocked
suffix:semicolon
)brace
DECL|function|sys_ssetmask
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
op_complement
(paren
l_int|1
op_lshift
(paren
id|SIGKILL
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
(paren
id|SIGSTOP
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
DECL|function|sys_sigpending
r_int
id|sys_sigpending
c_func
(paren
id|sigset_t
op_star
id|set
)paren
(brace
multiline_comment|/* fill in &quot;set&quot; with signals pending but blocked. */
id|verify_area
c_func
(paren
id|set
comma
l_int|4
)paren
suffix:semicolon
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/* atomically swap in the new signal mask, and wait for a signal.&n; *&n; * we need to play some games with syscall restarting.  We get help&n; * from the syscall library interface.  Note that we need to coordinate&n; * the calling convention with the libc routine.&n; *&n; * &quot;set&quot; is just the sigmask as described in 1003.1-1988, 3.3.7.&n; * &t;It is assumed that sigset_t can be passed as a 32 bit quantity.&n; *&n; * &quot;restart&quot; holds a restart indication.  If it&squot;s non-zero, then we &n; * &t;install the old mask, and return normally.  If it&squot;s zero, we store &n; * &t;the current mask in old_mask and block until a signal comes in.&n; */
DECL|function|sys_sigsuspend
r_int
id|sys_sigsuspend
c_func
(paren
r_int
id|restart
comma
r_int
r_int
id|old_mask
comma
r_int
r_int
id|set
)paren
(brace
r_extern
r_int
id|sys_pause
c_func
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restart
)paren
(brace
multiline_comment|/* we&squot;re restarting */
id|current-&gt;blocked
op_assign
id|old_mask
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
multiline_comment|/* we&squot;re not restarting.  do the work */
op_star
(paren
op_amp
id|restart
)paren
op_assign
l_int|1
suffix:semicolon
op_star
(paren
op_amp
id|old_mask
)paren
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_assign
id|set
suffix:semicolon
(paren
r_void
)paren
id|sys_pause
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* return after a signal arrives */
r_return
op_minus
id|ERESTARTNOINTR
suffix:semicolon
multiline_comment|/* handle the signal, and come back */
)brace
DECL|function|sys_signal
r_int
id|sys_signal
c_func
(paren
r_int
id|signum
comma
r_int
id|handler
comma
r_int
id|restorer
)paren
(brace
r_struct
id|sigaction
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|signum
l_int|32
op_logical_or
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
id|tmp.sa_handler
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_int
)paren
)paren
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
op_or
id|SA_INTERRUPT
suffix:semicolon
id|tmp.sa_restorer
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|restorer
suffix:semicolon
id|handler
op_assign
(paren
r_int
)paren
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
r_return
id|handler
suffix:semicolon
)brace
DECL|function|sys_sigaction
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
r_new
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|signum
l_int|32
op_logical_or
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
id|memcpy_fromfs
c_func
(paren
op_amp
r_new
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
r_new
dot
id|sa_flags
op_amp
id|SA_NOMASK
)paren
r_new
dot
id|sa_mask
op_assign
l_int|0
suffix:semicolon
r_else
r_new
dot
id|sa_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|signum
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldaction
)paren
(brace
id|verify_area
c_func
(paren
id|oldaction
comma
r_sizeof
(paren
r_struct
id|sigaction
)paren
)paren
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
op_star
id|p
op_assign
r_new
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|sys_waitpid
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
op_star
id|stat_addr
comma
r_int
id|options
)paren
suffix:semicolon
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|sa_handler
suffix:semicolon
r_int
id|old_eip
op_assign
id|regs-&gt;eip
suffix:semicolon
r_struct
id|sigaction
op_star
id|sa
op_assign
id|current-&gt;sigaction
op_plus
id|signr
op_minus
l_int|1
suffix:semicolon
r_int
id|longs
suffix:semicolon
r_int
r_int
op_star
id|tmp_esp
suffix:semicolon
id|sa_handler
op_assign
(paren
r_int
r_int
)paren
id|sa-&gt;sa_handler
suffix:semicolon
r_if
c_cond
(paren
(paren
id|regs-&gt;orig_eax
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTSYS
)paren
op_logical_or
(paren
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTNOINTR
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|sa_handler
OG
l_int|1
)paren
op_logical_and
(paren
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTSYS
)paren
op_logical_and
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_INTERRUPT
)paren
)paren
id|regs-&gt;eax
op_assign
op_minus
id|EINTR
suffix:semicolon
r_else
(brace
id|regs-&gt;eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|regs-&gt;eip
op_assign
id|old_eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sa_handler
op_eq
l_int|1
)paren
(brace
multiline_comment|/* check for SIGCHLD: it&squot;s special */
r_if
c_cond
(paren
id|signr
op_eq
id|SIGCHLD
)paren
r_while
c_loop
(paren
id|sys_waitpid
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
id|WNOHANG
)paren
OG
l_int|0
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Ignore, see if there are more signals... */
)brace
r_if
c_cond
(paren
op_logical_neg
id|sa_handler
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|signr
)paren
(brace
r_case
id|SIGCONT
suffix:colon
r_case
id|SIGCHLD
suffix:colon
r_case
id|SIGWINCH
suffix:colon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Ignore, ... */
r_case
id|SIGSTOP
suffix:colon
r_case
id|SIGTSTP
suffix:colon
r_case
id|SIGTTIN
suffix:colon
r_case
id|SIGTTOU
suffix:colon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;p_pptr-&gt;sigaction
(braket
id|SIGCHLD
op_minus
l_int|1
)braket
dot
id|sa_flags
op_amp
id|SA_NOCLDSTOP
)paren
)paren
id|send_sig
c_func
(paren
id|SIGCHLD
comma
id|current-&gt;p_pptr
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Reschedule another event */
r_case
id|SIGQUIT
suffix:colon
r_case
id|SIGILL
suffix:colon
r_case
id|SIGTRAP
suffix:colon
r_case
id|SIGIOT
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGSEGV
suffix:colon
r_if
c_cond
(paren
id|core_dump
c_func
(paren
id|signr
comma
id|regs
)paren
)paren
id|signr
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
id|current-&gt;signal
op_or_assign
l_int|1
op_lshift
(paren
(paren
id|signr
op_amp
l_int|0x7f
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|signr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * OK, we&squot;re invoking a handler &n;&t; */
r_if
c_cond
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_ONESHOT
)paren
id|sa-&gt;sa_handler
op_assign
l_int|NULL
suffix:semicolon
id|regs-&gt;eip
op_assign
id|sa_handler
suffix:semicolon
id|longs
op_assign
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_NOMASK
)paren
ques
c_cond
(paren
l_int|7
op_star
l_int|4
)paren
suffix:colon
(paren
l_int|8
op_star
l_int|4
)paren
suffix:semicolon
id|regs-&gt;esp
op_sub_assign
id|longs
suffix:semicolon
id|tmp_esp
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;esp
suffix:semicolon
id|verify_area
c_func
(paren
id|tmp_esp
comma
id|longs
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
(paren
r_int
)paren
id|sa-&gt;sa_restorer
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|signr
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_NOMASK
)paren
)paren
id|put_fs_long
c_func
(paren
id|current-&gt;blocked
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|regs-&gt;eax
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|regs-&gt;ecx
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|regs-&gt;edx
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|regs-&gt;eflags
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|old_eip
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|current-&gt;blocked
op_or_assign
id|sa-&gt;sa_mask
suffix:semicolon
multiline_comment|/* force a supervisor-mode page-in of the signal handler to reduce races */
id|__asm__
c_func
(paren
l_string|&quot;testb $0,%%fs:%0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|sa_handler
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Continue, execute handler */
)brace
eof
