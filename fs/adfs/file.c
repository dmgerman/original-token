multiline_comment|/*&n; *  linux/fs/adfs/file.c&n; *&n; * Copyright (C) 1997-1999 Russell King&n; * from:&n; *&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  adfs regular file handling primitives           &n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;adfs.h&quot;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
multiline_comment|/*&n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|adfs_file_write
id|adfs_file_write
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
id|ssize_t
id|retval
suffix:semicolon
id|retval
op_assign
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
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the adfs filesystem.&n; */
DECL|variable|adfs_file_operations
r_static
r_struct
id|file_operations
id|adfs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek&t;&t;*/
id|generic_file_read
comma
multiline_comment|/* read&t;&t;&t;*/
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
id|adfs_file_write
comma
multiline_comment|/* write&t;&t;*/
macro_line|#else
l_int|NULL
comma
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* readdir&t;&t;*/
l_int|NULL
comma
multiline_comment|/* poll&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* ioctl&t;&t;*/
id|generic_file_mmap
comma
multiline_comment|/* mmap&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* open&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* flush&t;&t;*/
l_int|NULL
comma
multiline_comment|/* release&t;&t;*/
id|file_fsync
comma
multiline_comment|/* fsync&t;&t;*/
l_int|NULL
comma
multiline_comment|/* fasync&t;&t;*/
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
l_int|NULL
comma
multiline_comment|/* create&t;&t;*/
l_int|NULL
comma
multiline_comment|/* lookup&t;&t;*/
l_int|NULL
comma
multiline_comment|/* link&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* unlink&t;&t;*/
l_int|NULL
comma
multiline_comment|/* symlink&t;&t;*/
l_int|NULL
comma
multiline_comment|/* mkdir&t;&t;*/
l_int|NULL
comma
multiline_comment|/* rmdir&t;&t;*/
l_int|NULL
comma
multiline_comment|/* mknod&t;&t;*/
l_int|NULL
comma
multiline_comment|/* rename&t;&t;*/
l_int|NULL
comma
multiline_comment|/* readlink&t;&t;*/
l_int|NULL
comma
multiline_comment|/* follow_link&t;&t;*/
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
id|adfs_get_block
comma
multiline_comment|/* bmap&t;&t;&t;*/
id|block_read_full_page
comma
multiline_comment|/* readpage&t;&t;*/
id|block_write_full_page
comma
multiline_comment|/* writepage&t;&t;*/
macro_line|#else
id|generic_readpage
comma
multiline_comment|/* readpage&t;&t;*/
l_int|NULL
comma
multiline_comment|/* writepage&t;&t;*/
id|adfs_bmap
comma
multiline_comment|/* bmap&t;&t;&t;*/
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* truncate&t;&t;*/
l_int|NULL
comma
multiline_comment|/* permission&t;&t;*/
l_int|NULL
comma
multiline_comment|/* revalidate&t;&t;*/
)brace
suffix:semicolon
eof
