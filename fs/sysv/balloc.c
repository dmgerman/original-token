multiline_comment|/*&n; *  linux/fs/sysv/balloc.c&n; *&n; *  minix/bitmap.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext/freelists.c&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *&n; *  xenix/alloc.c&n; *  Copyright (C) 1992  Doug Evans&n; *&n; *  coh/alloc.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/balloc.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  This file contains code for allocating/freeing blocks.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
multiline_comment|/* We don&squot;t trust the value of&n;   sb-&gt;sv_sbd-&gt;s_tfree = *sb-&gt;sv_sb_total_free_blocks&n;   but we nevertheless keep it up to date. */
DECL|function|memzero
r_extern
r_inline
r_void
id|memzero
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;rep&bslash;n&bslash;t&quot;
l_string|&quot;stosl&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;D&quot;
(paren
id|s
)paren
comma
l_string|&quot;c&quot;
(paren
id|count
op_div
l_int|4
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|sysv_free_block
r_void
id|sysv_free_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|bh_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_block: trying to free block on nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
OL
id|sb-&gt;sv_firstdatazone
op_logical_or
id|block
op_ge
id|sb-&gt;sv_nzones
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_block: trying to free block not in datazone&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_flc_count
OG
id|sb-&gt;sv_flc_size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_block: flc_count &gt; flc_size&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* If the free list head in super-block is full, it is copied&n;&t; * into this block being freed:&n;&t; */
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_flc_count
op_eq
id|sb-&gt;sv_flc_size
)paren
(brace
r_int
r_int
op_star
id|flc_count
suffix:semicolon
r_int
r_int
op_star
id|flc_blocks
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
OG
l_int|0
)paren
multiline_comment|/* block_size &lt; BLOCK_SIZE ? */
id|bh
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_block: getblk() or bread() failed&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
(paren
id|block
op_amp
id|sb-&gt;sv_block_size_ratio_1
)paren
op_lshift
id|sb-&gt;sv_block_size_bits
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sb-&gt;sv_type
)paren
(brace
r_case
id|FSTYPE_XENIX
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|xenix_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|xenix_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_SYSV4
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|sysv4_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|sysv4_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_SYSV2
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|sysv2_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|sysv2_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_COH
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|coh_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|coh_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;sysv_free_block: invalid fs type&bslash;n&quot;
)paren
suffix:semicolon
)brace
op_star
id|flc_count
op_assign
op_star
id|sb-&gt;sv_sb_flc_count
suffix:semicolon
multiline_comment|/* = sb-&gt;sv_flc_size */
id|memcpy
c_func
(paren
id|flc_blocks
comma
id|sb-&gt;sv_sb_flc_blocks
comma
op_star
id|flc_count
op_star
r_sizeof
(paren
id|sysv_zone_t
)paren
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
op_star
id|sb-&gt;sv_sb_flc_count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
multiline_comment|/* If the free list head in super-block is empty, create a new head&n;&t; * in this block being freed:&n;&t; */
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_flc_count
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Applies only to Coherent FS */
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
OG
l_int|0
)paren
multiline_comment|/* block_size &lt; BLOCK_SIZE ? */
id|bh
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_block: getblk() or bread() failed&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
(paren
id|block
op_amp
id|sb-&gt;sv_block_size_ratio_1
)paren
op_lshift
id|sb-&gt;sv_block_size_bits
)paren
suffix:semicolon
id|memzero
c_func
(paren
id|bh_data
comma
id|sb-&gt;sv_block_size
)paren
suffix:semicolon
multiline_comment|/* this implies ((struct ..._freelist_chunk *) bh_data)-&gt;flc_count = 0; */
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* still *sb-&gt;sv_sb_flc_count = 0 */
)brace
r_else
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
op_eq
l_int|0
)paren
(brace
multiline_comment|/* block_size == BLOCK_SIZE ? */
multiline_comment|/* Throw away block&squot;s contents */
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|bh-&gt;b_dirt
op_assign
l_int|0
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
id|block
op_assign
id|to_coh_ulong
c_func
(paren
id|block
)paren
suffix:semicolon
id|sb-&gt;sv_sb_flc_blocks
(braket
(paren
op_star
id|sb-&gt;sv_sb_flc_count
)paren
op_increment
)braket
op_assign
id|block
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_assign
id|to_coh_ulong
c_func
(paren
id|from_coh_ulong
c_func
(paren
op_star
id|sb-&gt;sv_sb_total_free_blocks
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_else
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_assign
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_plus
l_int|1
suffix:semicolon
id|sb-&gt;sv_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* super-block has been modified */
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* and needs time stamp */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|function|sysv_new_block
r_int
id|sysv_new_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
r_int
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|bh_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_new_block: trying to get new block from nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_flc_count
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Applies only to Coherent FS */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no blocks available */
)brace
id|block
op_assign
id|sb-&gt;sv_sb_flc_blocks
(braket
(paren
op_star
id|sb-&gt;sv_sb_flc_count
)paren
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
id|block
op_assign
id|from_coh_ulong
c_func
(paren
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Applies only to Xenix FS, SystemV FS */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no blocks available */
)brace
(paren
op_star
id|sb-&gt;sv_sb_flc_count
)paren
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
id|sb-&gt;sv_firstdatazone
op_logical_or
id|block
op_ge
id|sb-&gt;sv_nzones
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_new_block: new block %d is not in data zone&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_flc_count
op_eq
l_int|0
)paren
(brace
multiline_comment|/* the last block continues the free list */
r_int
r_int
op_star
id|flc_count
suffix:semicolon
r_int
r_int
op_star
id|flc_blocks
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|sysv_bread
c_func
(paren
id|sb
comma
id|sb-&gt;s_dev
comma
id|block
comma
op_amp
id|bh_data
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_new_block: cannot read free-list block&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* retry this same block next time */
(paren
op_star
id|sb-&gt;sv_sb_flc_count
)paren
op_increment
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sb-&gt;sv_type
)paren
(brace
r_case
id|FSTYPE_XENIX
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|xenix_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|xenix_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_SYSV4
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|sysv4_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|sysv4_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_SYSV2
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|sysv2_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|sysv2_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_COH
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|coh_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|coh_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;sysv_new_block: invalid fs type&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|flc_count
OG
id|sb-&gt;sv_flc_size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_new_block: free-list block with &gt;flc_size entries&bslash;n&quot;
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|sb-&gt;sv_sb_flc_count
op_assign
op_star
id|flc_count
suffix:semicolon
id|memcpy
c_func
(paren
id|sb-&gt;sv_sb_flc_blocks
comma
id|flc_blocks
comma
op_star
id|flc_count
op_star
r_sizeof
(paren
id|sysv_zone_t
)paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/* Now the free list head in the superblock is valid again. */
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
OG
l_int|0
)paren
multiline_comment|/* block_size &lt; BLOCK_SIZE ? */
id|bh
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|block
op_rshift
id|sb-&gt;sv_block_size_ratio_bits
)paren
op_plus
id|sb-&gt;sv_block_base
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_new_block: getblk() or bread() failed&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|bh_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
(paren
id|block
op_amp
id|sb-&gt;sv_block_size_ratio_1
)paren
op_lshift
id|sb-&gt;sv_block_size_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_block_size_ratio_bits
op_eq
l_int|0
)paren
multiline_comment|/* block_size == BLOCK_SIZE ? */
r_if
c_cond
(paren
id|bh-&gt;b_count
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_new_block: block already in use&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memzero
c_func
(paren
id|bh_data
comma
id|sb-&gt;sv_block_size
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_assign
id|to_coh_ulong
c_func
(paren
id|from_coh_ulong
c_func
(paren
op_star
id|sb-&gt;sv_sb_total_free_blocks
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_else
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_assign
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_minus
l_int|1
suffix:semicolon
id|sb-&gt;sv_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* super-block has been modified */
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* and needs time stamp */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|block
suffix:semicolon
)brace
DECL|function|sysv_count_free_blocks
r_int
r_int
id|sysv_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
macro_line|#if 1 /* test */
r_int
id|count
comma
id|old_count
suffix:semicolon
r_int
r_int
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|bh_data
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* this causes a lot of disk traffic ... */
id|count
op_assign
l_int|0
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sb-&gt;sv_sb_flc_count
OG
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
op_star
id|sb-&gt;sv_sb_flc_count
suffix:semicolon
multiline_comment|/* i &gt; 0 */
suffix:semicolon
)paren
(brace
id|block
op_assign
id|sb-&gt;sv_sb_flc_blocks
(braket
op_decrement
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
id|block
op_assign
id|from_coh_ulong
c_func
(paren
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|0
)paren
multiline_comment|/* block 0 terminates list */
r_goto
id|done
suffix:semicolon
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* block = sb-&gt;sv_sb_flc_blocks[0], the last block continues the free list */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
r_int
op_star
id|flc_count
suffix:semicolon
r_int
r_int
op_star
id|flc_blocks
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
id|sb-&gt;sv_firstdatazone
op_logical_or
id|block
op_ge
id|sb-&gt;sv_nzones
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_count_free_blocks: new block %d is not in data zone&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|sysv_bread
c_func
(paren
id|sb
comma
id|sb-&gt;s_dev
comma
id|block
comma
op_amp
id|bh_data
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_count_free_blocks: cannot read free-list block&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sb-&gt;sv_type
)paren
(brace
r_case
id|FSTYPE_XENIX
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|xenix_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|xenix_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_SYSV4
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|sysv4_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|sysv4_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_SYSV2
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|sysv2_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|sysv2_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FSTYPE_COH
suffix:colon
id|flc_count
op_assign
op_amp
(paren
(paren
r_struct
id|coh_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_nfree
suffix:semicolon
id|flc_blocks
op_assign
op_amp
(paren
(paren
r_struct
id|coh_freelist_chunk
op_star
)paren
id|bh_data
)paren
op_member_access_from_pointer
id|fl_free
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;sysv_count_free_blocks: invalid fs type&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|flc_count
OG
id|sb-&gt;sv_flc_size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_count_free_blocks: free-list block with &gt;flc_size entries&bslash;n&quot;
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|flc_count
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Applies only to Coherent FS */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
op_star
id|flc_count
suffix:semicolon
multiline_comment|/* i &gt; 0 */
suffix:semicolon
)paren
(brace
id|block
op_assign
id|flc_blocks
(braket
op_decrement
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
id|block
op_assign
id|from_coh_ulong
c_func
(paren
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|0
)paren
multiline_comment|/* block 0 terminates list */
r_break
suffix:semicolon
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* block = flc_blocks[0], the last block continues the free list */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|0
)paren
multiline_comment|/* Applies only to Xenix FS and SystemV FS */
r_break
suffix:semicolon
)brace
id|done
suffix:colon
suffix:semicolon
)brace
id|old_count
op_assign
op_star
id|sb-&gt;sv_sb_total_free_blocks
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
id|old_count
op_assign
id|from_coh_ulong
c_func
(paren
id|old_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
id|old_count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_count_free_blocks: free block count was %d, correcting to %d&bslash;n&quot;
comma
id|old_count
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
op_star
id|sb-&gt;sv_sb_total_free_blocks
op_assign
(paren
id|sb-&gt;sv_convert
ques
c_cond
id|to_coh_ulong
c_func
(paren
id|count
)paren
suffix:colon
id|count
)paren
suffix:semicolon
id|sb-&gt;sv_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* super-block has been modified */
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* and needs time stamp */
)brace
)brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
macro_line|#else
r_int
id|count
suffix:semicolon
id|count
op_assign
op_star
id|sb-&gt;sv_sb_total_free_blocks
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;sv_convert
)paren
id|count
op_assign
id|from_coh_ulong
c_func
(paren
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
macro_line|#endif
)brace
eof