multiline_comment|/*&n; *  linux/fs/truncate.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Copyright (C) 1996  Gertjan van Wingerde (gertjan@cs.vu.nl)&n; *&t;Minix V2 fs support.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
DECL|macro|DIRECT_BLOCK
mdefine_line|#define DIRECT_BLOCK&t;&t;((inode-&gt;i_size + 1023) &gt;&gt; 10)
DECL|macro|INDIRECT_BLOCK
mdefine_line|#define INDIRECT_BLOCK(offset)&t;(DIRECT_BLOCK-offset)
DECL|macro|DINDIRECT_BLOCK
mdefine_line|#define DINDIRECT_BLOCK(offset) ((DIRECT_BLOCK-offset)&gt;&gt;9)
DECL|macro|TINDIRECT_BLOCK
mdefine_line|#define TINDIRECT_BLOCK(offset)&t;((DIRECT_BLOCK-(offset))&gt;&gt;9)
multiline_comment|/*&n; * Truncate has the most races in the whole filesystem: coding it is&n; * a pain in the a**. Especially as I don&squot;t do any locking...&n; *&n; * The code may look a bit weird, but that&squot;s just because I&squot;ve tried to&n; * handle things like file-size changes in a somewhat graceful manner.&n; * Anyway, truncating a file at the same time somebody else writes to it&n; * is likely to result in pretty weird behaviour...&n; *&n; * The new code handles normal truncates (size = 0) as well as the more&n; * general case (size = XXX). I hope.&n; */
multiline_comment|/*&n; * The functions for minix V1 fs truncation.&n; */
DECL|function|V1_trunc_direct
r_static
r_int
id|V1_trunc_direct
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
op_star
id|p
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
comma
id|tmp
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|DIRECT_BLOCK
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
id|i
op_plus
id|inode-&gt;u.minix_i.u.i1_data
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
r_continue
suffix:semicolon
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|DIRECT_BLOCK
)paren
(brace
id|brelse
c_func
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
c_func
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|mark_buffer_clean
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V1_trunc_indirect
r_static
r_int
id|V1_trunc_indirect
c_func
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
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
comma
id|tmp
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
id|retry
op_assign
l_int|0
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
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
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
c_func
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
id|INDIRECT_BLOCK
c_func
(paren
id|offset
)paren
suffix:semicolon
id|i
OL
l_int|512
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
id|INDIRECT_BLOCK
c_func
(paren
id|offset
)paren
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
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|INDIRECT_BLOCK
c_func
(paren
id|offset
)paren
)paren
(brace
id|brelse
c_func
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
c_func
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
id|mark_buffer_dirty
c_func
(paren
id|ind_bh
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
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
l_int|512
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
l_int|512
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
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V1_trunc_dindirect
r_static
r_int
id|V1_trunc_dindirect
c_func
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
id|dind_bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
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
c_func
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
id|DINDIRECT_BLOCK
c_func
(paren
id|offset
)paren
suffix:semicolon
id|i
OL
l_int|512
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
id|DINDIRECT_BLOCK
c_func
(paren
id|offset
)paren
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
id|retry
op_or_assign
id|V1_trunc_indirect
c_func
(paren
id|inode
comma
id|offset
op_plus
(paren
id|i
op_lshift
l_int|9
)paren
comma
id|dind
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|dind_bh
comma
l_int|1
)paren
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
l_int|512
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
l_int|512
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V1_minix_truncate
r_void
id|V1_minix_truncate
c_func
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
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|retry
op_assign
id|V1_trunc_direct
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retry
op_or_assign
id|V1_trunc_indirect
c_func
(paren
id|inode
comma
l_int|7
comma
id|inode-&gt;u.minix_i.u.i1_data
op_plus
l_int|7
)paren
suffix:semicolon
id|retry
op_or_assign
id|V1_trunc_dindirect
c_func
(paren
id|inode
comma
l_int|7
op_plus
l_int|512
comma
id|inode-&gt;u.minix_i.u.i1_data
op_plus
l_int|8
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
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
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
multiline_comment|/*&n; * The functions for minix V2 fs truncation.&n; */
DECL|function|V2_trunc_direct
r_static
r_int
id|V2_trunc_direct
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
op_star
id|p
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
comma
id|tmp
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|DIRECT_BLOCK
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|inode-&gt;u.minix_i.u.i2_data
op_plus
id|i
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
r_continue
suffix:semicolon
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|DIRECT_BLOCK
)paren
(brace
id|brelse
c_func
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
c_func
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|mark_buffer_clean
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V2_trunc_indirect
r_static
r_int
id|V2_trunc_indirect
c_func
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
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
comma
id|tmp
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
id|retry
op_assign
l_int|0
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
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
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
c_func
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
id|INDIRECT_BLOCK
c_func
(paren
id|offset
)paren
suffix:semicolon
id|i
OL
l_int|256
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
id|INDIRECT_BLOCK
c_func
(paren
id|offset
)paren
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
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|INDIRECT_BLOCK
c_func
(paren
id|offset
)paren
)paren
(brace
id|brelse
c_func
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
c_func
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
id|mark_buffer_dirty
c_func
(paren
id|ind_bh
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
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
l_int|256
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
l_int|256
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
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|ind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V2_trunc_dindirect
r_static
r_int
id|V2_trunc_dindirect
c_func
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
id|dind_bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
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
c_func
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
id|DINDIRECT_BLOCK
c_func
(paren
id|offset
)paren
suffix:semicolon
id|i
OL
l_int|256
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
id|DINDIRECT_BLOCK
c_func
(paren
id|offset
)paren
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
id|retry
op_or_assign
id|V2_trunc_indirect
c_func
(paren
id|inode
comma
id|offset
op_plus
(paren
id|i
op_lshift
l_int|9
)paren
comma
id|dind
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|dind_bh
comma
l_int|1
)paren
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
l_int|256
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
l_int|256
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|dind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V2_trunc_tindirect
r_static
r_int
id|V2_trunc_tindirect
c_func
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
id|tind_bh
suffix:semicolon
r_int
r_int
op_star
id|tind
suffix:semicolon
r_int
id|retry
op_assign
l_int|0
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
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|BLOCK_SIZE
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
c_func
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
id|TINDIRECT_BLOCK
c_func
(paren
id|offset
)paren
suffix:semicolon
id|i
OL
l_int|256
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
id|TINDIRECT_BLOCK
c_func
(paren
id|offset
)paren
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
id|V2_trunc_dindirect
c_func
(paren
id|inode
comma
id|offset
op_plus
(paren
id|i
op_lshift
l_int|9
)paren
comma
id|tind
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|tind_bh
comma
l_int|1
)paren
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
l_int|256
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
l_int|256
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|minix_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|tind_bh
)paren
suffix:semicolon
r_return
id|retry
suffix:semicolon
)brace
DECL|function|V2_minix_truncate
r_static
r_void
id|V2_minix_truncate
c_func
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
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|retry
op_assign
id|V2_trunc_direct
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retry
op_or_assign
id|V2_trunc_indirect
c_func
(paren
id|inode
comma
l_int|7
comma
(paren
r_int
r_int
op_star
)paren
id|inode-&gt;u.minix_i.u.i2_data
op_plus
l_int|7
)paren
suffix:semicolon
id|retry
op_or_assign
id|V2_trunc_dindirect
c_func
(paren
id|inode
comma
l_int|7
op_plus
l_int|256
comma
(paren
r_int
r_int
op_star
)paren
id|inode-&gt;u.minix_i.u.i2_data
op_plus
l_int|8
)paren
suffix:semicolon
id|retry
op_or_assign
id|V2_trunc_tindirect
c_func
(paren
id|inode
comma
l_int|7
op_plus
l_int|256
op_plus
l_int|256
op_star
l_int|256
comma
(paren
r_int
r_int
op_star
)paren
id|inode-&gt;u.minix_i.u.i2_data
op_plus
l_int|9
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
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
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
multiline_comment|/*&n; * The function that is called for file truncation.&n; */
DECL|function|minix_truncate
r_void
id|minix_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|INODE_VERSION
c_func
(paren
id|inode
)paren
op_eq
id|MINIX_V1
)paren
id|V1_minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|V2_minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
eof
