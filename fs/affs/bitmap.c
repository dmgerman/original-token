multiline_comment|/*&n; *  linux/fs/affs/bitmap.c&n; *&n; *  (c) 1996 Hans-Joachim Widmaier&n; *&n; *  bitmap.c contains the code that handles all bitmap related stuff -&n; *  block allocation, deallocation, calculation of free space.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/* This is, of course, shamelessly stolen from fs/minix */
DECL|variable|nibblemap
r_static
r_int
id|nibblemap
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
)brace
suffix:semicolon
r_int
DECL|function|affs_count_free_bits
id|affs_count_free_bits
c_func
(paren
r_int
id|blocksize
comma
r_const
r_char
op_star
id|data
)paren
(brace
r_int
id|free
suffix:semicolon
r_int
id|i
suffix:semicolon
id|free
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
id|blocksize
suffix:semicolon
id|i
op_increment
)paren
(brace
id|free
op_add_assign
id|nibblemap
(braket
id|data
(braket
id|i
)braket
op_amp
l_int|0xF
)braket
op_plus
id|nibblemap
(braket
(paren
id|data
(braket
id|i
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0xF
)braket
suffix:semicolon
)brace
r_return
id|free
suffix:semicolon
)brace
r_int
DECL|function|affs_count_free_blocks
id|affs_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_int
id|free
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: count_free_blocks()&bslash;n&quot;
)paren
suffix:semicolon
id|free
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;u.affs_sb.s_flags
op_amp
id|SF_BM_VALID
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
id|s-&gt;u.affs_sb.s_num_az
suffix:semicolon
id|i
op_increment
)paren
(brace
id|free
op_add_assign
id|s-&gt;u.affs_sb.s_alloc
(braket
id|i
)braket
dot
id|az_free
suffix:semicolon
)brace
)brace
r_return
id|free
suffix:semicolon
)brace
r_void
DECL|function|affs_free_block
id|affs_free_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|s32
id|block
)paren
(brace
r_int
id|bmap
suffix:semicolon
r_int
id|bit
suffix:semicolon
r_int
id|blk
suffix:semicolon
r_int
id|zone_no
suffix:semicolon
r_struct
id|affs_bm_info
op_star
id|bm
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: free_block(%d)&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|blk
op_assign
id|block
op_minus
id|sb-&gt;u.affs_sb.s_reserved
suffix:semicolon
id|bmap
op_assign
id|blk
op_div
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
op_minus
l_int|32
)paren
suffix:semicolon
id|bit
op_assign
id|blk
op_mod
(paren
id|sb-&gt;s_blocksize
op_star
l_int|8
op_minus
l_int|32
)paren
suffix:semicolon
id|zone_no
op_assign
(paren
id|bmap
op_lshift
(paren
id|sb-&gt;s_blocksize_bits
op_minus
l_int|7
)paren
)paren
op_plus
id|bit
op_div
l_int|1024
suffix:semicolon
id|bm
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_bitmap
(braket
id|bmap
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bmap
op_ge
id|sb-&gt;u.affs_sb.s_bm_count
)paren
(brace
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;affs_free_block&quot;
comma
l_string|&quot;Block %d outside partition&quot;
comma
id|block
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|blk
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|bit
op_amp
l_int|31
comma
op_amp
id|blk
)paren
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bm-&gt;bm_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm-&gt;bm_bh
)paren
(brace
id|bm-&gt;bm_bh
op_assign
id|affs_bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|bm-&gt;bm_key
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm-&gt;bm_bh
)paren
(brace
id|bm-&gt;bm_count
op_decrement
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;affs_free_block&quot;
comma
l_string|&quot;Cannot read bitmap block %d&quot;
comma
id|bm-&gt;bm_key
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|bit
op_xor
id|BO_EXBITS
comma
id|bm-&gt;bm_bh-&gt;b_data
op_plus
l_int|4
)paren
)paren
id|affs_warning
c_func
(paren
id|sb
comma
l_string|&quot;affs_free_block&quot;
comma
l_string|&quot;Trying to free block %d which is already free&quot;
comma
id|block
)paren
suffix:semicolon
r_else
(brace
id|sb-&gt;u.affs_sb.s_alloc
(braket
id|zone_no
)braket
dot
id|az_free
op_increment
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|bm-&gt;bm_bh-&gt;b_data
)paren
(braket
l_int|0
)braket
op_assign
id|ntohl
c_func
(paren
id|htonl
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
id|bm-&gt;bm_bh-&gt;b_data
)paren
(braket
l_int|0
)braket
)paren
op_minus
id|blk
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bm-&gt;bm_bh
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|bm-&gt;bm_count
op_eq
l_int|0
)paren
(brace
id|affs_brelse
c_func
(paren
id|bm-&gt;bm_bh
)paren
suffix:semicolon
id|bm-&gt;bm_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
r_static
id|s32
DECL|function|affs_balloc
id|affs_balloc
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|zone_no
)paren
(brace
id|u32
id|w
suffix:semicolon
id|u32
op_star
id|bm
suffix:semicolon
r_int
id|fb
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|fwb
suffix:semicolon
id|s32
id|block
suffix:semicolon
r_struct
id|affs_zone
op_star
id|zone
suffix:semicolon
r_struct
id|affs_alloc_zone
op_star
id|az
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
id|zone
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_zones
(braket
id|zone_no
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zone-&gt;z_bm
op_logical_or
op_logical_neg
id|zone-&gt;z_bm-&gt;bm_bh
)paren
r_return
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: balloc(inode=%lu,zone=%d)&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|zone_no
)paren
suffix:semicolon
id|az
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_alloc
(braket
id|zone-&gt;z_az_no
)braket
suffix:semicolon
id|bm
op_assign
(paren
id|u32
op_star
)paren
id|zone-&gt;z_bm-&gt;bm_bh-&gt;b_data
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|zone-&gt;z_start
suffix:semicolon
id|i
OL
id|zone-&gt;z_end
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bm
(braket
id|i
)braket
)paren
r_goto
id|found
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|found
suffix:colon
id|fwb
op_assign
id|zone-&gt;z_bm-&gt;bm_firstblk
op_plus
(paren
id|i
op_minus
l_int|1
)paren
op_star
l_int|32
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|zone-&gt;z_start
op_assign
id|i
suffix:semicolon
id|w
op_assign
op_complement
id|htonl
c_func
(paren
id|bm
(braket
id|i
)braket
)paren
suffix:semicolon
id|fb
op_assign
id|find_first_zero_bit
c_func
(paren
op_amp
id|w
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fb
OG
l_int|31
op_logical_or
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|fb
op_xor
id|BO_EXBITS
comma
op_amp
id|bm
(braket
id|i
)braket
)paren
)paren
(brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|affs_warning
c_func
(paren
id|sb
comma
l_string|&quot;balloc&quot;
comma
l_string|&quot;Empty block disappeared somehow&quot;
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|block
op_assign
id|fwb
op_plus
id|fb
suffix:semicolon
id|az-&gt;az_free
op_decrement
suffix:semicolon
multiline_comment|/* prealloc as much as possible within this word, but not in header zone */
r_if
c_cond
(paren
id|zone_no
)paren
(brace
r_while
c_loop
(paren
id|inode-&gt;u.affs_i.i_pa_cnt
OL
id|AFFS_MAX_PREALLOC
op_logical_and
op_increment
id|fb
OL
l_int|32
)paren
(brace
id|fb
op_assign
id|find_next_zero_bit
c_func
(paren
op_amp
id|w
comma
l_int|32
comma
id|fb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fb
OG
l_int|31
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|fb
op_xor
id|BO_EXBITS
comma
op_amp
id|bm
(braket
id|i
)braket
)paren
)paren
(brace
id|affs_warning
c_func
(paren
id|sb
comma
l_string|&quot;balloc&quot;
comma
l_string|&quot;Empty block disappeared somehow&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|inode-&gt;u.affs_i.i_data
(braket
id|inode-&gt;u.affs_i.i_pa_last
op_increment
)braket
op_assign
id|fwb
op_plus
id|fb
suffix:semicolon
id|inode-&gt;u.affs_i.i_pa_last
op_and_assign
id|AFFS_MAX_PREALLOC
op_minus
l_int|1
suffix:semicolon
id|inode-&gt;u.affs_i.i_pa_cnt
op_increment
suffix:semicolon
id|az-&gt;az_free
op_decrement
suffix:semicolon
)brace
)brace
id|w
op_assign
op_complement
id|w
op_minus
id|htonl
c_func
(paren
id|bm
(braket
id|i
)braket
)paren
suffix:semicolon
id|bm
(braket
l_int|0
)braket
op_assign
id|ntohl
c_func
(paren
id|htonl
c_func
(paren
id|bm
(braket
l_int|0
)braket
)paren
op_plus
id|w
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|zone-&gt;z_bm-&gt;bm_bh
comma
l_int|1
)paren
suffix:semicolon
id|zone-&gt;z_lru_time
op_assign
id|jiffies
suffix:semicolon
r_return
id|block
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_find_new_zone
id|affs_find_new_zone
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|zone_no
)paren
(brace
r_struct
id|affs_bm_info
op_star
id|bm
suffix:semicolon
r_struct
id|affs_zone
op_star
id|zone
suffix:semicolon
r_struct
id|affs_alloc_zone
op_star
id|az
suffix:semicolon
r_int
id|bestfree
suffix:semicolon
r_int
id|bestno
suffix:semicolon
r_int
id|bestused
suffix:semicolon
r_int
id|lusers
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|min
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: find_new_zone(zone_no=%d)&bslash;n&quot;
comma
id|zone_no
)paren
suffix:semicolon
id|bestfree
op_assign
l_int|0
suffix:semicolon
id|bestused
op_assign
op_minus
l_int|1
suffix:semicolon
id|bestno
op_assign
op_minus
l_int|1
suffix:semicolon
id|lusers
op_assign
id|MAX_ZONES
suffix:semicolon
id|min
op_assign
id|zone_no
ques
c_cond
id|AFFS_DATA_MIN_FREE
suffix:colon
id|AFFS_HDR_MIN_FREE
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|zone
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_zones
(braket
id|zone_no
)braket
suffix:semicolon
id|i
op_assign
id|zone-&gt;z_az_no
suffix:semicolon
id|az
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_alloc
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;z_bm
op_logical_and
id|zone-&gt;z_bm-&gt;bm_count
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|zone-&gt;z_bm-&gt;bm_count
op_eq
l_int|0
)paren
(brace
id|affs_brelse
c_func
(paren
id|zone-&gt;z_bm-&gt;bm_bh
)paren
suffix:semicolon
id|zone-&gt;z_bm-&gt;bm_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|az-&gt;az_count
)paren
id|az-&gt;az_count
op_decrement
suffix:semicolon
r_else
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;find_new_zone&quot;
comma
l_string|&quot;az_count=0, but bm used&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|i
op_ge
id|sb-&gt;u.affs_sb.s_num_az
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|az
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_alloc
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|az-&gt;az_count
)paren
(brace
r_if
c_cond
(paren
id|az-&gt;az_free
OG
id|min
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|az-&gt;az_free
OG
id|bestfree
)paren
(brace
id|bestfree
op_assign
id|az-&gt;az_free
suffix:semicolon
id|bestno
op_assign
id|i
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|az-&gt;az_free
op_logical_and
id|az-&gt;az_count
OL
id|lusers
)paren
(brace
id|lusers
op_assign
id|az-&gt;az_count
suffix:semicolon
id|bestused
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|i
op_eq
id|zone-&gt;z_az_no
)paren
(brace
multiline_comment|/* Seen all */
r_if
c_cond
(paren
id|bestno
op_ge
l_int|0
)paren
(brace
id|i
op_assign
id|bestno
suffix:semicolon
)brace
r_else
(brace
id|i
op_assign
id|bestused
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
multiline_comment|/* Didn&squot;t find a single free block anywhere. */
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
id|az
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_alloc
(braket
id|i
)braket
suffix:semicolon
id|az-&gt;az_count
op_increment
suffix:semicolon
id|bm
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_bitmap
(braket
id|i
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
op_minus
l_int|7
)paren
)braket
suffix:semicolon
id|bm-&gt;bm_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm-&gt;bm_bh
)paren
id|bm-&gt;bm_bh
op_assign
id|affs_bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|bm-&gt;bm_key
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm-&gt;bm_bh
)paren
(brace
id|bm-&gt;bm_count
op_decrement
suffix:semicolon
id|az-&gt;az_count
op_decrement
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|affs_error
c_func
(paren
id|sb
comma
l_string|&quot;find_new_zone&quot;
comma
l_string|&quot;Cannot read bitmap&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|zone-&gt;z_bm
op_assign
id|bm
suffix:semicolon
id|zone-&gt;z_start
op_assign
(paren
id|i
op_amp
(paren
(paren
id|sb-&gt;s_blocksize
op_div
l_int|128
)paren
op_minus
l_int|1
)paren
)paren
op_star
l_int|32
op_plus
l_int|1
suffix:semicolon
id|zone-&gt;z_end
op_assign
id|zone-&gt;z_start
op_plus
id|az-&gt;az_size
suffix:semicolon
id|zone-&gt;z_az_no
op_assign
id|i
suffix:semicolon
id|zone-&gt;z_lru_time
op_assign
id|jiffies
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;  ++ found zone (%d) in bm %d at lw offset %d with %d free blocks&bslash;n&quot;
comma
id|i
comma
(paren
id|i
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
op_minus
l_int|7
)paren
)paren
comma
id|zone-&gt;z_start
comma
id|az-&gt;az_free
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|az-&gt;az_free
suffix:semicolon
)brace
id|s32
DECL|function|affs_new_header
id|affs_new_header
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|s32
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: new_header(ino=%lu)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|affs_balloc
c_func
(paren
id|inode
comma
l_int|0
)paren
)paren
)paren
(brace
r_while
c_loop
(paren
id|affs_find_new_zone
c_func
(paren
id|inode-&gt;i_sb
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|block
op_assign
id|affs_balloc
c_func
(paren
id|inode
comma
l_int|0
)paren
)paren
)paren
r_goto
id|init_block
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|init_block
suffix:colon
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
id|inode-&gt;i_dev
comma
id|block
comma
id|AFFS_I2BSIZE
c_func
(paren
id|inode
)paren
)paren
)paren
)paren
(brace
id|affs_error
c_func
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;new_header&quot;
comma
l_string|&quot;Cannot read block %d&quot;
comma
id|block
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
id|AFFS_I2BSIZE
c_func
(paren
id|inode
)paren
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
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|block
suffix:semicolon
)brace
id|s32
DECL|function|affs_new_data
id|affs_new_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|empty
comma
id|old
suffix:semicolon
r_int
r_int
id|oldest
suffix:semicolon
r_struct
id|affs_zone
op_star
id|zone
suffix:semicolon
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
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|s32
id|block
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: new_data(ino=%lu)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
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
id|inode-&gt;u.affs_i.i_pa_cnt
)paren
(brace
id|inode-&gt;u.affs_i.i_pa_cnt
op_decrement
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|block
op_assign
id|inode-&gt;u.affs_i.i_data
(braket
id|inode-&gt;u.affs_i.i_pa_next
op_increment
)braket
suffix:semicolon
id|inode-&gt;u.affs_i.i_pa_next
op_and_assign
id|AFFS_MAX_PREALLOC
op_minus
l_int|1
suffix:semicolon
r_goto
id|init_block
suffix:semicolon
)brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|oldest
op_assign
id|jiffies
suffix:semicolon
id|old
op_assign
l_int|0
suffix:semicolon
id|empty
op_assign
l_int|0
suffix:semicolon
id|zone
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_zones
(braket
id|inode-&gt;u.affs_i.i_zone
)braket
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;z_ino
op_eq
id|inode-&gt;i_ino
)paren
(brace
id|i
op_assign
id|inode-&gt;u.affs_i.i_zone
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|MAX_ZONES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|zone
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_zones
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty
op_logical_and
id|zone-&gt;z_bm
op_logical_and
op_logical_neg
id|zone-&gt;z_ino
)paren
id|empty
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;z_bm
op_logical_and
id|zone-&gt;z_lru_time
OL
id|oldest
)paren
(brace
id|old
op_assign
id|i
suffix:semicolon
id|oldest
op_assign
id|zone-&gt;z_lru_time
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|empty
)paren
id|i
op_assign
id|empty
suffix:semicolon
r_else
r_if
c_cond
(paren
id|old
)paren
id|i
op_assign
id|old
suffix:semicolon
r_else
(brace
id|inode-&gt;u.affs_i.i_zone
op_assign
l_int|0
suffix:semicolon
r_return
id|affs_new_header
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|inode-&gt;u.affs_i.i_zone
op_assign
id|i
suffix:semicolon
id|zone-&gt;z_ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|found
suffix:colon
id|zone
op_assign
op_amp
id|sb-&gt;u.affs_sb.s_zones
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|affs_balloc
c_func
(paren
id|inode
comma
id|i
)paren
)paren
)paren
(brace
multiline_comment|/* No data zones left */
r_while
c_loop
(paren
id|affs_find_new_zone
c_func
(paren
id|sb
comma
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|block
op_assign
id|affs_balloc
c_func
(paren
id|inode
comma
id|i
)paren
)paren
)paren
r_goto
id|init_block
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|inode-&gt;u.affs_i.i_zone
op_assign
l_int|0
suffix:semicolon
id|zone-&gt;z_ino
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|init_block
suffix:colon
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
id|inode-&gt;i_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
id|affs_error
c_func
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;new_data&quot;
comma
l_string|&quot;Cannot read block %d&quot;
comma
id|block
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
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|block
suffix:semicolon
)brace
r_void
DECL|function|affs_make_zones
id|affs_make_zones
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|i
comma
id|mid
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: make_zones(): num_zones=%d&bslash;n&quot;
comma
id|sb-&gt;u.affs_sb.s_num_az
)paren
suffix:semicolon
id|mid
op_assign
(paren
id|sb-&gt;u.affs_sb.s_num_az
op_plus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
id|sb-&gt;u.affs_sb.s_zones
(braket
l_int|0
)braket
dot
id|z_az_no
op_assign
id|mid
suffix:semicolon
id|affs_find_new_zone
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|MAX_ZONES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sb-&gt;u.affs_sb.s_zones
(braket
id|i
)braket
dot
id|z_az_no
op_assign
id|mid
suffix:semicolon
id|affs_find_new_zone
c_func
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
)brace
)brace
eof
