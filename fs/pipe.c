multiline_comment|/*&n; *  linux/fs/pipe.c&n; *&n; *  Copyright (C) 1991, 1992, 1999  Linus Torvalds&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * We use a start+len construction, which provides full use of the &n; * allocated memory.&n; * -- Florian Coosmann (FGC)&n; * &n; * Reads with count = 0 should always return 0.&n; * -- Julian Bradfield 1999-06-07.&n; */
multiline_comment|/* Drop the inode semaphore and wait for a pipe event, atomically */
DECL|function|pipe_wait
r_void
id|pipe_wait
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
op_amp
id|wait
)paren
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pipe_read
id|pipe_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|size
comma
id|read
comma
id|ret
suffix:semicolon
multiline_comment|/* Seeks are not allowed on pipes.  */
id|ret
op_assign
op_minus
id|ESPIPE
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|filp-&gt;f_pos
)paren
r_goto
id|out_nolock
suffix:semicolon
multiline_comment|/* Always return 0 on null read.  */
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|out_nolock
suffix:semicolon
multiline_comment|/* Get the pipe semaphore */
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
)paren
r_goto
id|out_nolock
suffix:semicolon
r_if
c_cond
(paren
id|PIPE_EMPTY
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
id|do_more_read
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|PIPE_WAITING_READERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|pipe_wait
c_func
(paren
id|inode
)paren
suffix:semicolon
id|PIPE_WAITING_READERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
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
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/* Read what data is available.  */
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
op_logical_and
(paren
id|size
op_assign
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
)paren
)paren
(brace
r_char
op_star
id|pipebuf
op_assign
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_plus
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
id|ssize_t
id|chars
op_assign
id|PIPE_MAX_RCHUNK
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|count
)paren
id|chars
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|size
)paren
id|chars
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|pipebuf
comma
id|chars
)paren
)paren
r_goto
id|out
suffix:semicolon
id|read
op_add_assign
id|chars
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_add_assign
id|chars
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_and_assign
(paren
id|PIPE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_sub_assign
id|chars
suffix:semicolon
id|count
op_sub_assign
id|chars
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
)brace
multiline_comment|/* Cache behaviour optimization */
r_if
c_cond
(paren
op_logical_neg
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
)paren
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_logical_and
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_logical_and
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We know that we are going to sleep: signal&n;&t;&t; * writers synchronously that there is more&n;&t;&t; * room.&n;&t;&t; */
id|wake_up_interruptible_sync
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
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
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_goto
id|do_more_read
suffix:semicolon
)brace
multiline_comment|/* Signal writers asynchronously that there is more room.  */
id|wake_up_interruptible
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|read
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|out_nolock
suffix:colon
r_if
c_cond
(paren
id|read
)paren
id|ret
op_assign
id|read
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pipe_write
id|pipe_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|free
comma
id|written
comma
id|ret
suffix:semicolon
multiline_comment|/* Seeks are not allowed on pipes.  */
id|ret
op_assign
op_minus
id|ESPIPE
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|filp-&gt;f_pos
)paren
r_goto
id|out_nolock
suffix:semicolon
multiline_comment|/* Null write succeeds.  */
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|out_nolock
suffix:semicolon
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
)paren
r_goto
id|out_nolock
suffix:semicolon
multiline_comment|/* No readers yields SIGPIPE.  */
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_goto
id|sigpipe
suffix:semicolon
multiline_comment|/* If count &lt;= PIPE_BUF, we have to make it atomic.  */
id|free
op_assign
(paren
id|count
op_le
id|PIPE_BUF
ques
c_cond
id|count
suffix:colon
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Wait, or check for, available space.  */
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
OL
id|free
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
OL
id|free
)paren
(brace
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|pipe_wait
c_func
(paren
id|inode
)paren
suffix:semicolon
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_goto
id|sigpipe
suffix:semicolon
)brace
)brace
multiline_comment|/* Copy into available space.  */
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
id|space
suffix:semicolon
r_char
op_star
id|pipebuf
op_assign
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_plus
id|PIPE_END
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
id|ssize_t
id|chars
op_assign
id|PIPE_MAX_WCHUNK
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|space
op_assign
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|chars
OG
id|count
)paren
id|chars
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|space
)paren
id|chars
op_assign
id|space
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pipebuf
comma
id|buf
comma
id|chars
)paren
)paren
r_goto
id|out
suffix:semicolon
id|written
op_add_assign
id|chars
suffix:semicolon
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_add_assign
id|chars
suffix:semicolon
id|count
op_sub_assign
id|chars
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
id|space
op_assign
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ret
op_assign
id|written
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_break
suffix:semicolon
r_do
(brace
multiline_comment|/*&n;&t;&t;&t; * Synchronous wake-up: it knows that this process&n;&t;&t;&t; * is going to give up this CPU, so it doesnt have&n;&t;&t;&t; * to do idle reschedules.&n;&t;&t;&t; */
id|wake_up_interruptible_sync
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|pipe_wait
c_func
(paren
id|inode
)paren
suffix:semicolon
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_goto
id|sigpipe
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|PIPE_FREE
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* Signal readers asynchronously that there is more data.  */
id|wake_up_interruptible
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|out_nolock
suffix:colon
r_if
c_cond
(paren
id|written
)paren
id|ret
op_assign
id|written
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|sigpipe
suffix:colon
r_if
c_cond
(paren
id|written
)paren
r_goto
id|out
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGPIPE
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
id|EPIPE
suffix:semicolon
)brace
r_static
id|loff_t
DECL|function|pipe_lseek
id|pipe_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|bad_pipe_r
id|bad_pipe_r
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|bad_pipe_w
id|bad_pipe_w
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_ioctl
id|pipe_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|pino
comma
r_struct
id|file
op_star
id|filp
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIONREAD
suffix:colon
r_return
id|put_user
c_func
(paren
id|PIPE_LEN
c_func
(paren
op_star
id|pino
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/* No kernel lock held - fine */
r_static
r_int
r_int
DECL|function|pipe_poll
id|pipe_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|poll_wait
c_func
(paren
id|filp
comma
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
id|wait
)paren
suffix:semicolon
multiline_comment|/* Reading only -- no need for aquiring the semaphore.  */
id|mask
op_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_if
c_cond
(paren
id|PIPE_EMPTY
c_func
(paren
op_star
id|inode
)paren
)paren
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_logical_and
id|filp-&gt;f_version
op_ne
id|PIPE_WCOUNTER
c_func
(paren
op_star
id|inode
)paren
)paren
id|mask
op_or_assign
id|POLLHUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
id|mask
op_or_assign
id|POLLERR
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/* FIXME: most Unices do not set POLLERR for fifos */
DECL|macro|fifo_poll
mdefine_line|#define fifo_poll pipe_poll
r_static
r_int
DECL|function|pipe_release
id|pipe_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|decr
comma
r_int
id|decw
)paren
(brace
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_sub_assign
id|decr
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_sub_assign
id|decw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_logical_and
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
r_struct
id|pipe_inode_info
op_star
id|info
op_assign
id|inode-&gt;i_pipe
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|info-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
r_else
(brace
id|wake_up_interruptible
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_read_release
id|pipe_read_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_return
id|pipe_release
c_func
(paren
id|inode
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_write_release
id|pipe_write_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_return
id|pipe_release
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_rdwr_release
id|pipe_rdwr_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|decr
comma
id|decw
suffix:semicolon
id|decr
op_assign
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_ne
l_int|0
suffix:semicolon
id|decw
op_assign
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_ne
l_int|0
suffix:semicolon
r_return
id|pipe_release
c_func
(paren
id|inode
comma
id|decr
comma
id|decw
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_read_open
id|pipe_read_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
multiline_comment|/* We could have perhaps used atomic_t, but this and friends&n;&t;   below are the only places.  So it doesn&squot;t seem worthwhile.  */
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_write_open
id|pipe_write_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pipe_rdwr_open
id|pipe_rdwr_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
id|down
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_READ
)paren
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
id|up
c_func
(paren
id|PIPE_SEM
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The file_operations structs are not static because they&n; * are also used in linux/fs/fifo.c to do operations on FIFOs.&n; */
DECL|variable|read_fifo_fops
r_struct
id|file_operations
id|read_fifo_fops
op_assign
(brace
id|llseek
suffix:colon
id|pipe_lseek
comma
id|read
suffix:colon
id|pipe_read
comma
id|write
suffix:colon
id|bad_pipe_w
comma
id|poll
suffix:colon
id|fifo_poll
comma
id|ioctl
suffix:colon
id|pipe_ioctl
comma
id|open
suffix:colon
id|pipe_read_open
comma
id|release
suffix:colon
id|pipe_read_release
comma
)brace
suffix:semicolon
DECL|variable|write_fifo_fops
r_struct
id|file_operations
id|write_fifo_fops
op_assign
(brace
id|llseek
suffix:colon
id|pipe_lseek
comma
id|read
suffix:colon
id|bad_pipe_r
comma
id|write
suffix:colon
id|pipe_write
comma
id|poll
suffix:colon
id|fifo_poll
comma
id|ioctl
suffix:colon
id|pipe_ioctl
comma
id|open
suffix:colon
id|pipe_write_open
comma
id|release
suffix:colon
id|pipe_write_release
comma
)brace
suffix:semicolon
DECL|variable|rdwr_fifo_fops
r_struct
id|file_operations
id|rdwr_fifo_fops
op_assign
(brace
id|llseek
suffix:colon
id|pipe_lseek
comma
id|read
suffix:colon
id|pipe_read
comma
id|write
suffix:colon
id|pipe_write
comma
id|poll
suffix:colon
id|fifo_poll
comma
id|ioctl
suffix:colon
id|pipe_ioctl
comma
id|open
suffix:colon
id|pipe_rdwr_open
comma
id|release
suffix:colon
id|pipe_rdwr_release
comma
)brace
suffix:semicolon
DECL|variable|read_pipe_fops
r_struct
id|file_operations
id|read_pipe_fops
op_assign
(brace
id|llseek
suffix:colon
id|pipe_lseek
comma
id|read
suffix:colon
id|pipe_read
comma
id|write
suffix:colon
id|bad_pipe_w
comma
id|poll
suffix:colon
id|pipe_poll
comma
id|ioctl
suffix:colon
id|pipe_ioctl
comma
id|open
suffix:colon
id|pipe_read_open
comma
id|release
suffix:colon
id|pipe_read_release
comma
)brace
suffix:semicolon
DECL|variable|write_pipe_fops
r_struct
id|file_operations
id|write_pipe_fops
op_assign
(brace
id|llseek
suffix:colon
id|pipe_lseek
comma
id|read
suffix:colon
id|bad_pipe_r
comma
id|write
suffix:colon
id|pipe_write
comma
id|poll
suffix:colon
id|pipe_poll
comma
id|ioctl
suffix:colon
id|pipe_ioctl
comma
id|open
suffix:colon
id|pipe_write_open
comma
id|release
suffix:colon
id|pipe_write_release
comma
)brace
suffix:semicolon
DECL|variable|rdwr_pipe_fops
r_struct
id|file_operations
id|rdwr_pipe_fops
op_assign
(brace
id|llseek
suffix:colon
id|pipe_lseek
comma
id|read
suffix:colon
id|pipe_read
comma
id|write
suffix:colon
id|pipe_write
comma
id|poll
suffix:colon
id|pipe_poll
comma
id|ioctl
suffix:colon
id|pipe_ioctl
comma
id|open
suffix:colon
id|pipe_rdwr_open
comma
id|release
suffix:colon
id|pipe_rdwr_release
comma
)brace
suffix:semicolon
DECL|function|pipe_new
r_struct
id|inode
op_star
id|pipe_new
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|NULL
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pipe_inode_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_pipe
)paren
r_goto
id|fail_page
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_assign
(paren
r_char
op_star
)paren
id|page
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_WAITING_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WAITING_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_RCOUNTER
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WCOUNTER
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
r_return
id|inode
suffix:semicolon
id|fail_page
suffix:colon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|get_pipe_inode
r_static
r_struct
id|inode
op_star
id|get_pipe_inode
c_func
(paren
r_void
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|get_empty_inode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|fail_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pipe_new
c_func
(paren
id|inode
)paren
)paren
(brace
r_goto
id|fail_iput
suffix:semicolon
)brace
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|rdwr_pipe_fops
suffix:semicolon
multiline_comment|/*&n;&t; * Mark the inode dirty from the very beginning,&n;&t; * that way it will never be moved to the dirty&n;&t; * list because &quot;mark_inode_dirty()&quot; will think&n;&t; * that it already _is_ on the dirty list.&n;&t; */
id|inode-&gt;i_state
op_assign
id|I_DIRTY
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFIFO
op_or
id|S_IRUSR
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
r_return
id|inode
suffix:semicolon
id|fail_iput
suffix:colon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|fail_inode
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|do_pipe
r_int
id|do_pipe
c_func
(paren
r_int
op_star
id|fd
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|f1
comma
op_star
id|f2
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|error
op_assign
op_minus
id|ENFILE
suffix:semicolon
id|f1
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f1
)paren
r_goto
id|no_files
suffix:semicolon
id|f2
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f2
)paren
r_goto
id|close_f1
suffix:semicolon
id|inode
op_assign
id|get_pipe_inode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|close_f12
suffix:semicolon
id|error
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|close_f12_inode
suffix:semicolon
id|i
op_assign
id|error
suffix:semicolon
id|error
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|close_f12_inode_i
suffix:semicolon
id|j
op_assign
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|f1-&gt;f_dentry
op_assign
id|f2-&gt;f_dentry
op_assign
id|dget
c_func
(paren
id|d_alloc_root
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f1-&gt;f_dentry
)paren
r_goto
id|close_f12_inode_i_j
suffix:semicolon
multiline_comment|/* read file */
id|f1-&gt;f_pos
op_assign
id|f2-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
id|f1-&gt;f_flags
op_assign
id|O_RDONLY
suffix:semicolon
id|f1-&gt;f_op
op_assign
op_amp
id|read_pipe_fops
suffix:semicolon
id|f1-&gt;f_mode
op_assign
l_int|1
suffix:semicolon
id|f1-&gt;f_version
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* write file */
id|f2-&gt;f_flags
op_assign
id|O_WRONLY
suffix:semicolon
id|f2-&gt;f_op
op_assign
op_amp
id|write_pipe_fops
suffix:semicolon
id|f2-&gt;f_mode
op_assign
l_int|2
suffix:semicolon
id|f2-&gt;f_version
op_assign
l_int|0
suffix:semicolon
id|fd_install
c_func
(paren
id|i
comma
id|f1
)paren
suffix:semicolon
id|fd_install
c_func
(paren
id|j
comma
id|f2
)paren
suffix:semicolon
id|fd
(braket
l_int|0
)braket
op_assign
id|i
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
id|j
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|close_f12_inode_i_j
suffix:colon
id|put_unused_fd
c_func
(paren
id|j
)paren
suffix:semicolon
id|close_f12_inode_i
suffix:colon
id|put_unused_fd
c_func
(paren
id|i
)paren
suffix:semicolon
id|close_f12_inode
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|inode-&gt;i_pipe
)paren
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|close_f12
suffix:colon
id|put_filp
c_func
(paren
id|f2
)paren
suffix:semicolon
id|close_f1
suffix:colon
id|put_filp
c_func
(paren
id|f1
)paren
suffix:semicolon
id|no_files
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
