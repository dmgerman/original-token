multiline_comment|/*&n; * linux/fs/ext2/ioctl.c&n; *&n; * Copyright (C) 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
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
r_int
id|flags
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
r_return
id|put_user
c_func
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
r_case
id|EXT2_IOC_SETFLAGS
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|flags
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The IMMUTABLE and APPEND_ONLY flags can only be changed by&n;&t;&t; * the super user when the security level is zero.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|EXT2_APPEND_FL
op_or
id|EXT2_IMMUTABLE_FL
)paren
)paren
op_xor
(paren
id|inode-&gt;u.ext2_i.i_flags
op_amp
(paren
id|EXT2_APPEND_FL
op_or
id|EXT2_IMMUTABLE_FL
)paren
)paren
)paren
(brace
multiline_comment|/* This test looks nicer. Thanks to Pauline Middelink */
r_if
c_cond
(paren
op_logical_neg
id|fsuser
c_func
(paren
)paren
op_logical_or
id|securelevel
OG
l_int|0
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_else
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
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT2_APPEND_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_APPEND
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_APPEND
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT2_IMMUTABLE_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_IMMUTABLE
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_IMMUTABLE
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
r_return
id|put_user
c_func
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
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|inode-&gt;u.ext2_i.i_version
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
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
id|ENOTTY
suffix:semicolon
)brace
)brace
eof
