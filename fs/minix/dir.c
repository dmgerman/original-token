multiline_comment|/*&n; *  linux/fs/minix/dir.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix directory handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|function|minix_dir_read
r_static
r_int
id|minix_dir_read
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
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_return
op_minus
id|EISDIR
suffix:semicolon
)brace
r_static
r_int
id|minix_readdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|dirent
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|minix_dir_operations
r_static
r_struct
id|file_operations
id|minix_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|minix_dir_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|minix_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* default fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|minix_dir_inode_operations
r_struct
id|inode_operations
id|minix_dir_inode_operations
op_assign
(brace
op_amp
id|minix_dir_operations
comma
multiline_comment|/* default directory file-ops */
id|minix_create
comma
multiline_comment|/* create */
id|minix_lookup
comma
multiline_comment|/* lookup */
id|minix_link
comma
multiline_comment|/* link */
id|minix_unlink
comma
multiline_comment|/* unlink */
id|minix_symlink
comma
multiline_comment|/* symlink */
id|minix_mkdir
comma
multiline_comment|/* mkdir */
id|minix_rmdir
comma
multiline_comment|/* rmdir */
id|minix_mknod
comma
multiline_comment|/* mknod */
id|minix_rename
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
multiline_comment|/* bmap */
id|minix_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|minix_readdir
r_static
r_int
id|minix_readdir
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
r_struct
id|dirent
op_star
id|dirent
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|offset
comma
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|inode-&gt;i_sb
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
id|EBADF
suffix:semicolon
id|info
op_assign
op_amp
id|inode-&gt;i_sb-&gt;u.minix_sb
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_amp
(paren
id|info-&gt;s_dirsize
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_while
c_loop
(paren
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
l_int|1023
suffix:semicolon
id|bh
op_assign
id|minix_bread
c_func
(paren
id|inode
comma
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|BLOCK_SIZE_BITS
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|filp-&gt;f_pos
op_add_assign
l_int|1024
op_minus
id|offset
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
l_int|1024
op_logical_and
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
id|de
op_assign
(paren
r_struct
id|minix_dir_entry
op_star
)paren
(paren
id|offset
op_plus
id|bh-&gt;b_data
)paren
suffix:semicolon
id|offset
op_add_assign
id|info-&gt;s_dirsize
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|info-&gt;s_dirsize
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|info-&gt;s_namelen
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|c
op_assign
id|de-&gt;name
(braket
id|i
)braket
)paren
op_ne
l_int|0
)paren
id|put_fs_byte
c_func
(paren
id|c
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|put_fs_long
c_func
(paren
id|de-&gt;inode
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
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
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
