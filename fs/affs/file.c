multiline_comment|/*&n; *  linux/fs/affs/file.c&n; *&n; *  (C) 1993  Ray Burr - Modified for Amiga FFS filesystem.&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; *&n; *  affs regular file handling primitives&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/dirent.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;16
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &quot;amigaffs.h&quot;
r_int
id|affs_file_read
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
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the affs filesystem.&n; */
DECL|variable|affs_file_operations
r_struct
id|file_operations
id|affs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|affs_file_read
comma
multiline_comment|/* read */
l_int|NULL
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
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|affs_file_inode_operations
r_struct
id|inode_operations
id|affs_file_inode_operations
op_assign
(brace
op_amp
id|affs_file_operations
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
multiline_comment|/* affs_bmap */
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|affs_smap
r_static
r_int
id|affs_smap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|key
suffix:semicolon
r_void
op_star
id|fh_data
suffix:semicolon
multiline_comment|/* FIXME */
DECL|macro|KEY_SLOTS_PER_BLOCK
mdefine_line|#define KEY_SLOTS_PER_BLOCK 72
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;affs_smap: ino=%d block=%d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|block
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|block
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;affs_smap: block &lt; 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|key
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|bh
op_assign
id|affs_pread
(paren
id|inode
comma
id|key
comma
op_amp
id|fh_data
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
r_if
c_cond
(paren
id|block
OL
id|KEY_SLOTS_PER_BLOCK
)paren
r_break
suffix:semicolon
id|block
op_sub_assign
id|KEY_SLOTS_PER_BLOCK
suffix:semicolon
id|key
op_assign
id|affs_get_extension
(paren
id|AFFS_I2BSIZE
(paren
id|inode
)paren
comma
id|fh_data
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;affs_smap: reading extension block %d&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
macro_line|#endif
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
id|key
op_assign
id|affs_get_key_entry
(paren
id|AFFS_I2BSIZE
(paren
id|inode
)paren
comma
id|fh_data
comma
(paren
id|KEY_SLOTS_PER_BLOCK
op_minus
l_int|1
)paren
op_minus
id|block
)paren
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;affs_smap: key=%d&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
macro_line|#endif
r_return
id|key
suffix:semicolon
)brace
multiline_comment|/*&n; * affs_file_read() is also needed by the directory read-routine,&n; * so it&squot;s not static. NOTE! reading directories directly is a bad idea,&n; * but has to be supported for now for compatibility reasons with older&n; * versions.&n; */
DECL|function|affs_file_read
r_int
id|affs_file_read
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
r_char
op_star
id|start
suffix:semicolon
r_int
id|left
comma
id|offset
comma
id|size
comma
id|sector
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_void
op_star
id|data
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
l_string|&quot;affs_file_read: inode = NULL&bslash;n&quot;
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
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;affs_file_read: mode = %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_ge
id|inode-&gt;i_size
op_logical_or
id|count
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|start
op_assign
id|buf
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|left
op_assign
id|MIN
(paren
id|inode-&gt;i_size
op_minus
id|filp-&gt;f_pos
comma
id|count
op_minus
(paren
id|buf
op_minus
id|start
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
r_break
suffix:semicolon
id|sector
op_assign
id|affs_smap
(paren
id|inode
comma
id|filp-&gt;f_pos
op_rshift
id|AFFS_BLOCK_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sector
)paren
r_break
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|AFFS_BLOCK_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|bh
op_assign
id|affs_pread
(paren
id|inode
comma
id|sector
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_break
suffix:semicolon
id|size
op_assign
id|MIN
(paren
id|AFFS_BLOCK_SIZE
op_minus
id|offset
comma
id|left
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|size
suffix:semicolon
id|memcpy_tofs
(paren
id|buf
comma
id|data
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
id|buf
op_add_assign
id|size
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
op_eq
id|buf
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|buf
op_minus
id|start
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|0
op_logical_and
id|count
OG
l_int|0
)paren
(brace
id|put_fs_byte
(paren
l_char|&squot;X&squot;
comma
id|buf
op_increment
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
eof
