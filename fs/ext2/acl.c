multiline_comment|/*&n; * linux/fs/ext2/acl.c&n; *&n; * Copyright (C) 1993  Remy Card (card@masi.ibp.fr)&n; */
multiline_comment|/*&n; * This file will contain the Access Control Lists management for the&n; * second extended file system.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
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
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
multiline_comment|/* Special case, access is always granted for root */
r_if
c_cond
(paren
id|suser
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* If no ACL, checks using the file mode */
r_else
r_if
c_cond
(paren
id|current-&gt;euid
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
l_int|0007
)paren
op_eq
id|mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
eof
