multiline_comment|/*&n; *  linux/fs/umsdos/file.c&n; *&n; *  Written 1993 by Jacques Gelinas&n; *      inspired from linux/fs/msdos/file.c Werner Almesberger&n; *&n; *  Extended MS-DOS regular file handling primitives&n; */
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
multiline_comment|/*&n; * Read a file into user space memory&n; */
DECL|function|UMSDOS_file_read
r_static
id|ssize_t
id|UMSDOS_file_read
(paren
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
multiline_comment|/* We have to set the access time because msdos don&squot;t care */
multiline_comment|/* FIXME */
r_int
id|ret
op_assign
id|fat_file_read
(paren
id|filp
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RDONLY
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
multiline_comment|/* FIXME &n;&t;&t; * inode-&gt;i_dirt = 1;&n;&t;&t; */
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a file from user space memory&n; */
DECL|function|UMSDOS_file_write
r_static
id|ssize_t
id|UMSDOS_file_write
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
r_return
id|fat_file_write
(paren
id|filp
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Truncate a file to 0 length.&n; */
DECL|function|UMSDOS_truncate
r_static
r_void
id|UMSDOS_truncate
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|Printk
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
multiline_comment|/*FIXME inode-&gt;i_dirt = 1; */
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
multiline_comment|/* flush */
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
l_int|NULL
comma
multiline_comment|/* follow_link */
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
multiline_comment|/* flush */
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
multiline_comment|/* follow link */
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
multiline_comment|/* For other with larger and unaligned file system with readpage */
DECL|variable|umsdos_file_operations_readpage
r_struct
id|file_operations
id|umsdos_file_operations_readpage
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
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* release */
id|file_fsync
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|umsdos_file_inode_operations_readpage
r_struct
id|inode_operations
id|umsdos_file_inode_operations_readpage
op_assign
(brace
op_amp
id|umsdos_file_operations_readpage
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
multiline_comment|/* follow link */
id|fat_readpage
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
