multiline_comment|/*&n; * linux/fs/ext2/acl.c&n; *&n; * Copyright (C) 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; */
multiline_comment|/*&n; * This file will contain the Access Control Lists management for the&n; * second extended file system.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
multiline_comment|/*&n; * ext2_permission ()&n; *&n; * Check for access rights&n; */
DECL|function|ext2_permission
r_int
id|ext2_permission
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
r_int
r_int
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
multiline_comment|/*&n;&t; * Nobody gets write access to an immutable file&n;&t; */
r_if
c_cond
(paren
(paren
id|mask
op_amp
id|S_IWOTH
)paren
op_logical_and
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/*&n;&t; * Special case, access is always granted for root&n;&t; */
r_if
c_cond
(paren
id|fsuser
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If no ACL, checks using the file mode&n;&t; */
r_else
r_if
c_cond
(paren
id|current-&gt;fsuid
op_eq
id|inode-&gt;i_uid
)paren
id|mode
op_rshift_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in_group_p
(paren
id|inode-&gt;i_gid
)paren
)paren
id|mode
op_rshift_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|mode
op_amp
id|mask
op_amp
id|S_IRWXO
)paren
op_eq
id|mask
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
eof
