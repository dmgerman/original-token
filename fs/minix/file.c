multiline_comment|/*&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix regular file handling primitives&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
DECL|function|minix_writepage
r_static
r_int
id|minix_writepage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|block
suffix:semicolon
r_int
op_star
id|p
comma
id|nr
(braket
id|PAGE_SIZE
op_div
id|BLOCK_SIZE
)braket
suffix:semicolon
r_int
id|i
comma
id|err
comma
id|created
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|i
op_assign
id|PAGE_SIZE
op_div
id|BLOCK_SIZE
suffix:semicolon
id|block
op_assign
id|page-&gt;offset
op_div
id|BLOCK_SIZE
suffix:semicolon
id|p
op_assign
id|nr
suffix:semicolon
id|bh
op_assign
id|page-&gt;buffers
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|bh
op_logical_and
id|bh-&gt;b_blocknr
)paren
op_star
id|p
op_assign
id|bh-&gt;b_blocknr
suffix:semicolon
r_else
op_star
id|p
op_assign
id|minix_getblk_block
c_func
(paren
id|inode
comma
id|block
comma
l_int|1
comma
op_amp
id|err
comma
op_amp
id|created
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|i
op_decrement
suffix:semicolon
id|block
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|bh
op_assign
id|bh-&gt;b_this_page
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* IO start */
id|brw_page
c_func
(paren
id|WRITE
comma
id|page
comma
id|inode-&gt;i_dev
comma
id|nr
comma
id|BLOCK_SIZE
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|minix_write_one_page
r_static
r_int
id|minix_write_one_page
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|bytes
comma
r_const
r_char
op_star
id|buf
)paren
(brace
r_return
id|block_write_one_page
c_func
(paren
id|file
comma
id|page
comma
id|offset
comma
id|bytes
comma
id|buf
comma
id|minix_getblk_block
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|minix_file_write
id|minix_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
comma
id|minix_write_one_page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the minix filesystem.&n; */
DECL|variable|minix_file_operations
r_static
r_struct
id|file_operations
id|minix_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|generic_file_read
comma
multiline_comment|/* read */
id|minix_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* poll - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* release */
id|minix_sync_file
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|minix_file_inode_operations
r_struct
id|inode_operations
id|minix_file_inode_operations
op_assign
(brace
op_amp
id|minix_file_operations
comma
multiline_comment|/* default file operations */
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
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
id|generic_readpage
comma
multiline_comment|/* readpage */
id|minix_writepage
comma
multiline_comment|/* writepage */
id|minix_bmap
comma
multiline_comment|/* bmap */
id|minix_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* updatepage */
l_int|NULL
comma
multiline_comment|/* revalidate */
id|generic_block_flushpage
comma
multiline_comment|/* flushpage */
)brace
suffix:semicolon
eof
