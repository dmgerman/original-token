multiline_comment|/*&n; *  linux/fs/nfs/symlink.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  Optimization changes Copyright (C) 1994 Florian La Roche&n; *&n; *  nfs symlink handling code&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_int
id|nfs_readlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|nfs_symlink_inode_operations
r_struct
id|inode_operations
id|nfs_symlink_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file-operations */
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
id|nfs_readlink
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
DECL|function|nfs_readlink
r_static
r_int
id|nfs_readlink
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
id|error
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_char
op_star
id|res
suffix:semicolon
r_void
op_star
id|mem
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: readlink(%x/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OG
id|NFS_MAXPATHLEN
)paren
id|buflen
op_assign
id|NFS_MAXPATHLEN
suffix:semicolon
id|error
op_assign
id|nfs_proc_readlink
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
op_amp
id|mem
comma
op_amp
id|res
comma
op_amp
id|len
comma
id|buflen
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|copy_to_user
c_func
(paren
id|buffer
comma
id|res
comma
id|len
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_char|&squot;&bslash;0&squot;
comma
id|buffer
op_plus
id|len
)paren
suffix:semicolon
id|error
op_assign
id|len
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
