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
DECL|variable|umsdos_symlink_operations
r_static
r_struct
id|file_operations
id|umsdos_symlink_operations
suffix:semicolon
multiline_comment|/*&n;&t;Read the data associate with the symlink.&n;&t;Return length read in buffer or  a negative error code.&n;&t;FIXME, this is messed up.&n;&t;&n;&t;/mn/ WIP fixing...&n;*/
DECL|function|umsdos_readlink_x
r_static
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
id|ret
op_assign
id|dentry-&gt;d_inode-&gt;i_size
suffix:semicolon
id|loff_t
id|loffs
op_assign
l_int|0
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
id|memset
(paren
op_amp
id|filp
comma
l_int|0
comma
r_sizeof
(paren
id|filp
)paren
)paren
suffix:semicolon
id|filp.f_pos
op_assign
l_int|0
suffix:semicolon
id|filp.f_reada
op_assign
l_int|0
suffix:semicolon
id|filp.f_flags
op_assign
id|O_RDONLY
suffix:semicolon
id|filp.f_dentry
op_assign
id|dentry
suffix:semicolon
id|filp.f_op
op_assign
op_amp
id|umsdos_symlink_operations
suffix:semicolon
multiline_comment|/* /mn/ - we have to fill it with dummy values so we won&squot;t segfault */
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
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;umsdos_readlink_x /mn/: Checkin: filp=%p, buffer=%p, size=%ld, offs=%d&bslash;n&quot;
comma
op_amp
id|filp
comma
id|buffer
comma
id|ret
comma
id|loffs
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  f_op=%p&bslash;n&quot;
comma
id|filp.f_op
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  inode=%d, i_size=%d&bslash;n&quot;
comma
id|filp.f_dentry-&gt;d_inode-&gt;i_ino
comma
id|filp.f_dentry-&gt;d_inode-&gt;i_size
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  f_pos=%ld&bslash;n&quot;
comma
id|filp.f_pos
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  name=%12s&bslash;n&quot;
comma
id|filp.f_dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  i_binary(sb)=%d&bslash;n&quot;
comma
id|MSDOS_I
c_func
(paren
id|filp.f_dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|i_binary
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  f_count=%d, f_flags=%d&bslash;n&quot;
comma
id|filp.f_count
comma
id|filp.f_flags
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  f_owner=%d&bslash;n&quot;
comma
id|filp.f_owner
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  f_version=%ld&bslash;n&quot;
comma
id|filp.f_version
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_WARNING
l_string|&quot;  f_reada=%ld, f_ramax=%ld, f_raend=%ld, f_ralen=%ld, f_rawin=%ld&bslash;n&quot;
comma
id|filp.f_reada
comma
id|filp.f_ramax
comma
id|filp.f_raend
comma
id|filp.f_ralen
comma
id|filp.f_rawin
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME */
id|Printk
(paren
(paren
l_string|&quot;umsdos_readlink_x: FIXME /mn/: running fat_file_read (%p, %p, %d, %ld)&bslash;n&quot;
comma
op_amp
id|filp
comma
id|buffer
comma
id|ret
comma
id|loffs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fat_file_read
(paren
op_amp
id|filp
comma
id|buffer
comma
(paren
r_int
)paren
id|ret
comma
op_amp
id|loffs
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
macro_line|#if 0
(brace
r_struct
id|umsdos_dirent
op_star
id|mydirent
op_assign
id|buffer
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_DEBUG
l_string|&quot;  (DDD) uid=%d&bslash;n&quot;
comma
id|mydirent-&gt;uid
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_DEBUG
l_string|&quot;  (DDD) gid=%d&bslash;n&quot;
comma
id|mydirent-&gt;gid
)paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_DEBUG
l_string|&quot;  (DDD) name=&gt;%20s&lt;&bslash;n&quot;
comma
id|mydirent-&gt;name
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif  
id|Printk
(paren
(paren
l_string|&quot;umsdos_readlink_x: FIXME /mn/: fat_file_read returned offs=%ld ret=%d&bslash;n&quot;
comma
id|loffs
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
r_int
id|ret
suffix:semicolon
id|Printk
(paren
(paren
l_string|&quot;UMSDOS_readlink: calling umsdos_readlink_x for %20s&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|umsdos_readlink_x
(paren
id|dentry
comma
id|buffer
comma
id|buflen
)paren
suffix:semicolon
id|Printk
(paren
(paren
l_string|&quot;readlink %d bufsiz %d&bslash;n&quot;
comma
id|ret
comma
id|buflen
)paren
)paren
suffix:semicolon
multiline_comment|/* dput(dentry); / * FIXME /mn/ */
id|Printk
(paren
(paren
l_string|&quot;UMSDOS_readlink /mn/: FIXME! skipped dput(dentry). returning %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|UMSDOS_followlink
r_static
r_struct
id|dentry
op_star
id|UMSDOS_followlink
c_func
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
)paren
(brace
r_int
id|ret
suffix:semicolon
r_char
id|symname
(braket
l_int|256
)braket
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|Printk
(paren
(paren
id|KERN_ERR
l_string|&quot;UMSDOS_followlink /mn/: (%s/%s)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* we read into kernel space */
id|ret
op_assign
id|umsdos_readlink_x
(paren
id|dentry
comma
op_amp
id|symname
comma
l_int|256
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
id|base
op_assign
id|creat_dentry
(paren
id|symname
comma
id|ret
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&t;UMSDOS_lookup (dentry-&gt;d_parent-&gt;d_inode, base);*/
r_return
id|base
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
l_int|NULL
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
multiline_comment|/*UMSDOS_followlink*/
comma
multiline_comment|/* followlink */
multiline_comment|/* /mn/ is this REALLY needed ? I recall seeing it working w/o it... */
id|generic_readpage
comma
multiline_comment|/* readpage */
multiline_comment|/* in original NULL. changed to generic_readpage. FIXME? /mn/ */
l_int|NULL
comma
multiline_comment|/* writepage */
id|fat_bmap
comma
multiline_comment|/* bmap */
multiline_comment|/* in original NULL. changed to fat_bmap. FIXME? /mn/ */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* updatepage */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
