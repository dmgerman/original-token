multiline_comment|/*&n; *  linux/fs/adfs/super.c&n; *&n; * Copyright (C) 1997 Russell King&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;stdarg.h&gt;
r_static
r_void
id|adfs_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_int
id|adfs_statfs
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
comma
r_int
id|bufsiz
)paren
suffix:semicolon
r_void
id|adfs_read_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
DECL|function|adfs_error
r_void
id|adfs_error
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
id|error_buf
(braket
l_int|128
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
(paren
id|error_buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
(paren
id|args
)paren
suffix:semicolon
id|printk
(paren
id|KERN_CRIT
l_string|&quot;ADFS-fs error (device %s)%s%s: %s&bslash;n&quot;
comma
id|kdevname
(paren
id|sb-&gt;s_dev
)paren
comma
id|function
ques
c_cond
l_string|&quot;: &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|function
ques
c_cond
id|function
suffix:colon
l_string|&quot;&quot;
comma
id|error_buf
)paren
suffix:semicolon
)brace
DECL|function|adfs_calccrosscheck
r_int
r_char
id|adfs_calccrosscheck
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|map
)paren
(brace
r_int
r_int
id|v0
comma
id|v1
comma
id|v2
comma
id|v3
suffix:semicolon
r_int
id|i
suffix:semicolon
id|v0
op_assign
id|v1
op_assign
id|v2
op_assign
id|v3
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sb-&gt;s_blocksize
op_minus
l_int|4
suffix:semicolon
id|i
suffix:semicolon
id|i
op_sub_assign
l_int|4
)paren
(brace
id|v0
op_add_assign
id|map
(braket
id|i
)braket
op_plus
(paren
id|v3
op_rshift
l_int|8
)paren
suffix:semicolon
id|v3
op_and_assign
l_int|0xff
suffix:semicolon
id|v1
op_add_assign
id|map
(braket
id|i
op_plus
l_int|1
)braket
op_plus
(paren
id|v0
op_rshift
l_int|8
)paren
suffix:semicolon
id|v0
op_and_assign
l_int|0xff
suffix:semicolon
id|v2
op_add_assign
id|map
(braket
id|i
op_plus
l_int|2
)braket
op_plus
(paren
id|v1
op_rshift
l_int|8
)paren
suffix:semicolon
id|v1
op_and_assign
l_int|0xff
suffix:semicolon
id|v3
op_add_assign
id|map
(braket
id|i
op_plus
l_int|3
)braket
op_plus
(paren
id|v2
op_rshift
l_int|8
)paren
suffix:semicolon
id|v2
op_and_assign
l_int|0xff
suffix:semicolon
)brace
id|v0
op_add_assign
id|v3
op_rshift
l_int|8
suffix:semicolon
id|v1
op_add_assign
id|map
(braket
l_int|1
)braket
op_plus
(paren
id|v0
op_rshift
l_int|8
)paren
suffix:semicolon
id|v2
op_add_assign
id|map
(braket
l_int|2
)braket
op_plus
(paren
id|v1
op_rshift
l_int|8
)paren
suffix:semicolon
id|v3
op_add_assign
id|map
(braket
l_int|3
)braket
op_plus
(paren
id|v2
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
id|v0
op_xor
id|v1
op_xor
id|v2
op_xor
id|v3
suffix:semicolon
)brace
DECL|function|adfs_checkmap
r_static
r_int
id|adfs_checkmap
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
r_char
id|crosscheck
op_assign
l_int|0
comma
id|zonecheck
op_assign
l_int|1
suffix:semicolon
r_int
id|i
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
id|sb-&gt;u.adfs_sb.s_map_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|map
suffix:semicolon
id|map
op_assign
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_if
c_cond
(paren
id|adfs_calccrosscheck
(paren
id|sb
comma
id|map
)paren
op_ne
id|map
(braket
l_int|0
)braket
)paren
(brace
id|adfs_error
(paren
id|sb
comma
l_string|&quot;adfs_checkmap&quot;
comma
l_string|&quot;zone %d fails zonecheck&quot;
comma
id|i
)paren
suffix:semicolon
id|zonecheck
op_assign
l_int|0
suffix:semicolon
)brace
id|crosscheck
op_xor_assign
id|map
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|crosscheck
op_ne
l_int|0xff
)paren
id|adfs_error
(paren
id|sb
comma
l_string|&quot;adfs_checkmap&quot;
comma
l_string|&quot;crosscheck != 0xff&quot;
)paren
suffix:semicolon
r_return
id|crosscheck
op_eq
l_int|0xff
op_logical_and
id|zonecheck
suffix:semicolon
)brace
DECL|variable|adfs_sops
r_static
r_struct
id|super_operations
id|adfs_sops
op_assign
(brace
id|adfs_read_inode
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|adfs_put_super
comma
l_int|NULL
comma
id|adfs_statfs
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|adfs_put_super
r_static
r_void
id|adfs_put_super
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
id|sb-&gt;u.adfs_sb.s_map_size
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
(paren
id|sb-&gt;u.adfs_sb.s_map
)paren
suffix:semicolon
id|brelse
(paren
id|sb-&gt;u.adfs_sb.s_sbh
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|adfs_read_super
r_struct
id|super_block
op_star
id|adfs_read_super
(paren
r_struct
id|super_block
op_star
id|sb
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
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_char
op_star
id|b_data
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|set_blocksize
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
(paren
id|dev
comma
id|ADFS_DISCRECORD
op_div
id|BLOCK_SIZE
comma
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;unable to read superblock&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|b_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
id|ADFS_DISCRECORD
op_mod
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkbblk
(paren
id|b_data
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
(paren
l_string|&quot;VFS: Can&squot;t find an adfs filesystem on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|failed_mount
suffix:colon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|b_data
op_plus
id|ADFS_DR_OFFSET
)paren
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|dr-&gt;log2secsize
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
l_int|1
op_lshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_ne
id|BLOCK_SIZE
op_logical_and
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|512
op_logical_or
id|sb-&gt;s_blocksize
op_eq
l_int|1024
op_logical_or
id|sb-&gt;s_blocksize
op_eq
l_int|2048
op_logical_or
id|sb-&gt;s_blocksize
op_eq
l_int|4096
)paren
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|set_blocksize
(paren
id|dev
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|bh
op_assign
id|bread
(paren
id|dev
comma
id|ADFS_DISCRECORD
op_div
id|sb-&gt;s_blocksize
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
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;couldn&squot;t read superblock on &quot;
l_string|&quot;2nd try.&quot;
)paren
suffix:semicolon
r_goto
id|failed_mount
suffix:semicolon
)brace
id|b_data
op_assign
id|bh-&gt;b_data
op_plus
(paren
id|ADFS_DISCRECORD
op_mod
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkbblk
(paren
id|b_data
)paren
)paren
(brace
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;disc record mismatch, very weird!&quot;
)paren
suffix:semicolon
r_goto
id|failed_mount
suffix:semicolon
)brace
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|b_data
op_plus
id|ADFS_DR_OFFSET
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_ne
id|bh-&gt;b_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
(paren
id|KERN_ERR
l_string|&quot;VFS: Unsupported blocksize on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|failed_mount
suffix:semicolon
)brace
multiline_comment|/* blocksize on this device should now be set to the adfs log2secsize */
id|sb-&gt;u.adfs_sb.s_sbh
op_assign
id|bh
suffix:semicolon
id|sb-&gt;u.adfs_sb.s_dr
op_assign
id|dr
suffix:semicolon
multiline_comment|/* s_zone_size = size of 1 zone (1 sector) * bits_in_byte - zone_spare =&gt;&n;&t; * number of map bits in a zone&n;&t; */
id|sb-&gt;u.adfs_sb.s_zone_size
op_assign
(paren
l_int|8
op_lshift
id|dr-&gt;log2secsize
)paren
op_minus
id|dr-&gt;zone_spare
suffix:semicolon
multiline_comment|/* s_ids_per_zone = bit size of 1 zone / min. length of fragment block =&gt;&n;&t; * number of ids in one zone&n;&t; */
id|sb-&gt;u.adfs_sb.s_ids_per_zone
op_assign
id|sb-&gt;u.adfs_sb.s_zone_size
op_div
(paren
id|dr-&gt;idlen
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* s_idlen = length of 1 id */
id|sb-&gt;u.adfs_sb.s_idlen
op_assign
id|dr-&gt;idlen
suffix:semicolon
multiline_comment|/* map size (in sectors) = number of zones */
id|sb-&gt;u.adfs_sb.s_map_size
op_assign
id|dr-&gt;nzones
suffix:semicolon
multiline_comment|/* zonesize = size of sector - zonespare */
id|sb-&gt;u.adfs_sb.s_zonesize
op_assign
(paren
id|sb-&gt;s_blocksize
op_lshift
l_int|3
)paren
op_minus
id|dr-&gt;zone_spare
suffix:semicolon
multiline_comment|/* map start (in sectors) = start of zone (number of zones) / 2 */
id|sb-&gt;u.adfs_sb.s_map_block
op_assign
(paren
id|dr-&gt;nzones
op_rshift
l_int|1
)paren
op_star
id|sb-&gt;u.adfs_sb.s_zone_size
op_minus
(paren
(paren
id|dr-&gt;nzones
OG
l_int|1
)paren
ques
c_cond
l_int|8
op_star
id|ADFS_DR_SIZE
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* (signed) number of bits to shift left a map address to a sector address */
id|sb-&gt;u.adfs_sb.s_map2blk
op_assign
id|dr-&gt;log2bpmb
op_minus
id|dr-&gt;log2secsize
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.adfs_sb.s_map2blk
op_ge
l_int|0
)paren
id|sb-&gt;u.adfs_sb.s_map_block
op_lshift_assign
id|sb-&gt;u.adfs_sb.s_map2blk
suffix:semicolon
r_else
id|sb-&gt;u.adfs_sb.s_map_block
op_rshift_assign
op_minus
id|sb-&gt;u.adfs_sb.s_map2blk
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;ADFS: zone size %d, IDs per zone %d, map address %X size %d sectors&bslash;n&quot;
comma
id|sb-&gt;u.adfs_sb.s_zone_size
comma
id|sb-&gt;u.adfs_sb.s_ids_per_zone
comma
id|sb-&gt;u.adfs_sb.s_map_block
comma
id|sb-&gt;u.adfs_sb.s_map_size
)paren
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;ADFS: sector size %d, map bit size %d&bslash;n&quot;
comma
l_int|1
op_lshift
id|dr-&gt;log2secsize
comma
l_int|1
op_lshift
id|dr-&gt;log2bpmb
)paren
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|ADFS_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
multiline_comment|/* we don&squot;t support writing yet */
id|sb-&gt;u.adfs_sb.s_map
op_assign
id|kmalloc
(paren
id|sb-&gt;u.adfs_sb.s_map_size
op_star
r_sizeof
(paren
r_struct
id|buffer_head
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.adfs_sb.s_map
op_eq
l_int|NULL
)paren
(brace
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;not enough memory&quot;
)paren
suffix:semicolon
r_goto
id|failed_mount
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
id|sb-&gt;u.adfs_sb.s_map_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
op_assign
id|bread
(paren
id|dev
comma
id|sb-&gt;u.adfs_sb.s_map_block
op_plus
id|i
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
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
id|i
suffix:semicolon
id|j
op_increment
)paren
id|brelse
(paren
id|sb-&gt;u.adfs_sb.s_map
(braket
id|j
)braket
)paren
suffix:semicolon
id|kfree
(paren
id|sb-&gt;u.adfs_sb.s_map
)paren
suffix:semicolon
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;unable to read map&quot;
)paren
suffix:semicolon
r_goto
id|failed_mount
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|adfs_checkmap
(paren
id|sb
)paren
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
id|sb-&gt;u.adfs_sb.s_map_size
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
)paren
suffix:semicolon
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;map corrupted&quot;
)paren
suffix:semicolon
r_goto
id|failed_mount
suffix:semicolon
)brace
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|sb-&gt;u.adfs_sb.s_map
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
op_plus
l_int|4
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set up enough so that it can read an inode&n;&t; */
id|sb-&gt;s_op
op_assign
op_amp
id|adfs_sops
suffix:semicolon
id|sb-&gt;u.adfs_sb.s_root
op_assign
id|adfs_inode_generate
(paren
id|dr-&gt;root
comma
l_int|0
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|sb
comma
id|sb-&gt;u.adfs_sb.s_root
)paren
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
(brace
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
id|sb-&gt;u.adfs_sb.s_map_size
suffix:semicolon
id|i
op_increment
)paren
id|brelse
(paren
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
)paren
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|sb
suffix:semicolon
)brace
DECL|function|adfs_statfs
r_static
r_int
id|adfs_statfs
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
comma
r_int
id|bufsiz
)paren
(brace
r_struct
id|statfs
id|tmp
suffix:semicolon
r_const
r_int
r_int
id|nidlen
op_assign
id|sb-&gt;u.adfs_sb.s_idlen
op_plus
l_int|1
suffix:semicolon
id|tmp.f_type
op_assign
id|ADFS_SUPER_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|tmp.f_blocks
op_assign
(paren
id|sb-&gt;u.adfs_sb.s_dr-&gt;disc_size
)paren
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|tmp.f_files
op_assign
id|tmp.f_blocks
op_rshift
id|nidlen
suffix:semicolon
(brace
r_int
r_int
id|i
comma
id|j
op_assign
l_int|0
suffix:semicolon
r_const
r_int
id|mask
op_assign
(paren
l_int|1
op_lshift
(paren
id|nidlen
op_minus
l_int|1
)paren
)paren
op_minus
l_int|1
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
id|sb-&gt;u.adfs_sb.s_map_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|map
op_assign
id|sb-&gt;u.adfs_sb.s_map
(braket
id|i
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_int
id|freelink
comma
id|mapindex
op_assign
l_int|24
suffix:semicolon
id|j
op_sub_assign
id|nidlen
suffix:semicolon
r_do
(brace
r_int
r_char
id|k
comma
id|l
comma
id|m
suffix:semicolon
r_int
id|off
op_assign
(paren
id|mapindex
op_minus
id|nidlen
)paren
op_rshift
l_int|3
suffix:semicolon
r_int
id|rem
suffix:semicolon
r_const
r_int
id|boff
op_assign
id|mapindex
op_amp
l_int|7
suffix:semicolon
multiline_comment|/* get next freelink */
id|k
op_assign
id|map
(braket
id|off
op_increment
)braket
suffix:semicolon
id|l
op_assign
id|map
(braket
id|off
op_increment
)braket
suffix:semicolon
id|m
op_assign
id|map
(braket
id|off
op_increment
)braket
suffix:semicolon
id|freelink
op_assign
(paren
id|m
op_lshift
l_int|16
)paren
op_or
(paren
id|l
op_lshift
l_int|8
)paren
op_or
id|k
suffix:semicolon
id|rem
op_assign
id|freelink
op_rshift
(paren
id|boff
op_plus
id|nidlen
op_minus
l_int|1
)paren
suffix:semicolon
id|freelink
op_assign
(paren
id|freelink
op_rshift
id|boff
)paren
op_amp
id|mask
suffix:semicolon
id|mapindex
op_add_assign
id|freelink
suffix:semicolon
multiline_comment|/* find its length and add it to running total */
r_while
c_loop
(paren
id|rem
op_eq
l_int|0
)paren
(brace
id|j
op_add_assign
l_int|8
suffix:semicolon
id|rem
op_assign
id|map
(braket
id|off
op_increment
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rem
op_amp
l_int|0xff
)paren
op_eq
l_int|0
)paren
id|j
op_add_assign
l_int|8
comma
id|rem
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rem
op_amp
l_int|0xf
)paren
op_eq
l_int|0
)paren
id|j
op_add_assign
l_int|4
comma
id|rem
op_rshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rem
op_amp
l_int|0x3
)paren
op_eq
l_int|0
)paren
id|j
op_add_assign
l_int|2
comma
id|rem
op_rshift_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rem
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
id|j
op_add_assign
l_int|1
suffix:semicolon
id|j
op_add_assign
id|nidlen
op_minus
id|boff
suffix:semicolon
r_if
c_cond
(paren
id|freelink
op_le
id|nidlen
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mapindex
OL
l_int|8
op_star
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapindex
OG
l_int|8
op_star
id|sb-&gt;s_blocksize
)paren
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;oversized free fragment&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|freelink
)paren
id|adfs_error
(paren
id|sb
comma
l_int|NULL
comma
l_string|&quot;undersized free fragment&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|tmp.f_bfree
op_assign
id|tmp.f_bavail
op_assign
id|j
op_lshift
(paren
id|sb-&gt;u.adfs_sb.s_dr-&gt;log2bpmb
op_minus
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
)brace
id|tmp.f_ffree
op_assign
id|tmp.f_bfree
op_rshift
id|nidlen
suffix:semicolon
id|tmp.f_namelen
op_assign
id|ADFS_NAME_LEN
suffix:semicolon
r_return
id|copy_to_user
(paren
id|buf
comma
op_amp
id|tmp
comma
id|bufsiz
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|adfs_fs_type
r_static
r_struct
id|file_system_type
id|adfs_fs_type
op_assign
(brace
l_string|&quot;adfs&quot;
comma
id|FS_REQUIRES_DEV
comma
id|adfs_read_super
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|init_adfs_fs
(paren
r_void
)paren
)paren
(brace
r_return
id|register_filesystem
(paren
op_amp
id|adfs_fs_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
(paren
r_void
)paren
(brace
r_return
id|init_adfs_fs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
id|unregister_filesystem
(paren
op_amp
id|adfs_fs_type
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
