multiline_comment|/*&n; *  linux/fs/adfs/file.c&n; *&n; * Copyright (C) 1997-1999 Russell King&n; * from:&n; *&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  adfs regular file handling primitives           &n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;adfs.h&quot;
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the adfs filesystem.&n; */
DECL|variable|adfs_file_operations
r_static
r_struct
id|file_operations
id|adfs_file_operations
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
id|fsync
suffix:colon
id|file_fsync
comma
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
id|write
suffix:colon
id|generic_file_write
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|adfs_file_inode_operations
r_struct
id|inode_operations
id|adfs_file_inode_operations
op_assign
(brace
op_amp
id|adfs_file_operations
comma
multiline_comment|/* default file operations */
)brace
suffix:semicolon
eof
