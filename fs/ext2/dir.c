multiline_comment|/*&n; *  linux/fs/ext2/dir.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/dir.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 directory handling functions&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|function|ext2_dir_read
r_static
r_int
id|ext2_dir_read
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
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_return
op_minus
id|EISDIR
suffix:semicolon
)brace
r_static
r_int
id|ext2_readdir
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
DECL|variable|ext2_dir_operations
r_static
r_struct
id|file_operations
id|ext2_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|ext2_dir_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|ext2_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
id|ext2_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
id|file_fsync
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
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|ext2_dir_inode_operations
r_struct
id|inode_operations
id|ext2_dir_inode_operations
op_assign
(brace
op_amp
id|ext2_dir_operations
comma
multiline_comment|/* default directory file-ops */
id|ext2_create
comma
multiline_comment|/* create */
id|ext2_lookup
comma
multiline_comment|/* lookup */
id|ext2_link
comma
multiline_comment|/* link */
id|ext2_unlink
comma
multiline_comment|/* unlink */
id|ext2_symlink
comma
multiline_comment|/* symlink */
id|ext2_mkdir
comma
multiline_comment|/* mkdir */
id|ext2_rmdir
comma
multiline_comment|/* rmdir */
id|ext2_mknod
comma
multiline_comment|/* mknod */
id|ext2_rename
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
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
id|ext2_truncate
comma
multiline_comment|/* truncate */
id|ext2_permission
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|function|ext2_check_dir_entry
r_int
id|ext2_check_dir_entry
(paren
r_const
r_char
op_star
id|function
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|ext2_dir_entry
op_star
id|de
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
r_int
id|offset
)paren
(brace
r_const
r_char
op_star
id|error_msg
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
OL
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
id|error_msg
op_assign
l_string|&quot;rec_len is smaller than minimal&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
op_mod
l_int|4
op_ne
l_int|0
)paren
id|error_msg
op_assign
l_string|&quot;rec_len % 4 != 0&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
OL
id|EXT2_DIR_REC_LEN
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|de-&gt;name_len
)paren
)paren
)paren
id|error_msg
op_assign
l_string|&quot;rec_len is too small for name_len&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir
op_logical_and
(paren
(paren
r_char
op_star
)paren
id|de
op_minus
id|bh-&gt;b_data
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
OG
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
id|error_msg
op_assign
l_string|&quot;directory entry across blocks&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir
op_logical_and
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
OG
id|le32_to_cpu
c_func
(paren
id|dir-&gt;i_sb-&gt;u.ext2_sb.s_es-&gt;s_inodes_count
)paren
)paren
id|error_msg
op_assign
l_string|&quot;inode out of bounds&quot;
suffix:semicolon
r_if
c_cond
(paren
id|error_msg
op_ne
l_int|NULL
)paren
id|ext2_error
(paren
id|dir-&gt;i_sb
comma
id|function
comma
l_string|&quot;bad entry in directory #%lu: %s - &quot;
l_string|&quot;offset=%lu, inode=%lu, rec_len=%d, name_len=%d&quot;
comma
id|dir-&gt;i_ino
comma
id|error_msg
comma
id|offset
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
comma
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
comma
id|le16_to_cpu
c_func
(paren
id|de-&gt;name_len
)paren
)paren
suffix:semicolon
r_return
id|error_msg
op_eq
l_int|NULL
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ext2_readdir
r_static
r_int
id|ext2_readdir
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
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
comma
id|blk
suffix:semicolon
r_int
id|i
comma
id|num
comma
id|stored
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|tmp
comma
op_star
id|bha
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|ext2_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|stored
op_assign
l_int|0
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|error
op_logical_and
op_logical_neg
id|stored
op_logical_and
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
id|blk
op_assign
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|EXT2_BLOCK_SIZE_BITS
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bh
op_assign
id|ext2_bread
(paren
id|inode
comma
id|blk
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_readdir&quot;
comma
l_string|&quot;directory #%lu contains a hole at offset %lu&quot;
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|filp-&gt;f_pos
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|sb-&gt;s_blocksize
op_minus
id|offset
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Do the readahead&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|16
op_rshift
(paren
id|EXT2_BLOCK_SIZE_BITS
c_func
(paren
id|sb
)paren
op_minus
l_int|9
)paren
comma
id|num
op_assign
l_int|0
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|tmp
op_assign
id|ext2_getblk
(paren
id|inode
comma
op_increment
id|blk
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|tmp
)paren
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
id|tmp
)paren
)paren
id|bha
(braket
id|num
op_increment
)braket
op_assign
id|tmp
suffix:semicolon
r_else
id|brelse
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num
)paren
(brace
id|ll_rw_block
(paren
id|READA
comma
id|num
comma
id|bha
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|bha
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|revalidate
suffix:colon
multiline_comment|/* If the dir block has changed since the last call to&n;&t;&t; * readdir(2), then we might be pointing to an invalid&n;&t;&t; * dirent right now.  Scan from the start of the block&n;&t;&t; * to make sure. */
r_if
c_cond
(paren
id|filp-&gt;f_version
op_ne
id|inode-&gt;i_version
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sb-&gt;s_blocksize
op_logical_and
id|i
OL
id|offset
suffix:semicolon
)paren
(brace
id|de
op_assign
(paren
r_struct
id|ext2_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* It&squot;s too expensive to do a full&n;&t;&t;&t;&t; * dirent test each time round this&n;&t;&t;&t;&t; * loop, but we do have to test at&n;&t;&t;&t;&t; * least that it is non-zero.  A&n;&t;&t;&t;&t; * failure will be detected in the&n;&t;&t;&t;&t; * dirent test below. */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
OL
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
r_break
suffix:semicolon
id|i
op_add_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|i
suffix:semicolon
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_amp
op_complement
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_or
id|offset
suffix:semicolon
id|filp-&gt;f_version
op_assign
id|inode-&gt;i_version
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|error
op_logical_and
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
op_logical_and
id|offset
OL
id|sb-&gt;s_blocksize
)paren
(brace
id|de
op_assign
(paren
r_struct
id|ext2_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ext2_check_dir_entry
(paren
l_string|&quot;ext2_readdir&quot;
comma
id|inode
comma
id|de
comma
id|bh
comma
id|offset
)paren
)paren
(brace
multiline_comment|/* On error, skip the f_pos to the&n;                                   next block. */
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
op_plus
id|sb-&gt;s_blocksize
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|stored
suffix:semicolon
)brace
id|offset
op_add_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
)paren
(brace
multiline_comment|/* We might block in the next section&n;&t;&t;&t;&t; * if the data destination is&n;&t;&t;&t;&t; * currently swapped out.  So, use a&n;&t;&t;&t;&t; * version stamp to detect whether or&n;&t;&t;&t;&t; * not the directory has been modified&n;&t;&t;&t;&t; * during the copy operation. */
r_int
r_int
id|version
suffix:semicolon
id|dcache_add
c_func
(paren
id|inode
comma
id|de-&gt;name
comma
id|le16_to_cpu
c_func
(paren
id|de-&gt;name_len
)paren
comma
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
)paren
suffix:semicolon
id|version
op_assign
id|inode-&gt;i_version
suffix:semicolon
id|error
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;name
comma
id|le16_to_cpu
c_func
(paren
id|de-&gt;name_len
)paren
comma
id|filp-&gt;f_pos
comma
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|version
op_ne
id|inode-&gt;i_version
)paren
r_goto
id|revalidate
suffix:semicolon
id|stored
op_increment
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_add_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DO_UPDATE_ATIME
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
