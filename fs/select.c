multiline_comment|/*&n; * This file contains the procedures for the handling of select&n; *&n; * Created for Linux based loosely upon Mathius Lattner&squot;s minix&n; * patches by Peter MacDonald. Heavily edited by Linus.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x,y) (((x)+(y)-1)/(y))
multiline_comment|/*&n; * Ok, Peter made a complicated, but straightforward multiple_wait() function.&n; * I have rewritten this, taking some shortcuts: This code may not be easy to&n; * follow, but it should be free of race-conditions, and it&squot;s practical. If you&n; * understand what I&squot;m doing here, then you understand how the linux&n; * sleep/wakeup mechanism works.&n; *&n; * Two very simple procedures, select_wait() and free_wait() make all the work.&n; * select_wait() is a inline-function defined in &lt;linux/sched.h&gt;, as all select&n; * functions have to call it to add an entry to the select table.&n; */
multiline_comment|/*&n; * I rewrote this again to make the select_table size variable, take some&n; * more shortcuts, improve responsiveness, and remove another race that&n; * Linus noticed.  -- jrs&n; */
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
r_struct
id|select_table_entry
op_star
id|entry
op_assign
id|p-&gt;entry
op_plus
id|p-&gt;nr
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;nr
OG
l_int|0
)paren
(brace
id|p-&gt;nr
op_decrement
suffix:semicolon
id|entry
op_decrement
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|entry-&gt;wait_address
comma
op_amp
id|entry-&gt;wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The check function checks the ready status of a file using the vfs layer.&n; *&n; * If the file was not ready we were added to its wait queue.  But in&n; * case it became ready just after the check and just before it called&n; * select_wait, we call it again, knowing we are already on its&n; * wait queue this time.  The second call is not necessary if the&n; * select_table is NULL indicating an earlier file check was ready&n; * and we aren&squot;t going to sleep on the select_table.  -- jrs&n; */
DECL|function|check
r_static
r_int
id|check
c_func
(paren
r_int
id|flag
comma
id|select_table
op_star
id|wait
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
r_int
(paren
op_star
id|select
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
id|select_table
op_star
)paren
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_inode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fops
op_assign
id|file-&gt;f_op
)paren
op_logical_and
(paren
id|select
op_assign
id|fops-&gt;select
)paren
)paren
r_return
id|select
c_func
(paren
id|inode
comma
id|file
comma
id|flag
comma
id|wait
)paren
op_logical_or
(paren
id|wait
op_logical_and
id|select
c_func
(paren
id|inode
comma
id|file
comma
id|flag
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
l_int|1
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
r_int
id|n
comma
id|fd_set
op_star
id|in
comma
id|fd_set
op_star
id|out
comma
id|fd_set
op_star
id|ex
comma
id|fd_set
op_star
id|res_in
comma
id|fd_set
op_star
id|res_out
comma
id|fd_set
op_star
id|res_ex
)paren
(brace
r_int
id|count
suffix:semicolon
id|select_table
id|wait_table
comma
op_star
id|wait
suffix:semicolon
r_struct
id|select_table_entry
op_star
id|entry
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|max
suffix:semicolon
id|max
op_assign
op_minus
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|FD_ISSET
c_func
(paren
id|i
comma
id|in
)paren
op_logical_and
op_logical_neg
id|FD_ISSET
c_func
(paren
id|i
comma
id|out
)paren
op_logical_and
op_logical_neg
id|FD_ISSET
c_func
(paren
id|i
comma
id|ex
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
id|max
op_assign
id|i
suffix:semicolon
)brace
id|n
op_assign
id|max
op_plus
l_int|1
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|select_table_entry
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|FD_ZERO
c_func
(paren
id|res_in
)paren
suffix:semicolon
id|FD_ZERO
c_func
(paren
id|res_out
)paren
suffix:semicolon
id|FD_ZERO
c_func
(paren
id|res_ex
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|wait_table.nr
op_assign
l_int|0
suffix:semicolon
id|wait_table.entry
op_assign
id|entry
suffix:semicolon
id|wait
op_assign
op_amp
id|wait_table
suffix:semicolon
id|repeat
suffix:colon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|FD_ISSET
c_func
(paren
id|i
comma
id|in
)paren
op_logical_and
id|check
c_func
(paren
id|SEL_IN
comma
id|wait
comma
id|current-&gt;filp
(braket
id|i
)braket
)paren
)paren
(brace
id|FD_SET
c_func
(paren
id|i
comma
id|res_in
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|wait
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|FD_ISSET
c_func
(paren
id|i
comma
id|out
)paren
op_logical_and
id|check
c_func
(paren
id|SEL_OUT
comma
id|wait
comma
id|current-&gt;filp
(braket
id|i
)braket
)paren
)paren
(brace
id|FD_SET
c_func
(paren
id|i
comma
id|res_out
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|wait
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|FD_ISSET
c_func
(paren
id|i
comma
id|ex
)paren
op_logical_and
id|check
c_func
(paren
id|SEL_EX
comma
id|wait
comma
id|current-&gt;filp
(braket
id|i
)braket
)paren
)paren
(brace
id|FD_SET
c_func
(paren
id|i
comma
id|res_ex
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|wait
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|wait
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
op_logical_and
id|current-&gt;timeout
op_logical_and
op_logical_neg
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
)paren
(brace
id|schedule
c_func
(paren
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
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|entry
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
DECL|function|__get_fd_set
r_static
r_void
id|__get_fd_set
c_func
(paren
r_int
id|nr
comma
r_int
r_int
op_star
id|fs_pointer
comma
r_int
r_int
op_star
id|fdset
)paren
(brace
id|FD_ZERO
c_func
(paren
id|fdset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fs_pointer
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|nr
OG
l_int|0
)paren
(brace
op_star
id|fdset
op_assign
id|get_fs_long
c_func
(paren
id|fs_pointer
)paren
suffix:semicolon
id|fdset
op_increment
suffix:semicolon
id|fs_pointer
op_increment
suffix:semicolon
id|nr
op_sub_assign
l_int|32
suffix:semicolon
)brace
)brace
DECL|function|__set_fd_set
r_static
r_void
id|__set_fd_set
c_func
(paren
r_int
id|nr
comma
r_int
r_int
op_star
id|fs_pointer
comma
r_int
r_int
op_star
id|fdset
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fs_pointer
)paren
r_return
suffix:semicolon
id|verify_area
c_func
(paren
id|fs_pointer
comma
r_sizeof
(paren
id|fd_set
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr
OG
l_int|0
)paren
(brace
id|put_fs_long
c_func
(paren
op_star
id|fdset
comma
id|fs_pointer
)paren
suffix:semicolon
id|fdset
op_increment
suffix:semicolon
id|fs_pointer
op_increment
suffix:semicolon
id|nr
op_sub_assign
l_int|32
suffix:semicolon
)brace
)brace
DECL|macro|get_fd_set
mdefine_line|#define get_fd_set(nr,fsp,fdp) &bslash;&n;__get_fd_set(nr, (unsigned long *) (fsp), (unsigned long *) (fdp))
DECL|macro|set_fd_set
mdefine_line|#define set_fd_set(nr,fsp,fdp) &bslash;&n;__set_fd_set(nr, (unsigned long *) (fsp), (unsigned long *) (fdp))
multiline_comment|/*&n; * We can actually return ERESTARTSYS insetad of EINTR, but I&squot;d&n; * like to be certain this leads to no problems. So I return&n; * EINTR just for safety.&n; */
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
comma
op_star
id|inp
suffix:semicolon
id|fd_set
id|res_out
comma
id|out
comma
op_star
id|outp
suffix:semicolon
id|fd_set
id|res_ex
comma
id|ex
comma
op_star
id|exp
suffix:semicolon
r_int
id|n
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
id|n
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
id|n
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|NR_OPEN
)paren
id|n
op_assign
id|NR_OPEN
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
id|get_fd_set
c_func
(paren
id|n
comma
id|inp
comma
op_amp
id|in
)paren
suffix:semicolon
id|get_fd_set
c_func
(paren
id|n
comma
id|outp
comma
op_amp
id|out
)paren
suffix:semicolon
id|get_fd_set
c_func
(paren
id|n
comma
id|exp
comma
op_amp
id|ex
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
id|jiffies
suffix:semicolon
id|timeout
op_add_assign
id|ROUND_UP
c_func
(paren
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
comma
(paren
l_int|1000000
op_div
id|HZ
)paren
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
r_if
c_cond
(paren
id|timeout
op_le
id|jiffies
)paren
id|timeout
op_assign
l_int|0
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
id|n
comma
op_amp
id|in
comma
op_amp
id|out
comma
op_amp
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
OL
l_int|0
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_and
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
id|set_fd_set
c_func
(paren
id|n
comma
id|inp
comma
op_amp
id|res_in
)paren
suffix:semicolon
id|set_fd_set
c_func
(paren
id|n
comma
id|outp
comma
op_amp
id|res_out
)paren
suffix:semicolon
id|set_fd_set
c_func
(paren
id|n
comma
id|exp
comma
op_amp
id|res_ex
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
