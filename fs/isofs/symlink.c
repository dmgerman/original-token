multiline_comment|/*&n; *  linux/fs/isofs/symlink.c&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  isofs symlink handling code.  This is only used with the Rock Ridge&n; *  extensions to iso9660&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
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
r_static
r_int
id|isofs_follow_link
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_struct
id|inode
op_star
op_star
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
id|isofs_follow_link
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
DECL|function|isofs_follow_link
r_static
r_int
id|isofs_follow_link
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
comma
r_int
id|mode
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
r_int
id|fs
suffix:semicolon
r_char
op_star
id|pnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
id|dir
op_assign
id|current-&gt;root
suffix:semicolon
id|dir-&gt;i_count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
id|inode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__asm__
c_func
(paren
l_string|&quot;mov %%fs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;link_count
OG
l_int|5
)paren
op_logical_or
op_logical_neg
(paren
id|pnt
op_assign
id|get_rock_ridge_symlink
c_func
(paren
id|inode
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ELOOP
suffix:semicolon
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
l_int|0x10
)paren
)paren
suffix:semicolon
id|current-&gt;link_count
op_increment
suffix:semicolon
id|error
op_assign
id|open_namei
c_func
(paren
id|pnt
comma
id|flag
comma
id|mode
comma
id|res_inode
comma
id|dir
)paren
suffix:semicolon
id|current-&gt;link_count
op_decrement
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|fs
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pnt
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
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
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|buflen
op_logical_and
(paren
id|c
op_assign
id|pnt
(braket
id|i
)braket
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
)brace
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