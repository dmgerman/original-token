multiline_comment|/*&n; * Pioctl operations for Coda.&n; * Original version: (C) 1996 Peter Braam &n; * Rewritten for Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
multiline_comment|/* pioctl ops */
r_static
r_int
id|coda_ioctl_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
r_static
r_int
id|coda_ioctl_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_static
r_int
id|coda_ioctl_release
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_static
r_int
id|coda_pioctl
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
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* exported from this file */
DECL|variable|coda_ioctl_inode_operations
r_struct
id|inode_operations
id|coda_ioctl_inode_operations
op_assign
(brace
op_amp
id|coda_ioctl_operations
comma
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
multiline_comment|/* get_block */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* flushpage */
l_int|NULL
comma
multiline_comment|/* truncate */
id|coda_ioctl_permission
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|coda_ioctl_operations
r_struct
id|file_operations
id|coda_ioctl_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default should work for coda */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
id|coda_pioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|coda_ioctl_open
comma
multiline_comment|/* open */
l_int|NULL
comma
id|coda_ioctl_release
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
)brace
suffix:semicolon
multiline_comment|/* the coda pioctl inode ops */
DECL|function|coda_ioctl_permission
r_static
r_int
id|coda_ioctl_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
id|ENTRY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The pioctl file ops*/
DECL|function|coda_ioctl_open
r_int
id|coda_ioctl_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
id|ENTRY
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;File inode number: %ld&bslash;n&quot;
comma
id|f-&gt;f_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_ioctl_release
r_int
id|coda_ioctl_release
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_pioctl
r_static
r_int
id|coda_pioctl
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
r_int
r_int
id|cmd
comma
r_int
r_int
id|user_data
)paren
(brace
r_struct
id|dentry
op_star
id|target_de
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|PioctlData
id|data
suffix:semicolon
r_struct
id|inode
op_star
id|target_inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cnp
suffix:semicolon
id|ENTRY
suffix:semicolon
multiline_comment|/* get the Pioctl data arguments from user space */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
(paren
r_int
op_star
)paren
id|user_data
comma
r_sizeof
(paren
id|data
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* &n;         * Look up the pathname. Note that the pathname is in &n;         * user memory, and namei takes care of this&n;         */
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;namei, data.follow = %d&bslash;n&quot;
comma
id|data.follow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data.follow
)paren
(brace
id|target_de
op_assign
id|namei
c_func
(paren
id|data.path
)paren
suffix:semicolon
)brace
r_else
(brace
id|target_de
op_assign
id|lnamei
c_func
(paren
id|data.path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|target_de
)paren
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;error: lookup fails.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|target_de
)paren
suffix:semicolon
)brace
r_else
(brace
id|target_inode
op_assign
id|target_de-&gt;d_inode
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;target ino: 0x%ld, dev: 0x%d&bslash;n&quot;
comma
id|target_inode-&gt;i_ino
comma
id|target_inode-&gt;i_dev
)paren
suffix:semicolon
multiline_comment|/* return if it is not a Coda inode */
r_if
c_cond
(paren
id|target_inode-&gt;i_sb
op_ne
id|inode-&gt;i_sb
)paren
(brace
r_if
c_cond
(paren
id|target_de
)paren
id|dput
c_func
(paren
id|target_de
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* now proceed to make the upcall */
id|cnp
op_assign
id|ITOC
c_func
(paren
id|target_inode
)paren
suffix:semicolon
id|error
op_assign
id|venus_pioctl
c_func
(paren
id|inode-&gt;i_sb
comma
op_amp
(paren
id|cnp-&gt;c_fid
)paren
comma
id|cmd
comma
op_amp
id|data
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;ioctl on inode %ld&bslash;n&quot;
comma
id|target_inode-&gt;i_ino
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_DOWNCALL
comma
l_string|&quot;dput on ino: %ld, icount %d, dcount %d&bslash;n&quot;
comma
id|target_inode-&gt;i_ino
comma
id|target_inode-&gt;i_count
comma
id|target_de-&gt;d_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_de
)paren
id|dput
c_func
(paren
id|target_de
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
