multiline_comment|/*&n; *  linux/fs/ncpfs/symlink.c&n; *&n; *  Code for allowing symbolic links on NCPFS (i.e. NetWare)&n; *  Symbolic links are not supported on native NetWare, so we use an&n; *  infrequently-used flag (Sh) and store a two-word magic header in&n; *  the file to make sure we don&squot;t accidentally use a non-link file&n; *  as a link.&n; *&n; *  from linux/fs/ext2/symlink.c&n; *&n; *  Copyright (C) 1998-99, Frank A. Vorstenbosch&n; *&n; *  ncpfs symlink handling code&n; *  NLS support (c) 1999 Petr Vandrovec&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NCPFS_EXTRAS
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
multiline_comment|/* these magic numbers must appear in the symlink file -- this makes it a bit&n;   more resilient against the magic attributes being set on random files. */
DECL|macro|NCP_SYMLINK_MAGIC0
mdefine_line|#define NCP_SYMLINK_MAGIC0&t;le32_to_cpu(0x6c6d7973)     /* &quot;symlnk-&gt;&quot; */
DECL|macro|NCP_SYMLINK_MAGIC1
mdefine_line|#define NCP_SYMLINK_MAGIC1&t;le32_to_cpu(0x3e2d6b6e)
r_static
r_int
id|ncp_readlink
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_struct
id|dentry
op_star
id|ncp_follow_link
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|ncp_create_new
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
r_int
id|attributes
)paren
suffix:semicolon
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|ncp_symlink_inode_operations
r_struct
id|inode_operations
id|ncp_symlink_inode_operations
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* ----- follow a symbolic link ------------------------------------------ */
DECL|function|ncp_follow_link
r_static
r_struct
id|dentry
op_star
id|ncp_follow_link
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
r_int
id|error
comma
id|length
comma
id|cnt
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
macro_line|#ifdef DEBUG
id|PRINTK
c_func
(paren
l_string|&quot;ncp_follow_link(dentry=%p,base=%p,follow=%u)&bslash;n&quot;
comma
id|dentry
comma
id|base
comma
id|follow
)paren
suffix:semicolon
macro_line|#endif
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
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDONLY
)paren
)paren
(brace
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
(paren
id|link
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|NCP_MAX_SYMLINK_SIZE
op_plus
l_int|1
comma
id|GFP_NFS
)paren
)paren
op_eq
l_int|NULL
suffix:semicolon
id|cnt
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cnt
OG
l_int|10
)paren
(brace
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
multiline_comment|/* -ENOMEM? */
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|error
op_assign
id|ncp_read_kernel
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
l_int|0
comma
id|NCP_MAX_SYMLINK_SIZE
comma
id|link
comma
op_amp
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
op_logical_or
id|length
OL
id|NCP_MIN_SYMLINK_SIZE
op_logical_or
(paren
(paren
id|__u32
op_star
)paren
id|link
)paren
(braket
l_int|0
)braket
op_ne
id|NCP_SYMLINK_MAGIC0
op_logical_or
(paren
(paren
id|__u32
op_star
)paren
id|link
)paren
(braket
l_int|1
)braket
op_ne
id|NCP_SYMLINK_MAGIC1
)paren
(brace
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
id|link
(braket
id|length
)braket
op_assign
l_int|0
suffix:semicolon
id|vol2io
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|link
op_plus
l_int|8
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* UPDATE_ATIME(inode); */
id|base
op_assign
id|lookup_dentry
c_func
(paren
id|link
op_plus
l_int|8
comma
id|base
comma
id|follow
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
multiline_comment|/* ----- read symbolic link ---------------------------------------------- */
DECL|function|ncp_readlink
r_static
r_int
id|ncp_readlink
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
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
r_int
id|length
comma
id|error
suffix:semicolon
macro_line|#ifdef DEBUG
id|PRINTK
c_func
(paren
l_string|&quot;ncp_readlink(dentry=%p,buffer=%p,buflen=%d)&bslash;n&quot;
comma
id|dentry
comma
id|buffer
comma
id|buflen
)paren
suffix:semicolon
macro_line|#endif
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDONLY
)paren
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|link
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|NCP_MAX_SYMLINK_SIZE
op_plus
l_int|1
comma
id|GFP_NFS
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
id|ncp_read_kernel
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
l_int|0
comma
id|NCP_MAX_SYMLINK_SIZE
comma
id|link
comma
op_amp
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
op_logical_or
id|length
OL
id|NCP_MIN_SYMLINK_SIZE
op_logical_or
id|buflen
OL
(paren
id|length
op_minus
l_int|8
)paren
op_logical_or
(paren
(paren
id|__u32
op_star
)paren
id|link
)paren
(braket
l_int|0
)braket
op_ne
id|NCP_SYMLINK_MAGIC0
op_logical_or
(paren
(paren
id|__u32
op_star
)paren
id|link
)paren
(braket
l_int|1
)braket
op_ne
id|NCP_SYMLINK_MAGIC1
)paren
(brace
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|link
(braket
id|length
)braket
op_assign
l_int|0
suffix:semicolon
id|vol2io
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|link
op_plus
l_int|8
comma
l_int|0
)paren
suffix:semicolon
id|error
op_assign
id|length
op_minus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|link
op_plus
l_int|8
comma
id|error
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|out
suffix:colon
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* ----- create a new symbolic link -------------------------------------- */
DECL|function|ncp_symlink
r_int
id|ncp_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_int
id|i
comma
id|length
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
macro_line|#ifdef DEBUG
id|PRINTK
c_func
(paren
l_string|&quot;ncp_symlink(dir=%p,dentry=%p,symname=%s)&bslash;n&quot;
comma
id|dir
comma
id|dentry
comma
id|symname
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|NCP_SERVER
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|m.flags
op_amp
id|NCP_MOUNT_SYMLINKS
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* EPERM is returned by VFS if symlink procedure does not exist */
r_if
c_cond
(paren
(paren
id|length
op_assign
id|strlen
c_func
(paren
id|symname
)paren
)paren
OG
id|NCP_MAX_SYMLINK_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|link
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|length
op_plus
l_int|9
comma
id|GFP_NFS
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|ncp_create_new
c_func
(paren
id|dir
comma
id|dentry
comma
l_int|0
comma
id|aSHARED
op_or
id|aHIDDEN
)paren
)paren
(brace
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
(paren
(paren
id|__u32
op_star
)paren
id|link
)paren
(braket
l_int|0
)braket
op_assign
id|NCP_SYMLINK_MAGIC0
suffix:semicolon
(paren
(paren
id|__u32
op_star
)paren
id|link
)paren
(braket
l_int|1
)braket
op_assign
id|NCP_SYMLINK_MAGIC1
suffix:semicolon
id|memcpy
c_func
(paren
id|link
op_plus
l_int|8
comma
id|symname
comma
id|length
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* including last zero for io2vol */
multiline_comment|/* map to/from server charset, do not touch upper/lower case as&n;&t;   symlink can point out of ncp filesystem */
id|io2vol
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|link
op_plus
l_int|8
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncp_write_kernel
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
l_int|0
comma
id|length
op_plus
l_int|8
comma
id|link
comma
op_amp
id|i
)paren
op_logical_or
id|i
op_ne
id|length
op_plus
l_int|8
)paren
(brace
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* ----- EOF ----- */
eof
