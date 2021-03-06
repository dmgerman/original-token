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
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
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
suffix:semicolon
multiline_comment|/* exported from this file */
DECL|variable|coda_ioctl_inode_operations
r_struct
id|inode_operations
id|coda_ioctl_inode_operations
op_assign
(brace
id|permission
suffix:colon
id|coda_ioctl_permission
comma
id|setattr
suffix:colon
id|coda_notify_change
comma
)brace
suffix:semicolon
DECL|variable|coda_ioctl_operations
r_struct
id|file_operations
id|coda_ioctl_operations
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|ioctl
suffix:colon
id|coda_pioctl
comma
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
id|nameidata
id|nd
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
id|error
op_assign
id|user_path_walk
c_func
(paren
id|data.path
comma
op_amp
id|nd
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|user_path_walk_link
c_func
(paren
id|data.path
comma
op_amp
id|nd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
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
id|error
suffix:semicolon
)brace
r_else
(brace
id|target_inode
op_assign
id|nd.dentry-&gt;d_inode
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_PIOCTL
comma
l_string|&quot;target ino: 0x%ld, dev: 0x%x&bslash;n&quot;
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
id|path_release
c_func
(paren
op_amp
id|nd
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
id|atomic_read
c_func
(paren
op_amp
id|target_inode-&gt;i_count
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|nd.dentry-&gt;d_count
)paren
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
