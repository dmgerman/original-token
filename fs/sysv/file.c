multiline_comment|/*&n; *  linux/fs/sysv/file.c&n; *&n; *  minix/file.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/file.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/file.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent regular file handling primitives&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
r_static
r_int
id|sysv_file_read
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
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|sysv_file_write
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
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the coh filesystem.&n; */
DECL|variable|sysv_file_operations
r_static
r_struct
id|file_operations
id|sysv_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|sysv_file_read
comma
multiline_comment|/* read */
id|sysv_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
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
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* release */
id|sysv_sync_file
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|sysv_file_operations_with_bmap
r_static
r_struct
id|file_operations
id|sysv_file_operations_with_bmap
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|sysv_file_read
comma
multiline_comment|/* read */
id|sysv_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
id|generic_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* release */
id|sysv_sync_file
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|sysv_file_inode_operations
r_struct
id|inode_operations
id|sysv_file_inode_operations
op_assign
(brace
op_amp
id|sysv_file_operations
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
l_int|NULL
comma
multiline_comment|/* bmap */
id|sysv_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|variable|sysv_file_inode_operations_with_bmap
r_struct
id|inode_operations
id|sysv_file_inode_operations_with_bmap
op_assign
(brace
op_amp
id|sysv_file_operations_with_bmap
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
id|sysv_bmap
comma
multiline_comment|/* bmap */
id|sysv_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|struct|sysv_buffer
r_struct
id|sysv_buffer
(brace
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
DECL|member|bh_data
r_char
op_star
id|bh_data
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sysv_file_read
r_static
r_int
id|sysv_file_read
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
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|read
comma
id|left
comma
id|chars
suffix:semicolon
r_int
r_int
id|block
suffix:semicolon
r_int
id|blocks
comma
id|offset
suffix:semicolon
r_int
id|bhrequest
comma
id|bhreqi
comma
id|uptodate
suffix:semicolon
r_struct
id|sysv_buffer
op_star
id|bhb
comma
op_star
id|bhe
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhreq
(braket
id|NBUF
)braket
suffix:semicolon
r_struct
id|sysv_buffer
id|buflist
(braket
id|NBUF
)braket
suffix:semicolon
r_int
r_int
id|size
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
l_string|&quot;sysv_file_read: inode = NULL&bslash;n&quot;
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
l_string|&quot;sysv_file_read: mode = %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|offset
op_assign
id|filp-&gt;f_pos
suffix:semicolon
id|size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|size
)paren
id|left
op_assign
l_int|0
suffix:semicolon
r_else
id|left
op_assign
id|size
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
id|count
)paren
id|left
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|left
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|offset
op_rshift
id|sb-&gt;sv_block_size_bits
suffix:semicolon
id|offset
op_and_assign
id|sb-&gt;sv_block_size_1
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
id|sb-&gt;sv_block_size_1
)paren
op_rshift
id|sb-&gt;sv_block_size_bits
suffix:semicolon
id|blocks
op_assign
(paren
id|left
op_plus
id|offset
op_plus
id|sb-&gt;sv_block_size_1
)paren
op_rshift
id|sb-&gt;sv_block_size_bits
suffix:semicolon
id|bhb
op_assign
id|bhe
op_assign
id|buflist
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_reada
)paren
(brace
id|blocks
op_add_assign
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)braket
op_rshift
(paren
id|sb-&gt;sv_block_size_bits
op_minus
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_plus
id|blocks
OG
id|size
)paren
id|blocks
op_assign
id|size
op_minus
id|block
suffix:semicolon
)brace
multiline_comment|/* We do this in a two stage process.  We first try and request&n;&t;   as many blocks as we can, then we wait for the first one to&n;&t;   complete, and then we try and wrap up as many as are actually&n;&t;   done.  This routine is rather generic, in that it can be used&n;&t;   in a filesystem by substituting the appropriate function in&n;&t;   for getblk.&n;&n;&t;   This routine is optimized to make maximum use of the various&n;&t;   buffers and caches.&n;&n;&t;   We must remove duplicates from the bhreq array as ll_rw_block&n;&t;   doesn&squot;t like duplicate requests (it hangs in wait_on_buffer...).&n;&t; */
r_do
(brace
id|bhrequest
op_assign
l_int|0
suffix:semicolon
id|uptodate
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|blocks
)paren
(brace
op_decrement
id|blocks
suffix:semicolon
id|bhb-&gt;bh
op_assign
id|sysv_getblk
c_func
(paren
id|inode
comma
id|block
op_increment
comma
l_int|0
comma
op_amp
id|bhb-&gt;bh_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bhb-&gt;bh
op_logical_and
op_logical_neg
id|bhb-&gt;bh-&gt;b_uptodate
)paren
(brace
id|uptodate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
OG
l_int|0
)paren
multiline_comment|/* block_size &lt; BLOCK_SIZE ? */
r_for
c_loop
(paren
id|bhreqi
op_assign
l_int|0
suffix:semicolon
id|bhreqi
OL
id|bhrequest
suffix:semicolon
id|bhreqi
op_increment
)paren
r_if
c_cond
(paren
id|bhreq
(braket
id|bhreqi
)braket
op_eq
id|bhb-&gt;bh
)paren
r_goto
id|notreq
suffix:semicolon
id|bhreq
(braket
id|bhrequest
op_increment
)braket
op_assign
id|bhb-&gt;bh
suffix:semicolon
id|notreq
suffix:colon
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|bhb
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhb
op_assign
id|buflist
suffix:semicolon
multiline_comment|/* If the block we have on hand is uptodate, go ahead&n;&t;&t;&t;   and complete processing. */
r_if
c_cond
(paren
id|uptodate
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|bhb
op_eq
id|bhe
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* Now request them all */
r_if
c_cond
(paren
id|bhrequest
)paren
id|ll_rw_block
c_func
(paren
id|READ
comma
id|bhrequest
comma
id|bhreq
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* Finish off all I/O that has actually completed */
r_if
c_cond
(paren
id|bhe-&gt;bh
)paren
(brace
id|wait_on_buffer
c_func
(paren
id|bhe-&gt;bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bhe-&gt;bh-&gt;b_uptodate
)paren
(brace
multiline_comment|/* read error? */
id|brelse
c_func
(paren
id|bhe-&gt;bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhe
op_assign
id|buflist
suffix:semicolon
id|left
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|left
OL
id|sb-&gt;sv_block_size
op_minus
id|offset
)paren
id|chars
op_assign
id|left
suffix:semicolon
r_else
id|chars
op_assign
id|sb-&gt;sv_block_size
op_minus
id|offset
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|chars
suffix:semicolon
id|left
op_sub_assign
id|chars
suffix:semicolon
id|read
op_add_assign
id|chars
suffix:semicolon
r_if
c_cond
(paren
id|bhe-&gt;bh
)paren
(brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|offset
op_plus
id|bhe-&gt;bh_data
comma
id|chars
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bhe-&gt;bh
)paren
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|chars
op_decrement
OG
l_int|0
)paren
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|buf
op_increment
)paren
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
r_while
c_loop
(paren
id|left
OG
l_int|0
op_logical_and
id|bhe
op_ne
id|bhb
op_logical_and
(paren
op_logical_neg
id|bhe-&gt;bh
op_logical_or
op_logical_neg
id|bhe-&gt;bh-&gt;b_lock
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|left
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Release the read-ahead blocks */
r_while
c_loop
(paren
id|bhe
op_ne
id|bhb
)paren
(brace
id|brelse
c_func
(paren
id|bhe-&gt;bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|read
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
DECL|function|sysv_file_write
r_static
r_int
id|sysv_file_write
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
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
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
id|bh_data
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
l_string|&quot;sysv_file_write: inode = NULL&bslash;n&quot;
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
l_string|&quot;sysv_file_write: mode = %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * ok, append may not work when many processes are writing at the same time&n; * but so what. That way leads to madness anyway.&n; * But we need to protect against simultaneous truncate as we may end up&n; * writing our data into blocks that have meanwhile been incorporated into&n; * the freelist, thereby trashing the freelist.&n; */
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
OG
l_int|0
)paren
multiline_comment|/* block_size &lt; BLOCK_SIZE ? */
id|coh_lock_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
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
id|sysv_getblk
(paren
id|inode
comma
id|pos
op_rshift
id|sb-&gt;sv_block_size_bits
comma
l_int|1
comma
op_amp
id|bh_data
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
id|sb-&gt;sv_block_size
op_minus
(paren
id|pos
op_amp
id|sb-&gt;sv_block_size_1
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
id|bh-&gt;b_uptodate
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
id|bh-&gt;b_uptodate
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
multiline_comment|/* now either c==BLOCK_SIZE or bh-&gt;b_uptodate */
id|p
op_assign
(paren
id|pos
op_amp
id|sb-&gt;sv_block_size_1
)paren
op_plus
id|bh_data
suffix:semicolon
id|pos
op_add_assign
id|c
suffix:semicolon
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|written
op_add_assign
id|c
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|p
comma
id|buf
comma
id|c
)paren
suffix:semicolon
id|buf
op_add_assign
id|c
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
OG
l_int|0
)paren
multiline_comment|/* block_size &lt; BLOCK_SIZE ? */
id|coh_unlock_inode
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