multiline_comment|/*&n; *  linux/fs/xiafs/inode.c&n; *&n; *  Copyright (C) Q. Frank Xia, 1993.&n; *  &n; *  Based on Linus&squot; minix/inode.c&n; *  Copyright (C) Linus Torvalds, 1991, 1992.&n; *&n; *  This software may be redistributed per Linux Copyright.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/xia_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;xiafs_mac.h&quot;
DECL|variable|random_nr
r_static
id|u_long
id|random_nr
suffix:semicolon
DECL|function|xiafs_put_inode
r_void
id|xiafs_put_inode
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
id|inode-&gt;i_nlink
)paren
r_return
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|xiafs_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|xiafs_free_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|xiafs_put_super
r_void
id|xiafs_put_super
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
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dev
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
id|_XIAFS_IMAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|sb-&gt;u.xiafs_sb.s_imap_buf
(braket
id|i
)braket
)paren
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
id|_XIAFS_ZMAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|sb-&gt;u.xiafs_sb.s_zmap_buf
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|variable|xiafs_sops
r_static
r_struct
id|super_operations
id|xiafs_sops
op_assign
(brace
id|xiafs_read_inode
comma
l_int|NULL
comma
id|xiafs_write_inode
comma
id|xiafs_put_inode
comma
id|xiafs_put_super
comma
l_int|NULL
comma
id|xiafs_statfs
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|xiafs_read_super
r_struct
id|super_block
op_star
id|xiafs_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|xiafs_super_block
op_star
id|sp
suffix:semicolon
r_int
id|i
comma
id|z
comma
id|dev
suffix:semicolon
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;XIA-FS: read super_block failed (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|sp
op_assign
(paren
r_struct
id|xiafs_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|sp-&gt;s_magic
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_magic
op_ne
id|_XIAFS_SUPER_MAGIC
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
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
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: Can&squot;t find a xiafs filesystem on dev 0x%04x.&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|s-&gt;s_blocksize
op_assign
id|sp-&gt;s_zone_size
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
op_plus
id|sp-&gt;s_zone_shift
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_blocksize
op_ne
id|BLOCK_SIZE
op_logical_and
(paren
id|s-&gt;s_blocksize
op_eq
l_int|1024
op_logical_or
id|s-&gt;s_blocksize
op_eq
l_int|2048
op_logical_or
id|s-&gt;s_blocksize
op_eq
l_int|4096
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
id|s-&gt;s_blocksize
)paren
suffix:semicolon
id|bh
op_assign
id|bread
(paren
id|dev
comma
l_int|0
comma
id|s-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|sp
op_assign
(paren
r_struct
id|xiafs_super_block
op_star
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
id|BLOCK_SIZE
)paren
suffix:semicolon
)brace
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_nzones
op_assign
id|sp-&gt;s_nzones
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_ninodes
op_assign
id|sp-&gt;s_ninodes
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_ndatazones
op_assign
id|sp-&gt;s_ndatazones
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_imap_zones
op_assign
id|sp-&gt;s_imap_zones
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_zmap_zones
op_assign
id|sp-&gt;s_zmap_zones
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_firstdatazone
op_assign
id|sp-&gt;s_firstdatazone
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_zone_shift
op_assign
id|sp-&gt;s_zone_shift
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_max_size
op_assign
id|sp-&gt;s_max_size
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
id|_XIAFS_IMAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|s-&gt;u.xiafs_sb.s_imap_buf
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_imap_iznr
(braket
id|i
)braket
op_assign
op_minus
l_int|1
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
id|_XIAFS_ZMAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|s-&gt;u.xiafs_sb.s_zmap_buf
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_zmap_zznr
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|z
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;u.xiafs_sb.s_imap_zones
OG
id|_XIAFS_IMAP_SLOTS
)paren
id|s-&gt;u.xiafs_sb.s_imap_cached
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|s-&gt;u.xiafs_sb.s_imap_cached
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
id|s-&gt;u.xiafs_sb.s_imap_zones
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
id|s-&gt;u.xiafs_sb.s_imap_buf
(braket
id|i
)braket
op_assign
id|bread
c_func
(paren
id|dev
comma
id|z
op_increment
comma
id|XIAFS_ZSIZE
c_func
(paren
id|s
)paren
)paren
)paren
)paren
r_goto
id|xiafs_read_super_fail
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_imap_iznr
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|s-&gt;u.xiafs_sb.s_zmap_zones
OG
id|_XIAFS_ZMAP_SLOTS
)paren
id|s-&gt;u.xiafs_sb.s_zmap_cached
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|s-&gt;u.xiafs_sb.s_zmap_cached
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
id|s-&gt;u.xiafs_sb.s_zmap_zones
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
id|s-&gt;u.xiafs_sb.s_zmap_buf
(braket
id|i
)braket
op_assign
id|bread
c_func
(paren
id|dev
comma
id|z
op_increment
comma
id|XIAFS_ZSIZE
c_func
(paren
id|s
)paren
)paren
)paren
)paren
r_goto
id|xiafs_read_super_fail
suffix:semicolon
id|s-&gt;u.xiafs_sb.s_zmap_zznr
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
)brace
)brace
multiline_comment|/* set up enough so that it can read an inode */
id|s-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|xiafs_sops
suffix:semicolon
id|s-&gt;s_mounted
op_assign
id|iget
c_func
(paren
id|s
comma
id|_XIAFS_ROOT_INO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_mounted
)paren
r_goto
id|xiafs_read_super_fail
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|random_nr
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|s
suffix:semicolon
id|xiafs_read_super_fail
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|_XIAFS_IMAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|s-&gt;u.xiafs_sb.s_imap_buf
(braket
id|i
)braket
)paren
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
id|_XIAFS_ZMAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|s-&gt;u.xiafs_sb.s_zmap_buf
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;XIA-FS: read bitmaps failed (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xiafs_statfs
r_void
id|xiafs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|put_fs_long
c_func
(paren
id|_XIAFS_SUPER_MAGIC
comma
op_amp
id|buf-&gt;f_type
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|XIAFS_ZSIZE
c_func
(paren
id|sb
)paren
comma
op_amp
id|buf-&gt;f_bsize
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sb-&gt;u.xiafs_sb.s_ndatazones
comma
op_amp
id|buf-&gt;f_blocks
)paren
suffix:semicolon
id|tmp
op_assign
id|xiafs_count_free_zones
c_func
(paren
id|sb
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp
comma
op_amp
id|buf-&gt;f_bfree
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp
comma
op_amp
id|buf-&gt;f_bavail
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sb-&gt;u.xiafs_sb.s_ninodes
comma
op_amp
id|buf-&gt;f_files
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|xiafs_count_free_inodes
c_func
(paren
id|sb
)paren
comma
op_amp
id|buf-&gt;f_ffree
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|_XIAFS_NAME_LEN
comma
op_amp
id|buf-&gt;f_namelen
)paren
suffix:semicolon
multiline_comment|/* don&squot;t know what should be put in buf-&gt;f_fsid */
)brace
DECL|function|zone_bmap
r_static
r_int
id|zone_bmap
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|nr
)paren
(brace
r_int
id|tmp
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
(paren
(paren
id|u_long
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
id|nr
)braket
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
DECL|function|xiafs_bmap
r_int
id|xiafs_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|zone
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|zone
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: block &lt; 0 (%s %d)&bslash;n&quot;
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
id|zone
op_ge
l_int|8
op_plus
(paren
l_int|1
op_plus
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
op_star
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: zone &gt; big (%s %d)&bslash;n&quot;
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
op_logical_neg
id|IS_RDONLY
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|zone
OL
l_int|8
)paren
r_return
id|inode-&gt;u.xiafs_i.i_zone
(braket
id|zone
)braket
suffix:semicolon
id|zone
op_sub_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|zone
OL
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
id|i
op_assign
id|inode-&gt;u.xiafs_i.i_ind_zone
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|i
op_assign
id|zone_bmap
c_func
(paren
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
comma
id|zone
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|zone
op_sub_assign
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|i
op_assign
id|inode-&gt;u.xiafs_i.i_dind_zone
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|i
op_assign
id|zone_bmap
c_func
(paren
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
comma
id|zone
op_rshift
id|XIAFS_ADDRS_PER_Z_BITS
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|i
op_assign
id|zone_bmap
c_func
(paren
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
comma
id|zone
op_amp
(paren
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|get_prev_addr
r_static
id|u_long
id|get_prev_addr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|zone
)paren
(brace
id|u_long
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|zone
OG
l_int|0
)paren
r_while
c_loop
(paren
op_decrement
id|zone
op_ge
l_int|0
)paren
multiline_comment|/* only files with holes suffer */
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|xiafs_bmap
c_func
(paren
id|inode
comma
id|zone
)paren
)paren
)paren
r_return
id|tmp
suffix:semicolon
id|random_nr
op_assign
(paren
id|random_nr
op_plus
l_int|23
)paren
op_mod
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_ndatazones
suffix:semicolon
r_return
id|random_nr
op_plus
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_firstdatazone
suffix:semicolon
)brace
r_static
r_struct
id|buffer_head
op_star
DECL|function|dt_getblk
id|dt_getblk
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u_long
op_star
id|lp
comma
r_int
id|create
comma
id|u_long
id|prev_addr
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|result
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
(paren
id|tmp
op_assign
op_star
id|lp
)paren
)paren
(brace
id|result
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
op_star
id|lp
)paren
r_return
id|result
suffix:semicolon
id|brelse
c_func
(paren
id|result
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
r_return
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|xiafs_new_zone
c_func
(paren
id|inode-&gt;i_sb
comma
id|prev_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
l_int|NULL
suffix:semicolon
id|result
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|lp
)paren
(brace
id|xiafs_free_zone
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|result
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
op_star
id|lp
op_assign
id|tmp
suffix:semicolon
id|inode-&gt;i_blocks
op_add_assign
l_int|2
op_lshift
id|XIAFS_ZSHIFT
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_struct
id|buffer_head
op_star
DECL|function|indt_getblk
id|indt_getblk
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|nr
comma
r_int
id|create
comma
id|u_long
id|prev_addr
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|u_long
op_star
id|lp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_uptodate
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_uptodate
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|lp
op_assign
id|nr
op_plus
(paren
id|u_long
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
(paren
id|tmp
op_assign
op_star
id|lp
)paren
)paren
(brace
id|result
op_assign
id|getblk
c_func
(paren
id|bh-&gt;b_dev
comma
id|tmp
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
op_star
id|lp
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|result
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|tmp
op_assign
id|xiafs_new_zone
c_func
(paren
id|inode-&gt;i_sb
comma
id|prev_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|result
op_assign
id|getblk
c_func
(paren
id|bh-&gt;b_dev
comma
id|tmp
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|lp
)paren
(brace
id|xiafs_free_zone
c_func
(paren
id|inode-&gt;i_sb
comma
id|tmp
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|result
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
op_star
id|lp
op_assign
id|tmp
suffix:semicolon
id|inode-&gt;i_blocks
op_add_assign
l_int|2
op_lshift
id|XIAFS_ZSHIFT
c_func
(paren
id|inode-&gt;i_sb
)paren
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
id|result
suffix:semicolon
)brace
DECL|function|xiafs_getblk
r_struct
id|buffer_head
op_star
id|xiafs_getblk
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|zone
comma
r_int
id|create
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|u_long
id|prev_addr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|zone
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: zone &lt; 0 (%s %d)&bslash;n&quot;
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
id|zone
op_ge
l_int|8
op_plus
(paren
l_int|1
op_plus
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
op_star
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
id|printk
c_func
(paren
l_string|&quot;XIA-FS: zone &gt; big (%s %d)&bslash;n&quot;
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
id|create
)paren
id|prev_addr
op_assign
id|get_prev_addr
c_func
(paren
id|inode
comma
id|zone
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zone
OL
l_int|8
)paren
r_return
id|dt_getblk
c_func
(paren
id|inode
comma
id|zone
op_plus
id|inode-&gt;u.xiafs_i.i_zone
comma
id|create
comma
id|prev_addr
)paren
suffix:semicolon
id|zone
op_sub_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|zone
OL
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
(brace
id|bh
op_assign
id|dt_getblk
c_func
(paren
id|inode
comma
op_amp
(paren
id|inode-&gt;u.xiafs_i.i_ind_zone
)paren
comma
id|create
comma
id|prev_addr
)paren
suffix:semicolon
id|bh
op_assign
id|indt_getblk
c_func
(paren
id|inode
comma
id|bh
comma
id|zone
comma
id|create
comma
id|prev_addr
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
id|zone
op_sub_assign
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|bh
op_assign
id|dt_getblk
c_func
(paren
id|inode
comma
op_amp
(paren
id|inode-&gt;u.xiafs_i.i_dind_zone
)paren
comma
id|create
comma
id|prev_addr
)paren
suffix:semicolon
id|bh
op_assign
id|indt_getblk
c_func
(paren
id|inode
comma
id|bh
comma
id|zone
op_rshift
id|XIAFS_ADDRS_PER_Z_BITS
c_func
(paren
id|inode-&gt;i_sb
)paren
comma
id|create
comma
id|prev_addr
)paren
suffix:semicolon
id|bh
op_assign
id|indt_getblk
c_func
(paren
id|inode
comma
id|bh
comma
id|zone
op_amp
(paren
id|XIAFS_ADDRS_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
op_minus
l_int|1
)paren
comma
id|create
comma
id|prev_addr
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|xiafs_bread
r_struct
id|buffer_head
op_star
id|xiafs_bread
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|zone
comma
r_int
id|create
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|xiafs_getblk
c_func
(paren
id|inode
comma
id|zone
comma
id|create
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|bh-&gt;b_uptodate
)paren
r_return
id|bh
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_uptodate
)paren
r_return
id|bh
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xiafs_read_inode
r_void
id|xiafs_read_inode
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
id|xiafs_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|zone
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
op_logical_or
id|ino
OG
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bad inode number (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|zone
op_assign
l_int|1
op_plus
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_imap_zones
op_plus
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_zmap_zones
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|XIAFS_INODES_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|zone
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: read i-node zone failed (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|raw_inode
op_assign
(paren
(paren
r_struct
id|xiafs_inode
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
(paren
id|ino
op_minus
l_int|1
)paren
op_amp
(paren
id|XIAFS_INODES_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|raw_inode-&gt;i_mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|raw_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|raw_inode-&gt;i_gid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|raw_inode-&gt;i_nlinks
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|raw_inode-&gt;i_size
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|raw_inode-&gt;i_mtime
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|raw_inode-&gt;i_atime
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|raw_inode-&gt;i_ctime
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
id|XIAFS_GET_BLOCKS
c_func
(paren
id|raw_inode
comma
id|inode-&gt;i_blocks
)paren
suffix:semicolon
r_for
c_loop
(paren
id|zone
op_assign
l_int|0
suffix:semicolon
id|zone
OL
l_int|8
suffix:semicolon
id|zone
op_increment
)paren
id|inode-&gt;u.xiafs_i.i_zone
(braket
id|zone
)braket
op_assign
id|raw_inode-&gt;i_zone
(braket
id|zone
)braket
op_amp
l_int|0xffffff
suffix:semicolon
id|inode-&gt;u.xiafs_i.i_ind_zone
op_assign
id|raw_inode-&gt;i_ind_zone
op_amp
l_int|0xffffff
suffix:semicolon
id|inode-&gt;u.xiafs_i.i_dind_zone
op_assign
id|raw_inode-&gt;i_dind_zone
op_amp
l_int|0xffffff
suffix:semicolon
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
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|xiafs_file_inode_operations
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|xiafs_dir_inode_operations
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|xiafs_symlink_inode_operations
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|chrdev_inode_operations
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|blkdev_inode_operations
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|init_fifo
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|xiafs_update_inode
r_static
r_struct
id|buffer_head
op_star
id|xiafs_update_inode
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
id|xiafs_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|zone
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
(paren
id|inode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: write_inode on a read-only filesystem (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: bad inode number (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|zone
op_assign
l_int|1
op_plus
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_imap_zones
op_plus
id|inode-&gt;i_sb-&gt;u.xiafs_sb.s_zmap_zones
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|XIAFS_INODES_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|zone
comma
id|XIAFS_ZSIZE
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;XIA-FS: read i-node zone failed (%s %d)&bslash;n&quot;
comma
id|WHERE_ERR
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|0
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
id|xiafs_inode
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
(paren
id|ino
op_minus
l_int|1
)paren
op_amp
(paren
id|XIAFS_INODES_PER_Z
c_func
(paren
id|inode-&gt;i_sb
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|raw_inode-&gt;i_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|raw_inode-&gt;i_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|raw_inode-&gt;i_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|raw_inode-&gt;i_nlinks
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|raw_inode-&gt;i_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|raw_inode-&gt;i_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|raw_inode-&gt;i_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|raw_inode-&gt;i_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_else
(brace
id|XIAFS_PUT_BLOCKS
c_func
(paren
id|raw_inode
comma
id|inode-&gt;i_blocks
)paren
suffix:semicolon
r_for
c_loop
(paren
id|zone
op_assign
l_int|0
suffix:semicolon
id|zone
OL
l_int|8
suffix:semicolon
id|zone
op_increment
)paren
id|raw_inode-&gt;i_zone
(braket
id|zone
)braket
op_assign
(paren
id|raw_inode-&gt;i_zone
(braket
id|zone
)braket
op_amp
l_int|0xff000000
)paren
op_or
(paren
id|inode-&gt;u.xiafs_i.i_zone
(braket
id|zone
)braket
op_amp
l_int|0xffffff
)paren
suffix:semicolon
id|raw_inode-&gt;i_ind_zone
op_assign
(paren
id|raw_inode-&gt;i_ind_zone
op_amp
l_int|0xff000000
)paren
op_or
(paren
id|inode-&gt;u.xiafs_i.i_ind_zone
op_amp
l_int|0xffffff
)paren
suffix:semicolon
id|raw_inode-&gt;i_dind_zone
op_assign
(paren
id|raw_inode-&gt;i_dind_zone
op_amp
l_int|0xff000000
)paren
op_or
(paren
id|inode-&gt;u.xiafs_i.i_dind_zone
op_amp
l_int|0xffffff
)paren
suffix:semicolon
)brace
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|xiafs_write_inode
r_void
id|xiafs_write_inode
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
id|bh
op_assign
id|xiafs_update_inode
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
DECL|function|xiafs_sync_inode
r_int
id|xiafs_sync_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|xiafs_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_logical_and
id|bh-&gt;b_dirt
)paren
(brace
id|ll_rw_block
c_func
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
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_req
op_logical_and
op_logical_neg
id|bh-&gt;b_uptodate
)paren
(brace
id|printk
(paren
l_string|&quot;IO error syncing xiafs inode [%04X:%lu]&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof