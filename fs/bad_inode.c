multiline_comment|/*&n; *  linux/fs/bad_inode.c&n; *&n; *  Copyright (C) 1997, Stephen Tweedie&n; *&n; *  Provide stub functions for unreadable inodes&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * The follow_link operation is special: it must behave as a no-op&n; * so that a bad root inode can at least be unmounted. To do this&n; * we must dput() the base and return the dentry with a dget().&n; */
DECL|function|bad_follow_link
r_static
r_struct
id|dentry
op_star
id|bad_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dent
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
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|dget
c_func
(paren
id|dent
)paren
suffix:semicolon
)brace
DECL|function|return_EIO
r_static
r_int
id|return_EIO
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|macro|EIO_ERROR
mdefine_line|#define EIO_ERROR ((void *) (return_EIO))
DECL|variable|bad_file_ops
r_static
r_struct
id|file_operations
id|bad_file_ops
op_assign
(brace
id|llseek
suffix:colon
id|EIO_ERROR
comma
id|read
suffix:colon
id|EIO_ERROR
comma
id|write
suffix:colon
id|EIO_ERROR
comma
id|readdir
suffix:colon
id|EIO_ERROR
comma
id|poll
suffix:colon
id|EIO_ERROR
comma
id|ioctl
suffix:colon
id|EIO_ERROR
comma
id|mmap
suffix:colon
id|EIO_ERROR
comma
id|open
suffix:colon
id|EIO_ERROR
comma
id|flush
suffix:colon
id|EIO_ERROR
comma
id|release
suffix:colon
id|EIO_ERROR
comma
id|fsync
suffix:colon
id|EIO_ERROR
comma
id|fasync
suffix:colon
id|EIO_ERROR
comma
id|lock
suffix:colon
id|EIO_ERROR
comma
)brace
suffix:semicolon
DECL|variable|bad_inode_ops
r_struct
id|inode_operations
id|bad_inode_ops
op_assign
(brace
op_amp
id|bad_file_ops
comma
multiline_comment|/* default file operations */
id|EIO_ERROR
comma
multiline_comment|/* create */
id|EIO_ERROR
comma
multiline_comment|/* lookup */
id|EIO_ERROR
comma
multiline_comment|/* link */
id|EIO_ERROR
comma
multiline_comment|/* unlink */
id|EIO_ERROR
comma
multiline_comment|/* symlink */
id|EIO_ERROR
comma
multiline_comment|/* mkdir */
id|EIO_ERROR
comma
multiline_comment|/* rmdir */
id|EIO_ERROR
comma
multiline_comment|/* mknod */
id|EIO_ERROR
comma
multiline_comment|/* rename */
id|EIO_ERROR
comma
multiline_comment|/* readlink */
id|bad_follow_link
comma
multiline_comment|/* follow_link */
id|EIO_ERROR
comma
multiline_comment|/* get_block */
id|EIO_ERROR
comma
multiline_comment|/* readpage */
id|EIO_ERROR
comma
multiline_comment|/* writepage */
id|EIO_ERROR
comma
multiline_comment|/* truncate */
id|EIO_ERROR
comma
multiline_comment|/* permission */
id|EIO_ERROR
multiline_comment|/* revalidate */
)brace
suffix:semicolon
multiline_comment|/* &n; * When a filesystem is unable to read an inode due to an I/O error in&n; * its read_inode() function, it can call make_bad_inode() to return a&n; * set of stubs which will return EIO errors as required. &n; *&n; * We only need to do limited initialisation: all other fields are&n; * preinitialised to zero automatically.&n; */
DECL|function|make_bad_inode
r_void
id|make_bad_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|bad_inode_ops
suffix:semicolon
)brace
multiline_comment|/*&n; * This tests whether an inode has been flagged as bad. The test uses&n; * &amp;bad_inode_ops to cover the case of invalidated inodes as well as&n; * those created by make_bad_inode() above.&n; */
DECL|function|is_bad_inode
r_int
id|is_bad_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|inode-&gt;i_op
op_eq
op_amp
id|bad_inode_ops
)paren
suffix:semicolon
)brace
eof
