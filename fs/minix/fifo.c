multiline_comment|/*&n; *  linux/fs/fifo.c&n; *&n; *  written by Paul H. Hargrove&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
r_extern
r_struct
id|file_operations
id|def_fifo_fops
suffix:semicolon
DECL|variable|minix_fifo_inode_operations
r_struct
id|inode_operations
id|minix_fifo_inode_operations
op_assign
(brace
op_amp
id|def_fifo_fops
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
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
eof
