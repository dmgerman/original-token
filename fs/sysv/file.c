multiline_comment|/*&n; *  linux/fs/sysv/file.c&n; *&n; *  minix/file.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/file.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/file.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent regular file handling primitives&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
multiline_comment|/*&n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|sysv_file_write
id|sysv_file_write
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
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the coh filesystem.&n; */
DECL|variable|sysv_file_operations
r_static
r_struct
id|file_operations
id|sysv_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|generic_file_read
comma
multiline_comment|/* read */
id|sysv_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* poll - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* release */
id|sysv_sync_file
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
)brace
suffix:semicolon
DECL|variable|sysv_file_inode_operations
r_struct
id|inode_operations
id|sysv_file_inode_operations
op_assign
(brace
op_amp
id|sysv_file_operations
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
id|sysv_get_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
id|block_write_full_page
comma
multiline_comment|/* writepage */
id|sysv_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
