multiline_comment|/*&n; *  linux/fs/nfs/file.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  Changes Copyright (C) 1994 by Florian La Roche&n; *   - Do not copy data too often around in the kernel.&n; *   - In nfs_file_read the return value of kmalloc wasn&squot;t checked.&n; *   - Put in a better version of read look-ahead buffering. Original idea&n; *     and implementation by Wai S Kok elekokws@ee.nus.sg.&n; *&n; *  Expire cache on write to a file by Wai S Kok (Oct 1994).&n; *&n; *  Total rewrite of read side for new NFS buffer cache.. Linus.&n; *&n; *  nfs regular file handling functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_static
r_int
id|nfs_file_mmap
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
id|vm_area_struct
op_star
)paren
suffix:semicolon
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
r_const
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
r_static
r_int
id|nfs_readpage
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
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
id|nfs_file_mmap
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
id|nfs_readpage
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
DECL|function|revalidate_inode
r_static
r_inline
r_void
id|revalidate_inode
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_minus
id|NFS_READTIME
c_func
(paren
id|inode
)paren
OL
id|server-&gt;acregmax
)paren
r_return
suffix:semicolon
id|NFS_READTIME
c_func
(paren
id|inode
)paren
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|nfs_proc_getattr
c_func
(paren
id|server
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
op_amp
id|fattr
)paren
op_eq
l_int|0
)paren
(brace
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fattr.mtime.seconds
op_eq
id|NFS_OLDMTIME
c_func
(paren
id|inode
)paren
)paren
r_return
suffix:semicolon
id|NFS_OLDMTIME
c_func
(paren
id|inode
)paren
op_assign
id|fattr.mtime.seconds
suffix:semicolon
)brace
id|invalidate_inode_pages
c_func
(paren
id|inode
)paren
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
id|revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
r_return
id|generic_file_read
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|nfs_file_mmap
r_static
r_int
id|nfs_file_mmap
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
r_return
id|generic_file_mmap
c_func
(paren
id|inode
comma
id|file
comma
id|vma
)paren
suffix:semicolon
)brace
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
DECL|function|do_read_nfs
r_static
r_inline
r_int
id|do_read_nfs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|pos
)paren
(brace
r_int
id|result
comma
id|refresh
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_int
id|rsize
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
id|page-&gt;locked
op_assign
l_int|1
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|count
OL
id|rsize
)paren
id|rsize
op_assign
id|count
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
id|rsize
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
r_break
suffix:semicolon
id|refresh
op_assign
l_int|1
suffix:semicolon
id|count
op_sub_assign
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
id|rsize
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|refresh
)paren
(brace
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|page-&gt;uptodate
op_assign
l_int|1
suffix:semicolon
)brace
id|page-&gt;locked
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|nfs_readpage
r_static
r_int
id|nfs_readpage
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|address
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|page-&gt;count
op_increment
suffix:semicolon
id|error
op_assign
id|do_read_nfs
c_func
(paren
id|inode
comma
id|page
comma
(paren
r_char
op_star
)paren
id|address
comma
id|page-&gt;offset
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|address
)paren
suffix:semicolon
r_return
id|error
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
r_const
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
id|written
comma
id|wsize
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_int
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
id|wsize
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|wsize
suffix:semicolon
id|result
op_assign
l_int|0
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
r_int
id|hunk
op_assign
id|count
op_minus
id|written
suffix:semicolon
r_if
c_cond
(paren
id|hunk
op_ge
id|wsize
)paren
id|hunk
op_assign
id|wsize
suffix:semicolon
id|result
op_assign
id|nfs_proc_write
c_func
(paren
id|inode
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
r_break
suffix:semicolon
id|pos
op_add_assign
id|hunk
suffix:semicolon
id|buf
op_add_assign
id|hunk
suffix:semicolon
id|written
op_add_assign
id|hunk
suffix:semicolon
r_if
c_cond
(paren
id|hunk
OL
id|wsize
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|written
)paren
r_return
id|result
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|pos
suffix:semicolon
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
id|written
suffix:semicolon
)brace
eof
