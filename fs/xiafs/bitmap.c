multiline_comment|/*&n; *  linux/fs/xiafs/bitmap.c&n; *&n; *  Copyright (C) Q. Frank Xia, 1993.&n; *  &n; *  Based on Linus&squot; minix/bitmap.c&n; *  Copyright (C) Linus Torvalds, 1991, 1992.&n; *  &n; *  This software may be redistributed per Linux Copyright.&n; */
multiline_comment|/* bitmap.c contains the code that handles the inode and block bitmaps */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/xia_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;xiafs_mac.h&quot;
DECL|macro|clear_bit
mdefine_line|#define clear_bit(nr,addr) ({&bslash;&n;char res; &bslash;&n;__asm__ __volatile__(&quot;btrl %1,%2&bslash;n&bslash;tsetnb %0&quot;: &bslash;&n;&quot;=q&quot; (res):&quot;r&quot; (nr),&quot;m&quot; (*(addr))); &bslash;&n;res;})
DECL|variable|internal_error_message
r_char
id|internal_error_message
(braket
)braket
op_assign
l_string|&quot;XIA-FS: internal error %s %d&bslash;n&quot;
suffix:semicolon
DECL|function|find_first_zero
r_static
r_int
id|find_first_zero
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|start_bit
comma
r_int
id|end_bit
)paren
(brace
multiline_comment|/* This routine searches first 0 bit from (start_bit) to (end_bit-1).&n;     * If found the bit is set to 1 and the bit # is returned, otherwise,&n;     * -1 is returned. Race condition is avoid by using &quot;btsl&quot; and &n;     * &quot;goto repeat&quot;.  ---Frank.&n;     */
r_int
id|end
comma
id|i
comma
id|j
comma
id|tmp
suffix:semicolon
id|u_long
op_star
id|bmap
suffix:semicolon
r_char
id|res
suffix:semicolon
id|bmap
op_assign
(paren
id|u_long
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|end
op_assign
id|end_bit
op_rshift
l_int|5
suffix:semicolon
id|repeat
suffix:colon
id|i
op_assign
id|start_bit
op_rshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_assign
(paren
op_complement
id|bmap
(braket
id|i
)braket
)paren
op_amp
(paren
l_int|0xffffffff
op_lshift
(paren
id|start_bit
op_amp
l_int|31
)paren
)paren
)paren
)paren
r_goto
id|zone_found
suffix:semicolon
r_while
c_loop
(paren
op_increment
id|i
OL
id|end
)paren
r_if
c_cond
(paren
op_complement
id|bmap
(braket
id|i
)braket
)paren
(brace
id|tmp
op_assign
op_complement
id|bmap
(braket
id|i
)braket
suffix:semicolon
r_goto
id|zone_found
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
op_complement
id|bmap
(braket
id|i
)braket
op_amp
(paren
(paren
l_int|1
op_lshift
(paren
id|end_bit
op_amp
l_int|31
)paren
)paren
op_minus
l_int|1
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|zone_found
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|32
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|tmp
op_amp
(paren
l_int|1
op_lshift
id|j
)paren
)paren
r_break
suffix:semicolon
id|__asm__
(paren
l_string|&quot;btsl %1,%2&bslash;n&bslash;tsetb %0&quot;
suffix:colon
"&bslash;"
l_string|&quot;=q&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|j
)paren
comma
l_string|&quot;m&quot;
(paren
id|bmap
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|start_bit
op_assign
id|j
op_plus
(paren
id|i
op_lshift
l_int|5
)paren
op_plus
l_int|1
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|j
op_plus
(paren
id|i
op_lshift
l_int|5
)paren
suffix:semicolon
)brace
DECL|function|clear_buf
r_static
r_void
id|clear_buf
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
r_int
op_star
id|lp
suffix:semicolon
id|lp
op_assign
(paren
r_int
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|bh-&gt;b_size
op_rshift
l_int|2
suffix:semicolon
id|i
op_decrement
OG
l_int|0
suffix:semicolon
)paren
op_star
id|lp
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|que
r_static
r_void
id|que
c_func
(paren
r_struct
id|buffer_head
op_star
id|bmap
(braket
)braket
comma
r_int
id|bznr
(braket
)braket
comma
r_int
id|pos
)paren
(brace
r_struct
id|buffer_head
op_star
id|tbh
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|tbh
op_assign
id|bmap
(braket
id|pos
)braket
suffix:semicolon
id|tmp
op_assign
id|bznr
(braket
id|pos
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pos
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|bmap
(braket
id|i
)braket
op_assign
id|bmap
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|bznr
(braket
id|i
)braket
op_assign
id|bznr
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|bmap
(braket
l_int|0
)braket
op_assign
id|tbh
suffix:semicolon
id|bznr
(braket
l_int|0
)braket
op_assign
id|tmp
suffix:semicolon
)brace
DECL|macro|get_imap_zone
mdefine_line|#define get_imap_zone(sb, bit_nr, not_que) &bslash;&n;      &t;get__map_zone((sb), (sb)-&gt;u.xiafs_sb.s_imap_buf, &bslash;&n;&t;&t;      (sb)-&gt;u.xiafs_sb.s_imap_iznr, &bslash;&n;&t;&t;      (sb)-&gt;u.xiafs_sb.s_imap_cached, 1, &bslash;&n;&t;&t;      (sb)-&gt;u.xiafs_sb.s_imap_zones, _XIAFS_IMAP_SLOTS, &bslash;&n;&t;&t;      bit_nr, not_que)
DECL|macro|get_zmap_zone
mdefine_line|#define get_zmap_zone(sb, bit_nr, not_que) &bslash;&n;      &t;get__map_zone((sb), (sb)-&gt;u.xiafs_sb.s_zmap_buf, &bslash;&n;&t;&t;      (sb)-&gt;u.xiafs_sb.s_zmap_zznr, &bslash;&n;&t;&t;      (sb)-&gt;u.xiafs_sb.s_zmap_cached, &bslash;&n;&t;&t;      1+(sb)-&gt;u.xiafs_sb.s_imap_zones, &bslash;&n;&t;&t;      (sb)-&gt;u.xiafs_sb.s_zmap_zones, _XIAFS_ZMAP_SLOTS, &bslash;&n;&t;&t;      bit_nr, not_que)
r_static
r_struct
id|buffer_head
op_star
DECL|function|get__map_zone
id|get__map_zone
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bmap_buf
(braket
)braket
comma
r_int
id|bznr
(braket
)braket
comma
id|u_char
id|cache
comma
r_int
id|first_zone
comma
r_int
id|bmap_zones
comma
r_int
id|slots
comma
id|u_long
id|bit_nr
comma
r_int
op_star
id|not_que
)paren
(brace
r_struct
id|buffer_head
op_star
id|tmp_bh
suffix:semicolon
r_int
id|z_nr
comma
id|i
suffix:semicolon
id|z_nr
op_assign
id|bit_nr
op_rshift
id|XIAFS_BITS_PER_Z_BITS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z_nr
op_ge
id|bmap_zones
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bad inode/zone number (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
r_return
id|bmap_buf
(braket
id|z_nr
)braket
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
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
id|slots
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bznr
(braket
id|i
)braket
op_eq
id|z_nr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|slots
)paren
(brace
multiline_comment|/* cache hit */
r_if
c_cond
(paren
id|not_que
)paren
(brace
op_star
id|not_que
op_assign
id|i
suffix:semicolon
r_return
id|bmap_buf
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
(brace
id|que
c_func
(paren
id|bmap_buf
comma
id|bznr
comma
id|i
)paren
suffix:semicolon
r_return
id|bmap_buf
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
id|tmp_bh
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|z_nr
op_plus
id|first_zone
comma
id|XIAFS_ZSIZE
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
multiline_comment|/* cache not hit */
r_if
c_cond
(paren
op_logical_neg
id|tmp_bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: read bitmap failed (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bmap_buf
(braket
id|slots
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|bmap_buf
(braket
id|slots
op_minus
l_int|1
)braket
op_assign
id|tmp_bh
suffix:semicolon
id|bznr
(braket
id|slots
op_minus
l_int|1
)braket
op_assign
id|z_nr
suffix:semicolon
r_if
c_cond
(paren
id|not_que
)paren
op_star
id|not_que
op_assign
id|slots
op_minus
l_int|1
suffix:semicolon
r_else
id|que
c_func
(paren
id|bmap_buf
comma
id|bznr
comma
id|slots
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|tmp_bh
suffix:semicolon
)brace
DECL|macro|xiafs_unlock_super
mdefine_line|#define xiafs_unlock_super(sb, cache)&t;if (cache) unlock_super(sb);
DECL|macro|get_free_ibit
mdefine_line|#define get_free_ibit(sb, prev_bit) &bslash;&n;   &t;get_free__bit(sb, sb-&gt;u.xiafs_sb.s_imap_buf, &bslash;&n;&t;&t;      sb-&gt;u.xiafs_sb.s_imap_iznr, &bslash;&n;&t;&t;      sb-&gt;u.xiafs_sb.s_imap_cached, &bslash;&n;&t;&t;      1, sb-&gt;u.xiafs_sb.s_imap_zones, &bslash;&n;&t;&t;      _XIAFS_IMAP_SLOTS, prev_bit);
DECL|macro|get_free_zbit
mdefine_line|#define get_free_zbit(sb, prev_bit) &bslash;&n;   &t;get_free__bit(sb, sb-&gt;u.xiafs_sb.s_zmap_buf, &bslash;&n;&t;&t;      sb-&gt;u.xiafs_sb.s_zmap_zznr, &bslash;&n;&t;&t;      sb-&gt;u.xiafs_sb.s_zmap_cached, &bslash;&n;&t;&t;      1 + sb-&gt;u.xiafs_sb.s_imap_zones, &bslash;&n;&t;&t;      sb-&gt;u.xiafs_sb.s_zmap_zones, &bslash;&n;&t;&t;      _XIAFS_ZMAP_SLOTS, prev_bit);
r_static
id|u_long
DECL|function|get_free__bit
id|get_free__bit
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bmap_buf
(braket
)braket
comma
r_int
id|bznr
(braket
)braket
comma
id|u_char
id|cache
comma
r_int
id|first_zone
comma
r_int
id|bmap_zones
comma
r_int
id|slots
comma
id|u_long
id|prev_bit
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|not_done
op_assign
l_int|0
suffix:semicolon
id|u_long
id|pos
comma
id|start_bit
comma
id|end_bit
comma
id|total_bits
suffix:semicolon
r_int
id|z_nr
comma
id|tmp
suffix:semicolon
id|total_bits
op_assign
id|bmap_zones
op_lshift
id|XIAFS_BITS_PER_Z_BITS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev_bit
op_ge
id|total_bits
)paren
id|prev_bit
op_assign
l_int|0
suffix:semicolon
id|pos
op_assign
id|prev_bit
op_plus
l_int|1
suffix:semicolon
id|end_bit
op_assign
id|XIAFS_BITS_PER_Z
c_func
(paren
id|sb
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|pos
op_ge
id|total_bits
)paren
id|pos
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|not_done
)paren
(brace
multiline_comment|/* first time */
id|not_done
op_assign
l_int|1
suffix:semicolon
id|start_bit
op_assign
id|pos
op_amp
(paren
id|end_bit
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|start_bit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|prev_bit
op_logical_and
id|pos
op_plus
id|end_bit
op_ge
id|prev_bit
)paren
(brace
multiline_comment|/* last time */
id|not_done
op_assign
l_int|0
suffix:semicolon
id|end_bit
op_assign
id|prev_bit
op_amp
(paren
id|end_bit
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* only here end_bit modified */
)brace
id|bh
op_assign
id|get__map_zone
c_func
(paren
id|sb
comma
id|bmap_buf
comma
id|bznr
comma
id|cache
comma
id|first_zone
comma
id|bmap_zones
comma
id|slots
comma
id|pos
comma
op_amp
id|z_nr
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
id|tmp
op_assign
id|find_first_zero
c_func
(paren
id|bh
comma
id|start_bit
comma
id|end_bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ge
l_int|0
)paren
r_break
suffix:semicolon
id|xiafs_unlock_super
c_func
(paren
id|sb
comma
id|sb-&gt;u.xiafs_sb.s_zmap_cached
)paren
suffix:semicolon
id|pos
op_assign
(paren
id|pos
op_amp
op_complement
(paren
id|end_bit
op_minus
l_int|1
)paren
)paren
op_plus
id|end_bit
suffix:semicolon
)brace
r_while
c_loop
(paren
id|not_done
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cache
)paren
id|que
c_func
(paren
id|bmap_buf
comma
id|bznr
comma
id|z_nr
)paren
suffix:semicolon
id|xiafs_unlock_super
c_func
(paren
id|sb
comma
id|cache
)paren
suffix:semicolon
r_return
(paren
id|pos
op_amp
op_complement
(paren
id|XIAFS_BITS_PER_Z
c_func
(paren
id|sb
)paren
op_minus
l_int|1
)paren
)paren
op_plus
id|tmp
suffix:semicolon
)brace
DECL|function|xiafs_free_zone
r_void
id|xiafs_free_zone
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|d_addr
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
id|offset
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
id|INTERN_ERR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d_addr
OL
id|sb-&gt;u.xiafs_sb.s_firstdatazone
op_logical_or
id|d_addr
op_ge
id|sb-&gt;u.xiafs_sb.s_nzones
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bad zone number (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
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
id|d_addr
comma
id|XIAFS_ZSIZE
c_func
(paren
id|sb
)paren
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
id|bit
op_assign
id|d_addr
op_minus
id|sb-&gt;u.xiafs_sb.s_firstdatazone
op_plus
l_int|1
suffix:semicolon
id|bh
op_assign
id|get_zmap_zone
c_func
(paren
id|sb
comma
id|bit
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
suffix:semicolon
id|offset
op_assign
id|bit
op_amp
(paren
id|XIAFS_BITS_PER_Z
c_func
(paren
id|sb
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clear_bit
c_func
(paren
id|offset
comma
id|bh-&gt;b_data
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bit %d (0x%x) already cleared (%s %d)&bslash;n&quot;
comma
id|bit
comma
id|bit
comma
id|WHERE_ERR
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|xiafs_unlock_super
c_func
(paren
id|sb
comma
id|sb-&gt;u.xiafs_sb.s_zmap_cached
)paren
suffix:semicolon
)brace
DECL|function|xiafs_new_zone
r_int
id|xiafs_new_zone
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u_long
id|prev_addr
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|prev_znr
comma
id|tmp
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
id|INTERN_ERR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev_addr
OL
id|sb-&gt;u.xiafs_sb.s_firstdatazone
op_logical_or
id|prev_addr
op_ge
id|sb-&gt;u.xiafs_sb.s_nzones
)paren
(brace
id|prev_addr
op_assign
id|sb-&gt;u.xiafs_sb.s_firstdatazone
suffix:semicolon
)brace
id|prev_znr
op_assign
id|prev_addr
op_minus
id|sb-&gt;u.xiafs_sb.s_firstdatazone
op_plus
l_int|1
suffix:semicolon
id|tmp
op_assign
id|get_free_zbit
c_func
(paren
id|sb
comma
id|prev_znr
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
id|tmp
op_add_assign
id|sb-&gt;u.xiafs_sb.s_firstdatazone
op_minus
l_int|1
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
id|XIAFS_ZSIZE
c_func
(paren
id|sb
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: I/O error (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|INTERN_ERR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|clear_buf
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|xiafs_free_inode
r_void
id|xiafs_free_inode
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
id|tmp
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
op_logical_or
id|inode-&gt;i_count
op_ne
l_int|1
op_logical_or
id|inode-&gt;i_nlink
op_logical_or
op_logical_neg
id|inode-&gt;i_sb
op_logical_or
id|inode-&gt;i_ino
template_param
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bad inode (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh
op_assign
id|get_imap_zone
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
suffix:semicolon
id|tmp
op_assign
id|inode-&gt;i_ino
op_amp
(paren
id|XIAFS_BITS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clear_bit
c_func
(paren
id|tmp
comma
id|bh-&gt;b_data
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bit %d (0x%x) already cleared (%s %d)&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_ino
comma
id|WHERE_ERR
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|xiafs_unlock_super
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_imap_cached
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|xiafs_new_inode
r_struct
id|inode
op_star
id|xiafs_new_inode
c_func
(paren
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
id|ino_t
id|tmp
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
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
id|inode-&gt;i_sb
op_assign
id|sb
suffix:semicolon
id|inode-&gt;i_flags
op_assign
id|inode-&gt;i_sb-&gt;s_flags
suffix:semicolon
id|tmp
op_assign
id|get_free_ibit
c_func
(paren
id|sb
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
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
id|current-&gt;euid
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
id|current-&gt;egid
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|tmp
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
r_return
id|inode
suffix:semicolon
)brace
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
DECL|function|count_zone
r_static
id|u_long
id|count_zone
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|i
comma
id|tmp
suffix:semicolon
id|u_long
id|sum
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|bh-&gt;b_size
suffix:semicolon
id|i
op_decrement
OG
l_int|0
suffix:semicolon
)paren
(brace
id|tmp
op_assign
id|bh-&gt;b_data
(braket
id|i
)braket
suffix:semicolon
id|sum
op_add_assign
id|nibblemap
(braket
id|tmp
op_amp
l_int|0xf
)braket
op_plus
id|nibblemap
(braket
(paren
id|tmp
op_amp
l_int|0xff
)paren
op_rshift
l_int|4
)braket
suffix:semicolon
)brace
r_return
id|sum
suffix:semicolon
)brace
DECL|function|xiafs_count_free_inodes
r_int
r_int
id|xiafs_count_free_inodes
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
id|izones
comma
id|i
comma
id|not_que
suffix:semicolon
id|u_long
id|sum
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
id|izones
op_assign
id|sb-&gt;u.xiafs_sb.s_imap_zones
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
id|izones
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh
op_assign
id|get_imap_zone
c_func
(paren
id|sb
comma
id|i
op_lshift
id|XIAFS_BITS_PER_Z_BITS
c_func
(paren
id|sb
)paren
comma
op_amp
id|not_que
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|sum
op_add_assign
id|count_zone
c_func
(paren
id|bh
)paren
suffix:semicolon
id|xiafs_unlock_super
c_func
(paren
id|sb
comma
id|sb-&gt;u.xiafs_sb.s_imap_cached
)paren
suffix:semicolon
)brace
)brace
id|i
op_assign
id|izones
op_lshift
id|XIAFS_BITS_PER_Z_BITS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|i
op_minus
id|sum
suffix:semicolon
)brace
DECL|function|xiafs_count_free_zones
r_int
r_int
id|xiafs_count_free_zones
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
id|zzones
comma
id|i
comma
id|not_que
suffix:semicolon
id|u_long
id|sum
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
id|zzones
op_assign
id|sb-&gt;u.xiafs_sb.s_zmap_zones
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
id|zzones
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh
op_assign
id|get_zmap_zone
c_func
(paren
id|sb
comma
id|i
op_lshift
id|XIAFS_BITS_PER_Z_BITS
c_func
(paren
id|sb
)paren
comma
op_amp
id|not_que
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|sum
op_add_assign
id|count_zone
c_func
(paren
id|bh
)paren
suffix:semicolon
id|xiafs_unlock_super
c_func
(paren
id|sb
comma
id|sb-&gt;u.xiafs_sb.s_zmap_cached
)paren
suffix:semicolon
)brace
)brace
id|i
op_assign
id|zzones
op_lshift
id|XIAFS_BITS_PER_Z_BITS
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|i
op_minus
id|sum
suffix:semicolon
)brace
eof
