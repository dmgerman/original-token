multiline_comment|/*&n; *  linux/fs/ext/dir.c&n; *&n; *  Copyright (C) 1992 Remy Card (card@masi.ibp.fr)&n; *&n; *  from&n; *&n; *  linux/fs/minix/dir.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  ext directory handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|function|ext_dir_read
r_static
r_int
id|ext_dir_read
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
id|ext_readdir
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
DECL|variable|ext_dir_operations
r_static
r_struct
id|file_operations
id|ext_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|ext_dir_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|ext_readdir
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
id|file_fsync
multiline_comment|/* fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|ext_dir_inode_operations
r_struct
id|inode_operations
id|ext_dir_inode_operations
op_assign
(brace
op_amp
id|ext_dir_operations
comma
multiline_comment|/* default directory file-ops */
id|ext_create
comma
multiline_comment|/* create */
id|ext_lookup
comma
multiline_comment|/* lookup */
id|ext_link
comma
multiline_comment|/* link */
id|ext_unlink
comma
multiline_comment|/* unlink */
id|ext_symlink
comma
multiline_comment|/* symlink */
id|ext_mkdir
comma
multiline_comment|/* mkdir */
id|ext_rmdir
comma
multiline_comment|/* rmdir */
id|ext_mknod
comma
multiline_comment|/* mknod */
id|ext_rename
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
id|ext_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|ext_readdir
r_static
r_int
id|ext_readdir
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
id|i
suffix:semicolon
id|off_t
id|offset
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
id|ext_dir_entry
op_star
id|de
suffix:semicolon
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
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_mod
l_int|8
op_ne
l_int|0
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
id|ext_bread
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
id|de
op_assign
(paren
r_struct
id|ext_dir_entry
op_star
)paren
(paren
id|offset
op_plus
id|bh-&gt;b_data
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|de-&gt;rec_len
OL
l_int|8
op_logical_or
id|de-&gt;rec_len
op_mod
l_int|8
op_ne
l_int|0
op_logical_or
id|de-&gt;rec_len
template_param
(paren
(paren
id|off_t
)paren
id|filp-&gt;f_pos
op_div
l_int|1024
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;ext_readdir: bad dir entry, skipping&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;dev=%d, dir=%ld, offset=%ld, rec_len=%d, name_len=%d&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|offset
comma
id|de-&gt;rec_len
comma
id|de-&gt;name_len
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
l_int|1024
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
OG
id|inode-&gt;i_size
)paren
id|filp-&gt;f_pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|offset
op_add_assign
id|de-&gt;rec_len
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|de-&gt;rec_len
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
id|de-&gt;name_len
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
id|de
op_assign
(paren
r_struct
id|ext_dir_entry
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|de-&gt;rec_len
)paren
suffix:semicolon
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
