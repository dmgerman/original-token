multiline_comment|/*&n; *  linux/fs/adfs/file.c&n; *&n; * Copyright (C) 1997 Russell King&n; * from:&n; *&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  adfs regular file handling primitives           &n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
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
multiline_comment|/* lseek - default&t;*/
id|generic_file_read
comma
multiline_comment|/* read&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* write&t;&t;*/
l_int|NULL
comma
multiline_comment|/* readdir - bad&t;*/
l_int|NULL
comma
multiline_comment|/* select - default&t;*/
l_int|NULL
comma
multiline_comment|/* ioctl&t;&t;*/
id|generic_file_mmap
comma
multiline_comment|/* mmap&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* open - not special&t;*/
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
l_int|NULL
comma
multiline_comment|/* check_media_change&t;*/
l_int|NULL
multiline_comment|/* revalidate&t;&t;*/
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
multiline_comment|/* default file operations&t;*/
l_int|NULL
comma
multiline_comment|/* create&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* lookup&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* link&t;&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* unlink&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* symlink&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* mkdir&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* rmdir&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* mknod&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* rename&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* readlink&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* follow_link&t;&t;&t;*/
id|adfs_bmap
comma
multiline_comment|/* bmap&t;&t;&t;&t;*/
id|block_read_full_page
comma
multiline_comment|/* readpage&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* writepage&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* flushpage&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* truncate&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* permission&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* smap&t;&t;&t;&t;*/
l_int|NULL
multiline_comment|/* revalidate&t;&t;&t;*/
)brace
suffix:semicolon
eof
