multiline_comment|/*&n; *  linux/fs/isofs/file.c&n; *&n; *  (C) 1992, 1993, 1994  Eric Youngdale Modified for ISO 9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; *&n; *  isofs regular file handling primitives&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the isofs filesystem.&n; */
DECL|variable|isofs_file_operations
r_static
r_struct
id|file_operations
id|isofs_file_operations
op_assign
(brace
id|read
suffix:colon
id|generic_file_read
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
)brace
suffix:semicolon
DECL|variable|isofs_file_inode_operations
r_struct
id|inode_operations
id|isofs_file_inode_operations
op_assign
(brace
op_amp
id|isofs_file_operations
comma
multiline_comment|/* default file operations */
)brace
suffix:semicolon
eof
