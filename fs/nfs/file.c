multiline_comment|/*&n; *  linux/fs/nfs/file.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  Changes Copyright (C) 1994 by Florian La Roche&n; *   - Do not copy data too often around in the kernel.&n; *   - In nfs_file_read the return value of kmalloc wasn&squot;t checked.&n; *   - Put in a better version of read look-ahead buffering. Original idea&n; *     and implementation by Wai S Kok elekokws@ee.nus.sg.&n; *&n; *  Expire cache on write to a file by Wai S Kok (Oct 1994).&n; *&n; *  nfs regular file handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
r_static
r_int
id|nfs_file_read
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
id|nfs_file_write
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
id|nfs_fsync
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|variable|nfs_file_operations
r_static
r_struct
id|file_operations
id|nfs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|nfs_file_read
comma
multiline_comment|/* read */
id|nfs_file_write
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
id|nfs_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* release */
id|nfs_fsync
comma
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|nfs_file_inode_operations
r_struct
id|inode_operations
id|nfs_file_inode_operations
op_assign
(brace
op_amp
id|nfs_file_operations
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
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
multiline_comment|/* Once data is inserted, it can only be deleted, if (in_use==0). */
DECL|struct|read_cache
r_struct
id|read_cache
(brace
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
multiline_comment|/* currently in use? */
DECL|member|inode_num
r_int
r_int
id|inode_num
suffix:semicolon
multiline_comment|/* inode number */
DECL|member|file_pos
id|off_t
id|file_pos
suffix:semicolon
multiline_comment|/* file position */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
multiline_comment|/* time, this entry was inserted */
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* data */
DECL|member|buf_size
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* size of buffer */
)brace
suffix:semicolon
DECL|macro|READ_CACHE_SIZE
mdefine_line|#define READ_CACHE_SIZE 5
DECL|macro|EXPIRE_CACHE
mdefine_line|#define EXPIRE_CACHE (HZ * 3)&t;&t;/* keep no longer than 3 seconds */
DECL|variable|num_requests
r_int
r_int
id|num_requests
op_assign
l_int|0
suffix:semicolon
DECL|variable|num_cache_hits
r_int
r_int
id|num_cache_hits
op_assign
l_int|0
suffix:semicolon
DECL|variable|tail
r_static
r_int
id|tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* next cache slot to replace */
DECL|variable|cache
r_static
r_struct
id|read_cache
id|cache
(braket
id|READ_CACHE_SIZE
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|nfs_fsync
r_static
r_int
id|nfs_fsync
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
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nfs_file_read
r_static
r_int
id|nfs_file_read
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
id|file
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
id|result
comma
id|hunk
comma
id|i
comma
id|n
comma
id|fs
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
id|off_t
id|pos
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
l_string|&quot;nfs_file_read: inode = NULL&bslash;n&quot;
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
l_string|&quot;nfs_file_read: read from non-file, mode %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pos
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|count
OG
id|inode-&gt;i_size
)paren
id|count
op_assign
id|inode-&gt;i_size
op_minus
id|pos
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
op_increment
id|num_requests
suffix:semicolon
id|cli
c_func
(paren
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
id|READ_CACHE_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|cache
(braket
id|i
)braket
dot
id|inode_num
op_eq
id|inode-&gt;i_ino
)paren
op_logical_and
(paren
id|cache
(braket
id|i
)braket
dot
id|file_pos
op_le
id|pos
)paren
op_logical_and
(paren
id|cache
(braket
id|i
)braket
dot
id|file_pos
op_plus
id|cache
(braket
id|i
)braket
dot
id|len
op_ge
id|pos
op_plus
id|count
)paren
op_logical_and
(paren
id|abs
c_func
(paren
id|jiffies
op_minus
id|cache
(braket
id|i
)braket
dot
id|time
)paren
op_le
id|EXPIRE_CACHE
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|READ_CACHE_SIZE
)paren
(brace
op_increment
id|cache
(braket
id|i
)braket
dot
id|in_use
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
op_increment
id|num_cache_hits
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|cache
(braket
id|i
)braket
dot
id|buf
op_plus
id|pos
op_minus
id|cache
(braket
id|i
)braket
dot
id|file_pos
comma
id|count
)paren
suffix:semicolon
op_decrement
id|cache
(braket
id|i
)braket
dot
id|in_use
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|n
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
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
id|count
op_minus
id|n
suffix:semicolon
id|i
op_add_assign
id|n
)paren
(brace
id|result
op_assign
id|nfs_proc_read
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
id|pos
comma
id|n
comma
id|buf
comma
op_amp
id|fattr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|pos
op_add_assign
id|result
suffix:semicolon
id|buf
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|n
)paren
(brace
id|file-&gt;f_pos
op_assign
id|pos
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_return
id|i
op_plus
id|result
suffix:semicolon
)brace
)brace
id|fs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|n
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|data
op_assign
id|buf
suffix:semicolon
id|fs
op_assign
l_int|1
suffix:semicolon
)brace
id|result
op_assign
id|nfs_proc_read
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
id|pos
comma
id|n
comma
id|data
comma
op_amp
id|fattr
comma
id|fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fs
)paren
id|kfree_s
c_func
(paren
id|data
comma
id|n
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|hunk
op_assign
id|count
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|hunk
)paren
id|hunk
op_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|fs
)paren
(brace
id|file-&gt;f_pos
op_assign
id|pos
op_plus
id|hunk
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_return
id|i
op_plus
id|hunk
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|data
comma
id|hunk
)paren
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|pos
op_plus
id|hunk
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache
(braket
id|tail
)braket
dot
id|in_use
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cache
(braket
id|tail
)braket
dot
id|buf
)paren
id|kfree_s
c_func
(paren
id|cache
(braket
id|tail
)braket
dot
id|buf
comma
id|cache
(braket
id|tail
)braket
dot
id|buf_size
)paren
suffix:semicolon
id|cache
(braket
id|tail
)braket
dot
id|buf
op_assign
id|data
suffix:semicolon
id|cache
(braket
id|tail
)braket
dot
id|buf_size
op_assign
id|n
suffix:semicolon
id|cache
(braket
id|tail
)braket
dot
id|inode_num
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|cache
(braket
id|tail
)braket
dot
id|file_pos
op_assign
id|pos
suffix:semicolon
id|cache
(braket
id|tail
)braket
dot
id|len
op_assign
id|result
suffix:semicolon
id|cache
(braket
id|tail
)braket
dot
id|time
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|tail
op_ge
id|READ_CACHE_SIZE
)paren
id|tail
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|kfree_s
c_func
(paren
id|data
comma
id|n
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|i
op_plus
id|hunk
suffix:semicolon
)brace
DECL|function|nfs_file_write
r_static
r_int
id|nfs_file_write
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
id|file
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
id|result
comma
id|hunk
comma
id|i
comma
id|n
comma
id|pos
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
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
l_string|&quot;nfs_file_write: inode = NULL&bslash;n&quot;
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
l_string|&quot;nfs_file_write: write to non-file, mode %07o&bslash;n&quot;
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
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If hit, cache is dirty and must be expired. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|READ_CACHE_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cache
(braket
id|i
)braket
dot
id|inode_num
op_eq
id|inode-&gt;i_ino
)paren
(brace
id|cache
(braket
id|i
)braket
dot
id|time
op_sub_assign
id|EXPIRE_CACHE
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|pos
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_APPEND
)paren
id|pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|n
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|wsize
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
id|count
suffix:semicolon
id|i
op_add_assign
id|n
)paren
(brace
id|hunk
op_assign
id|count
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|hunk
op_ge
id|n
)paren
id|hunk
op_assign
id|n
suffix:semicolon
id|result
op_assign
id|nfs_proc_write
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
id|pos
comma
id|hunk
comma
id|buf
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|pos
op_add_assign
id|hunk
suffix:semicolon
id|buf
op_add_assign
id|hunk
suffix:semicolon
r_if
c_cond
(paren
id|hunk
OL
id|n
)paren
(brace
id|i
op_add_assign
id|hunk
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|file-&gt;f_pos
op_assign
id|pos
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
