multiline_comment|/*&n; *  linux/fs/sysv/symlink.c&n; *&n; *  minix/symlink.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/symlink.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/symlink.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent symlink handling code&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
r_static
r_int
id|sysv_readlink
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
id|sysv_follow_link
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
DECL|variable|sysv_symlink_inode_operations
r_struct
id|inode_operations
id|sysv_symlink_inode_operations
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
id|sysv_readlink
comma
multiline_comment|/* readlink */
id|sysv_follow_link
comma
multiline_comment|/* follow_link */
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
DECL|function|sysv_follow_link
r_static
r_int
id|sysv_follow_link
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
c_func
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
r_if
c_cond
(paren
id|current-&gt;link_count
OG
l_int|5
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
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
op_logical_neg
(paren
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
multiline_comment|/* is reading 1 block enough ?? */
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|iput
c_func
(paren
id|inode
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
id|bh-&gt;b_data
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
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysv_readlink
r_static
r_int
id|sysv_readlink
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
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|bh_data
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
id|inode-&gt;i_sb-&gt;sv_block_size_1
)paren
id|buflen
op_assign
id|inode-&gt;i_sb-&gt;sv_block_size_1
suffix:semicolon
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
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
id|bh
)paren
r_return
l_int|0
suffix:semicolon
id|bh_data
op_assign
id|bh-&gt;b_data
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
id|bh_data
(braket
id|i
)braket
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
id|put_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
