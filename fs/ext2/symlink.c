multiline_comment|/*&n; *  linux/fs/ext2/symlink.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/symlink.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 symlink handling code&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
r_static
r_int
id|ext2_readlink
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
id|ext2_follow_link
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
DECL|variable|ext2_symlink_inode_operations
r_struct
id|inode_operations
id|ext2_symlink_inode_operations
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
id|ext2_readlink
comma
multiline_comment|/* readlink */
id|ext2_follow_link
comma
multiline_comment|/* follow_link */
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
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|function|ext2_follow_link
r_static
r_int
id|ext2_follow_link
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
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
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
id|current-&gt;fs-&gt;root
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
(paren
id|dir
)paren
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
r_if
c_cond
(paren
id|current-&gt;link_count
OG
l_int|5
)paren
(brace
id|iput
(paren
id|dir
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ELOOP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_blocks
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|ext2_bread
(paren
id|inode
comma
l_int|0
comma
l_int|0
comma
op_amp
id|error
)paren
)paren
)paren
(brace
id|iput
(paren
id|dir
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|link
op_assign
id|bh-&gt;b_data
suffix:semicolon
)brace
r_else
id|link
op_assign
(paren
r_char
op_star
)paren
id|inode-&gt;u.ext2_i.i_data
suffix:semicolon
r_if
c_cond
(paren
id|DO_UPDATE_ATIME
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|current-&gt;link_count
op_increment
suffix:semicolon
id|error
op_assign
id|open_namei
(paren
id|link
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
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|ext2_readlink
r_static
r_int
id|ext2_readlink
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
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
r_int
id|i
comma
id|err
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
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
)paren
id|buflen
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_blocks
)paren
(brace
id|bh
op_assign
id|ext2_bread
(paren
id|inode
comma
l_int|0
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|link
op_assign
id|bh-&gt;b_data
suffix:semicolon
)brace
r_else
id|link
op_assign
(paren
r_char
op_star
)paren
id|inode-&gt;u.ext2_i.i_data
suffix:semicolon
multiline_comment|/* XXX I hope link is always &squot;&bslash;0&squot;-terminated. */
id|i
op_assign
id|strlen
c_func
(paren
id|link
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
id|link
comma
id|i
)paren
)paren
id|i
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|DO_UPDATE_ATIME
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
