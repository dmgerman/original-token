multiline_comment|/*&n; *  linux/fs/read_write.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/dirent.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * Count is not yet used: but we&squot;ll probably support reading several entries&n; * at once in the future. Use count=1 in the library for future expansions.&n; */
DECL|function|sys_readdir
r_int
id|sys_readdir
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|dirent
op_star
id|dirent
comma
r_int
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
id|current-&gt;filp
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
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;readdir
)paren
(brace
id|verify_area
c_func
(paren
id|dirent
comma
r_sizeof
(paren
op_star
id|dirent
)paren
)paren
suffix:semicolon
r_return
id|file-&gt;f_op
op_member_access_from_pointer
id|readdir
c_func
(paren
id|inode
comma
id|file
comma
id|dirent
comma
id|count
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOTDIR
suffix:semicolon
)brace
DECL|function|sys_lseek
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
id|current-&gt;filp
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
id|file-&gt;f_pos
op_assign
id|tmp
suffix:semicolon
id|file-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
DECL|function|sys_read
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
id|current-&gt;filp
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
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|verify_area
c_func
(paren
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;read
)paren
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|sys_write
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
id|current-&gt;filp
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
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;write
)paren
r_return
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
