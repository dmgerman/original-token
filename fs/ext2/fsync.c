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
r_int
id|tmp
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
id|tmp
op_assign
op_star
id|block
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
op_star
id|block
op_ne
id|tmp
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
macro_line|#ifndef __LITTLE_ENDIAN
DECL|function|sync_block_swab32
r_static
r_int
id|sync_block_swab32
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
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|le32_to_cpu
c_func
(paren
op_star
id|block
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|le32_to_cpu
c_func
(paren
op_star
id|block
)paren
suffix:semicolon
id|bh
op_assign
id|get_hash_table
(paren
id|inode-&gt;i_dev
comma
id|le32_to_cpu
c_func
(paren
op_star
id|block
)paren
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
id|le32_to_cpu
c_func
(paren
op_star
id|block
)paren
op_ne
id|tmp
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
macro_line|#else
DECL|macro|sync_block_swab32
mdefine_line|#define sync_block_swab32 sync_block
macro_line|#endif
DECL|function|sync_iblock
r_static
r_int
id|sync_iblock
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|iblock
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_int
id|wait
)paren
(brace
r_int
id|rc
comma
id|tmp
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_assign
op_star
id|iblock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_block
(paren
id|inode
comma
id|iblock
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
op_star
id|bh
op_assign
id|bread
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_star
id|iblock
)paren
(brace
id|brelse
(paren
op_star
id|bh
)paren
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef __LITTLE_ENDIAN
DECL|function|sync_iblock_swab32
r_static
r_int
id|sync_iblock_swab32
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|iblock
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_int
id|wait
)paren
(brace
r_int
id|rc
comma
id|tmp
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|le32_to_cpu
c_func
(paren
op_star
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_block_swab32
(paren
id|inode
comma
id|iblock
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
op_star
id|bh
op_assign
id|bread
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|le32_to_cpu
c_func
(paren
op_star
id|iblock
)paren
)paren
(brace
id|brelse
(paren
op_star
id|bh
)paren
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|sync_iblock_swab32
mdefine_line|#define sync_iblock_swab32 sync_iblock
macro_line|#endif
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
OG
l_int|0
)paren
r_break
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
DECL|function|sync_indirect
r_static
r_int
id|sync_indirect
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|iblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|ind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock
(paren
id|inode
comma
id|iblock
comma
op_amp
id|ind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|ind_bh
)paren
r_return
id|rc
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
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_block_swab32
(paren
id|inode
comma
(paren
(paren
id|u32
op_star
)paren
id|ind_bh-&gt;b_data
)paren
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
OG
l_int|0
)paren
r_break
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
id|brelse
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifndef __LITTLE_ENDIAN
DECL|function|sync_indirect_swab32
r_static
id|__inline__
r_int
id|sync_indirect_swab32
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|iblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|ind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock_swab32
(paren
id|inode
comma
id|iblock
comma
op_amp
id|ind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|ind_bh
)paren
r_return
id|rc
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
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_block_swab32
(paren
id|inode
comma
(paren
(paren
id|u32
op_star
)paren
id|ind_bh-&gt;b_data
)paren
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
OG
l_int|0
)paren
r_break
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
id|brelse
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#else
DECL|macro|sync_indirect_swab32
mdefine_line|#define sync_indirect_swab32 sync_indirect
macro_line|#endif
DECL|function|sync_dindirect
r_static
r_int
id|sync_dindirect
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|diblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock
(paren
id|inode
comma
id|diblock
comma
op_amp
id|dind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|dind_bh
)paren
r_return
id|rc
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
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_indirect_swab32
(paren
id|inode
comma
(paren
(paren
id|u32
op_star
)paren
id|dind_bh-&gt;b_data
)paren
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
OG
l_int|0
)paren
r_break
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
id|brelse
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifndef __LITTLE_ENDIAN
DECL|function|sync_dindirect_swab32
r_static
id|__inline__
r_int
id|sync_dindirect_swab32
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|diblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock_swab32
(paren
id|inode
comma
id|diblock
comma
op_amp
id|dind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|dind_bh
)paren
r_return
id|rc
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
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_indirect_swab32
(paren
id|inode
comma
(paren
(paren
id|u32
op_star
)paren
id|dind_bh-&gt;b_data
)paren
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
OG
l_int|0
)paren
r_break
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
id|brelse
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#else
DECL|macro|sync_dindirect_swab32
mdefine_line|#define sync_dindirect_swab32 sync_dindirect
macro_line|#endif
DECL|function|sync_tindirect
r_static
r_int
id|sync_tindirect
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|tiblock
comma
r_int
id|wait
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|tind_bh
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|sync_iblock
(paren
id|inode
comma
id|tiblock
comma
op_amp
id|tind_bh
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
op_logical_neg
id|tind_bh
)paren
r_return
id|rc
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
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|sync_dindirect_swab32
(paren
id|inode
comma
(paren
(paren
id|u32
op_star
)paren
id|tind_bh-&gt;b_data
)paren
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
OG
l_int|0
)paren
r_break
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
id|brelse
(paren
id|tind_bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;File may be NULL when we are called. Perhaps we shouldn&squot;t&n; *&t;even pass file to fsync ?&n; */
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
id|err
op_or_assign
id|sync_indirect
(paren
id|inode
comma
id|inode-&gt;u.ext2_i.i_data
op_plus
id|EXT2_IND_BLOCK
comma
id|wait
)paren
suffix:semicolon
id|err
op_or_assign
id|sync_dindirect
(paren
id|inode
comma
id|inode-&gt;u.ext2_i.i_data
op_plus
id|EXT2_DIND_BLOCK
comma
id|wait
)paren
suffix:semicolon
id|err
op_or_assign
id|sync_tindirect
(paren
id|inode
comma
id|inode-&gt;u.ext2_i.i_data
op_plus
id|EXT2_TIND_BLOCK
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
(paren
id|err
OL
l_int|0
)paren
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
