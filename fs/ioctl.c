multiline_comment|/*&n; *  linux/fs/ioctl.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt; /* for f_flags values */
DECL|function|file_ioctl
r_static
r_int
id|file_ioctl
c_func
(paren
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
r_int
id|error
suffix:semicolon
r_int
id|block
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIBMAP
suffix:colon
r_if
c_cond
(paren
id|filp-&gt;f_inode-&gt;i_op
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_inode-&gt;i_op-&gt;bmap
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|4
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
id|block
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
id|block
op_assign
id|filp-&gt;f_inode-&gt;i_op
op_member_access_from_pointer
id|bmap
c_func
(paren
id|filp-&gt;f_inode
comma
id|block
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|block
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIGETBSZ
suffix:colon
r_if
c_cond
(paren
id|filp-&gt;f_inode-&gt;i_sb
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|4
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
id|filp-&gt;f_inode-&gt;i_sb-&gt;s_blocksize
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIONREAD
suffix:colon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
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
id|filp-&gt;f_inode-&gt;i_size
op_minus
id|filp-&gt;f_pos
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;ioctl
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|filp-&gt;f_inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|sys_ioctl
id|asmlinkage
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
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
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|on
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
id|filp
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIOCLEX
suffix:colon
id|FD_SET
c_func
(paren
id|fd
comma
op_amp
id|current-&gt;files-&gt;close_on_exec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIONCLEX
suffix:colon
id|FD_CLR
c_func
(paren
id|fd
comma
op_amp
id|current-&gt;files-&gt;close_on_exec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIONBIO
suffix:colon
id|on
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_int
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
r_return
id|on
suffix:semicolon
)brace
id|on
op_assign
id|get_user
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|filp-&gt;f_flags
op_or_assign
id|O_NONBLOCK
suffix:semicolon
r_else
id|filp-&gt;f_flags
op_and_assign
op_complement
id|O_NONBLOCK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIOASYNC
suffix:colon
multiline_comment|/* O_SYNC is not yet implemented,&n;&t;&t;&t;&t;  but it&squot;s here for completeness. */
id|on
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_int
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
r_return
id|on
suffix:semicolon
)brace
id|on
op_assign
id|get_user
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|filp-&gt;f_flags
op_or_assign
id|O_SYNC
suffix:semicolon
r_else
id|filp-&gt;f_flags
op_and_assign
op_complement
id|O_SYNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|filp-&gt;f_inode
op_logical_and
id|S_ISREG
c_func
(paren
id|filp-&gt;f_inode-&gt;i_mode
)paren
)paren
r_return
id|file_ioctl
c_func
(paren
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;ioctl
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|filp-&gt;f_inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
eof
