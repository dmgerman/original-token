multiline_comment|/* &n; * QNX4 file system, Linux implementation.&n; * &n; * Version : 0.1&n; * &n; * Using parts of the xiafs filesystem.&n; * &n; * History :&n; * &n; * 25-05-1998 by Richard Frowijn : first release.&n; * 21-06-1998 by Frank Denis : wrote qnx4_readpage to use generic_file_read.&n; * 27-06-1998 by Frank Denis : file overwriting.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
r_static
r_int
id|qnx4_readpage
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
suffix:semicolon
macro_line|#ifdef CONFIG_QNX4FS_RW
DECL|function|qnx4_file_write
r_static
id|ssize_t
id|qnx4_file_write
c_func
(paren
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|qnx4_inode_info
op_star
id|qnx4_ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|ssize_t
id|result
op_assign
op_minus
id|EBUSY
comma
id|c
suffix:semicolon
id|off_t
id|pos
suffix:semicolon
r_int
r_int
id|start
comma
id|block
comma
id|extent_end
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: file_write(%s/%s (%d), %lu@%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|inode-&gt;i_count
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
op_star
id|ppos
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: NULL inode for file_write&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|qnx4_ino
op_assign
op_amp
id|inode-&gt;u.qnx4_i
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: write to non-file, mode %07o&bslash;n&quot;
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
id|count
op_eq
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_APPEND
)paren
(brace
id|pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
r_else
(brace
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
)brace
id|start
op_assign
id|qnx4_ino-&gt;i_first_xtnt.xtnt_blk
op_plus
(paren
(paren
id|pos
op_rshift
l_int|9
)paren
op_star
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|extent_end
op_assign
id|start
op_plus
id|qnx4_ino-&gt;i_first_xtnt.xtnt_size
op_minus
l_int|1
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: extent length : [%lu] bytes&bslash;n&quot;
comma
id|qnx4_ino-&gt;i_first_xtnt.xtnt_size
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|result
OL
id|count
)paren
(brace
id|block
op_assign
id|start
op_plus
id|pos
op_div
id|QNX4_BLOCK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|block
OG
id|extent_end
)paren
(brace
r_if
c_cond
(paren
id|qnx4_is_free
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
)paren
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: next inode is busy -&gt; write aborted.&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
comma
id|QNX4_BLOCK_SIZE
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: I/O error on write.&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
id|result
op_assign
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
OG
id|extent_end
)paren
(brace
id|qnx4_set_bitmap
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
comma
l_int|1
)paren
suffix:semicolon
id|extent_end
op_increment
suffix:semicolon
id|qnx4_ino-&gt;i_first_xtnt.xtnt_size
op_assign
id|extent_end
op_minus
id|start
op_plus
l_int|1
suffix:semicolon
)brace
id|c
op_assign
id|QNX4_BLOCK_SIZE
op_minus
(paren
id|pos
op_mod
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
id|count
op_minus
id|result
)paren
(brace
id|c
op_assign
id|count
op_minus
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ne
id|QNX4_BLOCK_SIZE
op_logical_and
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_eq
l_int|0
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
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
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_eq
l_int|0
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
id|result
op_ne
l_int|0
)paren
(brace
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|p
op_assign
id|bh-&gt;b_data
op_plus
(paren
id|pos
op_mod
id|QNX4_BLOCK_SIZE
)paren
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
id|c
op_eq
l_int|0
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
id|result
op_eq
l_int|0
)paren
(brace
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
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
id|buf
op_add_assign
id|c
suffix:semicolon
id|result
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
(brace
id|inode-&gt;i_size
op_assign
id|pos
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * We have moostly NULL&squot;s here: the current defaults are ok for&n; * the qnx4 filesystem.&n; */
DECL|variable|qnx4_file_operations
r_static
r_struct
id|file_operations
id|qnx4_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|generic_file_read
comma
multiline_comment|/* read */
macro_line|#ifdef CONFIG_QNX4FS_RW
id|qnx4_file_write
comma
multiline_comment|/* write */
macro_line|#else
l_int|NULL
comma
macro_line|#endif
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
multiline_comment|/* no special flush code */
l_int|NULL
comma
multiline_comment|/* release */
macro_line|#ifdef CONFIG_QNX4FS_RW   
id|qnx4_sync_file
comma
multiline_comment|/* fsync */
macro_line|#else
l_int|NULL
comma
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
l_int|NULL
multiline_comment|/* lock */
)brace
suffix:semicolon
DECL|variable|qnx4_file_inode_operations
r_struct
id|inode_operations
id|qnx4_file_inode_operations
op_assign
(brace
op_amp
id|qnx4_file_operations
comma
multiline_comment|/* default file operations */
macro_line|#ifdef CONFIG_QNX4FS_RW
id|qnx4_create
comma
multiline_comment|/* create */
macro_line|#else
l_int|NULL
comma
macro_line|#endif
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
id|qnx4_readpage
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
id|qnx4_bmap
comma
multiline_comment|/* bmap */
macro_line|#ifdef CONFIG_QNX4FS_RW
id|qnx4_truncate
comma
multiline_comment|/* truncate */
macro_line|#else
l_int|NULL
comma
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|function|qnx4_readpage
r_static
r_int
id|qnx4_readpage
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
r_struct
id|qnx4_inode_info
op_star
id|qnx4_ino
op_assign
op_amp
id|inode-&gt;u.qnx4_i
suffix:semicolon
r_int
r_int
id|buf
suffix:semicolon
r_int
r_int
id|offset
comma
id|avail
comma
id|readlen
suffix:semicolon
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: readpage offset=[%ld]&bslash;n&quot;
comma
(paren
r_int
)paren
id|page-&gt;offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qnx4_ino-&gt;i_xblk
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: sorry, this file is extended, don&squot;t know how to handle it (yet) !&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|page-&gt;count
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_locked
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|buf
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_uptodate
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_error
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|offset
op_assign
id|page-&gt;offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
id|inode-&gt;i_size
)paren
(brace
id|res
op_assign
l_int|0
suffix:semicolon
id|avail
op_assign
id|inode-&gt;i_size
op_minus
id|offset
suffix:semicolon
id|readlen
op_assign
id|MIN
c_func
(paren
id|avail
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|start
op_assign
id|qnx4_ino-&gt;i_first_xtnt.xtnt_blk
op_plus
(paren
id|offset
op_rshift
l_int|9
)paren
op_minus
l_int|1
suffix:semicolon
id|count
op_assign
id|PAGE_SIZE
op_div
id|QNX4_BLOCK_SIZE
suffix:semicolon
r_do
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: reading page starting at [%ld]&bslash;n&quot;
comma
(paren
r_int
)paren
id|start
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|start
comma
id|QNX4_BLOCK_SIZE
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: data corrupted or I/O error.&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|buf
comma
id|bh-&gt;b_data
comma
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
)brace
id|buf
op_add_assign
id|QNX4_BLOCK_SIZE
suffix:semicolon
id|start
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_ne
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
op_ne
l_int|0
)paren
(brace
id|set_bit
c_func
(paren
id|PG_error
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|buf
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_bit
c_func
(paren
id|PG_uptodate
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|PG_locked
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
multiline_comment|/*  free_page(buf); */
r_return
id|res
suffix:semicolon
)brace
eof