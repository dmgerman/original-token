multiline_comment|/*&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix regular file handling primitives&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the minix filesystem.&n; */
DECL|variable|minix_file_operations
r_struct
id|file_operations
id|minix_file_operations
op_assign
(brace
id|read
suffix:colon
id|generic_file_read
comma
id|write
suffix:colon
id|generic_file_write
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|fsync
suffix:colon
id|minix_sync_file
comma
)brace
suffix:semicolon
DECL|variable|minix_file_inode_operations
r_struct
id|inode_operations
id|minix_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|minix_truncate
comma
)brace
suffix:semicolon
eof
