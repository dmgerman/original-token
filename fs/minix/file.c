multiline_comment|/*&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix regular file handling primitives&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
multiline_comment|/*&n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|minix_file_write
id|minix_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
comma
id|block_write_partial_page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the minix filesystem.&n; */
DECL|variable|minix_file_operations
r_static
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
id|minix_file_write
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
op_amp
id|minix_file_operations
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
id|minix_get_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
id|block_write_full_page
comma
multiline_comment|/* writepage */
id|minix_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
