multiline_comment|/*&n; *  linux/fs/nfs/file.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  nfs regular file handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
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
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
multiline_comment|/* release */
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
suffix:semicolon
r_int
id|hunk
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|n
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
id|file-&gt;f_pos
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
OG
id|n
)paren
id|hunk
op_assign
id|n
suffix:semicolon
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
id|hunk
comma
id|data
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
(brace
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
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|data
comma
id|result
)paren
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
id|i
op_add_assign
id|result
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|file-&gt;f_pos
op_assign
id|pos
suffix:semicolon
id|kfree_s
c_func
(paren
id|data
comma
id|n
)paren
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
suffix:semicolon
r_int
id|hunk
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|n
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_int
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
id|memcpy_fromfs
c_func
(paren
id|data
comma
id|buf
comma
id|hunk
)paren
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
id|data
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
(brace
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
id|kfree_s
c_func
(paren
id|data
comma
id|n
)paren
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
