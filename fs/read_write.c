multiline_comment|/*&n; *  linux/fs/read_write.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|function|sys_lseek
id|asmlinkage
r_int
id|sys_lseek
c_func
(paren
r_int
r_int
id|fd
comma
id|off_t
id|offset
comma
r_int
r_int
id|origin
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|tmp
op_assign
op_minus
l_int|1
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
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|origin
OG
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;lseek
)paren
r_return
id|file-&gt;f_op
op_member_access_from_pointer
id|lseek
c_func
(paren
id|file-&gt;f_inode
comma
id|file
comma
id|offset
comma
id|origin
)paren
suffix:semicolon
multiline_comment|/* this is the default handler if no lseek handler is present */
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|0
suffix:colon
id|tmp
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tmp
op_assign
id|file-&gt;f_pos
op_plus
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmp
op_assign
id|file-&gt;f_inode-&gt;i_size
op_plus
id|offset
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp
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
id|tmp
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|tmp
suffix:semicolon
id|file-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
id|file-&gt;f_version
op_assign
op_increment
id|event
suffix:semicolon
)brace
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
DECL|function|sys_llseek
id|asmlinkage
r_int
id|sys_llseek
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|offset_high
comma
r_int
r_int
id|offset_low
comma
id|loff_t
op_star
id|result
comma
r_int
r_int
id|origin
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|loff_t
id|tmp
op_assign
op_minus
l_int|1
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
r_int
id|err
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
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|origin
OG
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|result
comma
r_sizeof
(paren
id|loff_t
)paren
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|offset
op_assign
(paren
id|loff_t
)paren
(paren
(paren
(paren
r_int
r_int
r_int
)paren
id|offset_high
op_lshift
l_int|32
)paren
op_or
id|offset_low
)paren
suffix:semicolon
multiline_comment|/* if there is a fs-specific handler, we can&squot;t just ignore it.. */
multiline_comment|/* accept llseek() only for the signed long subset of long long */
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;lseek
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ne
(paren
r_int
)paren
id|offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|file-&gt;f_op
op_member_access_from_pointer
id|lseek
c_func
(paren
id|file-&gt;f_inode
comma
id|file
comma
id|offset
comma
id|origin
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|0
suffix:colon
id|tmp
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tmp
op_assign
id|file-&gt;f_pos
op_plus
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmp
op_assign
id|file-&gt;f_inode-&gt;i_size
op_plus
id|offset
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp
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
id|tmp
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|tmp
suffix:semicolon
id|file-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
id|file-&gt;f_version
op_assign
op_increment
id|event
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|result
comma
op_amp
id|file-&gt;f_pos
comma
r_sizeof
(paren
id|loff_t
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_read
id|asmlinkage
r_int
id|sys_read
c_func
(paren
r_int
r_int
id|fd
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
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
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
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
l_int|1
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
op_logical_neg
id|file-&gt;f_op-&gt;read
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|error
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_READ
comma
id|inode
comma
id|file
comma
id|file-&gt;f_pos
comma
id|count
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
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
r_return
id|file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|sys_write
id|asmlinkage
r_int
id|sys_write
c_func
(paren
r_int
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|written
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
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
op_logical_neg
id|file-&gt;f_op-&gt;write
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|error
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_WRITE
comma
id|inode
comma
id|file
comma
id|file-&gt;f_pos
comma
id|count
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
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
multiline_comment|/*&n;&t; * If data has been written to the file, remove the setuid and&n;&t; * the setgid bits. We do it anyway otherwise there is an&n;&t; * extremely exploitable race - does your OS get it right |-&gt;&n;&t; *&n;&t; * Set ATTR_FORCE so it will always be changed.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
(paren
id|S_ISUID
op_or
id|S_ISGID
)paren
)paren
)paren
(brace
r_struct
id|iattr
id|newattrs
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t turn off setgid if no group execute. This special&n;&t;&t; * case marks candidates for mandatory locking.&n;&t;&t; */
id|newattrs.ia_mode
op_assign
id|inode-&gt;i_mode
op_amp
op_complement
(paren
id|S_ISUID
op_or
(paren
(paren
id|inode-&gt;i_mode
op_amp
id|S_IXGRP
)paren
ques
c_cond
id|S_ISGID
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_CTIME
op_or
id|ATTR_MODE
op_or
id|ATTR_FORCE
suffix:semicolon
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|written
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
DECL|function|sock_readv_writev
r_static
r_int
id|sock_readv_writev
c_func
(paren
r_int
id|type
comma
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
r_const
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|count
comma
r_int
id|size
)paren
(brace
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|socket
op_star
id|sock
suffix:semicolon
id|sock
op_assign
op_amp
id|inode-&gt;u.socket_i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock-&gt;ops
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_control
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_iov
op_assign
(paren
r_struct
id|iovec
op_star
)paren
id|iov
suffix:semicolon
id|msg.msg_iovlen
op_assign
id|count
suffix:semicolon
multiline_comment|/* read() does a VERIFY_WRITE */
r_if
c_cond
(paren
id|type
op_eq
id|VERIFY_WRITE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sock-&gt;ops-&gt;recvmsg
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|sock-&gt;ops
op_member_access_from_pointer
id|recvmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|size
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sock-&gt;ops-&gt;sendmsg
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|sock-&gt;ops
op_member_access_from_pointer
id|sendmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|size
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|typedef|IO_fn_t
r_typedef
r_int
(paren
op_star
id|IO_fn_t
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
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|do_readv_writev
r_static
r_int
id|do_readv_writev
c_func
(paren
r_int
id|type
comma
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
r_const
r_struct
id|iovec
op_star
id|vector
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|tot_len
suffix:semicolon
r_struct
id|iovec
id|iov
(braket
id|MAX_IOVEC
)braket
suffix:semicolon
r_int
id|retval
comma
id|i
suffix:semicolon
id|IO_fn_t
id|fn
suffix:semicolon
multiline_comment|/*&n;&t; * First get the &quot;struct iovec&quot; from user memory and&n;&t; * verify all the pointers&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|MAX_IOVEC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|retval
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|vector
comma
id|count
op_star
r_sizeof
(paren
op_star
id|vector
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|iov
comma
id|vector
comma
id|count
op_star
r_sizeof
(paren
op_star
id|vector
)paren
)paren
suffix:semicolon
id|tot_len
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
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tot_len
op_add_assign
id|iov
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
id|retval
op_assign
id|verify_area
c_func
(paren
id|type
comma
id|iov
(braket
id|i
)braket
dot
id|iov_base
comma
id|iov
(braket
id|i
)braket
dot
id|iov_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
)brace
id|retval
op_assign
id|locks_verify_area
c_func
(paren
id|type
op_eq
id|VERIFY_READ
ques
c_cond
id|FLOCK_VERIFY_READ
suffix:colon
id|FLOCK_VERIFY_WRITE
comma
id|inode
comma
id|file
comma
id|file-&gt;f_pos
comma
id|tot_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/*&n;&t; * Then do the actual IO.  Note that sockets need to be handled&n;&t; * specially as they have atomicity guarantees and can handle&n;&t; * iovec&squot;s natively&n;&t; */
r_if
c_cond
(paren
id|inode-&gt;i_sock
)paren
r_return
id|sock_readv_writev
c_func
(paren
id|type
comma
id|inode
comma
id|file
comma
id|iov
comma
id|count
comma
id|tot_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* VERIFY_WRITE actually means a read, as we write to user space */
id|fn
op_assign
id|file-&gt;f_op-&gt;read
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|VERIFY_READ
)paren
id|fn
op_assign
(paren
id|IO_fn_t
)paren
id|file-&gt;f_op-&gt;write
suffix:semicolon
id|vector
op_assign
id|iov
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_void
op_star
id|base
suffix:semicolon
r_int
id|len
comma
id|nr
suffix:semicolon
id|base
op_assign
id|vector-&gt;iov_base
suffix:semicolon
id|len
op_assign
id|vector-&gt;iov_len
suffix:semicolon
id|vector
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|nr
op_assign
id|fn
c_func
(paren
id|inode
comma
id|file
comma
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
)paren
r_break
suffix:semicolon
id|retval
op_assign
id|nr
suffix:semicolon
r_break
suffix:semicolon
)brace
id|retval
op_add_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ne
id|len
)paren
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sys_readv
id|asmlinkage
r_int
id|sys_readv
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_struct
id|iovec
op_star
id|vector
comma
r_int
id|count
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
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
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
l_int|1
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_return
id|do_readv_writev
c_func
(paren
id|VERIFY_WRITE
comma
id|inode
comma
id|file
comma
id|vector
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|sys_writev
id|asmlinkage
r_int
id|sys_writev
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_struct
id|iovec
op_star
id|vector
comma
r_int
id|count
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
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
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_readv_writev
c_func
(paren
id|VERIFY_READ
comma
id|inode
comma
id|file
comma
id|vector
comma
id|count
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
