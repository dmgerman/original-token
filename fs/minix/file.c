multiline_comment|/*&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix regular file handling primitives&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;16
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
DECL|function|wait_on_buffer
r_static
r_inline
r_void
id|wait_on_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bh-&gt;b_lock
)paren
id|sleep_on
c_func
(paren
op_amp
id|bh-&gt;b_wait
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
r_int
id|minix_file_read
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
r_char
op_star
comma
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
id|minix_file_read
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
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
multiline_comment|/* release */
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
id|minix_bmap
comma
multiline_comment|/* bmap */
id|minix_truncate
multiline_comment|/* truncate */
)brace
suffix:semicolon
multiline_comment|/*&n; * minix_file_read() is also needed by the directory read-routine,&n; * so it&squot;s not static. NOTE! reading directories directly is a bad idea,&n; * but has to be supported for now for compatability reasons with older&n; * versions.&n; */
DECL|function|minix_file_read
r_int
id|minix_file_read
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
r_int
id|read
comma
id|left
comma
id|chars
suffix:semicolon
r_int
id|block
comma
id|blocks
comma
id|offset
suffix:semicolon
r_struct
id|buffer_head
op_star
op_star
id|bhb
comma
op_star
op_star
id|bhe
suffix:semicolon
r_struct
id|buffer_head
op_star
id|buflist
(braket
id|NBUF
)braket
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
l_string|&quot;minix_file_read: inode = NULL&bslash;n&quot;
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
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_file_read: mode = %07o&bslash;n&quot;
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
id|filp-&gt;f_pos
OG
id|inode-&gt;i_size
)paren
id|left
op_assign
l_int|0
suffix:semicolon
r_else
id|left
op_assign
id|inode-&gt;i_size
op_minus
id|filp-&gt;f_pos
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
id|filp-&gt;f_pos
op_rshift
id|BLOCK_SIZE_BITS
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|BLOCK_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|blocks
op_assign
(paren
id|left
op_plus
id|offset
op_plus
id|BLOCK_SIZE
op_minus
l_int|1
)paren
op_div
id|BLOCK_SIZE
suffix:semicolon
id|bhb
op_assign
id|bhe
op_assign
id|buflist
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|blocks
)paren
(brace
op_decrement
id|blocks
suffix:semicolon
op_star
id|bhb
op_assign
id|minix_getblk
c_func
(paren
id|inode
comma
id|block
op_increment
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bhb
op_logical_and
op_logical_neg
(paren
op_star
id|bhb
)paren
op_member_access_from_pointer
id|b_uptodate
)paren
id|ll_rw_block
c_func
(paren
id|READ
comma
op_star
id|bhb
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|bhb
op_ne
id|bhe
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|bhe
)paren
(brace
id|wait_on_buffer
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_uptodate
)paren
(brace
r_do
(brace
id|brelse
c_func
(paren
op_star
id|bhe
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
r_while
c_loop
(paren
id|bhe
op_ne
id|bhb
)paren
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
id|BLOCK_SIZE
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
id|BLOCK_SIZE
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
op_star
id|bhe
)paren
(brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|offset
op_plus
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_data
comma
id|chars
)paren
suffix:semicolon
id|brelse
c_func
(paren
op_star
id|bhe
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
)paren
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
r_return
id|read
suffix:semicolon
)brace
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
r_char
op_star
id|buf
comma
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
multiline_comment|/*&n; * ok, append may not work when many processes are writing at the same time&n; * but so what. That way leads to madness anyway.&n; */
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
id|bh-&gt;b_uptodate
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
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
id|CURRENT_TIME
suffix:semicolon
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
r_return
id|written
suffix:semicolon
)brace
eof
