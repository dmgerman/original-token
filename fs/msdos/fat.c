multiline_comment|/*&n; *  linux/fs/msdos/fat.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; */
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|variable|fat_cache
DECL|variable|cache
r_static
r_struct
id|fat_cache
op_star
id|fat_cache
comma
id|cache
(braket
id|FAT_CACHE
)braket
suffix:semicolon
multiline_comment|/* Returns the this&squot;th FAT entry, -1 if it is an end-of-file entry. If&n;   new_value is != -1, that FAT entry is replaced by it. */
DECL|function|fat_access
r_int
id|fat_access
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|this
comma
r_int
id|new_value
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|bh2
comma
op_star
id|c_bh
comma
op_star
id|c_bh2
suffix:semicolon
r_int
r_char
op_star
id|p_first
comma
op_star
id|p_last
suffix:semicolon
r_void
op_star
id|data
comma
op_star
id|data2
comma
op_star
id|c_data
comma
op_star
id|c_data2
suffix:semicolon
r_int
id|first
comma
id|last
comma
id|next
comma
id|copy
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|this
op_minus
l_int|2
)paren
op_ge
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|16
)paren
id|first
op_assign
id|last
op_assign
id|this
op_star
l_int|2
suffix:semicolon
r_else
(brace
id|first
op_assign
id|this
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
id|last
op_assign
id|first
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|msdos_sread
c_func
(paren
id|sb-&gt;s_dev
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_start
op_plus
(paren
id|first
op_rshift
id|SECTOR_BITS
)paren
comma
op_amp
id|data
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bread in fat_access failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|first
op_rshift
id|SECTOR_BITS
)paren
op_eq
(paren
id|last
op_rshift
id|SECTOR_BITS
)paren
)paren
(brace
id|bh2
op_assign
id|bh
suffix:semicolon
id|data2
op_assign
id|data
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh2
op_assign
id|msdos_sread
c_func
(paren
id|sb-&gt;s_dev
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_start
op_plus
(paren
id|last
op_rshift
id|SECTOR_BITS
)paren
comma
op_amp
id|data2
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;bread in fat_access failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|16
)paren
(brace
id|p_first
op_assign
id|p_last
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* GCC needs that stuff */
id|next
op_assign
id|CF_LE_W
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
(braket
(paren
id|first
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ge
l_int|0xfff7
)paren
id|next
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|p_first
op_assign
op_amp
(paren
(paren
r_int
r_char
op_star
)paren
id|data
)paren
(braket
id|first
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|p_last
op_assign
op_amp
(paren
(paren
r_int
r_char
op_star
)paren
id|data2
)paren
(braket
(paren
id|first
op_plus
l_int|1
)paren
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|this
op_amp
l_int|1
)paren
id|next
op_assign
(paren
(paren
op_star
id|p_first
op_rshift
l_int|4
)paren
op_or
(paren
op_star
id|p_last
op_lshift
l_int|4
)paren
)paren
op_amp
l_int|0xfff
suffix:semicolon
r_else
id|next
op_assign
(paren
op_star
id|p_first
op_plus
(paren
op_star
id|p_last
op_lshift
l_int|8
)paren
)paren
op_amp
l_int|0xfff
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ge
l_int|0xff7
)paren
id|next
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_value
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|16
)paren
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
(braket
(paren
id|first
op_amp
(paren
id|SECTOR_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
l_int|1
)braket
op_assign
id|CT_LE_W
c_func
(paren
id|new_value
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|this
op_amp
l_int|1
)paren
(brace
op_star
id|p_first
op_assign
(paren
op_star
id|p_first
op_amp
l_int|0xf
)paren
op_or
(paren
id|new_value
op_lshift
l_int|4
)paren
suffix:semicolon
op_star
id|p_last
op_assign
id|new_value
op_rshift
l_int|4
suffix:semicolon
)brace
r_else
(brace
op_star
id|p_first
op_assign
id|new_value
op_amp
l_int|0xff
suffix:semicolon
op_star
id|p_last
op_assign
(paren
op_star
id|p_last
op_amp
l_int|0xf0
)paren
op_or
(paren
id|new_value
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|bh2-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|copy
op_assign
l_int|1
suffix:semicolon
id|copy
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fats
suffix:semicolon
id|copy
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|c_bh
op_assign
id|msdos_sread
c_func
(paren
id|sb-&gt;s_dev
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_start
op_plus
(paren
id|first
op_rshift
id|SECTOR_BITS
)paren
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_length
op_star
id|copy
comma
op_amp
id|c_data
)paren
)paren
)paren
r_break
suffix:semicolon
id|memcpy
c_func
(paren
id|c_data
comma
id|data
comma
id|SECTOR_SIZE
)paren
suffix:semicolon
id|c_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|data
op_ne
id|data2
op_logical_or
id|bh
op_ne
id|bh2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|c_bh2
op_assign
id|msdos_sread
c_func
(paren
id|sb-&gt;s_dev
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_start
op_plus
(paren
id|first
op_rshift
id|SECTOR_BITS
)paren
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_length
op_star
id|copy
op_plus
l_int|1
comma
op_amp
id|c_data2
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|c_bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|c_data2
comma
id|data2
comma
id|SECTOR_SIZE
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|c_bh2
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|c_bh
)paren
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_ne
id|data2
)paren
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
DECL|function|cache_init
r_void
id|cache_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|initialized
)paren
r_return
suffix:semicolon
id|fat_cache
op_assign
op_amp
id|cache
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|FAT_CACHE
suffix:semicolon
id|count
op_increment
)paren
(brace
id|cache
(braket
id|count
)braket
dot
id|device
op_assign
l_int|0
suffix:semicolon
id|cache
(braket
id|count
)braket
dot
id|next
op_assign
id|count
op_eq
id|FAT_CACHE
op_minus
l_int|1
ques
c_cond
l_int|NULL
suffix:colon
op_amp
id|cache
(braket
id|count
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|cache_lookup
r_void
id|cache_lookup
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
comma
r_int
op_star
id|f_clu
comma
r_int
op_star
id|d_clu
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cache lookup: &lt;%d,%d&gt; %d (%d,%d) -&gt; &quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|cluster
comma
op_star
id|f_clu
comma
op_star
id|d_clu
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_eq
id|walk-&gt;device
op_logical_and
id|walk-&gt;ino
op_eq
id|inode-&gt;i_ino
op_logical_and
id|walk-&gt;file_cluster
op_le
id|cluster
op_logical_and
id|walk-&gt;file_cluster
OG
op_star
id|f_clu
)paren
(brace
op_star
id|d_clu
op_assign
id|walk-&gt;disk_cluster
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cache hit: %d (%d)&bslash;n&quot;
comma
id|walk-&gt;file_cluster
comma
op_star
id|d_clu
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
op_star
id|f_clu
op_assign
id|walk-&gt;file_cluster
)paren
op_eq
id|cluster
)paren
r_return
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cache miss&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef DEBUG
DECL|function|list_cache
r_static
r_void
id|list_cache
c_func
(paren
r_void
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|walk-&gt;device
)paren
id|printk
c_func
(paren
l_string|&quot;&lt;%d,%d&gt;(%d,%d) &quot;
comma
id|walk-&gt;device
comma
id|walk-&gt;ino
comma
id|walk-&gt;file_cluster
comma
id|walk-&gt;disk_cluster
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;-- &quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|cache_add
r_void
id|cache_add
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|f_clu
comma
r_int
id|d_clu
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
comma
op_star
id|last
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;cache add: &lt;%d,%d&gt; %d (%d)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|f_clu
comma
id|d_clu
)paren
suffix:semicolon
macro_line|#endif
id|last
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk-&gt;next
suffix:semicolon
id|walk
op_assign
(paren
id|last
op_assign
id|walk
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_eq
id|walk-&gt;device
op_logical_and
id|walk-&gt;ino
op_eq
id|inode-&gt;i_ino
op_logical_and
id|walk-&gt;file_cluster
op_eq
id|f_clu
)paren
(brace
r_if
c_cond
(paren
id|walk-&gt;disk_cluster
op_ne
id|d_clu
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FAT cache corruption&quot;
)paren
suffix:semicolon
id|cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* update LRU */
r_if
c_cond
(paren
id|last
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|last-&gt;next
op_assign
id|walk-&gt;next
suffix:semicolon
id|walk-&gt;next
op_assign
id|fat_cache
suffix:semicolon
id|fat_cache
op_assign
id|walk
suffix:semicolon
macro_line|#ifdef DEBUG
id|list_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
id|walk-&gt;device
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|walk-&gt;ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|walk-&gt;file_cluster
op_assign
id|f_clu
suffix:semicolon
id|walk-&gt;disk_cluster
op_assign
id|d_clu
suffix:semicolon
id|last-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|walk-&gt;next
op_assign
id|fat_cache
suffix:semicolon
id|fat_cache
op_assign
id|walk
suffix:semicolon
macro_line|#ifdef DEBUG
id|list_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Cache invalidation occurs rarely, thus the LRU chain is not updated. It&n;   fixes itself after a while. */
DECL|function|cache_inval_inode
r_void
id|cache_inval_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|walk-&gt;device
op_eq
id|inode-&gt;i_dev
op_logical_and
id|walk-&gt;ino
op_eq
id|inode-&gt;i_ino
)paren
id|walk-&gt;device
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|cache_inval_dev
r_void
id|cache_inval_dev
c_func
(paren
r_int
id|device
)paren
(brace
r_struct
id|fat_cache
op_star
id|walk
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|fat_cache
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|walk-&gt;device
op_eq
id|device
)paren
id|walk-&gt;device
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|get_cluster
r_int
id|get_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
)paren
(brace
r_int
id|this
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|this
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cluster
)paren
r_return
id|this
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cache_lookup
c_func
(paren
id|inode
comma
id|cluster
comma
op_amp
id|count
comma
op_amp
id|this
)paren
suffix:semicolon
id|count
OL
id|cluster
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|this
op_assign
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|this
comma
op_minus
l_int|1
)paren
)paren
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|cache_add
c_func
(paren
id|inode
comma
id|cluster
comma
id|this
)paren
suffix:semicolon
r_return
id|this
suffix:semicolon
)brace
DECL|function|msdos_smap
r_int
id|msdos_smap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sector
)paren
(brace
r_struct
id|msdos_sb_info
op_star
id|sb
suffix:semicolon
r_int
id|cluster
comma
id|offset
suffix:semicolon
id|sb
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
)paren
(brace
r_if
c_cond
(paren
id|sector
op_ge
id|sb-&gt;dir_entries
op_rshift
id|MSDOS_DPS_BITS
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sector
op_plus
id|sb-&gt;dir_start
suffix:semicolon
)brace
id|cluster
op_assign
id|sector
op_div
id|sb-&gt;cluster_size
suffix:semicolon
id|offset
op_assign
id|sector
op_mod
id|sb-&gt;cluster_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cluster
op_assign
id|get_cluster
c_func
(paren
id|inode
comma
id|cluster
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|cluster
op_minus
l_int|2
)paren
op_star
id|sb-&gt;cluster_size
op_plus
id|sb-&gt;data_start
op_plus
id|offset
suffix:semicolon
)brace
multiline_comment|/* Free all clusters after the skip&squot;th cluster. Doesn&squot;t use the cache,&n;   because this way we get an additional sanity check. */
DECL|function|fat_free
r_int
id|fat_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|skip
)paren
(brace
r_int
id|this
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|this
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|last
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|skip
op_decrement
)paren
(brace
id|last
op_assign
id|this
suffix:semicolon
r_if
c_cond
(paren
(paren
id|this
op_assign
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|this
comma
op_minus
l_int|1
)paren
)paren
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fat_free: skipped EOF&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|last
)paren
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|last
comma
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|12
ques
c_cond
l_int|0xff8
suffix:colon
l_int|0xfff8
)paren
suffix:semicolon
r_else
(brace
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|lock_fat
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_while
c_loop
(paren
id|this
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|this
op_assign
id|fat_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|this
comma
l_int|0
)paren
)paren
)paren
(brace
id|fs_panic
c_func
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;fat_free: deleting beyond EOF&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|free_clusters
op_ne
op_minus
l_int|1
)paren
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|free_clusters
op_increment
suffix:semicolon
id|inode-&gt;i_blocks
op_sub_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
)brace
id|unlock_fat
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
