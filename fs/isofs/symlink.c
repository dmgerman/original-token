multiline_comment|/*&n; *  linux/fs/isofs/symlink.c&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  isofs symlink handling code.  This is only used with the Rock Ridge&n; *  extensions to iso9660&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_int
id|isofs_readlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|isofs_symlink_inode_operations
r_struct
id|inode_operations
id|isofs_symlink_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file-operations */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
id|isofs_readlink
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|isofs_readlink
r_static
r_int
id|isofs_readlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_char
op_star
id|pnt
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OG
l_int|1023
)paren
id|buflen
op_assign
l_int|1023
suffix:semicolon
id|pnt
op_assign
id|get_rock_ridge_symlink
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnt
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|strlen
c_func
(paren
id|pnt
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|buflen
)paren
id|i
op_assign
id|buflen
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|pnt
comma
id|i
)paren
)paren
id|i
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree
c_func
(paren
id|pnt
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
