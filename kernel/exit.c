multiline_comment|/*&n; *  linux/kernel/exit.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
DECL|macro|DEBUG_PROC_TREE
mdefine_line|#define DEBUG_PROC_TREE
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
r_int
id|sys_close
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
DECL|function|send_sig
r_int
id|send_sig
c_func
(paren
r_int
id|sig
comma
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|priv
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
(paren
id|sig
OL
l_int|0
)paren
op_logical_or
(paren
id|sig
OG
l_int|32
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
op_logical_and
(paren
(paren
id|sig
op_ne
id|SIGCONT
)paren
op_logical_or
(paren
id|current-&gt;session
op_ne
id|p-&gt;session
)paren
)paren
op_logical_and
(paren
id|current-&gt;euid
op_ne
id|p-&gt;euid
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|p-&gt;uid
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sig
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sig
op_eq
id|SIGKILL
)paren
op_logical_or
(paren
id|sig
op_eq
id|SIGCONT
)paren
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|TASK_STOPPED
)paren
id|p-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|p-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
id|p-&gt;signal
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
(paren
id|SIGSTOP
op_minus
l_int|1
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGTSTP
op_minus
l_int|1
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGTTIN
op_minus
l_int|1
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGTTOU
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Depends on order SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU */
r_if
c_cond
(paren
(paren
id|sig
op_ge
id|SIGSTOP
)paren
op_logical_and
(paren
id|sig
op_le
id|SIGTTOU
)paren
)paren
id|p-&gt;signal
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|SIGCONT
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Actually deliver the signal */
id|p-&gt;signal
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|sig
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;flags
op_amp
id|PF_PTRACED
)paren
(brace
multiline_comment|/* save the signal number for wait. */
id|p-&gt;exit_code
op_assign
id|sig
suffix:semicolon
multiline_comment|/* we have to make sure the parent process is awake. */
r_if
c_cond
(paren
id|p-&gt;p_pptr
op_ne
l_int|NULL
op_logical_and
id|p-&gt;p_pptr-&gt;state
op_eq
id|TASK_INTERRUPTIBLE
)paren
id|p-&gt;p_pptr-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
multiline_comment|/* we have to make sure that the process stops. */
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|TASK_INTERRUPTIBLE
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
id|p-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release
r_void
id|release
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|current
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;task releasing itself&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_eq
id|p
)paren
(brace
id|task
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;trying to release non-existent task&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_PROC_TREE
multiline_comment|/*&n; * Check to see if a task_struct pointer is present in the task[] array&n; * Return 0 if found, and 1 if not found.&n; */
DECL|function|bad_task_ptr
r_int
id|bad_task_ptr
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|0
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
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_eq
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine scans the pid tree and make sure the rep invarient still&n; * holds.  Used for debugging only, since it&squot;s very slow....&n; *&n; * It looks a lot scarier than it really is.... we&squot;re doing &#xfffd;nothing more&n; * than verifying the doubly-linked list found&#xfffd;in p_ysptr and p_osptr, &n; * and checking it corresponds with the process tree defined by p_cptr and &n; * p_pptr;&n; */
DECL|function|audit_ptree
r_void
id|audit_ptree
c_func
(paren
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
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|task
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|bad_task_ptr
c_func
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_pptr
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d&squot;s parent link is bad&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_task_ptr
c_func
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d&squot;s child link is bad&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_task_ptr
c_func
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_ysptr
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d&squot;s ys link is bad&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_task_ptr
c_func
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d&squot;s os link is bad&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_pptr
op_eq
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d parent link points to self&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr
op_eq
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d child link points to self&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_ysptr
op_eq
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d ys link points to self&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr
op_eq
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d os link points to self&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr
)paren
(brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_pptr
op_ne
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;p_pptr
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d older sibling %d parent is %d&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;p_pptr-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;p_ysptr
op_ne
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d older sibling %d has mismatched ys link&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;pid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_ysptr
)paren
(brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_pptr
op_ne
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_ysptr-&gt;p_pptr
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d younger sibling %d parent is %d&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_osptr-&gt;p_pptr-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_ysptr-&gt;p_osptr
op_ne
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d younger sibling %d has mismatched os link&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_ysptr-&gt;pid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr
)paren
(brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr-&gt;p_pptr
op_ne
id|task
(braket
id|i
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d youngest child %d has mismatched parent link&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr-&gt;p_ysptr
)paren
id|printk
c_func
(paren
l_string|&quot;Warning, pid %d youngest child %d has non-NULL ys link&bslash;n&quot;
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_cptr-&gt;pid
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* DEBUG_PROC_TREE */
multiline_comment|/*&n; * This checks not only the pgrp, but falls back on the pid if no&n; * satisfactory prgp is found. I dunno - gdb doesn&squot;t work correctly&n; * without this...&n; */
DECL|function|session_of_pgrp
r_int
id|session_of_pgrp
c_func
(paren
r_int
id|pgrp
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_int
id|fallback
suffix:semicolon
id|fallback
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
op_logical_or
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|session
op_le
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pgrp
op_eq
id|pgrp
)paren
r_return
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|session
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pid
op_eq
id|pgrp
)paren
id|fallback
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|session
suffix:semicolon
)brace
r_return
id|fallback
suffix:semicolon
)brace
DECL|function|kill_pg
r_int
id|kill_pg
c_func
(paren
r_int
id|pgrp
comma
r_int
id|sig
comma
r_int
id|priv
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_int
id|err
comma
id|retval
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sig
l_int|32
op_logical_or
id|pgrp
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pgrp
op_eq
id|pgrp
)paren
(brace
r_if
c_cond
(paren
id|sig
op_logical_and
(paren
id|err
op_assign
id|send_sig
c_func
(paren
id|sig
comma
op_star
id|p
comma
id|priv
)paren
)paren
)paren
id|retval
op_assign
id|err
suffix:semicolon
r_else
id|found
op_increment
suffix:semicolon
)brace
r_return
id|found
ques
c_cond
l_int|0
suffix:colon
id|retval
suffix:semicolon
)brace
DECL|function|kill_proc
r_int
id|kill_proc
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
comma
r_int
id|priv
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|sig
l_int|32
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pid
op_eq
id|pid
)paren
r_return
id|sig
ques
c_cond
id|send_sig
c_func
(paren
id|sig
comma
op_star
id|p
comma
id|priv
)paren
suffix:colon
l_int|0
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
multiline_comment|/*&n; * POSIX specifies that kill(-1,sig) is unspecified, but what we have&n; * is probably wrong.  Should make it like BSD or SYSV.&n; */
DECL|function|sys_kill
r_int
id|sys_kill
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
op_assign
id|NR_TASKS
op_plus
id|task
suffix:semicolon
r_int
id|err
comma
id|retval
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
r_return
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|sig
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
op_minus
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|p
OG
op_amp
id|FIRST_TASK
)paren
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pid
OG
l_int|1
op_logical_and
op_star
id|p
op_ne
id|current
)paren
(brace
op_increment
id|count
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|send_sig
c_func
(paren
id|sig
comma
op_star
id|p
comma
l_int|0
)paren
)paren
op_ne
op_minus
id|EPERM
)paren
id|retval
op_assign
id|err
suffix:semicolon
)brace
r_return
id|count
ques
c_cond
id|retval
suffix:colon
op_minus
id|ESRCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
id|kill_pg
c_func
(paren
op_minus
id|pid
comma
id|sig
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Normal kill */
r_return
id|kill_proc
c_func
(paren
id|pid
comma
id|sig
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine if a process group is &quot;orphaned&quot;, according to the POSIX&n; * definition in 2.2.2.52.  Orphaned process groups are not to be affected&n; * by terminal-generated stop signals.  Newly orphaned process groups are &n; * to receive a SIGHUP and a SIGCONT.&n; * &n; * &quot;I ask you, have you ever known what it is to be an orphan?&quot;&n; */
DECL|function|is_orphaned_pgrp
r_int
id|is_orphaned_pgrp
c_func
(paren
r_int
id|pgrp
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|p
)paren
op_logical_or
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pgrp
op_ne
id|pgrp
)paren
op_logical_or
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_ZOMBIE
)paren
op_logical_or
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_pptr-&gt;pid
op_eq
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_pptr-&gt;pgrp
op_ne
id|pgrp
)paren
op_logical_and
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_pptr-&gt;session
op_eq
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|session
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* (sighing) &quot;Often!&quot; */
)brace
DECL|function|has_stopped_jobs
r_static
r_int
id|has_stopped_jobs
c_func
(paren
r_int
id|pgrp
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
op_logical_or
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pgrp
op_ne
id|pgrp
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_STOPPED
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|forget_original_parent
r_static
r_void
id|forget_original_parent
c_func
(paren
r_struct
id|task_struct
op_star
id|father
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_opptr
op_eq
id|father
)paren
r_if
c_cond
(paren
id|task
(braket
l_int|1
)braket
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_opptr
op_assign
id|task
(braket
l_int|1
)braket
suffix:semicolon
r_else
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_opptr
op_assign
id|task
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|do_exit
r_volatile
r_void
id|do_exit
c_func
(paren
r_int
id|code
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|fake_volatile
suffix:colon
id|free_page_tables
c_func
(paren
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
)paren
comma
id|get_limit
c_func
(paren
l_int|0x0f
)paren
)paren
suffix:semicolon
id|free_page_tables
c_func
(paren
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|2
)braket
)paren
comma
id|get_limit
c_func
(paren
l_int|0x17
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
id|NR_OPEN
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|current-&gt;filp
(braket
id|i
)braket
)paren
id|sys_close
c_func
(paren
id|i
)paren
suffix:semicolon
id|forget_original_parent
c_func
(paren
id|current
)paren
suffix:semicolon
id|iput
c_func
(paren
id|current-&gt;pwd
)paren
suffix:semicolon
id|current-&gt;pwd
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|current-&gt;root
)paren
suffix:semicolon
id|current-&gt;root
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|current-&gt;executable
)paren
suffix:semicolon
id|current-&gt;executable
op_assign
l_int|NULL
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
id|current-&gt;numlibraries
suffix:semicolon
id|i
op_increment
)paren
(brace
id|iput
c_func
(paren
id|current-&gt;libraries
(braket
id|i
)braket
dot
id|library
)paren
suffix:semicolon
id|current-&gt;libraries
(braket
id|i
)braket
dot
id|library
op_assign
l_int|NULL
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_ZOMBIE
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|code
suffix:semicolon
id|current-&gt;rss
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;&t; * Check to see if any process groups have become orphaned&n;&t; * as a result of our exiting, and if they have any stopped&n;&t; * jobs, send them a SIGUP and then a SIGCONT.  (POSIX 3.2.2.2)&n;&t; *&n;&t; * Case i: Our father is in a different pgrp than we are&n;&t; * and we were the only connection outside, so our pgrp&n;&t; * is about to become orphaned.&n; &t; */
r_if
c_cond
(paren
(paren
id|current-&gt;p_pptr-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
op_logical_and
(paren
id|current-&gt;p_pptr-&gt;session
op_eq
id|current-&gt;session
)paren
op_logical_and
id|is_orphaned_pgrp
c_func
(paren
id|current-&gt;pgrp
)paren
op_logical_and
id|has_stopped_jobs
c_func
(paren
id|current-&gt;pgrp
)paren
)paren
(brace
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|SIGCONT
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Let father know we died */
id|send_sig
(paren
id|SIGCHLD
comma
id|current-&gt;p_pptr
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This loop does two things:&n;&t; * &n;  &t; * A.  Make init inherit all the child processes&n;&t; * B.  Check to see if any process groups have become orphaned&n;&t; *&t;as a result of our exiting, and if they have any stopped&n;&t; *&t;jobs, send them a SIGHUP and then a SIGCONT.  (POSIX 3.2.2.2)&n;&t; */
r_while
c_loop
(paren
id|p
op_assign
id|current-&gt;p_cptr
)paren
(brace
id|current-&gt;p_cptr
op_assign
id|p-&gt;p_osptr
suffix:semicolon
id|p-&gt;p_ysptr
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_and_assign
op_complement
id|PF_PTRACED
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
l_int|1
)braket
)paren
id|p-&gt;p_pptr
op_assign
id|task
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|p-&gt;p_pptr
op_assign
id|task
(braket
l_int|0
)braket
suffix:semicolon
id|p-&gt;p_osptr
op_assign
id|p-&gt;p_pptr-&gt;p_cptr
suffix:semicolon
id|p-&gt;p_osptr-&gt;p_ysptr
op_assign
id|p
suffix:semicolon
id|p-&gt;p_pptr-&gt;p_cptr
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
id|send_sig
c_func
(paren
id|SIGCHLD
comma
id|p-&gt;p_pptr
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * process group orphan check&n;&t;&t; * Case ii: Our child is in a different pgrp &n;&t;&t; * than we are, and it was the only connection&n;&t;&t; * outside, so the child pgrp is now orphaned.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|p-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
op_logical_and
(paren
id|p-&gt;session
op_eq
id|current-&gt;session
)paren
op_logical_and
id|is_orphaned_pgrp
c_func
(paren
id|p-&gt;pgrp
)paren
op_logical_and
id|has_stopped_jobs
c_func
(paren
id|p-&gt;pgrp
)paren
)paren
(brace
id|kill_pg
c_func
(paren
id|p-&gt;pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
id|kill_pg
c_func
(paren
id|p-&gt;pgrp
comma
id|SIGCONT
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|current-&gt;leader
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;tty
op_ge
l_int|0
)paren
(brace
id|tty
op_assign
id|TTY_TABLE
c_func
(paren
id|current-&gt;tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;pgrp
OG
l_int|0
)paren
id|kill_pg
c_func
(paren
id|tty-&gt;pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
id|tty-&gt;pgrp
op_assign
op_minus
l_int|1
suffix:semicolon
id|tty-&gt;session
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|session
op_eq
id|current-&gt;session
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|tty
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef DEBUG_PROC_TREE
id|audit_ptree
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * In order to get rid of the &quot;volatile function does return&quot; message&n; * I did this little loop that confuses gcc to think do_exit really&n; * is volatile. In fact it&squot;s schedule() that is volatile in some&n; * circumstances: when current-&gt;state = ZOMBIE, schedule() never&n; * returns.&n; *&n; * In fact the natural way to do all this is to have the label and the&n; * goto right after each other, but I put the fake_volatile label at&n; * the start of the function just in case something /really/ bad&n; * happens, and the schedule returns. This way we can try again. I&squot;m&n; * not paranoid: it&squot;s just that everybody is out to get me.&n; */
r_goto
id|fake_volatile
suffix:semicolon
)brace
DECL|function|sys_exit
r_int
id|sys_exit
c_func
(paren
r_int
id|error_code
)paren
(brace
id|do_exit
c_func
(paren
(paren
id|error_code
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|sys_waitpid
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
(brace
r_int
id|flag
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|oldblocked
suffix:semicolon
r_if
c_cond
(paren
id|stat_addr
)paren
id|verify_area
c_func
(paren
id|stat_addr
comma
l_int|4
)paren
suffix:semicolon
id|repeat
suffix:colon
id|flag
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|current-&gt;p_cptr
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;p_osptr
)paren
(brace
r_if
c_cond
(paren
id|pid
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_ne
id|pid
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pid
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pgrp
op_ne
op_minus
id|pid
)paren
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p-&gt;state
)paren
(brace
r_case
id|TASK_STOPPED
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;exit_code
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|options
op_amp
id|WUNTRACED
)paren
op_logical_and
op_logical_neg
(paren
id|p-&gt;flags
op_amp
id|PF_PTRACED
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|stat_addr
)paren
id|put_fs_long
c_func
(paren
(paren
id|p-&gt;exit_code
op_lshift
l_int|8
)paren
op_or
l_int|0x7f
comma
id|stat_addr
)paren
suffix:semicolon
id|p-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
r_return
id|p-&gt;pid
suffix:semicolon
r_case
id|TASK_ZOMBIE
suffix:colon
id|current-&gt;cutime
op_add_assign
id|p-&gt;utime
op_plus
id|p-&gt;cutime
suffix:semicolon
id|current-&gt;cstime
op_add_assign
id|p-&gt;stime
op_plus
id|p-&gt;cstime
suffix:semicolon
id|current-&gt;cmin_flt
op_add_assign
id|p-&gt;min_flt
op_plus
id|p-&gt;cmin_flt
suffix:semicolon
id|current-&gt;cmaj_flt
op_add_assign
id|p-&gt;maj_flt
op_plus
id|p-&gt;cmaj_flt
suffix:semicolon
id|flag
op_assign
id|p-&gt;pid
suffix:semicolon
r_if
c_cond
(paren
id|stat_addr
)paren
id|put_fs_long
c_func
(paren
id|p-&gt;exit_code
comma
id|stat_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;p_opptr
op_ne
id|p-&gt;p_pptr
)paren
(brace
id|REMOVE_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;p_pptr
op_assign
id|p-&gt;p_opptr
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGCHLD
comma
id|p-&gt;p_pptr
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|release
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PROC_TREE
id|audit_ptree
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|flag
suffix:semicolon
r_default
suffix:colon
id|flag
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|flag
)paren
(brace
r_if
c_cond
(paren
id|options
op_amp
id|WNOHANG
)paren
r_return
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|oldblocked
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_and_assign
op_complement
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
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|oldblocked
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
(paren
id|current-&gt;blocked
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGCHLD
op_minus
l_int|1
)paren
)paren
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_else
r_goto
id|repeat
suffix:semicolon
)brace
r_return
op_minus
id|ECHILD
suffix:semicolon
)brace
eof
