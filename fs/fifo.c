multiline_comment|/*&n; *  linux/fs/fifo.c&n; *&n; *  written by Paul H. Hargrove&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
r_extern
r_struct
id|file_operations
id|read_pipe_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|write_pipe_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|rdwr_pipe_fops
suffix:semicolon
DECL|function|fifo_open
r_static
r_int
id|fifo_open
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
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_switch
c_cond
(paren
id|filp-&gt;f_mode
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/*&n;&t; *  O_RDONLY&n;&t; *  POSIX.1 says that O_NONBLOCK means return with the FIFO&n;&t; *  opened, even when there is no process writing the FIFO.&n;&t; */
id|filp-&gt;f_op
op_assign
op_amp
id|read_pipe_fops
suffix:semicolon
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
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
r_while
c_loop
(paren
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
id|PIPE_HEAD
c_func
(paren
op_star
id|inode
)paren
op_ne
id|PIPE_TAIL
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
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|PIPE_READ_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/*&n;&t; *  O_WRONLY&n;&t; *  POSIX.1 says that O_NONBLOCK means return -1 with&n;&t; *  errno=ENXIO when there is no process reading the FIFO.&n;&t; */
r_if
c_cond
(paren
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
op_logical_and
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|filp-&gt;f_op
op_assign
op_amp
id|write_pipe_fops
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|PIPE_WRITE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/*&n;&t; *  O_RDWR&n;&t; *  POSIX.1 leaves this case &quot;undefined&quot; when O_NONBLOCK is set.&n;&t; *  This implementation will NEVER block on a O_RDWR open, since&n;&t; *  the process can at least talk to itself.&n;&t; */
id|filp-&gt;f_op
op_assign
op_amp
id|rdwr_pipe_fops
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_add_assign
l_int|1
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_add_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|PIPE_READ_WAIT
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
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|PIPE_WRITE_WAIT
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
id|retval
op_logical_or
id|inode-&gt;i_size
)paren
r_return
id|retval
suffix:semicolon
id|page
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
)paren
(brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|page
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Dummy default file-operations: the only thing this does&n; * is contain the open that then fills in the correct operations&n; * depending on the access mode of the file...&n; */
DECL|variable|def_fifo_fops
r_struct
id|file_operations
id|def_fifo_fops
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|fifo_open
comma
multiline_comment|/* will set read or write pipe_fops */
l_int|NULL
)brace
suffix:semicolon
eof
