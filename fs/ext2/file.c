multiline_comment|/*&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 fs regular file handling primitives&n; *&n; *  64-bit file support on 64-bit platforms by Jakub Jelinek&n; * &t;(jj@sunsite.ms.mff.cuni.cz)&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
r_static
r_int
id|ext2_writepage
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_static
r_int
r_int
id|ext2_file_lseek
c_func
(paren
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &lt; 64
r_static
r_int
id|ext2_open_file
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|EXT2_MAX_SIZE
mdefine_line|#define EXT2_MAX_SIZE(bits)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((EXT2_NDIR_BLOCKS + (1LL &lt;&lt; (bits - 2)) + &t;&t;&t;&t;&bslash;&n;&t;   (1LL &lt;&lt; (bits - 2)) * (1LL &lt;&lt; (bits - 2)) + &t;&t;&t;&t;&bslash;&n;&t;   (1LL &lt;&lt; (bits - 2)) * (1LL &lt;&lt; (bits - 2)) * (1LL &lt;&lt; (bits - 2))) * &t;&bslash;&n;&t;  (1LL &lt;&lt; bits)) - 1)
DECL|variable|ext2_max_sizes
r_static
r_int
r_int
id|ext2_max_sizes
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|EXT2_MAX_SIZE
c_func
(paren
l_int|10
)paren
comma
id|EXT2_MAX_SIZE
c_func
(paren
l_int|11
)paren
comma
id|EXT2_MAX_SIZE
c_func
(paren
l_int|12
)paren
comma
id|EXT2_MAX_SIZE
c_func
(paren
l_int|13
)paren
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Make sure the offset never goes beyond the 32-bit mark..&n; */
DECL|function|ext2_file_lseek
r_static
r_int
r_int
id|ext2_file_lseek
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
op_ne
l_int|0
)paren
(brace
macro_line|#if BITS_PER_LONG &lt; 64
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|offset
OG
id|ext2_max_sizes
(braket
id|EXT2_BLOCK_SIZE_BITS
c_func
(paren
id|inode-&gt;i_sb
)paren
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
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
r_return
id|offset
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
id|capable
c_func
(paren
id|CAP_FSETID
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
DECL|function|ext2_writepage
r_static
r_int
id|ext2_writepage
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|file
comma
id|page
comma
id|ext2_getblk_block
)paren
suffix:semicolon
)brace
DECL|function|ext2_write_one_page
r_static
r_int
id|ext2_write_one_page
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|bytes
comma
r_const
r_char
op_star
id|buf
)paren
(brace
r_return
id|block_write_one_page
c_func
(paren
id|file
comma
id|page
comma
id|offset
comma
id|bytes
comma
id|buf
comma
id|ext2_getblk_block
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|ext2_file_write
id|ext2_file_write
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
id|ext2_write_one_page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when an inode is released. Note that this is different&n; * from ext2_file_open: open gets called at every open, but release&n; * gets called only when /all/ the files are closed.&n; */
DECL|function|ext2_release_file
r_static
r_int
id|ext2_release_file
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
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|ext2_discard_prealloc
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if BITS_PER_LONG &lt; 64
multiline_comment|/*&n; * Called when an inode is about to be open.&n; * We use this to disallow opening RW large files on 32bit systems.&n; */
DECL|function|ext2_open_file
r_static
r_int
id|ext2_open_file
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
r_if
c_cond
(paren
id|inode-&gt;u.ext2_i.i_high_size
op_logical_and
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the ext2 filesystem.&n; */
DECL|variable|ext2_file_operations
r_static
r_struct
id|file_operations
id|ext2_file_operations
op_assign
(brace
id|ext2_file_lseek
comma
multiline_comment|/* lseek */
id|generic_file_read
comma
multiline_comment|/* read */
id|ext2_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* poll - default */
id|ext2_ioctl
comma
multiline_comment|/* ioctl */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
macro_line|#if BITS_PER_LONG == 64&t;
l_int|NULL
comma
multiline_comment|/* no special open is needed */
macro_line|#else
id|ext2_open_file
comma
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* flush */
id|ext2_release_file
comma
multiline_comment|/* release */
id|ext2_sync_file
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
DECL|variable|ext2_file_inode_operations
r_struct
id|inode_operations
id|ext2_file_inode_operations
op_assign
(brace
op_amp
id|ext2_file_operations
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
id|generic_readpage
comma
multiline_comment|/* readpage */
id|ext2_writepage
comma
multiline_comment|/* writepage */
id|ext2_bmap
comma
multiline_comment|/* bmap */
id|ext2_truncate
comma
multiline_comment|/* truncate */
id|ext2_permission
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* updatepage */
l_int|NULL
comma
multiline_comment|/* revalidate */
id|generic_block_flushpage
comma
multiline_comment|/* flushpage */
)brace
suffix:semicolon
eof
