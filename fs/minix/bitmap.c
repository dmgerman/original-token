multiline_comment|/*&n; *  linux/fs/minix/bitmap.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * Modified for 680x0 by Hamish Macdonald&n; * Fixed for 680x0 by Andreas Schwab&n; */
multiline_comment|/* bitmap.c contains the code that handles the inode and block bitmaps */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|variable|nibblemap
r_static
r_int
id|nibblemap
(braket
)braket
op_assign
(brace
l_int|4
comma
l_int|3
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|3
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
l_int|0
)brace
suffix:semicolon
DECL|function|count_free
r_static
r_int
r_int
id|count_free
c_func
(paren
r_struct
id|buffer_head
op_star
id|map
(braket
)braket
comma
r_int
id|numblocks
comma
id|__u32
id|numbits
)paren
(brace
r_int
id|i
comma
id|j
comma
id|sum
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
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
id|numblocks
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|map
(braket
id|i
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|BLOCK_SIZE
suffix:semicolon
id|j
op_increment
)paren
id|sum
op_add_assign
id|nibblemap
(braket
id|bh-&gt;b_data
(braket
id|j
)braket
op_amp
l_int|0xf
)braket
op_plus
id|nibblemap
(braket
(paren
id|bh-&gt;b_data
(braket
id|j
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numblocks
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|map
(braket
id|numblocks
op_minus
l_int|1
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
(paren
(paren
id|numbits
op_minus
(paren
id|numblocks
op_minus
l_int|1
)paren
op_star
id|BLOCK_SIZE
op_star
l_int|8
)paren
op_div
l_int|16
)paren
op_star
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sum
op_add_assign
id|nibblemap
(braket
id|bh-&gt;b_data
(braket
id|j
)braket
op_amp
l_int|0xf
)braket
op_plus
id|nibblemap
(braket
(paren
id|bh-&gt;b_data
(braket
id|j
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
id|i
op_assign
id|numbits
op_mod
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
(brace
id|i
op_assign
op_star
(paren
id|__u16
op_star
)paren
(paren
op_amp
id|bh-&gt;b_data
(braket
id|j
)braket
)paren
op_or
op_complement
(paren
(paren
l_int|1
op_lshift
id|i
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|sum
op_add_assign
id|nibblemap
(braket
id|i
op_amp
l_int|0xf
)braket
op_plus
id|nibblemap
(braket
(paren
id|i
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
id|sum
op_add_assign
id|nibblemap
(braket
(paren
id|i
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
)braket
op_plus
id|nibblemap
(braket
(paren
id|i
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
r_return
id|sum
suffix:semicolon
)brace
DECL|function|minix_free_block
r_void
id|minix_free_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|bit
comma
id|zone
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
l_string|&quot;trying to free block on nonexistent device&bslash;n&quot;
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
id|sb-&gt;u.minix_sb.s_firstdatazone
op_logical_or
id|block
op_ge
id|sb-&gt;u.minix_sb.s_nzones
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;trying to free block not in datazone&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|clear_bit
c_func
(paren
id|BH_Dirty
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|zone
op_assign
id|block
op_minus
id|sb-&gt;u.minix_sb.s_firstdatazone
op_plus
l_int|1
suffix:semicolon
id|bit
op_assign
id|zone
op_amp
l_int|8191
suffix:semicolon
id|zone
op_rshift_assign
l_int|13
suffix:semicolon
r_if
c_cond
(paren
id|zone
op_ge
id|sb-&gt;u.minix_sb.s_zmap_blocks
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_free_block: nonexistent bitmap buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh
op_assign
id|sb-&gt;u.minix_sb.s_zmap
(braket
id|zone
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minix_clear_bit
c_func
(paren
id|bit
comma
id|bh-&gt;b_data
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;free_block (%s:%d): bit already cleared&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
comma
id|block
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
r_return
suffix:semicolon
)brace
DECL|function|minix_new_block
r_int
id|minix_new_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
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
id|j
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
l_string|&quot;trying to get new block from nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|repeat
suffix:colon
id|j
op_assign
l_int|8192
suffix:semicolon
id|bh
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
id|sb-&gt;u.minix_sb.s_zmap_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh
op_assign
id|sb-&gt;u.minix_sb.s_zmap
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|j
op_assign
id|minix_find_first_zero_bit
c_func
(paren
id|bh-&gt;b_data
comma
l_int|8192
)paren
)paren
OL
l_int|8192
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|j
op_ge
l_int|8192
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|minix_set_bit
c_func
(paren
id|j
comma
id|bh-&gt;b_data
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;new_block: bit already set&quot;
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
id|j
op_add_assign
id|i
op_star
l_int|8192
op_plus
id|sb-&gt;u.minix_sb.s_firstdatazone
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|sb-&gt;u.minix_sb.s_firstdatazone
op_logical_or
id|j
op_ge
id|sb-&gt;u.minix_sb.s_nzones
)paren
r_return
l_int|0
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
id|j
comma
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;new_block: cannot get block&quot;
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
id|BLOCK_SIZE
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
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|j
suffix:semicolon
)brace
DECL|function|minix_count_free_blocks
r_int
r_int
id|minix_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
(paren
id|count_free
c_func
(paren
id|sb-&gt;u.minix_sb.s_zmap
comma
id|sb-&gt;u.minix_sb.s_zmap_blocks
comma
id|sb-&gt;u.minix_sb.s_nzones
op_minus
id|sb-&gt;u.minix_sb.s_firstdatazone
op_plus
l_int|1
)paren
op_lshift
id|sb-&gt;u.minix_sb.s_log_zone_size
)paren
suffix:semicolon
)brace
DECL|function|V1_minix_clear_inode
r_static
r_struct
id|buffer_head
op_star
id|V1_minix_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|ino
comma
id|block
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
op_logical_or
id|ino
OG
id|inode-&gt;i_sb-&gt;u.minix_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad inode number on dev %s: %d is out of range&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|block
op_assign
(paren
l_int|2
op_plus
id|inode-&gt;i_sb-&gt;u.minix_sb.s_imap_blocks
op_plus
id|inode-&gt;i_sb-&gt;u.minix_sb.s_zmap_blocks
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|MINIX_INODES_PER_BLOCK
)paren
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
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
l_string|&quot;unable to read i-node block&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|raw_inode
op_assign
(paren
(paren
r_struct
id|minix_inode
op_star
)paren
id|bh-&gt;b_data
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_mod
id|MINIX_INODES_PER_BLOCK
)paren
suffix:semicolon
id|raw_inode-&gt;i_nlinks
op_assign
l_int|0
suffix:semicolon
id|raw_inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|V2_minix_clear_inode
r_static
r_struct
id|buffer_head
op_star
id|V2_minix_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|minix2_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|ino
comma
id|block
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
op_logical_or
id|ino
OG
id|inode-&gt;i_sb-&gt;u.minix_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad inode number on dev %s: %d is out of range&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|block
op_assign
(paren
l_int|2
op_plus
id|inode-&gt;i_sb-&gt;u.minix_sb.s_imap_blocks
op_plus
id|inode-&gt;i_sb-&gt;u.minix_sb.s_zmap_blocks
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|MINIX2_INODES_PER_BLOCK
)paren
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
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
l_string|&quot;unable to read i-node block&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|raw_inode
op_assign
(paren
(paren
r_struct
id|minix2_inode
op_star
)paren
id|bh-&gt;b_data
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_mod
id|MINIX2_INODES_PER_BLOCK
)paren
suffix:semicolon
id|raw_inode-&gt;i_nlinks
op_assign
l_int|0
suffix:semicolon
id|raw_inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
multiline_comment|/* Clear the link count and mode of a deleted inode on disk. */
DECL|function|minix_clear_inode
r_static
r_void
id|minix_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
id|INODE_VERSION
c_func
(paren
id|inode
)paren
op_eq
id|MINIX_V1
)paren
id|bh
op_assign
id|V1_minix_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|V2_minix_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|minix_free_inode
r_void
id|minix_free_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|ino
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
c_func
(paren
l_string|&quot;free_inode: inode has no device&bslash;n&quot;
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
c_func
(paren
l_string|&quot;free_inode: inode has count=%d&bslash;n&quot;
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
c_func
(paren
l_string|&quot;free_inode: inode has nlink=%d&bslash;n&quot;
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
l_string|&quot;free_inode: inode on nonexistent device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_ino
template_param
id|inode-&gt;i_sb-&gt;u.minix_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;free_inode: inode 0 or nonexistent inode&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ino
op_rshift
l_int|13
)paren
op_ge
id|inode-&gt;i_sb-&gt;u.minix_sb.s_imap_blocks
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;free_inode: nonexistent imap in superblock&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh
op_assign
id|inode-&gt;i_sb-&gt;u.minix_sb.s_imap
(braket
id|ino
op_rshift
l_int|13
)braket
suffix:semicolon
id|minix_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minix_clear_bit
c_func
(paren
id|ino
op_amp
l_int|8191
comma
id|bh-&gt;b_data
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;free_inode: bit %lu already cleared.&bslash;n&quot;
comma
id|ino
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
)brace
DECL|function|minix_new_inode
r_struct
id|inode
op_star
id|minix_new_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
comma
id|j
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
c_func
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
l_int|0
suffix:semicolon
id|j
op_assign
l_int|8192
suffix:semicolon
id|bh
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
id|sb-&gt;u.minix_sb.s_imap_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh
op_assign
id|inode-&gt;i_sb-&gt;u.minix_sb.s_imap
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|j
op_assign
id|minix_find_first_zero_bit
c_func
(paren
id|bh-&gt;b_data
comma
l_int|8192
)paren
)paren
OL
l_int|8192
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|j
op_ge
l_int|8192
)paren
(brace
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
r_if
c_cond
(paren
id|minix_set_bit
c_func
(paren
id|j
comma
id|bh-&gt;b_data
)paren
)paren
(brace
multiline_comment|/* shouldn&squot;t happen */
id|printk
c_func
(paren
l_string|&quot;new_inode: bit already set&quot;
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
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|j
op_add_assign
id|i
op_star
l_int|8192
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|j
op_logical_or
id|j
OG
id|inode-&gt;i_sb-&gt;u.minix_sb.s_ninodes
)paren
(brace
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
id|inode-&gt;i_gid
op_assign
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
ques
c_cond
id|dir-&gt;i_gid
suffix:colon
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|j
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|minix_count_free_inodes
r_int
r_int
id|minix_count_free_inodes
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|count_free
c_func
(paren
id|sb-&gt;u.minix_sb.s_imap
comma
id|sb-&gt;u.minix_sb.s_imap_blocks
comma
id|sb-&gt;u.minix_sb.s_ninodes
op_plus
l_int|1
)paren
suffix:semicolon
)brace
eof
