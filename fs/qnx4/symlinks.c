multiline_comment|/* &n; * QNX4 file system, Linux implementation.&n; * &n; * Version : 0.2.1&n; * &n; * Using parts of the xiafs filesystem.&n; * &n; * History :&n; * &n; * 28-05-1998 by Richard Frowijn : first release.&n; * 21-06-1998 by Frank Denis : ugly changes to make it compile on Linux 2.1.99+&n; */
multiline_comment|/* THIS FILE HAS TO BE REWRITTEN */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_int
id|qnx4_readlink
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
id|qnx4_follow_link
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
id|follow
)paren
suffix:semicolon
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|qnx4_symlink_inode_operations
r_struct
id|inode_operations
id|qnx4_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|page_readlink
comma
id|follow_link
suffix:colon
id|page_follow_link
comma
id|get_block
suffix:colon
id|qnx4_get_block
comma
id|readpage
suffix:colon
id|block_read_full_page
comma
)brace
suffix:semicolon
eof
