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
r_static
r_int
id|minix_file_write
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
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the minix filesystem.&n; */
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
l_int|NULL
comma
multiline_comment|/* writepage */
id|minix_bmap
comma
multiline_comment|/* bmap */
id|minix_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|minix_file_write
r_static
r_int
id|minix_file_write
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
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
id|off_t
id|pos
suffix:semicolon
r_int
id|written
comma
id|c
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_file_write: inode = NULL&bslash;n&quot;
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
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_file_write: mode = %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
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
id|filp-&gt;f_flags
op_amp
id|O_APPEND
)paren
id|pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_else
id|pos
op_assign
id|filp-&gt;f_pos
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|written
OL
id|count
)paren
(brace
id|bh
op_assign
id|minix_getblk
c_func
(paren
id|inode
comma
id|pos
op_div
id|BLOCK_SIZE
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|written
)paren
id|written
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c
op_assign
id|BLOCK_SIZE
op_minus
(paren
id|pos
op_mod
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
id|count
op_minus
id|written
)paren
id|c
op_assign
id|count
op_minus
id|written
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
id|BLOCK_SIZE
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|written
)paren
id|written
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|p
op_assign
(paren
id|pos
op_mod
id|BLOCK_SIZE
)paren
op_plus
id|bh-&gt;b_data
suffix:semicolon
id|c
op_sub_assign
id|copy_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|written
)paren
id|written
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|update_vm_cache
c_func
(paren
id|inode
comma
id|pos
comma
id|p
comma
id|c
)paren
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|0
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|pos
op_add_assign
id|c
suffix:semicolon
id|written
op_add_assign
id|c
suffix:semicolon
id|buf
op_add_assign
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|inode-&gt;i_size
)paren
id|inode-&gt;i_size
op_assign
id|pos
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|pos
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
eof
