multiline_comment|/*&n; *  linux/fs/ext2/truncate.c&n; *&n; *  Copyright (C) 1992, 1993, 1994  Remy Card (card@masi.ibp.fr)&n; *                                  Laboratoire MASI - Institut Blaise Pascal&n; *                                  Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/truncate.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
DECL|macro|clear_block
mdefine_line|#define clear_block(addr,size,value) &bslash;&n;&t;__asm__(&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;rep&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;stosl&quot; &bslash;&n;&t;&t;: &bslash;&n;&t;&t;:&quot;a&quot; (value), &quot;c&quot; (size / 4), &quot;D&quot; ((long) (addr)) &bslash;&n;&t;&t;:&quot;cx&quot;, &quot;di&quot;)
multiline_comment|/*&n; * Truncate has the most races in the whole filesystem: coding it is&n; * a pain in the a**. Especially as I don&squot;t do any locking...&n; *&n; * The code may look a bit weird, but that&squot;s just because I&squot;ve tried to&n; * handle things like file-size changes in a somewhat graceful manner.&n; * Anyway, truncating a file at the same time somebody else writes to it&n; * is likely to result in pretty weird behaviour...&n; *&n; * The new code handles normal truncates (size = 0) as well as the more&n; * general case (size = XXX). I hope.&n; */
DECL|function|trunc_direct
r_static
r_int
id|trunc_direct
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|i
comma
id|tmp
suffix:semicolon
r_int
r_int
op_star
id|p
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|block_to_free
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|free_count
op_assign
l_int|0
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|blocks
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_div
l_int|512
suffix:semicolon
DECL|macro|DIRECT_BLOCK
mdefine_line|#define DIRECT_BLOCK ((inode-&gt;i_size + inode-&gt;i_sb-&gt;s_blocksize - 1) / &bslash;&n;&t;&t;&t;inode-&gt;i_sb-&gt;s_blocksize)
r_int
id|direct_block
op_assign
id|DIRECT_BLOCK
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|direct_block
suffix:semicolon
id|i
OL
id|EXT2_NDIR_BLOCKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
id|inode-&gt;u.ext2_i.i_data
op_plus
id|i
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;u.ext2_i.i_flags
op_amp
id|EXT2_SECRM_FL
)paren
id|bh
op_assign
id|getblk
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|get_hash_table
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|direct_block
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|bh
op_logical_and
id|bh-&gt;b_count
op_ne
l_int|1
)paren
op_logical_or
id|tmp
op_ne
op_star
id|p
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|blocks
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;u.ext2_i.i_flags
op_amp
id|EXT2_SECRM_FL
)paren
(brace
id|clear_block
(paren
id|bh-&gt;b_data
comma
id|inode-&gt;i_sb-&gt;s_blocksize
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
op_eq
l_int|0
)paren
(brace
id|block_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|free_count
OG
l_int|0
op_logical_and
id|block_to_free
op_eq
id|tmp
op_minus
id|free_count
)paren
id|free_count
op_increment
suffix:semicolon
r_else
(brace
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|block_to_free
comma
id|free_count
)paren
suffix:semicolon
id|block_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&t;&t;ext2_free_blocks (inode-&gt;i_sb, tmp, 1); */
)brace
r_if
c_cond
(paren
id|free_count
OG
l_int|0
)paren
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|block_to_free
comma
id|free_count
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|trunc_indirect
r_static
r_int
id|trunc_indirect
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|offset
comma
r_int
r_int
op_star
id|p
)paren
(brace
r_int
id|i
comma
id|tmp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|ind_bh
suffix:semicolon
r_int
r_int
op_star
id|ind
suffix:semicolon
r_int
r_int
id|block_to_free
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|free_count
op_assign
l_int|0
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|addr_per_block
op_assign
id|EXT2_ADDR_PER_BLOCK
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
id|blocks
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_div
l_int|512
suffix:semicolon
DECL|macro|INDIRECT_BLOCK
mdefine_line|#define INDIRECT_BLOCK ((int)DIRECT_BLOCK - offset)
r_int
id|indirect_block
op_assign
id|INDIRECT_BLOCK
suffix:semicolon
id|tmp
op_assign
op_star
id|p
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
id|ind_bh
op_assign
id|bread
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_star
id|p
)paren
(brace
id|brelse
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ind_bh
)paren
(brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|indirect_block
suffix:semicolon
id|i
OL
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|indirect_block
)paren
r_goto
id|repeat
suffix:semicolon
id|ind
op_assign
id|i
op_plus
(paren
r_int
r_int
op_star
)paren
id|ind_bh-&gt;b_data
suffix:semicolon
id|tmp
op_assign
op_star
id|ind
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;u.ext2_i.i_flags
op_amp
id|EXT2_SECRM_FL
)paren
id|bh
op_assign
id|getblk
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|get_hash_table
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|indirect_block
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|bh
op_logical_and
id|bh-&gt;b_count
op_ne
l_int|1
)paren
op_logical_or
id|tmp
op_ne
op_star
id|ind
)paren
(brace
id|retry
op_assign
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|ind
op_assign
l_int|0
suffix:semicolon
id|ind_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;u.ext2_i.i_flags
op_amp
id|EXT2_SECRM_FL
)paren
(brace
id|clear_block
(paren
id|bh-&gt;b_data
comma
id|inode-&gt;i_sb-&gt;s_blocksize
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
op_eq
l_int|0
)paren
(brace
id|block_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|free_count
OG
l_int|0
op_logical_and
id|block_to_free
op_eq
id|tmp
op_minus
id|free_count
)paren
id|free_count
op_increment
suffix:semicolon
r_else
(brace
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|block_to_free
comma
id|free_count
)paren
suffix:semicolon
id|block_to_free
op_assign
id|tmp
suffix:semicolon
id|free_count
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&t;&t;ext2_free_blocks (inode-&gt;i_sb, tmp, 1); */
id|inode-&gt;i_blocks
op_sub_assign
id|blocks
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|free_count
OG
l_int|0
)paren
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|block_to_free
comma
id|free_count
)paren
suffix:semicolon
id|ind
op_assign
(paren
r_int
r_int
op_star
)paren
id|ind_bh-&gt;b_data
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
r_if
c_cond
(paren
op_star
(paren
id|ind
op_increment
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|addr_per_block
)paren
r_if
c_cond
(paren
id|ind_bh-&gt;b_count
op_ne
l_int|1
)paren
id|retry
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|blocks
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|tmp
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|ind_bh-&gt;b_dirt
)paren
(brace
id|ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|ind_bh
)paren
suffix:semicolon
id|wait_on_buffer
(paren
id|ind_bh
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|trunc_dindirect
r_static
r_int
id|trunc_dindirect
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|offset
comma
r_int
r_int
op_star
id|p
)paren
(brace
r_int
id|i
comma
id|tmp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dind_bh
suffix:semicolon
r_int
r_int
op_star
id|dind
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|addr_per_block
op_assign
id|EXT2_ADDR_PER_BLOCK
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
id|blocks
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_div
l_int|512
suffix:semicolon
DECL|macro|DINDIRECT_BLOCK
mdefine_line|#define DINDIRECT_BLOCK (((int)DIRECT_BLOCK - offset) / addr_per_block)
r_int
id|dindirect_block
op_assign
id|DINDIRECT_BLOCK
suffix:semicolon
id|tmp
op_assign
op_star
id|p
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
id|dind_bh
op_assign
id|bread
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_star
id|p
)paren
(brace
id|brelse
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dind_bh
)paren
(brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|dindirect_block
suffix:semicolon
id|i
OL
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|dindirect_block
)paren
r_goto
id|repeat
suffix:semicolon
id|dind
op_assign
id|i
op_plus
(paren
r_int
r_int
op_star
)paren
id|dind_bh-&gt;b_data
suffix:semicolon
id|tmp
op_assign
op_star
id|dind
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
id|retry
op_or_assign
id|trunc_indirect
(paren
id|inode
comma
id|offset
op_plus
(paren
id|i
op_star
id|addr_per_block
)paren
comma
id|dind
)paren
suffix:semicolon
id|dind_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|dind
op_assign
(paren
r_int
r_int
op_star
)paren
id|dind_bh-&gt;b_data
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
r_if
c_cond
(paren
op_star
(paren
id|dind
op_increment
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|addr_per_block
)paren
r_if
c_cond
(paren
id|dind_bh-&gt;b_count
op_ne
l_int|1
)paren
id|retry
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|blocks
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|tmp
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|dind_bh-&gt;b_dirt
)paren
(brace
id|ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|dind_bh
)paren
suffix:semicolon
id|wait_on_buffer
(paren
id|dind_bh
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|trunc_tindirect
r_static
r_int
id|trunc_tindirect
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|i
comma
id|tmp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|tind_bh
suffix:semicolon
r_int
r_int
op_star
id|tind
comma
op_star
id|p
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_int
id|addr_per_block
op_assign
id|EXT2_ADDR_PER_BLOCK
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
id|blocks
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_div
l_int|512
suffix:semicolon
DECL|macro|TINDIRECT_BLOCK
mdefine_line|#define TINDIRECT_BLOCK (((int)DIRECT_BLOCK - (addr_per_block * addr_per_block + &bslash;&n;&t;&t;&t;  addr_per_block + EXT2_NDIR_BLOCKS)) / &bslash;&n;&t;&t;&t;  (addr_per_block * addr_per_block))
r_int
id|tindirect_block
op_assign
id|TINDIRECT_BLOCK
suffix:semicolon
id|p
op_assign
id|inode-&gt;u.ext2_i.i_data
op_plus
id|EXT2_TIND_BLOCK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
op_star
id|p
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|tind_bh
op_assign
id|bread
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_star
id|p
)paren
(brace
id|brelse
(paren
id|tind_bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tind_bh
)paren
(brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|tindirect_block
suffix:semicolon
id|i
OL
id|addr_per_block
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|tindirect_block
)paren
r_goto
id|repeat
suffix:semicolon
id|tind
op_assign
id|i
op_plus
(paren
r_int
r_int
op_star
)paren
id|tind_bh-&gt;b_data
suffix:semicolon
id|retry
op_or_assign
id|trunc_dindirect
c_func
(paren
id|inode
comma
id|EXT2_NDIR_BLOCKS
op_plus
id|addr_per_block
op_plus
(paren
id|i
op_plus
l_int|1
)paren
op_star
id|addr_per_block
op_star
id|addr_per_block
comma
id|tind
)paren
suffix:semicolon
id|tind_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|tind
op_assign
(paren
r_int
r_int
op_star
)paren
id|tind_bh-&gt;b_data
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
r_if
c_cond
(paren
op_star
(paren
id|tind
op_increment
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|addr_per_block
)paren
r_if
c_cond
(paren
id|tind_bh-&gt;b_count
op_ne
l_int|1
)paren
id|retry
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|blocks
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|ext2_free_blocks
(paren
id|inode-&gt;i_sb
comma
id|tmp
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|tind_bh-&gt;b_dirt
)paren
(brace
id|ll_rw_block
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|tind_bh
)paren
suffix:semicolon
id|wait_on_buffer
(paren
id|tind_bh
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|tind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|ext2_truncate
r_void
id|ext2_truncate
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|retry
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
suffix:semicolon
id|ext2_discard_prealloc
c_func
(paren
id|inode
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|retry
op_assign
id|trunc_direct
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retry
op_or_assign
id|trunc_indirect
(paren
id|inode
comma
id|EXT2_IND_BLOCK
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|inode-&gt;u.ext2_i.i_data
(braket
id|EXT2_IND_BLOCK
)braket
)paren
suffix:semicolon
id|retry
op_or_assign
id|trunc_dindirect
(paren
id|inode
comma
id|EXT2_IND_BLOCK
op_plus
id|EXT2_ADDR_PER_BLOCK
c_func
(paren
id|inode-&gt;i_sb
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|inode-&gt;u.ext2_i.i_data
(braket
id|EXT2_DIND_BLOCK
)braket
)paren
suffix:semicolon
id|retry
op_or_assign
id|trunc_tindirect
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retry
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_and
id|inode-&gt;i_dirt
)paren
id|ext2_sync_inode
(paren
id|inode
)paren
suffix:semicolon
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|schedule
(paren
)paren
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
eof
