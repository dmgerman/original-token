multiline_comment|/*&n; * linux/fs/ext2/ioctl.c&n; *&n; * Copyright (C) 1993, 1994  Remy Card (card@masi.ibp.fr)&n; *                           Laboratoire MASI - Institut Blaise Pascal&n; *                           Universite Pierre et Marie Curie (Paris VI)&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|function|ext2_ioctl
r_int
id|ext2_ioctl
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
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
suffix:semicolon
id|ext2_debug
(paren
l_string|&quot;cmd = %u, arg = %lu&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|EXT2_IOC_GETFLAGS
suffix:colon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
(paren
id|VERIFY_WRITE
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|put_fs_long
(paren
id|inode-&gt;u.ext2_i.i_flags
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
id|EXT2_IOC_SETFLAGS
suffix:colon
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|fsuser
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
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
id|inode-&gt;u.ext2_i.i_flags
op_assign
id|get_fs_long
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|EXT2_IOC_GETVERSION
suffix:colon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
(paren
id|VERIFY_WRITE
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|put_fs_long
(paren
id|inode-&gt;u.ext2_i.i_version
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
id|EXT2_IOC_SETVERSION
suffix:colon
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|fsuser
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
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
id|inode-&gt;u.ext2_i.i_version
op_assign
id|get_fs_long
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
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
eof
