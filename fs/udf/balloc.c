multiline_comment|/*&n; * balloc.c&n; *&n; * PURPOSE&n; *&t;Block allocation handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hootie.lvld.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1999 Ben Fennema&n; *  (C) 1999 Stelias Computing Inc&n; *&n; * HISTORY&n; *&n; *  02/24/99 blf  Created.&n; *&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
DECL|function|read_block_bitmap
r_static
r_int
id|read_block_bitmap
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
comma
r_int
r_int
id|bitmap_nr
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|lb_addr
id|loc
suffix:semicolon
id|loc.logicalBlockNum
op_assign
id|UDF_SB_PARTMAPS
c_func
(paren
id|sb
)paren
(braket
id|UDF_SB_PARTITION
c_func
(paren
id|sb
)paren
)braket
dot
id|s_uspace_bitmap
suffix:semicolon
id|loc.partitionReferenceNum
op_assign
id|UDF_SB_PARTITION
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bh
op_assign
id|udf_tread
c_func
(paren
id|sb
comma
id|udf_get_lb_pblock
c_func
(paren
id|sb
comma
id|loc
comma
id|block
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
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|bitmap_nr
)paren
op_assign
id|block
suffix:semicolon
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|bitmap_nr
)paren
op_assign
id|bh
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|load__block_bitmap
r_static
r_int
id|load__block_bitmap
c_func
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
comma
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|block_bitmap_number
suffix:semicolon
r_struct
id|buffer_head
op_star
id|block_bitmap
op_assign
l_int|NULL
suffix:semicolon
r_int
id|nr_groups
op_assign
(paren
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|UDF_SB_PARTITION
c_func
(paren
id|sb
)paren
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
op_plus
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
op_minus
l_int|1
)paren
op_div
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block_group
op_ge
id|nr_groups
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;block_group (%d) &gt; nr_groups (%d)&bslash;n&quot;
comma
id|block_group
comma
id|nr_groups
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_groups
op_le
id|UDF_MAX_BLOCK_LOADED
)paren
(brace
r_if
c_cond
(paren
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|block_group
)paren
)paren
(brace
r_if
c_cond
(paren
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|block_group
)paren
op_eq
id|block_group
)paren
r_return
id|block_group
suffix:semicolon
)brace
id|retval
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
id|block_group
suffix:semicolon
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
id|UDF_SB_LOADED_BLOCK_BITMAPS
c_func
(paren
id|sb
)paren
op_logical_and
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|i
)paren
op_ne
id|block_group
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|UDF_SB_LOADED_BLOCK_BITMAPS
c_func
(paren
id|sb
)paren
op_logical_and
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|i
)paren
op_eq
id|block_group
)paren
(brace
id|block_bitmap_number
op_assign
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
id|block_bitmap
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|i
)paren
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
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|j
)paren
op_assign
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|j
op_minus
l_int|1
)paren
suffix:semicolon
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|j
)paren
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|j
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
l_int|0
)paren
op_assign
id|block_bitmap_number
suffix:semicolon
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
l_int|0
)paren
op_assign
id|block_bitmap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block_bitmap
)paren
id|retval
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|UDF_SB_LOADED_BLOCK_BITMAPS
c_func
(paren
id|sb
)paren
OL
id|UDF_MAX_BLOCK_LOADED
)paren
id|UDF_SB_LOADED_BLOCK_BITMAPS
c_func
(paren
id|sb
)paren
op_increment
suffix:semicolon
r_else
id|brelse
c_func
(paren
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|UDF_MAX_BLOCK_LOADED
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|UDF_SB_LOADED_BLOCK_BITMAPS
c_func
(paren
id|sb
)paren
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
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|j
)paren
op_assign
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|j
op_minus
l_int|1
)paren
suffix:semicolon
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|j
)paren
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|j
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|retval
op_assign
id|read_block_bitmap
c_func
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
id|retval
suffix:semicolon
)brace
DECL|function|load_block_bitmap
r_static
r_inline
r_int
id|load_block_bitmap
c_func
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
id|slot
suffix:semicolon
r_int
id|nr_groups
op_assign
(paren
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|UDF_SB_PARTITION
c_func
(paren
id|sb
)paren
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
op_plus
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
op_minus
l_int|1
)paren
op_div
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_LOADED_BLOCK_BITMAPS
c_func
(paren
id|sb
)paren
OG
l_int|0
op_logical_and
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
l_int|0
)paren
op_eq
id|block_group
op_logical_and
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|block_group
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nr_groups
op_le
id|UDF_MAX_BLOCK_LOADED
op_logical_and
id|UDF_SB_BLOCK_BITMAP_NUMBER
c_func
(paren
id|sb
comma
id|block_group
)paren
op_eq
id|block_group
op_logical_and
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|block_group
)paren
)paren
(brace
id|slot
op_assign
id|block_group
suffix:semicolon
)brace
r_else
(brace
id|slot
op_assign
id|load__block_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot
OL
l_int|0
)paren
r_return
id|slot
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|slot
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
DECL|function|udf_free_blocks
r_void
id|udf_free_blocks
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
id|lb_addr
id|bloc
comma
id|Uint32
id|offset
comma
id|Uint32
id|count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|block
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
r_int
id|i
suffix:semicolon
r_int
id|bitmap_nr
suffix:semicolon
r_int
r_int
id|overflow
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;nonexistent device&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|UDF_SB_PARTMAPS
c_func
(paren
id|sb
)paren
(braket
id|bloc.partitionReferenceNum
)braket
dot
id|s_uspace_bitmap
op_eq
l_int|0xFFFFFFFF
)paren
r_return
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
id|bloc.logicalBlockNum
template_param
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|bloc.partitionReferenceNum
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;%d &lt; %d || %d + %d &gt; %d&bslash;n&quot;
comma
id|bloc.logicalBlockNum
comma
l_int|0
comma
id|bloc.logicalBlockNum
comma
id|count
comma
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|bloc.partitionReferenceNum
)paren
)paren
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
id|block
op_assign
id|bloc.logicalBlockNum
op_plus
id|offset
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|do_more
suffix:colon
id|overflow
op_assign
l_int|0
suffix:semicolon
id|block_group
op_assign
id|block
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
op_plus
l_int|3
)paren
suffix:semicolon
id|bit
op_assign
id|block
op_mod
(paren
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check to see if we are freeing blocks across a group boundary.&n;&t; */
r_if
c_cond
(paren
id|bit
op_plus
id|count
OG
(paren
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
)paren
(brace
id|overflow
op_assign
id|bit
op_plus
id|count
op_minus
(paren
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
suffix:semicolon
id|count
op_sub_assign
id|overflow
suffix:semicolon
)brace
id|bitmap_nr
op_assign
id|load_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_goto
id|error_return
suffix:semicolon
id|bh
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|bitmap_nr
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|udf_set_bit
c_func
(paren
id|bit
op_plus
id|i
comma
id|bh-&gt;b_data
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;bit %ld already set&bslash;n&quot;
comma
id|bit
op_plus
id|i
)paren
suffix:semicolon
id|udf_debug
c_func
(paren
l_string|&quot;byte=%2x&bslash;n&quot;
comma
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
(paren
id|bit
op_plus
id|i
)paren
op_rshift
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
(brace
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|freeSpaceTable
(braket
id|UDF_SB_PARTITION
c_func
(paren
id|sb
)paren
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|freeSpaceTable
(braket
id|UDF_SB_PARTITION
c_func
(paren
id|sb
)paren
)braket
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
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
id|overflow
)paren
(brace
id|block
op_add_assign
id|count
suffix:semicolon
id|count
op_assign
id|overflow
suffix:semicolon
r_goto
id|do_more
suffix:semicolon
)brace
id|error_return
suffix:colon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
id|mark_buffer_dirty
c_func
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
comma
l_int|1
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
DECL|function|udf_alloc_blocks
r_int
id|udf_alloc_blocks
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
id|Uint16
id|partition
comma
id|Uint32
id|first_block
comma
id|Uint32
id|block_count
)paren
(brace
r_int
id|alloc_count
op_assign
l_int|0
suffix:semicolon
r_int
id|bit
comma
id|block
comma
id|block_group
comma
id|group_start
suffix:semicolon
r_int
id|nr_groups
comma
id|bitmap_nr
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;nonexistent device&bslash;n&quot;
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
id|first_block
OL
l_int|0
op_logical_or
id|first_block
op_ge
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|partition
)paren
)paren
r_goto
id|out
suffix:semicolon
id|repeat
suffix:colon
id|nr_groups
op_assign
(paren
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|partition
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
op_plus
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
op_minus
l_int|1
)paren
op_div
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
suffix:semicolon
id|block
op_assign
id|first_block
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|block_group
op_assign
id|block
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
op_plus
l_int|3
)paren
suffix:semicolon
id|group_start
op_assign
id|block_group
ques
c_cond
l_int|0
suffix:colon
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|bh
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|bitmap_nr
)paren
suffix:semicolon
id|bit
op_assign
id|block
op_mod
(paren
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bit
template_param
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|udf_test_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|udf_clear_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;bit already cleared for block %d&bslash;n&quot;
comma
id|bit
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|block_count
op_decrement
suffix:semicolon
id|alloc_count
op_increment
suffix:semicolon
id|bit
op_increment
suffix:semicolon
id|block
op_increment
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
id|block_count
OG
l_int|0
)paren
r_goto
id|repeat
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
(brace
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|freeSpaceTable
(braket
id|partition
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|freeSpaceTable
(braket
id|partition
)braket
)paren
op_minus
id|alloc_count
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|alloc_count
suffix:semicolon
)brace
DECL|function|udf_new_block
r_int
id|udf_new_block
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
id|Uint16
id|partition
comma
id|Uint32
id|goal
comma
r_int
op_star
id|err
)paren
(brace
r_int
id|tmp
comma
id|newbit
comma
id|bit
op_assign
l_int|0
comma
id|block
comma
id|block_group
comma
id|group_start
suffix:semicolon
r_int
id|end_goal
comma
id|nr_groups
comma
id|bitmap_nr
comma
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_int
id|newblock
op_assign
l_int|0
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|newblock
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
id|goal
OL
l_int|0
op_logical_or
id|goal
op_ge
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|partition
)paren
)paren
id|goal
op_assign
l_int|0
suffix:semicolon
id|nr_groups
op_assign
(paren
id|UDF_SB_PARTLEN
c_func
(paren
id|sb
comma
id|partition
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
op_plus
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
op_minus
l_int|1
)paren
op_div
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
)paren
suffix:semicolon
id|block
op_assign
id|goal
op_plus
(paren
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|block_group
op_assign
id|block
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
op_plus
l_int|3
)paren
suffix:semicolon
id|group_start
op_assign
id|block_group
ques
c_cond
l_int|0
suffix:colon
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_goto
id|error_return
suffix:semicolon
id|bh
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|bitmap_nr
)paren
suffix:semicolon
id|ptr
op_assign
id|memscan
c_func
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
id|group_start
comma
l_int|0xFF
comma
id|sb-&gt;s_blocksize
op_minus
id|group_start
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptr
op_minus
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
)paren
OL
id|sb-&gt;s_blocksize
)paren
(brace
id|bit
op_assign
id|block
op_mod
(paren
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udf_test_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
(brace
r_goto
id|got_block
suffix:semicolon
)brace
id|end_goal
op_assign
(paren
id|bit
op_plus
l_int|63
)paren
op_amp
op_complement
l_int|63
suffix:semicolon
id|bit
op_assign
id|udf_find_next_one_bit
c_func
(paren
id|bh-&gt;b_data
comma
id|end_goal
comma
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
id|end_goal
)paren
r_goto
id|got_block
suffix:semicolon
id|ptr
op_assign
id|memscan
c_func
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
(paren
id|bit
op_rshift
l_int|3
)paren
comma
l_int|0xFF
comma
id|sb-&gt;s_blocksize
op_minus
(paren
(paren
id|bit
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
)paren
suffix:semicolon
id|newbit
op_assign
(paren
id|ptr
op_minus
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|newbit
OL
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
(brace
id|bit
op_assign
id|newbit
suffix:semicolon
r_goto
id|search_back
suffix:semicolon
)brace
id|newbit
op_assign
id|udf_find_next_one_bit
c_func
(paren
id|bh-&gt;b_data
comma
id|sb-&gt;s_blocksize
op_lshift
l_int|3
comma
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newbit
OL
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
(brace
id|bit
op_assign
id|newbit
suffix:semicolon
r_goto
id|got_block
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
(paren
id|nr_groups
op_star
l_int|2
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|block_group
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|block_group
op_ge
id|nr_groups
)paren
id|block_group
op_assign
l_int|0
suffix:semicolon
id|group_start
op_assign
id|block_group
ques
c_cond
l_int|0
suffix:colon
r_sizeof
(paren
r_struct
id|SpaceBitmapDesc
)paren
suffix:semicolon
id|bitmap_nr
op_assign
id|load_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bitmap_nr
OL
l_int|0
)paren
r_goto
id|error_return
suffix:semicolon
id|bh
op_assign
id|UDF_SB_BLOCK_BITMAP
c_func
(paren
id|sb
comma
id|bitmap_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|nr_groups
)paren
(brace
id|ptr
op_assign
id|memscan
c_func
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
id|group_start
comma
l_int|0xFF
comma
id|sb-&gt;s_blocksize
op_minus
id|group_start
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptr
op_minus
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
)paren
OL
id|sb-&gt;s_blocksize
)paren
(brace
id|bit
op_assign
(paren
id|ptr
op_minus
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|bit
op_assign
id|udf_find_next_one_bit
c_func
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
comma
id|sb-&gt;s_blocksize
op_lshift
l_int|3
comma
id|group_start
op_lshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_ge
(paren
id|nr_groups
op_star
l_int|2
)paren
)paren
(brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|newblock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bit
OL
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
r_goto
id|search_back
suffix:semicolon
r_else
id|bit
op_assign
id|udf_find_next_one_bit
c_func
(paren
id|bh-&gt;b_data
comma
id|sb-&gt;s_blocksize
op_lshift
l_int|3
comma
id|group_start
op_lshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
op_ge
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
(brace
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
id|search_back
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
(paren
id|group_start
op_lshift
l_int|3
)paren
op_logical_and
id|udf_test_bit
c_func
(paren
id|bit
op_minus
l_int|1
comma
id|bh-&gt;b_data
)paren
suffix:semicolon
id|i
op_increment
comma
id|bit
op_decrement
)paren
suffix:semicolon
id|got_block
suffix:colon
id|newblock
op_assign
id|bit
op_plus
(paren
id|block_group
op_lshift
(paren
id|sb-&gt;s_blocksize_bits
op_plus
l_int|3
)paren
)paren
op_minus
(paren
id|group_start
op_lshift
l_int|3
)paren
suffix:semicolon
id|tmp
op_assign
id|udf_get_pblock
c_func
(paren
id|sb
comma
id|newblock
comma
id|partition
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|udf_clear_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;bit already cleared for block %d&bslash;n&quot;
comma
id|bit
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
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
id|tmp
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;cannot get block %d&bslash;n&quot;
comma
id|tmp
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
id|memset
c_func
(paren
id|bh-&gt;b_data
comma
l_int|0
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
(brace
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|freeSpaceTable
(braket
id|partition
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|freeSpaceTable
(braket
id|partition
)braket
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
op_star
id|err
op_assign
l_int|0
suffix:semicolon
r_return
id|newblock
suffix:semicolon
id|error_return
suffix:colon
op_star
id|err
op_assign
op_minus
id|EIO
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
eof
