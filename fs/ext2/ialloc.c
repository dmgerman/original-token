multiline_comment|/*&n; *  linux/fs/ext2/ialloc.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  BSD ufs-inspired inode and directory allocation by &n; *  Stephen Tweedie (sct@dcs.ed.ac.uk), 1993&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
multiline_comment|/*&n; * ialloc.c contains the inodes allocation and deallocation routines&n; */
multiline_comment|/*&n; * The free inodes are managed by bitmaps.  A file system contains several&n; * blocks groups.  Each group contains 1 bitmap block for blocks, 1 bitmap&n; * block for inodes, N blocks for the inode table and data blocks.&n; *&n; * The file system contains group descriptors which are located after the&n; * super block.  Each descriptor contains the number of the bitmap block and&n; * the free blocks count in the block.  The descriptors are loaded in memory&n; * when a file system is mounted (see ext2_read_super).&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|function|get_group_desc
r_static
r_struct
id|ext2_group_desc
op_star
id|get_group_desc
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
(brace
r_int
r_int
id|group_desc
suffix:semicolon
r_int
r_int
id|desc
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|gdp
suffix:semicolon
r_if
c_cond
(paren
id|block_group
op_ge
id|sb-&gt;u.ext2_sb.s_groups_count
)paren
id|ext2_panic
(paren
id|sb
comma
l_string|&quot;get_group_desc&quot;
comma
l_string|&quot;block_group &gt;= groups_count - &quot;
l_string|&quot;block_group = %d, groups_count = %lu&quot;
comma
id|block_group
comma
id|sb-&gt;u.ext2_sb.s_groups_count
)paren
suffix:semicolon
id|group_desc
op_assign
id|block_group
op_div
id|EXT2_DESC_PER_BLOCK
c_func
(paren
id|sb
)paren
suffix:semicolon
id|desc
op_assign
id|block_group
op_mod
id|EXT2_DESC_PER_BLOCK
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext2_sb.s_group_desc
(braket
id|group_desc
)braket
)paren
id|ext2_panic
(paren
id|sb
comma
l_string|&quot;get_group_desc&quot;
comma
l_string|&quot;Group descriptor not loaded - &quot;
l_string|&quot;block_group = %d, group_desc = %lu, desc = %lu&quot;
comma
id|block_group
comma
id|group_desc
comma
id|desc
)paren
suffix:semicolon
id|gdp
op_assign
(paren
r_struct
id|ext2_group_desc
op_star
)paren
id|sb-&gt;u.ext2_sb.s_group_desc
(braket
id|group_desc
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
op_star
id|bh
op_assign
id|sb-&gt;u.ext2_sb.s_group_desc
(braket
id|group_desc
)braket
suffix:semicolon
r_return
id|gdp
op_plus
id|desc
suffix:semicolon
)brace
DECL|function|read_inode_bitmap
r_static
r_void
id|read_inode_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
comma
r_int
r_int
id|bitmap_nr
)paren
(brace
r_struct
id|ext2_group_desc
op_star
id|gdp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|gdp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|block_group
comma
l_int|NULL
)paren
suffix:semicolon
id|bh
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|le32_to_cpu
c_func
(paren
id|gdp-&gt;bg_inode_bitmap
)paren
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
id|ext2_panic
(paren
id|sb
comma
l_string|&quot;read_inode_bitmap&quot;
comma
l_string|&quot;Cannot read inode bitmap - &quot;
l_string|&quot;block_group = %lu, inode_bitmap = %lu&quot;
comma
id|block_group
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|gdp-&gt;bg_inode_bitmap
)paren
)paren
suffix:semicolon
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|bitmap_nr
)braket
op_assign
id|block_group
suffix:semicolon
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
op_assign
id|bh
suffix:semicolon
)brace
multiline_comment|/*&n; * load_inode_bitmap loads the inode bitmap for a blocks group&n; *&n; * It maintains a cache for the last bitmaps loaded.  This cache is managed&n; * with a LRU algorithm.&n; *&n; * Notes:&n; * 1/ There is one cache per mounted file system.&n; * 2/ If the file system contains less than EXT2_MAX_GROUP_LOADED groups,&n; *    this function reads the bitmap without maintaining a LRU cache.&n; */
DECL|function|load_inode_bitmap
r_static
r_int
id|load_inode_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|inode_bitmap_number
suffix:semicolon
r_struct
id|buffer_head
op_star
id|inode_bitmap
suffix:semicolon
r_if
c_cond
(paren
id|block_group
op_ge
id|sb-&gt;u.ext2_sb.s_groups_count
)paren
id|ext2_panic
(paren
id|sb
comma
l_string|&quot;load_inode_bitmap&quot;
comma
l_string|&quot;block_group &gt;= groups_count - &quot;
l_string|&quot;block_group = %d, groups_count = %lu&quot;
comma
id|block_group
comma
id|sb-&gt;u.ext2_sb.s_groups_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.ext2_sb.s_loaded_inode_bitmaps
OG
l_int|0
op_logical_and
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
l_int|0
)braket
op_eq
id|block_group
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.ext2_sb.s_groups_count
op_le
id|EXT2_MAX_GROUP_LOADED
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|block_group
)braket
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|block_group
)braket
op_ne
id|block_group
)paren
id|ext2_panic
(paren
id|sb
comma
l_string|&quot;load_inode_bitmap&quot;
comma
l_string|&quot;block_group != inode_bitmap_number&quot;
)paren
suffix:semicolon
r_else
r_return
id|block_group
suffix:semicolon
)brace
r_else
(brace
id|read_inode_bitmap
(paren
id|sb
comma
id|block_group
comma
id|block_group
)paren
suffix:semicolon
r_return
id|block_group
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sb-&gt;u.ext2_sb.s_loaded_inode_bitmaps
op_logical_and
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|i
)braket
op_ne
id|block_group
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|sb-&gt;u.ext2_sb.s_loaded_inode_bitmaps
op_logical_and
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|i
)braket
op_eq
id|block_group
)paren
(brace
id|inode_bitmap_number
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|i
)braket
suffix:semicolon
id|inode_bitmap
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
l_int|0
)braket
op_assign
id|inode_bitmap_number
suffix:semicolon
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
l_int|0
)braket
op_assign
id|inode_bitmap
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ext2_sb.s_loaded_inode_bitmaps
OL
id|EXT2_MAX_GROUP_LOADED
)paren
id|sb-&gt;u.ext2_sb.s_loaded_inode_bitmaps
op_increment
suffix:semicolon
r_else
id|brelse
(paren
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|EXT2_MAX_GROUP_LOADED
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|sb-&gt;u.ext2_sb.s_loaded_inode_bitmaps
op_minus
l_int|1
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap_number
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|read_inode_bitmap
(paren
id|sb
comma
id|block_group
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ext2_free_inode
r_void
id|ext2_free_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
r_int
r_int
id|block_group
suffix:semicolon
r_int
r_int
id|bit
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|gdp
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_dev
)paren
(brace
id|printk
(paren
l_string|&quot;ext2_free_inode: inode has no device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_count
OG
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;ext2_free_inode: inode has count=%d&bslash;n&quot;
comma
id|inode-&gt;i_count
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_nlink
)paren
(brace
id|printk
(paren
l_string|&quot;ext2_free_inode: inode has nlink=%d&bslash;n&quot;
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ext2_free_inode: inode on nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ext2_debug
(paren
l_string|&quot;freeing inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
template_param
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.ext2_sb.s_es-&gt;s_inodes_count
)paren
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;free_inode&quot;
comma
l_string|&quot;reserved inode or nonexistent inode&quot;
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|es
op_assign
id|sb-&gt;u.ext2_sb.s_es
suffix:semicolon
id|block_group
op_assign
(paren
id|inode-&gt;i_ino
op_minus
l_int|1
)paren
op_div
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bit
op_assign
(paren
id|inode-&gt;i_ino
op_minus
l_int|1
)paren
op_mod
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
id|bh
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ext2_clear_bit
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
id|ext2_warning
(paren
id|sb
comma
l_string|&quot;ext2_free_inode&quot;
comma
l_string|&quot;bit already cleared for inode %lu&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_else
(brace
id|gdp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|block_group
comma
op_amp
id|bh2
)paren
suffix:semicolon
id|gdp-&gt;bg_free_inodes_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|gdp-&gt;bg_used_dirs_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_used_dirs_count
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh2
comma
l_int|1
)paren
suffix:semicolon
id|es-&gt;s_free_inodes_count
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.ext2_sb.s_sbh
comma
l_int|1
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
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
id|wait_on_buffer
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
id|sb-&gt;dq_op-&gt;free_inode
(paren
id|inode
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|clear_inode
(paren
id|inode
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function increments the inode version number&n; *&n; * This may be used one day by the NFS server&n; */
DECL|function|inc_inode_version
r_static
r_void
id|inc_inode_version
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|ext2_group_desc
op_star
id|gdp
comma
r_int
id|mode
)paren
(brace
id|inode-&gt;u.ext2_i.i_version
op_increment
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * There are two policies for allocating an inode.  If the new inode is&n; * a directory, then a forward search is made for a block group with both&n; * free space and a low directory-to-inode ratio; if that fails, then of&n; * the groups with above-average free space, that group with the fewest&n; * directories already is chosen.&n; *&n; * For other inodes, search forward from the parent directory&bslash;&squot;s block&n; * group to find a free inode.&n; */
DECL|function|ext2_new_inode
r_struct
id|inode
op_star
id|ext2_new_inode
(paren
r_const
r_struct
id|inode
op_star
id|dir
comma
r_int
id|mode
comma
r_int
op_star
id|err
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|avefreei
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|gdp
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|tmp
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|get_empty_inode
(paren
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|inode-&gt;i_sb
op_assign
id|sb
suffix:semicolon
id|inode-&gt;i_flags
op_assign
id|sb-&gt;s_flags
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext2_sb.s_es
suffix:semicolon
id|repeat
suffix:colon
id|gdp
op_assign
l_int|NULL
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
id|avefreei
op_assign
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_div
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
multiline_comment|/* I am not yet convinced that this next bit is necessary.&n;&t;&t;i = dir-&gt;u.ext2_i.i_block_group;&n;&t;&t;for (j = 0; j &lt; sb-&gt;u.ext2_sb.s_groups_count; j++) {&n;&t;&t;&t;tmp = get_group_desc (sb, i, &amp;bh2);&n;&t;&t;&t;if ((le16_to_cpu(tmp-&gt;bg_used_dirs_count) &lt;&lt; 8) &lt; &n;&t;&t;&t;    le16_to_cpu(tmp-&gt;bg_free_inodes_count)) {&n;&t;&t;&t;&t;gdp = tmp;&n;&t;&t;&t;&t;break;&n;&t;&t;&t;}&n;&t;&t;&t;else&n;&t;&t;&t;i = ++i % sb-&gt;u.ext2_sb.s_groups_count;&n;&t;&t;}&n;*/
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
id|j
op_increment
)paren
(brace
id|tmp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|j
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
op_ge
id|avefreei
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gdp
op_logical_or
(paren
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_blocks_count
)paren
OG
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_blocks_count
)paren
)paren
)paren
(brace
id|i
op_assign
id|j
suffix:semicolon
id|gdp
op_assign
id|tmp
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Try to place the inode in its parent directory&n;&t;&t; */
id|i
op_assign
id|dir-&gt;u.ext2_i.i_block_group
suffix:semicolon
id|tmp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
)paren
id|gdp
op_assign
id|tmp
suffix:semicolon
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Use a quadratic hash to find a group with a&n;&t;&t;&t; * free inode&n;&t;&t;&t; */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
id|j
op_lshift_assign
l_int|1
)paren
(brace
id|i
op_add_assign
id|j
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|sb-&gt;u.ext2_sb.s_groups_count
)paren
id|i
op_sub_assign
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
id|tmp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
)paren
(brace
id|gdp
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * That failed: try linear search for a free inode&n;&t;&t;&t; */
id|i
op_assign
id|dir-&gt;u.ext2_i.i_block_group
op_plus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|2
suffix:semicolon
id|j
OL
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
id|sb-&gt;u.ext2_sb.s_groups_count
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|tmp-&gt;bg_free_inodes_count
)paren
)paren
(brace
id|gdp
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
(brace
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
id|bh
op_assign
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|j
op_assign
id|ext2_find_first_zero_bit
(paren
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
comma
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
)paren
)paren
OL
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
)paren
(brace
r_if
c_cond
(paren
id|ext2_set_bit
(paren
id|j
comma
id|bh-&gt;b_data
)paren
)paren
(brace
id|ext2_warning
(paren
id|sb
comma
l_string|&quot;ext2_new_inode&quot;
comma
l_string|&quot;bit already set for inode %d&quot;
comma
id|j
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
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
id|wait_on_buffer
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_ne
l_int|0
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_new_inode&quot;
comma
l_string|&quot;Free inodes count corrupted in group %d&quot;
comma
id|i
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_goto
id|repeat
suffix:semicolon
)brace
id|j
op_add_assign
id|i
op_star
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|j
template_param
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_inodes_count
)paren
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_new_inode&quot;
comma
l_string|&quot;reserved inode or inode &gt; inodes count - &quot;
l_string|&quot;block_group = %d,inode=%d&quot;
comma
id|i
comma
id|j
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|gdp-&gt;bg_free_inodes_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|gdp-&gt;bg_used_dirs_count
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_used_dirs_count
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh2
comma
l_int|1
)paren
suffix:semicolon
id|es-&gt;s_free_inodes_count
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.ext2_sb.s_sbh
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_sb
op_assign
id|sb
suffix:semicolon
id|inode-&gt;i_count
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
r_if
c_cond
(paren
id|test_opt
(paren
id|sb
comma
id|GRPID
)paren
)paren
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|j
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* This is the optimal IO size (for stat), not the fs block size */
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;u.ext2_i.i_new_inode
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;u.ext2_i.i_flags
op_assign
id|dir-&gt;u.ext2_i.i_flags
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|inode-&gt;u.ext2_i.i_flags
op_and_assign
op_complement
(paren
id|EXT2_IMMUTABLE_FL
op_or
id|EXT2_APPEND_FL
)paren
suffix:semicolon
id|inode-&gt;u.ext2_i.i_faddr
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.ext2_i.i_frag_no
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.ext2_i.i_frag_size
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.ext2_i.i_file_acl
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.ext2_i.i_dir_acl
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.ext2_i.i_dtime
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.ext2_i.i_block_group
op_assign
id|i
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;u.ext2_i.i_flags
op_amp
id|EXT2_SYNC_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|MS_SYNCHRONOUS
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inc_inode_version
(paren
id|inode
comma
id|gdp
comma
id|mode
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
(brace
id|sb-&gt;dq_op-&gt;initialize
(paren
id|inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;dq_op-&gt;alloc_inode
(paren
id|inode
comma
l_int|1
)paren
)paren
(brace
id|sb-&gt;dq_op-&gt;drop
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|EDQUOT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|inode-&gt;i_flags
op_or_assign
id|S_WRITE
suffix:semicolon
)brace
id|ext2_debug
(paren
l_string|&quot;allocating inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
op_star
id|err
op_assign
l_int|0
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|ext2_count_free_inodes
r_int
r_int
id|ext2_count_free_inodes
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
macro_line|#ifdef EXT2FS_DEBUG
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_int
r_int
id|desc_count
comma
id|bitmap_count
comma
id|x
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|gdp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext2_sb.s_es
suffix:semicolon
id|desc_count
op_assign
l_int|0
suffix:semicolon
id|bitmap_count
op_assign
l_int|0
suffix:semicolon
id|gdp
op_assign
l_int|NULL
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
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gdp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
id|desc_count
op_add_assign
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
id|x
op_assign
id|ext2_count_free
(paren
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
comma
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
op_div
l_int|8
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;group %d: stored = %d, counted = %lu&bslash;n&quot;
comma
id|i
comma
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
comma
id|x
)paren
suffix:semicolon
id|bitmap_count
op_add_assign
id|x
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ext2_count_free_inodes: stored = %lu, computed = %lu, %lu&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
comma
id|desc_count
comma
id|bitmap_count
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|desc_count
suffix:semicolon
macro_line|#else
r_return
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.ext2_sb.s_es-&gt;s_free_inodes_count
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ext2_check_inodes_bitmap
r_void
id|ext2_check_inodes_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_int
r_int
id|desc_count
comma
id|bitmap_count
comma
id|x
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|gdp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|sb-&gt;u.ext2_sb.s_es
suffix:semicolon
id|desc_count
op_assign
l_int|0
suffix:semicolon
id|bitmap_count
op_assign
l_int|0
suffix:semicolon
id|gdp
op_assign
l_int|NULL
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
id|sb-&gt;u.ext2_sb.s_groups_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gdp
op_assign
id|get_group_desc
(paren
id|sb
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
id|desc_count
op_add_assign
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_inode_bitmap
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
id|x
op_assign
id|ext2_count_free
(paren
id|sb-&gt;u.ext2_sb.s_inode_bitmap
(braket
id|bitmap_nr
)braket
comma
id|EXT2_INODES_PER_GROUP
c_func
(paren
id|sb
)paren
op_div
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
op_ne
id|x
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_inodes_bitmap&quot;
comma
l_string|&quot;Wrong free inodes count in group %d, &quot;
l_string|&quot;stored = %d, counted = %lu&quot;
comma
id|i
comma
id|le16_to_cpu
c_func
(paren
id|gdp-&gt;bg_free_inodes_count
)paren
comma
id|x
)paren
suffix:semicolon
id|bitmap_count
op_add_assign
id|x
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
op_ne
id|bitmap_count
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_inodes_bitmap&quot;
comma
l_string|&quot;Wrong free inodes count in super block, &quot;
l_string|&quot;stored = %lu, counted = %lu&quot;
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_inodes_count
)paren
comma
id|bitmap_count
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
)brace
eof
