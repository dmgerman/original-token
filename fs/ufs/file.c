multiline_comment|/*&n; *  linux/fs/ufs/file.c&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  from&n; *&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 fs regular file handling primitives&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
multiline_comment|/*&n; * Make sure the offset never goes beyond the 32-bit mark..&n; */
DECL|function|ufs_file_lseek
r_static
r_int
r_int
id|ufs_file_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|origin
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* make sure the offset fits in 32 bits */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
r_int
)paren
id|offset
op_rshift
l_int|32
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|file-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
id|file-&gt;f_version
op_assign
op_increment
id|event
suffix:semicolon
)brace
id|retval
op_assign
id|offset
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|remove_suid
r_static
r_inline
r_void
id|remove_suid
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* set S_IGID if S_IXGRP is set, and always set S_ISUID */
id|mode
op_assign
(paren
id|inode-&gt;i_mode
op_amp
id|S_IXGRP
)paren
op_star
(paren
id|S_ISGID
op_div
id|S_IXGRP
)paren
op_or
id|S_ISUID
suffix:semicolon
multiline_comment|/* was any of the uid bits set? */
id|mode
op_and_assign
id|inode-&gt;i_mode
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
(brace
id|inode-&gt;i_mode
op_and_assign
op_complement
id|mode
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|ufs_file_write
id|ufs_file_write
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
id|remove_suid
c_func
(paren
id|inode
)paren
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
multiline_comment|/*&n; * Called when an inode is released. Note that this is different&n; * from ufs_open: open gets called at every open, but release&n; * gets called only when /all/ the files are closed.&n; */
DECL|function|ufs_release_file
r_static
r_int
id|ufs_release_file
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the ufs filesystem.&n; */
DECL|variable|ufs_file_operations
r_static
r_struct
id|file_operations
id|ufs_file_operations
op_assign
(brace
id|ufs_file_lseek
comma
multiline_comment|/* lseek */
id|generic_file_read
comma
multiline_comment|/* read */
id|ufs_file_write
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
multiline_comment|/* ioctl */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* flush */
id|ufs_release_file
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|ufs_file_inode_operations
r_struct
id|inode_operations
id|ufs_file_inode_operations
op_assign
(brace
op_amp
id|ufs_file_operations
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
id|ufs_getfrag_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
id|block_write_full_page
comma
multiline_comment|/* writepage */
id|block_flushpage
comma
multiline_comment|/* flushpage */
id|ufs_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
