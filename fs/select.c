multiline_comment|/*&n; * This file contains the procedures for the handling of select&n; *&n; * Created for Linux based loosely upon Mathius Lattner&squot;s minix&n; * patches by Peter MacDonald. Heavily edited by Linus.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;const.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
multiline_comment|/*&n; * Ok, Peter made a complicated, but straightforward multiple_wait() function.&n; * I have rewritten this, taking some shortcuts: This code may not be easy to&n; * follow, but it should be free of race-conditions, and it&squot;s practical. If you&n; * understand what I&squot;m doing here, then you understand how the linux sleep/wakeup&n; * mechanism works.&n; *&n; * Two very simple procedures, add_wait() and free_wait() make all the work. We&n; * have to have interrupts disabled throughout the select, but that&squot;s not really&n; * such a loss: sleeping automatically frees interrupts when we aren&squot;t in this&n; * task.&n; */
DECL|variable|sel_tables
r_static
id|select_table
op_star
id|sel_tables
op_assign
l_int|NULL
suffix:semicolon
DECL|function|add_wait
r_static
r_void
id|add_wait
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|wait_address
comma
id|select_table
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
id|wait_address
)paren
r_return
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
id|p-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|p-&gt;entry
(braket
id|i
)braket
dot
id|wait_address
op_eq
id|wait_address
)paren
r_return
suffix:semicolon
id|current-&gt;next_wait
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;entry
(braket
id|p-&gt;nr
)braket
dot
id|wait_address
op_assign
id|wait_address
suffix:semicolon
id|p-&gt;entry
(braket
id|p-&gt;nr
)braket
dot
id|old_task
op_assign
op_star
id|wait_address
suffix:semicolon
op_star
id|wait_address
op_assign
id|current
suffix:semicolon
id|p-&gt;nr
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * free_wait removes the current task from any wait-queues and then&n; * wakes up the queues.&n; */
DECL|function|free_one_table
r_static
r_void
id|free_one_table
c_func
(paren
id|select_table
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|tpp
suffix:semicolon
r_for
c_loop
(paren
id|tpp
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|tpp
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|tpp
)paren
r_if
c_cond
(paren
op_star
id|tpp
op_logical_and
(paren
(paren
op_star
id|tpp
)paren
op_member_access_from_pointer
id|next_wait
op_eq
id|p-&gt;current
)paren
)paren
(paren
op_star
id|tpp
)paren
op_member_access_from_pointer
id|next_wait
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;nr
)paren
r_return
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
id|p-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wake_up
c_func
(paren
id|p-&gt;entry
(braket
id|i
)braket
dot
id|wait_address
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|p-&gt;entry
(braket
id|i
)braket
dot
id|old_task
)paren
suffix:semicolon
)brace
id|p-&gt;nr
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|free_wait
r_static
r_void
id|free_wait
c_func
(paren
id|select_table
op_star
id|p
)paren
(brace
id|select_table
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;woken
)paren
r_return
suffix:semicolon
id|p
op_assign
id|sel_tables
suffix:semicolon
id|sel_tables
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|p-&gt;current
)paren
suffix:semicolon
id|p-&gt;woken
op_assign
l_int|1
suffix:semicolon
id|tmp
op_assign
id|p-&gt;next_table
suffix:semicolon
id|p-&gt;next_table
op_assign
l_int|NULL
suffix:semicolon
id|free_one_table
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|tmp
suffix:semicolon
)brace
)brace
DECL|function|get_tty
r_static
r_struct
id|tty_struct
op_star
id|get_tty
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|major
comma
id|minor
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|major
op_assign
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
op_ne
l_int|5
op_logical_and
id|major
op_ne
l_int|4
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|major
op_eq
l_int|5
)paren
id|minor
op_assign
id|current-&gt;tty
suffix:semicolon
r_else
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|TTY_TABLE
c_func
(paren
id|minor
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The check_XX functions check out a file. We know it&squot;s either&n; * a pipe, a character device or a fifo (fifo&squot;s not implemented)&n; */
DECL|function|check_in
r_static
r_int
id|check_in
c_func
(paren
id|select_table
op_star
id|wait
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_assign
id|get_tty
c_func
(paren
id|inode
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|EMPTY
c_func
(paren
id|tty-&gt;secondary
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tty-&gt;link
op_logical_and
op_logical_neg
id|tty-&gt;link-&gt;count
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|tty-&gt;secondary-&gt;proc_list
comma
id|wait
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
r_if
c_cond
(paren
op_logical_neg
id|PIPE_EMPTY
c_func
(paren
op_star
id|inode
)paren
op_logical_or
id|inode-&gt;i_count
OL
l_int|2
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
id|wait
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_if
c_cond
(paren
id|sock_select
c_func
(paren
id|inode
comma
l_int|NULL
comma
id|SEL_IN
comma
id|wait
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_out
r_static
r_int
id|check_out
c_func
(paren
id|select_table
op_star
id|wait
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_assign
id|get_tty
c_func
(paren
id|inode
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|FULL
c_func
(paren
id|tty-&gt;write_q
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|tty-&gt;write_q-&gt;proc_list
comma
id|wait
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
r_if
c_cond
(paren
op_logical_neg
id|PIPE_FULL
c_func
(paren
op_star
id|inode
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
id|wait
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_if
c_cond
(paren
id|sock_select
c_func
(paren
id|inode
comma
l_int|NULL
comma
id|SEL_OUT
comma
id|wait
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_ex
r_static
r_int
id|check_ex
c_func
(paren
id|select_table
op_star
id|wait
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_assign
id|get_tty
c_func
(paren
id|inode
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|FULL
c_func
(paren
id|tty-&gt;write_q
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
r_if
c_cond
(paren
id|inode-&gt;i_count
OL
l_int|2
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
id|wait
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_if
c_cond
(paren
id|sock_select
c_func
(paren
id|inode
comma
l_int|NULL
comma
id|SEL_EX
comma
id|wait
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|add_wait
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_select
r_int
id|do_select
c_func
(paren
id|fd_set
id|in
comma
id|fd_set
id|out
comma
id|fd_set
id|ex
comma
id|fd_set
op_star
id|inp
comma
id|fd_set
op_star
id|outp
comma
id|fd_set
op_star
id|exp
)paren
(brace
r_int
id|count
suffix:semicolon
id|select_table
id|wait_table
suffix:semicolon
r_int
id|i
suffix:semicolon
id|fd_set
id|mask
suffix:semicolon
id|mask
op_assign
id|in
op_or
id|out
op_or
id|ex
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
comma
id|mask
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;filp
(braket
id|i
)braket
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode-&gt;i_pipe
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode-&gt;i_mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode-&gt;i_mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode-&gt;i_mode
)paren
)paren
r_continue
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|repeat
suffix:colon
id|wait_table.nr
op_assign
l_int|0
suffix:semicolon
id|wait_table.woken
op_assign
l_int|0
suffix:semicolon
id|wait_table.current
op_assign
id|current
suffix:semicolon
id|wait_table.next_table
op_assign
id|sel_tables
suffix:semicolon
id|sel_tables
op_assign
op_amp
id|wait_table
suffix:semicolon
op_star
id|inp
op_assign
op_star
id|outp
op_assign
op_star
id|exp
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|mask
op_assign
l_int|1
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
comma
id|mask
op_add_assign
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
id|in
)paren
r_if
c_cond
(paren
id|check_in
c_func
(paren
op_amp
id|wait_table
comma
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode
)paren
)paren
(brace
op_star
id|inp
op_or_assign
id|mask
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
op_amp
id|out
)paren
r_if
c_cond
(paren
id|check_out
c_func
(paren
op_amp
id|wait_table
comma
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode
)paren
)paren
(brace
op_star
id|outp
op_or_assign
id|mask
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
op_amp
id|ex
)paren
r_if
c_cond
(paren
id|check_ex
c_func
(paren
op_amp
id|wait_table
comma
id|current-&gt;filp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_inode
)paren
)paren
(brace
op_star
id|exp
op_or_assign
id|mask
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
op_logical_and
id|current-&gt;timeout
op_logical_and
op_logical_neg
id|count
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|free_wait
c_func
(paren
op_amp
id|wait_table
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|free_wait
c_func
(paren
op_amp
id|wait_table
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that we cannot return -ERESTARTSYS, as we change our input&n; * parameters. Sad, but there you are. We could do some tweaking in&n; * the library function ...&n; */
DECL|function|sys_select
r_int
id|sys_select
c_func
(paren
r_int
r_int
op_star
id|buffer
)paren
(brace
multiline_comment|/* Perform the select(nd, in, out, ex, tv) system call. */
r_int
id|i
suffix:semicolon
id|fd_set
id|res_in
comma
id|in
op_assign
l_int|0
comma
op_star
id|inp
suffix:semicolon
id|fd_set
id|res_out
comma
id|out
op_assign
l_int|0
comma
op_star
id|outp
suffix:semicolon
id|fd_set
id|res_ex
comma
id|ex
op_assign
l_int|0
comma
op_star
id|exp
suffix:semicolon
id|fd_set
id|mask
suffix:semicolon
r_struct
id|timeval
op_star
id|tvp
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|mask
op_assign
id|get_fs_long
c_func
(paren
id|buffer
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_ge
l_int|32
)paren
id|mask
op_assign
op_complement
l_int|0
suffix:semicolon
r_else
id|mask
op_assign
op_complement
(paren
(paren
op_complement
l_int|0
)paren
op_lshift
id|mask
)paren
suffix:semicolon
id|inp
op_assign
(paren
id|fd_set
op_star
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_increment
)paren
suffix:semicolon
id|outp
op_assign
(paren
id|fd_set
op_star
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_increment
)paren
suffix:semicolon
id|exp
op_assign
(paren
id|fd_set
op_star
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_increment
)paren
suffix:semicolon
id|tvp
op_assign
(paren
r_struct
id|timeval
op_star
)paren
id|get_fs_long
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inp
)paren
id|in
op_assign
id|mask
op_amp
id|get_fs_long
c_func
(paren
id|inp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|outp
)paren
id|out
op_assign
id|mask
op_amp
id|get_fs_long
c_func
(paren
id|outp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp
)paren
id|ex
op_assign
id|mask
op_amp
id|get_fs_long
c_func
(paren
id|exp
)paren
suffix:semicolon
id|timeout
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|tvp
)paren
(brace
id|timeout
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|tvp-&gt;tv_usec
)paren
op_div
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|timeout
op_add_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|tvp-&gt;tv_sec
)paren
op_star
id|HZ
suffix:semicolon
id|timeout
op_add_assign
id|jiffies
suffix:semicolon
)brace
id|current-&gt;timeout
op_assign
id|timeout
suffix:semicolon
id|i
op_assign
id|do_select
c_func
(paren
id|in
comma
id|out
comma
id|ex
comma
op_amp
id|res_in
comma
op_amp
id|res_out
comma
op_amp
id|res_ex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;timeout
OG
id|jiffies
)paren
id|timeout
op_assign
id|current-&gt;timeout
op_minus
id|jiffies
suffix:semicolon
r_else
id|timeout
op_assign
l_int|0
suffix:semicolon
id|current-&gt;timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|inp
)paren
(brace
id|verify_area
c_func
(paren
id|inp
comma
l_int|4
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|res_in
comma
id|inp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|outp
)paren
(brace
id|verify_area
c_func
(paren
id|outp
comma
l_int|4
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|res_out
comma
id|outp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exp
)paren
(brace
id|verify_area
c_func
(paren
id|exp
comma
l_int|4
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|res_ex
comma
id|exp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tvp
)paren
(brace
id|verify_area
c_func
(paren
id|tvp
comma
r_sizeof
(paren
op_star
id|tvp
)paren
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|timeout
op_div
id|HZ
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tvp-&gt;tv_sec
)paren
suffix:semicolon
id|timeout
op_mod_assign
id|HZ
suffix:semicolon
id|timeout
op_mul_assign
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|timeout
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tvp-&gt;tv_usec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
