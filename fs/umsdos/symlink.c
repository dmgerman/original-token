multiline_comment|/*&n; *  linux/fs/umsdos/file.c&n; *&n; *  Written 1992 by Jacques Gelinas&n; *&t;inspired from linux/fs/msdos/file.c Werner Almesberger&n; *&n; *  Extended MS-DOS regular file handling primitives&n; */
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
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x)
DECL|macro|Printk
mdefine_line|#define Printk(x)&t;printk x
multiline_comment|/*&n;&t;Read the data associate with the symlink.&n;&t;Return length read in buffer or  a negative error code.&n;*/
DECL|function|umsdos_readlink_x
r_static
r_int
id|umsdos_readlink_x
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
(paren
op_star
id|msdos_read
)paren
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
r_int
)paren
comma
r_int
id|bufsiz
)paren
(brace
r_int
id|ret
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
id|filp.f_pos
op_assign
l_int|0
suffix:semicolon
id|filp.f_reada
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
id|bufsiz
)paren
id|ret
op_assign
id|bufsiz
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|msdos_read
)paren
(paren
id|inode
comma
op_amp
id|filp
comma
id|buffer
comma
id|ret
)paren
op_ne
id|ret
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
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|umsdos_readlink_x
(paren
id|inode
comma
id|buffer
comma
id|fat_file_read
comma
id|buflen
)paren
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;readlink %d %x bufsiz %d&bslash;n&quot;
comma
id|ret
comma
id|inode-&gt;i_mode
comma
id|buflen
)paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
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
op_amp
id|umsdos_symlink_operations
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
id|UMSDOS_readlink
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
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
eof
