multiline_comment|/*&n; *  linux/fs/umsdos/file.c&n; *&n; *  Written 1993 by Jacques Gelinas&n; *&t;inspired from linux/fs/msdos/file.c Werner Almesberger&n; *&n; *  Extended MS-DOS regular file handling primitives&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x)
DECL|macro|Printk
mdefine_line|#define Printk(x)&t;printk x
multiline_comment|/*&n;&t;Read a file into user space memory&n;*/
DECL|function|UMSDOS_file_read
r_static
r_int
id|UMSDOS_file_read
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
r_int
id|count
)paren
(brace
multiline_comment|/* We have to set the access time because msdos don&squot;t care */
r_int
id|ret
op_assign
id|fat_file_read
c_func
(paren
id|inode
comma
id|filp
comma
id|buf
comma
id|count
)paren
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
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Write a file from user space memory&n;*/
DECL|function|UMSDOS_file_write
r_static
r_int
id|UMSDOS_file_write
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
r_return
id|fat_file_write
c_func
(paren
id|inode
comma
id|filp
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Truncate a file to 0 length.&n;*/
DECL|function|UMSDOS_truncate
r_static
r_void
id|UMSDOS_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|PRINTK
(paren
(paren
l_string|&quot;UMSDOS_truncate&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|fat_truncate
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Function for normal file system (512 bytes hardware sector size) */
DECL|variable|umsdos_file_operations
r_struct
id|file_operations
id|umsdos_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|UMSDOS_file_read
comma
multiline_comment|/* read */
id|UMSDOS_file_write
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
id|file_fsync
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|umsdos_file_inode_operations
r_struct
id|inode_operations
id|umsdos_file_inode_operations
op_assign
(brace
op_amp
id|umsdos_file_operations
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
id|generic_readpage
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
id|fat_bmap
comma
multiline_comment|/* bmap */
id|UMSDOS_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
id|fat_smap
multiline_comment|/* smap */
)brace
suffix:semicolon
multiline_comment|/* For other with larger and unaligned file system */
DECL|variable|umsdos_file_operations_no_bmap
r_struct
id|file_operations
id|umsdos_file_operations_no_bmap
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|UMSDOS_file_read
comma
multiline_comment|/* read */
id|UMSDOS_file_write
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
id|fat_mmap
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
DECL|variable|umsdos_file_inode_operations_no_bmap
r_struct
id|inode_operations
id|umsdos_file_inode_operations_no_bmap
op_assign
(brace
op_amp
id|umsdos_file_operations_no_bmap
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
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
id|UMSDOS_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
)brace
suffix:semicolon
eof
