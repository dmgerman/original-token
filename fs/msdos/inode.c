multiline_comment|/*&n; *  linux/fs/msdos/inode.c&n; *&n; *  Written 1992 by Werner Almesberger&n; */
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|function|msdos_put_inode
r_void
id|msdos_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|inode
op_star
id|depend
suffix:semicolon
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
id|msdos_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|depend
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_depend
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
id|depend
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_I
c_func
(paren
id|depend
)paren
op_member_access_from_pointer
id|i_old
op_ne
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid link (0x%X): expected 0x%X, got &quot;
l_string|&quot;0x%X&bslash;n&quot;
comma
(paren
r_int
)paren
id|depend
comma
(paren
r_int
)paren
id|inode
comma
(paren
r_int
)paren
id|MSDOS_I
c_func
(paren
id|depend
)paren
op_member_access_from_pointer
id|i_old
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;That&squot;s fatal&quot;
)paren
suffix:semicolon
)brace
id|MSDOS_I
c_func
(paren
id|depend
)paren
op_member_access_from_pointer
id|i_old
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|depend
)paren
suffix:semicolon
)brace
)brace
DECL|function|msdos_put_super
r_void
id|msdos_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|cache_inval_dev
c_func
(paren
id|sb-&gt;s_dev
)paren
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
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|msdos_sops
r_static
r_struct
id|super_operations
id|msdos_sops
op_assign
(brace
id|msdos_read_inode
comma
l_int|NULL
comma
id|msdos_write_inode
comma
id|msdos_put_inode
comma
id|msdos_put_super
comma
l_int|NULL
comma
multiline_comment|/* added in 0.96c */
id|msdos_statfs
)brace
suffix:semicolon
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_char
op_star
id|check
comma
r_char
op_star
id|conversion
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
comma
r_int
op_star
id|umask
)paren
(brace
r_char
op_star
id|this
comma
op_star
id|value
suffix:semicolon
op_star
id|check
op_assign
l_char|&squot;n&squot;
suffix:semicolon
op_star
id|conversion
op_assign
l_char|&squot;b&squot;
suffix:semicolon
op_star
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
op_star
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
op_star
id|umask
op_assign
id|current-&gt;umask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|this
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this
suffix:semicolon
id|this
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|this
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this
comma
l_string|&quot;check&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|value
(braket
l_int|1
)braket
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;rns&quot;
comma
op_star
id|value
)paren
)paren
op_star
id|check
op_assign
op_star
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;relaxed&quot;
)paren
)paren
op_star
id|check
op_assign
l_char|&squot;r&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;normal&quot;
)paren
)paren
op_star
id|check
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;strict&quot;
)paren
)paren
op_star
id|check
op_assign
l_char|&squot;s&squot;
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this
comma
l_string|&quot;conv&quot;
)paren
op_logical_and
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|value
(braket
l_int|1
)braket
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;bta&quot;
comma
op_star
id|value
)paren
)paren
op_star
id|conversion
op_assign
op_star
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;binary&quot;
)paren
)paren
op_star
id|conversion
op_assign
l_char|&squot;b&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;text&quot;
)paren
)paren
op_star
id|conversion
op_assign
l_char|&squot;t&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;auto&quot;
)paren
)paren
op_star
id|conversion
op_assign
l_char|&squot;a&squot;
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this
comma
l_string|&quot;umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|umask
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Read the super block of an MS-DOS FS. */
DECL|function|msdos_read_super
r_struct
id|super_block
op_star
id|msdos_read_super
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
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_boot_sector
op_star
id|b
suffix:semicolon
r_int
id|data_sectors
suffix:semicolon
r_char
id|check
comma
id|conversion
suffix:semicolon
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
r_int
id|umask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
(paren
r_char
op_star
)paren
id|data
comma
op_amp
id|check
comma
op_amp
id|conversion
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|umask
)paren
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|cache_init
c_func
(paren
)paren
suffix:semicolon
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|s-&gt;s_dev
comma
l_int|0
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MSDOS bread failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|b
op_assign
(paren
r_struct
id|msdos_boot_sector
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
multiline_comment|/* we cannot handle anything else yet */
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|cluster_size
op_assign
id|b-&gt;cluster_size
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fats
op_assign
id|b-&gt;fats
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_start
op_assign
id|b-&gt;reserved
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_length
op_assign
id|b-&gt;fat_length
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_start
op_assign
id|b-&gt;reserved
op_plus
id|b-&gt;fats
op_star
id|b-&gt;fat_length
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_entries
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|b-&gt;dir_entries
)paren
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|data_start
op_assign
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_start
op_plus
(paren
(paren
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_entries
op_lshift
l_int|5
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
id|data_sectors
op_assign
(paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|b-&gt;sectors
)paren
ques
c_cond
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|b-&gt;sectors
)paren
suffix:colon
id|b-&gt;total_sect
)paren
op_minus
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|data_start
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|clusters
op_assign
id|b-&gt;cluster_size
ques
c_cond
id|data_sectors
op_div
id|b-&gt;cluster_size
suffix:colon
l_int|0
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_bits
op_assign
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|clusters
OG
id|MSDOS_FAT12
ques
c_cond
l_int|16
suffix:colon
l_int|12
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[MS-DOS FS Rel. alpha.8, FAT %d, check=%c, conv=%c, uid=%d, gid=%d, umask=%03o]&bslash;n&quot;
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_bits
comma
id|check
comma
id|conversion
comma
id|uid
comma
id|gid
comma
id|umask
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[me=0x%x,cs=%d,#f=%d,fs=%d,fl=%d,ds=%d,de=%d,data=%d,se=%d,ts=%d]&bslash;n&quot;
comma
id|b-&gt;media
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|cluster_size
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fats
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_start
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_length
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_start
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_entries
comma
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|data_start
comma
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|b-&gt;sectors
comma
id|b-&gt;total_sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fats
op_logical_or
(paren
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|dir_entries
op_amp
(paren
id|MSDOS_DPS
op_minus
l_int|1
)paren
)paren
op_logical_or
op_logical_neg
id|b-&gt;cluster_size
op_logical_or
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|clusters
op_plus
l_int|2
OG
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_length
op_star
id|SECTOR_SIZE
op_star
l_int|8
op_div
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_bits
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unsupported FS parameters&bslash;n&quot;
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
id|MSDOS_CAN_BMAP
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|s
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;No bmap support&bslash;n&quot;
)paren
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|MSDOS_SUPER_MAGIC
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|name_check
op_assign
id|check
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|conversion
op_assign
id|conversion
suffix:semicolon
multiline_comment|/* set up enough so that it can read an inode */
id|s-&gt;s_op
op_assign
op_amp
id|msdos_sops
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fs_uid
op_assign
id|uid
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fs_gid
op_assign
id|gid
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fs_umask
op_assign
id|umask
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|free_clusters
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t know yet */
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_wait
op_assign
l_int|NULL
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|fat_lock
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_mounted
op_assign
id|iget
c_func
(paren
id|s
comma
id|MSDOS_ROOT_INO
)paren
)paren
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|msdos_statfs
r_void
id|msdos_statfs
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
id|free
comma
id|this
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sb-&gt;s_magic
comma
op_amp
id|buf-&gt;f_type
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
op_star
id|SECTOR_SIZE
comma
op_amp
id|buf-&gt;f_bsize
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
comma
op_amp
id|buf-&gt;f_blocks
)paren
suffix:semicolon
id|lock_fat
c_func
(paren
id|sb
)paren
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
id|free_clusters
op_ne
op_minus
l_int|1
)paren
id|free
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
suffix:semicolon
r_else
(brace
id|free
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|this
op_assign
l_int|2
suffix:semicolon
id|this
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
op_plus
l_int|2
suffix:semicolon
id|this
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|fat_access
c_func
(paren
id|sb
comma
id|this
comma
op_minus
l_int|1
)paren
)paren
id|free
op_increment
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_assign
id|free
suffix:semicolon
)brace
id|unlock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|free
comma
op_amp
id|buf-&gt;f_bfree
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|free
comma
op_amp
id|buf-&gt;f_bavail
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_files
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_ffree
)paren
suffix:semicolon
)brace
DECL|function|msdos_bmap
r_int
id|msdos_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
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
(paren
id|sb-&gt;cluster_size
op_amp
l_int|1
)paren
op_logical_or
(paren
id|sb-&gt;data_start
op_amp
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dir_start
op_amp
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|sb-&gt;dir_start
op_rshift
l_int|1
)paren
op_plus
id|block
suffix:semicolon
)brace
id|cluster
op_assign
(paren
id|block
op_star
l_int|2
)paren
op_div
id|sb-&gt;cluster_size
suffix:semicolon
id|offset
op_assign
(paren
id|block
op_star
l_int|2
)paren
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
)paren
op_rshift
l_int|1
suffix:semicolon
)brace
DECL|function|msdos_read_inode
r_void
id|msdos_read_inode
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
id|msdos_dir_entry
op_star
id|raw_entry
suffix:semicolon
r_int
id|this
suffix:semicolon
multiline_comment|/* printk(&quot;read inode %d&bslash;n&quot;,inode-&gt;i_ino); */
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_busy
op_assign
l_int|0
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_depend
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_old
op_assign
l_int|NULL
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_binary
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fs_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fs_gid
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
(brace
id|inode-&gt;i_mode
op_assign
(paren
l_int|0777
op_amp
op_complement
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fs_umask
)paren
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|msdos_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|msdos_subdirs
c_func
(paren
id|inode
)paren
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* subdirs (neither . nor ..) plus . and &quot;self&quot; */
id|inode-&gt;i_size
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|dir_entries
op_star
r_sizeof
(paren
r_struct
id|msdos_dir_entry
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
op_star
id|SECTOR_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|inode-&gt;i_blksize
op_minus
l_int|1
)paren
op_div
id|inode-&gt;i_blksize
op_star
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
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
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|inode-&gt;i_ino
op_rshift
id|MSDOS_DPB_BITS
comma
id|BLOCK_SIZE
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
id|raw_entry
op_assign
op_amp
(paren
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
)paren
)paren
(braket
id|inode-&gt;i_ino
op_amp
(paren
id|MSDOS_DPB
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|raw_entry-&gt;attr
op_amp
id|ATTR_DIR
)paren
op_logical_and
op_star
id|raw_entry-&gt;name
op_logical_and
op_star
(paren
r_int
r_char
op_star
)paren
id|raw_entry-&gt;name
op_ne
id|DELETED_FLAG
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|MSDOS_MKMODE
c_func
(paren
id|raw_entry-&gt;attr
comma
l_int|0777
op_amp
op_complement
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fs_umask
)paren
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|msdos_dir_inode_operations
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
id|raw_entry-&gt;start
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|msdos_subdirs
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* includes .., compensating for &quot;self&quot; */
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;directory %d: i_nlink == 0&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|this
op_assign
id|raw_entry-&gt;start
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|this
op_ne
op_minus
l_int|1
)paren
(brace
id|inode-&gt;i_size
op_add_assign
id|SECTOR_SIZE
op_star
id|MSDOS_SB
c_func
(paren
id|inode
op_member_access_from_pointer
id|i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
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
op_minus
l_int|1
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Directory %d: bad FAT&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|inode-&gt;i_mode
op_assign
id|MSDOS_MKMODE
c_func
(paren
id|raw_entry-&gt;attr
comma
l_int|0666
op_amp
op_complement
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|fs_umask
)paren
op_or
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_op
op_assign
id|MSDOS_CAN_BMAP
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
ques
c_cond
op_amp
id|msdos_file_inode_operations
suffix:colon
op_amp
id|msdos_file_inode_operations_no_bmap
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
id|raw_entry-&gt;start
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|raw_entry-&gt;size
suffix:semicolon
)brace
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_binary
op_assign
id|is_binary
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|conversion
comma
id|raw_entry-&gt;ext
)paren
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_assign
id|raw_entry-&gt;attr
op_amp
id|ATTR_UNUSED
suffix:semicolon
multiline_comment|/* this is as close to the truth as we can get ... */
id|inode-&gt;i_blksize
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
op_star
id|SECTOR_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|inode-&gt;i_blksize
op_minus
l_int|1
)paren
op_div
id|inode-&gt;i_blksize
op_star
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|date_dos2unix
c_func
(paren
id|raw_entry-&gt;time
comma
id|raw_entry-&gt;date
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|msdos_write_inode
r_void
id|msdos_write_inode
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
id|msdos_dir_entry
op_star
id|raw_entry
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
op_logical_or
op_logical_neg
id|inode-&gt;i_nlink
)paren
r_return
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
id|inode-&gt;i_ino
op_rshift
id|MSDOS_DPB_BITS
comma
id|BLOCK_SIZE
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
id|raw_entry
op_assign
op_amp
(paren
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
)paren
)paren
(braket
id|inode-&gt;i_ino
op_amp
(paren
id|MSDOS_DPB
op_minus
l_int|1
)paren
)braket
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
(brace
id|raw_entry-&gt;attr
op_assign
id|ATTR_DIR
suffix:semicolon
id|raw_entry-&gt;size
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|raw_entry-&gt;attr
op_assign
id|ATTR_NONE
suffix:semicolon
id|raw_entry-&gt;size
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
id|raw_entry-&gt;attr
op_or_assign
id|MSDOS_MKATTR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_or
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
suffix:semicolon
id|raw_entry-&gt;start
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
suffix:semicolon
id|date_unix2dos
c_func
(paren
id|inode-&gt;i_mtime
comma
op_amp
id|raw_entry-&gt;time
comma
op_amp
id|raw_entry-&gt;date
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
)brace
eof
