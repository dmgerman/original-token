multiline_comment|/*&n; *  linux/fs/umsdos/file.c&n; *&n; *  Written 1992 by Jacques Gelinas&n; *      inspired from linux/fs/msdos/file.c Werner Almesberger&n; *&n; *  Extended MS-DOS regular file handling primitives&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|umsdos_symlink_operations
r_static
r_struct
id|file_operations
id|umsdos_symlink_operations
suffix:semicolon
multiline_comment|/*&n; * Read the data associate with the symlink.&n; * Return length read in buffer or  a negative error code.&n; * &n; */
DECL|function|umsdos_readlink_x
r_int
id|umsdos_readlink_x
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|bufsiz
)paren
(brace
r_int
id|size
op_assign
id|dentry-&gt;d_inode-&gt;i_size
suffix:semicolon
id|loff_t
id|loffs
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
id|Printk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;UMSDOS_read: %s/%s, size=%u&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|size
)paren
)paren
suffix:semicolon
id|fill_new_filp
(paren
op_amp
id|filp
comma
id|dentry
)paren
suffix:semicolon
id|filp.f_reada
op_assign
l_int|0
suffix:semicolon
id|filp.f_flags
op_assign
id|O_RDONLY
suffix:semicolon
id|filp.f_op
op_assign
op_amp
id|umsdos_symlink_operations
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|bufsiz
)paren
id|size
op_assign
id|bufsiz
suffix:semicolon
id|ret
op_assign
id|fat_file_read
(paren
op_amp
id|filp
comma
id|buffer
comma
id|size
comma
op_amp
id|loffs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|size
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|UMSDOS_readlink
r_static
r_int
id|UMSDOS_readlink
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_return
id|umsdos_readlink_x
(paren
id|dentry
comma
id|buffer
comma
id|buflen
)paren
suffix:semicolon
)brace
multiline_comment|/* this one mostly stolen from romfs :) */
DECL|function|UMSDOS_followlink
r_static
r_struct
id|dentry
op_star
id|UMSDOS_followlink
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|base
comma
r_int
r_int
id|follow
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_char
op_star
id|symname
suffix:semicolon
r_int
id|len
comma
id|cnt
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
(paren
)paren
suffix:semicolon
id|Printk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;UMSDOS_followlink /mn/: (%s/%s)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|len
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|symname
op_assign
id|kmalloc
(paren
id|len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|dentry
op_assign
id|ERR_PTR
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_goto
id|outnobuf
suffix:semicolon
)brace
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* we read into kernel space this time */
id|cnt
op_assign
id|umsdos_readlink_x
(paren
id|dentry
comma
id|symname
comma
id|len
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
id|cnt
)paren
(brace
id|dentry
op_assign
id|ERR_PTR
(paren
op_minus
id|EIO
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|symname
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|dentry
op_assign
id|lookup_dentry
(paren
id|symname
comma
id|base
comma
id|follow
)paren
suffix:semicolon
id|kfree
(paren
id|symname
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|out
suffix:colon
id|kfree
(paren
id|symname
)paren
suffix:semicolon
id|outnobuf
suffix:colon
id|dput
(paren
id|base
)paren
suffix:semicolon
)brace
r_return
id|dentry
suffix:semicolon
)brace
multiline_comment|/* needed to patch the file structure */
DECL|variable|umsdos_symlink_operations
r_static
r_struct
id|file_operations
id|umsdos_symlink_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
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
multiline_comment|/* poll - default */
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
multiline_comment|/* no flush code */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|umsdos_symlink_inode_operations
r_struct
id|inode_operations
id|umsdos_symlink_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* default file operations (none) */
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
id|UMSDOS_readlink
comma
multiline_comment|/* readlink */
id|UMSDOS_followlink
comma
multiline_comment|/* followlink */
id|fat_get_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
