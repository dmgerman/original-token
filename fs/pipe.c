multiline_comment|/*&n; *  linux/fs/pipe.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
DECL|function|pipe_read
r_static
r_int
id|pipe_read
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
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|chars
comma
id|size
comma
id|read
op_assign
l_int|0
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
id|PIPE_SIZE
c_func
(paren
op_star
id|inode
)paren
)paren
(brace
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
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
multiline_comment|/* are there any writers? */
r_return
l_int|0
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
id|ERESTARTSYS
suffix:semicolon
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
id|PIPE_SIZE
c_func
(paren
op_star
id|inode
)paren
)paren
)paren
(brace
id|chars
op_assign
id|PAGE_SIZE
op_minus
id|PIPE_TAIL
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
id|memcpy_tofs
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|inode-&gt;i_size
op_plus
id|PIPE_TAIL
c_func
(paren
op_star
id|inode
)paren
comma
id|chars
)paren
suffix:semicolon
id|read
op_add_assign
id|chars
suffix:semicolon
id|PIPE_TAIL
c_func
(paren
op_star
id|inode
)paren
op_add_assign
id|chars
suffix:semicolon
id|PIPE_TAIL
c_func
(paren
op_star
id|inode
)paren
op_and_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
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
r_return
id|read
ques
c_cond
id|read
suffix:colon
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|pipe_write
r_static
r_int
id|pipe_write
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
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|chars
comma
id|size
comma
id|written
op_assign
l_int|0
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
(brace
multiline_comment|/* no readers */
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
multiline_comment|/* if count &lt; PAGE_SIZE, we have to make it atomic */
r_if
c_cond
(paren
id|count
OL
id|PAGE_SIZE
)paren
id|size
op_assign
id|PAGE_SIZE
op_minus
id|count
suffix:semicolon
r_else
id|size
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_while
c_loop
(paren
id|PIPE_SIZE
c_func
(paren
op_star
id|inode
)paren
op_ge
id|size
)paren
(brace
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
(brace
multiline_comment|/* no readers */
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
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EPIPE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_else
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
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_minus
id|PIPE_SIZE
c_func
(paren
op_star
id|inode
)paren
)paren
)paren
(brace
id|chars
op_assign
id|PAGE_SIZE
op_minus
id|PIPE_HEAD
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
id|memcpy_fromfs
c_func
(paren
(paren
r_char
op_star
)paren
id|inode-&gt;i_size
op_plus
id|PIPE_HEAD
c_func
(paren
op_star
id|inode
)paren
comma
id|buf
comma
id|chars
)paren
suffix:semicolon
id|written
op_add_assign
id|chars
suffix:semicolon
id|PIPE_HEAD
c_func
(paren
op_star
id|inode
)paren
op_add_assign
id|chars
suffix:semicolon
id|PIPE_HEAD
c_func
(paren
op_star
id|inode
)paren
op_and_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
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
id|size
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|written
suffix:semicolon
)brace
DECL|function|pipe_lseek
r_static
r_int
id|pipe_lseek
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
id|file
comma
id|off_t
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
DECL|function|pipe_readdir
r_static
r_int
id|pipe_readdir
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
id|file
comma
r_struct
id|dirent
op_star
id|de
comma
r_int
id|count
)paren
(brace
r_return
op_minus
id|ENOTDIR
suffix:semicolon
)brace
DECL|function|bad_pipe_rw
r_static
r_int
id|bad_pipe_rw
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
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
DECL|function|pipe_ioctl
r_static
r_int
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
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
l_int|4
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|PIPE_SIZE
c_func
(paren
op_star
id|pino
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|pipe_select
r_static
r_int
id|pipe_select
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
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
(brace
r_switch
c_cond
(paren
id|sel_type
)paren
(brace
r_case
id|SEL_IN
suffix:colon
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
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|select_wait
c_func
(paren
op_amp
id|PIPE_READ_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SEL_OUT
suffix:colon
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
op_logical_or
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|select_wait
c_func
(paren
op_amp
id|PIPE_WRITE_WAIT
c_func
(paren
op_star
id|inode
)paren
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SEL_EX
suffix:colon
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
op_logical_or
op_logical_neg
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|select_wait
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, these three routines NOW keep track of readers/writers,&n; * Linus previously did it with inode-&gt;i_count checking.&n; */
DECL|function|pipe_read_release
r_static
r_void
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
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
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
)brace
DECL|function|pipe_write_release
r_static
r_void
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
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
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
)brace
DECL|function|pipe_rdwr_release
r_static
r_void
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
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_decrement
suffix:semicolon
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
)brace
multiline_comment|/*&n; * The three file_operations structs are not static because they&n; * are also used in linux/fs/fifo.c to do operations on fifo&squot;s.&n; */
DECL|variable|read_pipe_fops
r_struct
id|file_operations
id|read_pipe_fops
op_assign
(brace
id|pipe_lseek
comma
id|pipe_read
comma
id|bad_pipe_rw
comma
id|pipe_readdir
comma
id|pipe_select
comma
id|pipe_ioctl
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
id|pipe_read_release
)brace
suffix:semicolon
DECL|variable|write_pipe_fops
r_struct
id|file_operations
id|write_pipe_fops
op_assign
(brace
id|pipe_lseek
comma
id|bad_pipe_rw
comma
id|pipe_write
comma
id|pipe_readdir
comma
id|pipe_select
comma
id|pipe_ioctl
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
id|pipe_write_release
)brace
suffix:semicolon
DECL|variable|rdwr_pipe_fops
r_struct
id|file_operations
id|rdwr_pipe_fops
op_assign
(brace
id|pipe_lseek
comma
id|pipe_read
comma
id|pipe_write
comma
id|pipe_readdir
comma
id|pipe_select
comma
id|pipe_ioctl
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
id|pipe_rdwr_release
)brace
suffix:semicolon
DECL|function|sys_pipe
r_int
id|sys_pipe
c_func
(paren
r_int
r_int
op_star
id|fildes
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
id|f
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|verify_area
c_func
(paren
id|fildes
comma
l_int|8
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|f
(braket
id|j
)braket
op_assign
id|get_empty_filp
c_func
(paren
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
l_int|1
)paren
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|2
)paren
r_return
op_minus
id|ENFILE
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
op_logical_and
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
op_logical_neg
id|current-&gt;filp
(braket
id|i
)braket
)paren
(brace
id|current-&gt;filp
(braket
id|fd
(braket
id|j
)braket
op_assign
id|i
)braket
op_assign
id|f
(braket
id|j
)braket
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
op_eq
l_int|1
)paren
id|current-&gt;filp
(braket
id|fd
(braket
l_int|0
)braket
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|2
)paren
(brace
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_count
op_decrement
suffix:semicolon
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_count
op_decrement
suffix:semicolon
r_return
op_minus
id|EMFILE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|get_pipe_inode
c_func
(paren
)paren
)paren
)paren
(brace
id|current-&gt;filp
(braket
id|fd
(braket
l_int|0
)braket
)braket
op_assign
l_int|NULL
suffix:semicolon
id|current-&gt;filp
(braket
id|fd
(braket
l_int|1
)braket
)braket
op_assign
l_int|NULL
suffix:semicolon
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_count
op_decrement
suffix:semicolon
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_count
op_decrement
suffix:semicolon
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_inode
op_assign
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_inode
op_assign
id|inode
suffix:semicolon
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_pos
op_assign
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_pos
op_assign
l_int|0
suffix:semicolon
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_flags
op_assign
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_flags
op_assign
l_int|0
suffix:semicolon
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_op
op_assign
op_amp
id|read_pipe_fops
suffix:semicolon
id|f
(braket
l_int|0
)braket
op_member_access_from_pointer
id|f_mode
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* read */
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_op
op_assign
op_amp
id|write_pipe_fops
suffix:semicolon
id|f
(braket
l_int|1
)braket
op_member_access_from_pointer
id|f_mode
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* write */
id|put_fs_long
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
op_plus
id|fildes
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_int|1
op_plus
id|fildes
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
