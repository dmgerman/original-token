multiline_comment|/*&n; *  linux/fs/ext2/fsync.c&n; *&n; *  Copyright (C) 1993  Stephen Tweedie (sct@dcs.ed.ac.uk)&n; *  from&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *                      Laboratoire MASI - Institut Blaise Pascal&n; *                      Universite Pierre et Marie Curie (Paris VI)&n; *  from&n; *  linux/fs/minix/truncate.c   Copyright (C) 1991, 1992  Linus Torvalds&n; * &n; *  ext2fs fsync primitive&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; * &n; *  Removed unnecessary code duplication for little endian machines&n; *  and excessive __inline__s. &n; *        Andi Kleen, 1997&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
DECL|macro|blocksize
mdefine_line|#define blocksize (EXT2_BLOCK_SIZE(inode-&gt;i_sb))
DECL|macro|addr_per_block
mdefine_line|#define addr_per_block (EXT2_ADDR_PER_BLOCK(inode-&gt;i_sb))
DECL|function|sync_block
r_static
r_int
id|sync_block
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|block
comma
r_int
id|wait
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|block
)paren
r_return
l_int|0
suffix:semicolon
id|bh
op_assign
id|get_hash_table
(paren
id|inode-&gt;i_dev
comma
op_star
id|block
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|wait
op_logical_and
id|buffer_req
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wait
op_logical_or
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_logical_or
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|bh-&gt;b_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sync_direct
r_static
r_int
id|sync_direct
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
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
id|EXT2_NDIR_BLOCKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_block
(paren
id|inode
comma
id|inode-&gt;u.ext2_i.i_data
op_plus
id|i
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|err
op_assign
id|rc
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;File may be NULL when we are called. Perhaps we shouldn&squot;t&n; *&t;even pass file to fsync ?&n; *&n; *&t;This currently falls back to synching the whole device when&n; *&t;the file is larger than can fit directly in the inode. This&n; *&t;is because dirty-buffer handling is indexed by the device&n; *&t;of the buffer, which makes it much faster to sync the whole&n; *&t;device than to sync just one large file.&n; */
DECL|function|ext2_sync_file
r_int
id|ext2_sync_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|wait
comma
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
(paren
id|inode-&gt;i_blocks
)paren
)paren
multiline_comment|/*&n;&t;&t; * Don&squot;t sync fast links!&n;&t;&t; */
r_goto
id|skip
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OG
id|EXT2_NDIR_BLOCKS
op_star
id|blocksize
)paren
(brace
id|err
op_assign
id|fsync_dev
c_func
(paren
id|inode-&gt;i_dev
)paren
suffix:semicolon
r_goto
id|skip
suffix:semicolon
)brace
r_for
c_loop
(paren
id|wait
op_assign
l_int|0
suffix:semicolon
id|wait
op_le
l_int|1
suffix:semicolon
id|wait
op_increment
)paren
(brace
id|err
op_or_assign
id|sync_direct
(paren
id|inode
comma
id|wait
)paren
suffix:semicolon
)brace
id|skip
suffix:colon
id|err
op_or_assign
id|ext2_sync_inode
(paren
id|inode
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
