multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/dir.c&n; *&n; *  Copyright 1997 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/modversions.h&gt;
macro_line|#include &lt;linux/auto_fs.h&gt;
DECL|function|autofs_dir_readdir
r_static
r_int
id|autofs_dir_readdir
c_func
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
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|ENOTDIR
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|filp-&gt;f_pos
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
l_int|0
comma
id|inode-&gt;i_ino
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
l_int|1
comma
id|AUTOFS_ROOT_INO
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fall through */
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|autofs_dir_lookup
r_static
r_int
id|autofs_dir_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
op_star
id|result
op_assign
id|dir
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
id|len
op_eq
l_int|2
)paren
(brace
multiline_comment|/* Return the root directory */
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|AUTOFS_ROOT_INO
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
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
multiline_comment|/* No other entries */
)brace
DECL|variable|autofs_dir_operations
r_static
r_struct
id|file_operations
id|autofs_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
id|autofs_dir_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|autofs_dir_inode_operations
r_struct
id|inode_operations
id|autofs_dir_inode_operations
op_assign
(brace
op_amp
id|autofs_dir_operations
comma
multiline_comment|/* file operations */
l_int|NULL
comma
multiline_comment|/* create */
id|autofs_dir_lookup
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
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* read_page */
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
eof
