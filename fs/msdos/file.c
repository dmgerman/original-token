multiline_comment|/*&n; *  linux/fs/msdos/file.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *&n; *  MS-DOS regular file handling primitives&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a) &gt; (b)) ? (a) : (b))
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x)
DECL|macro|Printk
mdefine_line|#define Printk(x) printk x
DECL|variable|msdos_file_operations
r_static
r_struct
id|file_operations
id|msdos_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|msdos_file_read
comma
multiline_comment|/* read */
id|msdos_file_write
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
id|file_fsync
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|msdos_file_inode_operations
r_struct
id|inode_operations
id|msdos_file_inode_operations
op_assign
(brace
op_amp
id|msdos_file_operations
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
id|msdos_bmap
comma
multiline_comment|/* bmap */
id|msdos_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|macro|MSDOS_PREFETCH
mdefine_line|#define MSDOS_PREFETCH&t;32
DECL|struct|msdos_pre
r_struct
id|msdos_pre
(brace
DECL|member|file_sector
r_int
id|file_sector
suffix:semicolon
multiline_comment|/* Next sector to read in the prefetch table */
multiline_comment|/* This is relative to the file, not the disk */
DECL|member|bhlist
r_struct
id|buffer_head
op_star
id|bhlist
(braket
id|MSDOS_PREFETCH
)braket
suffix:semicolon
multiline_comment|/* All buffers needed */
DECL|member|nblist
r_int
id|nblist
suffix:semicolon
multiline_comment|/* Number of buffers in bhlist */
DECL|member|nolist
r_int
id|nolist
suffix:semicolon
multiline_comment|/* index in bhlist */
)brace
suffix:semicolon
multiline_comment|/*&n;&t;Order the prefetch of more sectors.&n;*/
DECL|function|msdos_prefetch
r_static
r_void
id|msdos_prefetch
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|msdos_pre
op_star
id|pre
comma
r_int
id|nb
)paren
multiline_comment|/* How many must be prefetch at once */
(brace
r_struct
id|buffer_head
op_star
id|bhreq
(braket
id|MSDOS_PREFETCH
)braket
suffix:semicolon
multiline_comment|/* Buffers not */
multiline_comment|/* already read */
r_int
id|nbreq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Number of buffers in bhreq */
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|sector
op_assign
id|msdos_smap
c_func
(paren
id|inode
comma
id|pre-&gt;file_sector
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sector
op_ne
l_int|0
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;fsector2 %d -&gt; %d&bslash;n&quot;
comma
id|pre-&gt;file_sector
op_minus
l_int|1
comma
id|sector
)paren
)paren
suffix:semicolon
id|pre-&gt;file_sector
op_increment
suffix:semicolon
id|bh
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|sector
comma
id|SECTOR_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|pre-&gt;bhlist
(braket
id|pre-&gt;nblist
op_increment
)braket
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_uptodate
)paren
id|bhreq
(braket
id|nbreq
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|nbreq
OG
l_int|0
)paren
id|ll_rw_block
(paren
id|READ
comma
id|nbreq
comma
id|bhreq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pre-&gt;nblist
suffix:semicolon
id|i
OL
id|MSDOS_PREFETCH
suffix:semicolon
id|i
op_increment
)paren
id|pre-&gt;bhlist
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Read a file into user space&n;*/
DECL|function|msdos_file_read
r_int
id|msdos_file_read
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
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|msdos_pre
id|pre
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
l_string|&quot;msdos_file_read: inode = NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* S_ISLNK allows for UMSDOS. Should never happen for normal MSDOS */
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;msdos_file_read: mode = %07o&bslash;n&quot;
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
multiline_comment|/*&n;&t;&t;Tell the buffer cache which block we expect to read in advance&n;&t;&t;Since we are limited with the stack, we preread only MSDOS_PREFETCH&n;&t;&t;because we have to keep the result into the local&n;&t;&t;arrays pre.bhlist and bhreq.&n;&t;&t;&n;&t;&t;Each time we process one block in bhlist, we replace&n;&t;&t;it by a new prefetch block if needed.&n;&t;*/
id|PRINTK
(paren
(paren
l_string|&quot;#### ino %ld pos %ld size %ld count %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|filp-&gt;f_pos
comma
id|inode-&gt;i_size
comma
id|count
)paren
)paren
suffix:semicolon
(brace
multiline_comment|/*&n;&t;&t;&t;We must prefetch complete block, so we must&n;&t;&t;&t;take in account the offset in the first block.&n;&t;&t;*/
r_int
id|count_max
op_assign
(paren
id|filp-&gt;f_pos
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
op_plus
id|count
suffix:semicolon
r_int
id|to_reada
suffix:semicolon
multiline_comment|/* How many block to read all at once */
id|pre.file_sector
op_assign
id|filp-&gt;f_pos
op_rshift
id|SECTOR_BITS
suffix:semicolon
id|to_reada
op_assign
id|count_max
op_div
id|SECTOR_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|count_max
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
id|to_reada
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_reada
op_logical_or
op_logical_neg
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_binary
)paren
(brace
multiline_comment|/* Doing a read ahead on ascii file make sure we always */
multiline_comment|/* pre read enough, since we don&squot;t know how many blocks */
multiline_comment|/* we really need */
r_int
id|ahead
op_assign
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ahead
op_eq
l_int|0
)paren
id|ahead
op_assign
l_int|8
suffix:semicolon
id|to_reada
op_add_assign
id|ahead
suffix:semicolon
)brace
r_if
c_cond
(paren
id|to_reada
OG
id|MSDOS_PREFETCH
)paren
id|to_reada
op_assign
id|MSDOS_PREFETCH
suffix:semicolon
id|pre.nblist
op_assign
l_int|0
suffix:semicolon
id|msdos_prefetch
(paren
id|inode
comma
op_amp
id|pre
comma
id|to_reada
)paren
suffix:semicolon
)brace
id|start
op_assign
id|buf
suffix:semicolon
id|pre.nolist
op_assign
l_int|0
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;count %d ahead %d nblist %d&bslash;n&quot;
comma
id|count
comma
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)braket
comma
id|pre.nblist
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|left
op_assign
id|MIN
c_func
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
)paren
OG
l_int|0
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|pre.bhlist
(braket
id|pre.nolist
)braket
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_int
id|size
comma
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|pre.bhlist
(braket
id|pre.nolist
)braket
op_assign
l_int|NULL
suffix:semicolon
id|pre.nolist
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pre.nolist
op_eq
id|MSDOS_PREFETCH
op_div
l_int|2
)paren
(brace
id|memcpy
(paren
id|pre.bhlist
comma
id|pre.bhlist
op_plus
id|MSDOS_PREFETCH
op_div
l_int|2
comma
(paren
id|MSDOS_PREFETCH
op_div
l_int|2
)paren
op_star
r_sizeof
(paren
id|pre.bhlist
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|pre.nblist
op_sub_assign
id|MSDOS_PREFETCH
op_div
l_int|2
suffix:semicolon
id|msdos_prefetch
(paren
id|inode
comma
op_amp
id|pre
comma
id|MSDOS_PREFETCH
op_div
l_int|2
)paren
suffix:semicolon
id|pre.nolist
op_assign
l_int|0
suffix:semicolon
)brace
id|PRINTK
(paren
(paren
l_string|&quot;file_read pos %ld nblist %d %d %d&bslash;n&quot;
comma
id|filp-&gt;f_pos
comma
id|pre.nblist
comma
id|pre.fetched
comma
id|count
)paren
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
multiline_comment|/* read error  ? */
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
(paren
id|size
op_assign
id|MIN
c_func
(paren
id|SECTOR_SIZE
op_minus
id|offset
comma
id|left
)paren
)paren
suffix:semicolon
id|data
op_assign
id|bh-&gt;b_data
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_binary
)paren
(brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|data
comma
id|size
)paren
suffix:semicolon
id|buf
op_add_assign
id|size
suffix:semicolon
)brace
r_else
(brace
r_int
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
id|size
suffix:semicolon
id|cnt
suffix:semicolon
id|cnt
op_decrement
)paren
(brace
r_char
id|ch
op_assign
op_star
id|data
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|26
)paren
(brace
id|filp-&gt;f_pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ch
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|put_fs_byte
c_func
(paren
id|ch
comma
id|buf
op_increment
)paren
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
id|PRINTK
(paren
(paren
l_string|&quot;--- %d -&gt; %d&bslash;n&quot;
comma
id|count
comma
(paren
r_int
)paren
(paren
id|buf
op_minus
id|start
)paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pre.nblist
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|pre.bhlist
(braket
id|i
)braket
)paren
suffix:semicolon
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
id|PRINTK
(paren
(paren
l_string|&quot;file_read ret %d&bslash;n&quot;
comma
(paren
id|buf
op_minus
id|start
)paren
)paren
)paren
suffix:semicolon
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Will be reset if a lseek is done */
r_return
id|buf
op_minus
id|start
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Write to a file either from user space&n;*/
DECL|function|msdos_file_write
r_int
id|msdos_file_write
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
id|sector
comma
id|offset
comma
id|size
comma
id|left
comma
id|written
suffix:semicolon
r_int
id|error
comma
id|carry
suffix:semicolon
r_char
op_star
id|start
comma
op_star
id|to
comma
id|ch
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|binary_mode
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_binary
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
l_string|&quot;msdos_file_write: inode = NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* S_ISLNK allows for UMSDOS. Should never happen for normal MSDOS */
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;msdos_file_write: mode = %07o&bslash;n&quot;
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
id|filp-&gt;f_pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|error
op_assign
id|carry
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|start
op_assign
id|buf
suffix:semicolon
id|count
op_logical_or
id|carry
suffix:semicolon
id|count
op_sub_assign
id|size
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|sector
op_assign
id|msdos_smap
c_func
(paren
id|inode
comma
id|filp-&gt;f_pos
op_rshift
id|SECTOR_BITS
)paren
)paren
)paren
r_if
c_cond
(paren
(paren
id|error
op_assign
id|msdos_add_cluster
c_func
(paren
id|inode
)paren
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|msdos_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|size
op_assign
id|MIN
c_func
(paren
id|SECTOR_SIZE
op_minus
id|offset
comma
id|MAX
c_func
(paren
id|carry
comma
id|count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|binary_mode
op_logical_and
id|offset
op_eq
l_int|0
op_logical_and
(paren
id|size
op_eq
id|SECTOR_SIZE
op_logical_or
id|filp-&gt;f_pos
op_plus
id|size
op_ge
id|inode-&gt;i_size
)paren
)paren
(brace
multiline_comment|/* No need to read the block first since we will */
multiline_comment|/* completely overwrite it */
multiline_comment|/* or at least write past the end of file */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|sector
comma
id|SECTOR_SIZE
)paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|msdos_sread
c_func
(paren
id|inode-&gt;i_dev
comma
id|sector
)paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|binary_mode
)paren
(brace
id|memcpy_fromfs
c_func
(paren
id|bh-&gt;b_data
op_plus
id|offset
comma
id|buf
comma
id|written
op_assign
id|size
)paren
suffix:semicolon
id|buf
op_add_assign
id|size
suffix:semicolon
)brace
r_else
(brace
id|written
op_assign
id|left
op_assign
id|SECTOR_SIZE
op_minus
id|offset
suffix:semicolon
id|to
op_assign
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
(paren
id|filp-&gt;f_pos
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|carry
)paren
(brace
op_star
id|to
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|left
op_decrement
suffix:semicolon
id|carry
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|size
op_assign
l_int|0
suffix:semicolon
id|size
OL
id|count
op_logical_and
id|left
suffix:semicolon
id|size
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|ch
op_assign
id|get_fs_byte
c_func
(paren
id|buf
op_increment
)paren
)paren
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_star
id|to
op_increment
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
id|left
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
id|carry
op_assign
l_int|1
suffix:semicolon
r_else
(brace
op_star
id|to
op_increment
op_assign
id|ch
suffix:semicolon
id|left
op_decrement
suffix:semicolon
)brace
)brace
id|written
op_sub_assign
id|left
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_add_assign
id|written
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
OG
id|inode-&gt;i_size
)paren
(brace
id|inode-&gt;i_size
op_assign
id|filp-&gt;f_pos
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|bh-&gt;b_uptodate
op_assign
l_int|1
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
)brace
r_if
c_cond
(paren
id|start
op_eq
id|buf
)paren
r_return
id|error
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|buf
op_minus
id|start
suffix:semicolon
)brace
DECL|function|msdos_truncate
r_void
id|msdos_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|cluster
suffix:semicolon
id|cluster
op_assign
id|SECTOR_SIZE
op_star
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
(paren
r_void
)paren
id|fat_free
c_func
(paren
id|inode
comma
(paren
id|inode-&gt;i_size
op_plus
(paren
id|cluster
op_minus
l_int|1
)paren
)paren
op_div
id|cluster
)paren
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
eof
