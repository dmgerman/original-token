multiline_comment|/*&n; *  linux/kernel/signal.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
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
DECL|function|save_old
r_static
r_inline
r_void
id|save_old
c_func
(paren
r_char
op_star
id|from
comma
r_char
op_star
id|to
)paren
(brace
r_int
id|i
suffix:semicolon
id|verify_area
c_func
(paren
id|to
comma
r_sizeof
(paren
r_struct
id|sigaction
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
r_struct
id|sigaction
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|put_fs_byte
c_func
(paren
op_star
id|from
comma
id|to
)paren
suffix:semicolon
id|from
op_increment
suffix:semicolon
id|to
op_increment
suffix:semicolon
)brace
)brace
DECL|function|get_new
r_static
r_inline
r_void
id|get_new
c_func
(paren
r_char
op_star
id|from
comma
r_char
op_star
id|to
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
r_struct
id|sigaction
)paren
suffix:semicolon
id|i
op_increment
)paren
op_star
(paren
id|to
op_increment
)paren
op_assign
id|get_fs_byte
c_func
(paren
id|from
op_increment
)paren
suffix:semicolon
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
id|tmp
op_assign
id|current-&gt;sigaction
(braket
id|signum
op_minus
l_int|1
)braket
suffix:semicolon
id|get_new
c_func
(paren
(paren
r_char
op_star
)paren
id|action
comma
(paren
r_char
op_star
)paren
(paren
id|signum
op_minus
l_int|1
op_plus
id|current-&gt;sigaction
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldaction
)paren
id|save_old
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|tmp
comma
(paren
r_char
op_star
)paren
id|oldaction
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;sigaction
(braket
id|signum
op_minus
l_int|1
)braket
dot
id|sa_flags
op_amp
id|SA_NOMASK
)paren
id|current-&gt;sigaction
(braket
id|signum
op_minus
l_int|1
)braket
dot
id|sa_mask
op_assign
l_int|0
suffix:semicolon
r_else
id|current-&gt;sigaction
(braket
id|signum
op_minus
l_int|1
)braket
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Routine writes a core dump image in the current directory.&n; * Currently not implemented.&n; */
DECL|function|core_dump
r_int
id|core_dump
c_func
(paren
r_int
id|signr
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* We didn&squot;t do a dump */
)brace
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
r_int
id|signr
comma
r_int
id|eax
comma
r_int
id|ebx
comma
r_int
id|ecx
comma
r_int
id|edx
comma
r_int
id|orig_eax
comma
r_int
id|fs
comma
r_int
id|es
comma
r_int
id|ds
comma
r_int
id|eip
comma
r_int
id|cs
comma
r_int
id|eflags
comma
r_int
r_int
op_star
id|esp
comma
r_int
id|ss
)paren
(brace
r_int
r_int
id|sa_handler
suffix:semicolon
r_int
id|old_eip
op_assign
id|eip
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
macro_line|#ifdef notdef
id|printk
c_func
(paren
l_string|&quot;pid: %d, signr: %x, eax=%d, oeax = %d, int=%d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|signr
comma
id|eax
comma
id|orig_eax
comma
id|sa-&gt;sa_flags
op_amp
id|SA_INTERRUPT
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|orig_eax
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
(paren
id|eax
op_eq
op_minus
id|ERESTARTSYS
)paren
op_logical_or
(paren
id|eax
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
id|eax
op_eq
op_minus
id|ERESTARTSYS
)paren
op_logical_and
(paren
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_INTERRUPT
)paren
op_logical_or
id|signr
template_param
id|SIGTTOU
)paren
)paren
op_star
(paren
op_amp
id|eax
)paren
op_assign
op_minus
id|EINTR
suffix:semicolon
r_else
(brace
op_star
(paren
op_amp
id|eax
)paren
op_assign
id|orig_eax
suffix:semicolon
op_star
(paren
op_amp
id|eip
)paren
op_assign
id|old_eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
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
id|sa_handler
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Ignore, see if there are more signals... */
r_if
c_cond
(paren
op_logical_neg
id|sa_handler
)paren
(brace
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
id|current-&gt;p_pptr-&gt;signal
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|SIGCHLD
op_minus
l_int|1
)paren
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
)paren
)paren
id|do_exit
c_func
(paren
id|signr
op_or
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
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
op_star
(paren
op_amp
id|eip
)paren
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
l_int|7
suffix:colon
l_int|8
suffix:semicolon
op_star
(paren
op_amp
id|esp
)paren
op_sub_assign
id|longs
suffix:semicolon
id|verify_area
c_func
(paren
id|esp
comma
id|longs
op_star
l_int|4
)paren
suffix:semicolon
id|tmp_esp
op_assign
id|esp
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
id|eax
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ecx
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|edx
comma
id|tmp_esp
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|eflags
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Continue, execute handler */
)brace
eof
