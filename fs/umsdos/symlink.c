multiline_comment|/*&n; *  linux/fs/umsdos/file.c&n; *&n; *  Written 1992 by Jacques Gelinas&n; *&t;inspired from linux/fs/msdos/file.c Werner Almesberger&n; *&n; *  Extended MS-DOS regular file handling primitives&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
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
multiline_comment|/*&n;&t;Follow a symbolic link chain by calling open_namei recursively&n;&t;until an inode is found.&n;&n;&t;Return 0 if ok, or a negative error code if not.&n;*/
DECL|function|UMSDOS_follow_link
r_static
r_int
id|UMSDOS_follow_link
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
comma
r_int
id|mode
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ELOOP
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;link_count
OL
l_int|5
)paren
(brace
r_char
op_star
id|path
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|PATH_MAX
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
id|dir
op_assign
id|current-&gt;fs
(braket
l_int|1
)braket
dot
id|root
suffix:semicolon
id|dir-&gt;i_count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|PRINTK
(paren
(paren
l_string|&quot;symlink: inode = NULL&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|PRINTK
(paren
(paren
l_string|&quot;symlink: Not ISLNK&bslash;n&quot;
)paren
)paren
suffix:semicolon
op_star
id|res_inode
op_assign
id|inode
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|umsdos_readlink_x
(paren
id|inode
comma
id|path
comma
id|umsdos_file_read_kmem
comma
id|PATH_MAX
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|path
(braket
id|ret
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;follow :%s: %d &quot;
comma
id|path
comma
id|ret
)paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|current-&gt;link_count
op_increment
suffix:semicolon
id|ret
op_assign
id|open_namei
c_func
(paren
id|path
comma
id|flag
comma
id|mode
comma
id|res_inode
comma
id|dir
)paren
suffix:semicolon
id|current-&gt;link_count
op_decrement
suffix:semicolon
id|dir
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
)brace
id|kfree
(paren
id|path
)paren
suffix:semicolon
)brace
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;follow_link ret %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
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
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|ret
op_assign
id|umsdos_readlink_x
(paren
id|inode
comma
id|buffer
comma
id|msdos_file_read
comma
id|buflen
)paren
suffix:semicolon
)brace
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
id|UMSDOS_follow_link
comma
multiline_comment|/* follow_link */
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