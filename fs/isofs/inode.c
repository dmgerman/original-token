multiline_comment|/*&n; *  linux/fs/isofs/inode.c&n; * &n; *  (C) 1992  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifndef CONFIG_BLK_DEV_SR
macro_line|#error The iso9660 filesystem can only be used with CDROM.
macro_line|#endif
r_extern
r_int
id|check_cdrom_media_change
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef LEAK_CHECK
DECL|variable|check_malloc
r_static
r_int
id|check_malloc
op_assign
l_int|0
suffix:semicolon
DECL|variable|check_bread
r_static
r_int
id|check_bread
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|function|isofs_put_super
r_void
id|isofs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
macro_line|#ifdef LEAK_CHECK
id|printk
c_func
(paren
l_string|&quot;Outstanding mallocs:%d, outstanding buffers: %d&bslash;n&quot;
comma
id|check_malloc
comma
id|check_bread
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|isofs_sops
r_static
r_struct
id|super_operations
id|isofs_sops
op_assign
(brace
id|isofs_read_inode
comma
l_int|NULL
comma
multiline_comment|/* notify_change */
l_int|NULL
comma
multiline_comment|/* write_inode */
l_int|NULL
comma
multiline_comment|/* put_inode */
id|isofs_put_super
comma
l_int|NULL
comma
multiline_comment|/* write_super */
id|isofs_statfs
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
id|map
comma
r_char
op_star
id|conversion
comma
r_char
op_star
id|rock
comma
r_char
op_star
id|cruft
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
id|map
op_assign
l_char|&squot;n&squot;
suffix:semicolon
op_star
id|rock
op_assign
l_char|&squot;y&squot;
suffix:semicolon
op_star
id|cruft
op_assign
l_char|&squot;n&squot;
suffix:semicolon
op_star
id|conversion
op_assign
l_char|&squot;a&squot;
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
id|strncmp
c_func
(paren
id|this
comma
l_string|&quot;norock&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|rock
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|this
comma
l_string|&quot;cruft&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|cruft
op_assign
l_char|&squot;y&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
suffix:semicolon
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
l_string|&quot;map&quot;
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
l_string|&quot;on&quot;
comma
op_star
id|value
)paren
)paren
op_star
id|map
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
l_string|&quot;off&quot;
)paren
)paren
op_star
id|map
op_assign
l_char|&squot;o&squot;
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
id|map
op_assign
l_char|&squot;n&squot;
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
l_string|&quot;mtext&quot;
)paren
)paren
op_star
id|conversion
op_assign
l_char|&squot;m&squot;
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
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|isofs_read_super
r_struct
id|super_block
op_star
id|isofs_read_super
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
r_int
id|iso_blknum
suffix:semicolon
r_int
id|high_sierra
suffix:semicolon
r_int
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
r_struct
id|iso_volume_descriptor
op_star
id|vdp
suffix:semicolon
r_struct
id|hs_volume_descriptor
op_star
id|hdp
suffix:semicolon
r_struct
id|iso_primary_descriptor
op_star
id|pri
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|hs_primary_descriptor
op_star
id|h_pri
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|rootp
suffix:semicolon
r_char
id|map
comma
id|conversion
comma
id|rock
comma
id|cruft
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
id|map
comma
op_amp
id|conversion
comma
op_amp
id|rock
comma
op_amp
id|cruft
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
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;u.isofs_sb.s_high_sierra
op_assign
id|high_sierra
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* default is iso9660 */
r_for
c_loop
(paren
id|iso_blknum
op_assign
l_int|16
suffix:semicolon
id|iso_blknum
OL
l_int|100
suffix:semicolon
id|iso_blknum
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
id|bread
c_func
(paren
id|dev
comma
id|iso_blknum
op_lshift
(paren
id|ISOFS_BLOCK_BITS
op_minus
id|ISOFS_BUFFER_BITS
)paren
comma
id|ISOFS_BUFFER_SIZE
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
l_string|&quot;isofs_read_super: bread failed, dev 0x%x iso_blknum %d&bslash;n&quot;
comma
id|dev
comma
id|iso_blknum
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|vdp
op_assign
(paren
r_struct
id|iso_volume_descriptor
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|hdp
op_assign
(paren
r_struct
id|hs_volume_descriptor
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
(paren
id|hdp-&gt;id
comma
id|HS_STANDARD_ID
comma
r_sizeof
id|hdp-&gt;id
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|isonum_711
(paren
id|hdp-&gt;type
)paren
op_ne
id|ISO_VD_PRIMARY
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|isonum_711
(paren
id|hdp-&gt;type
)paren
op_eq
id|ISO_VD_END
)paren
r_goto
id|out
suffix:semicolon
id|s-&gt;u.isofs_sb.s_high_sierra
op_assign
l_int|1
suffix:semicolon
id|high_sierra
op_assign
l_int|1
suffix:semicolon
id|rock
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|h_pri
op_assign
(paren
r_struct
id|hs_primary_descriptor
op_star
)paren
id|vdp
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
(paren
id|vdp-&gt;id
comma
id|ISO_STANDARD_ID
comma
r_sizeof
id|vdp-&gt;id
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|isonum_711
(paren
id|vdp-&gt;type
)paren
op_ne
id|ISO_VD_PRIMARY
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|isonum_711
(paren
id|vdp-&gt;type
)paren
op_eq
id|ISO_VD_END
)paren
r_goto
id|out
suffix:semicolon
id|pri
op_assign
(paren
r_struct
id|iso_primary_descriptor
op_star
)paren
id|vdp
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iso_blknum
op_eq
l_int|100
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to identify CD-ROM format.&bslash;n&quot;
)paren
suffix:semicolon
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
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|high_sierra
)paren
(brace
id|rootp
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
id|h_pri-&gt;root_directory_record
suffix:semicolon
r_if
c_cond
(paren
id|isonum_723
(paren
id|h_pri-&gt;volume_set_size
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Multi-volume disks not (yet) supported.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
id|s-&gt;u.isofs_sb.s_nzones
op_assign
id|isonum_733
(paren
id|h_pri-&gt;volume_space_size
)paren
suffix:semicolon
id|s-&gt;u.isofs_sb.s_log_zone_size
op_assign
id|isonum_723
(paren
id|h_pri-&gt;logical_block_size
)paren
suffix:semicolon
id|s-&gt;u.isofs_sb.s_max_size
op_assign
id|isonum_733
c_func
(paren
id|h_pri-&gt;volume_space_size
)paren
suffix:semicolon
)brace
r_else
(brace
id|rootp
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
id|pri-&gt;root_directory_record
suffix:semicolon
r_if
c_cond
(paren
id|isonum_723
(paren
id|pri-&gt;volume_set_size
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Multi-volume disks not (yet) supported.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
id|s-&gt;u.isofs_sb.s_nzones
op_assign
id|isonum_733
(paren
id|pri-&gt;volume_space_size
)paren
suffix:semicolon
id|s-&gt;u.isofs_sb.s_log_zone_size
op_assign
id|isonum_723
(paren
id|pri-&gt;logical_block_size
)paren
suffix:semicolon
id|s-&gt;u.isofs_sb.s_max_size
op_assign
id|isonum_733
c_func
(paren
id|pri-&gt;volume_space_size
)paren
suffix:semicolon
)brace
id|s-&gt;u.isofs_sb.s_ninodes
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No way to figure this out easily */
id|s-&gt;u.isofs_sb.s_firstdatazone
op_assign
id|isonum_733
c_func
(paren
id|rootp-&gt;extent
)paren
op_lshift
(paren
id|ISOFS_BLOCK_BITS
op_minus
id|ISOFS_BUFFER_BITS
)paren
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|ISOFS_SUPER_MAGIC
suffix:semicolon
multiline_comment|/* The CDROM is read-only, has no nodes (devices) on it, and since&n;&t;   all of the files appear to be owned by root, we really do not want&n;&t;   to allow suid.  (suid or devices will not show up unless we have&n;&t;   Rock Ridge extensions) */
id|s-&gt;s_flags
op_assign
id|MS_RDONLY
multiline_comment|/* | MS_NODEV | MS_NOSUID */
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;u.isofs_sb.s_log_zone_size
op_ne
(paren
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;1 &lt;&lt;Block bits != Block size&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
l_string|&quot;Max size:%d   Log zone size:%d&bslash;n&quot;
comma
id|s-&gt;u.isofs_sb.s_max_size
comma
id|s-&gt;u.isofs_sb.s_log_zone_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;First datazone:%d   Root inode number %d&bslash;n&quot;
comma
id|s-&gt;u.isofs_sb.s_firstdatazone
comma
id|isonum_733
(paren
id|rootp-&gt;extent
)paren
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high_sierra
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Disc in High Sierra format.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* set up enough so that it can read an inode */
id|s-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|isofs_sops
suffix:semicolon
id|s-&gt;u.isofs_sb.s_mapping
op_assign
id|map
suffix:semicolon
id|s-&gt;u.isofs_sb.s_rock
op_assign
(paren
id|rock
op_eq
l_char|&squot;y&squot;
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|s-&gt;u.isofs_sb.s_conversion
op_assign
id|conversion
suffix:semicolon
id|s-&gt;u.isofs_sb.s_cruft
op_assign
id|cruft
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
id|ISOFS_BUFFER_SIZE
suffix:semicolon
id|s-&gt;s_mounted
op_assign
id|iget
c_func
(paren
id|s
comma
id|isonum_733
(paren
id|rootp-&gt;extent
)paren
op_lshift
id|ISOFS_BLOCK_BITS
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
op_logical_neg
(paren
id|s-&gt;s_mounted
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
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|s-&gt;s_dev
)paren
op_eq
l_int|11
)paren
(brace
multiline_comment|/* Chech this one more time. */
r_if
c_cond
(paren
id|check_cdrom_media_change
c_func
(paren
id|s-&gt;s_dev
comma
l_int|0
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
suffix:semicolon
r_return
id|s
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* Kick out for various error conditions */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
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
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|isofs_statfs
r_void
id|isofs_statfs
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
id|put_fs_long
c_func
(paren
id|ISOFS_SUPER_MAGIC
comma
op_amp
id|buf-&gt;f_type
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
comma
op_amp
id|buf-&gt;f_bsize
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sb-&gt;u.isofs_sb.s_nzones
comma
op_amp
id|buf-&gt;f_blocks
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_bfree
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_bavail
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sb-&gt;u.isofs_sb.s_ninodes
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
multiline_comment|/* Don&squot;t know what value to put in buf-&gt;f_fsid */
)brace
DECL|function|isofs_bmap
r_int
id|isofs_bmap
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
r_if
c_cond
(paren
id|block
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;_isofs_bmap: block&lt;0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|inode-&gt;u.isofs_i.i_first_extent
op_plus
id|block
suffix:semicolon
)brace
DECL|function|isofs_read_inode
r_void
id|isofs_read_inode
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
r_char
op_star
id|pnt
comma
op_star
id|cpnt
op_assign
l_int|0
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|raw_inode
suffix:semicolon
r_int
id|high_sierra
suffix:semicolon
r_int
id|block
suffix:semicolon
r_int
id|i
suffix:semicolon
id|block
op_assign
id|inode-&gt;i_ino
op_rshift
id|ISOFS_BUFFER_BITS
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
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
id|pnt
op_assign
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|inode-&gt;i_ino
op_amp
(paren
id|ISOFS_BUFFER_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|raw_inode
op_assign
(paren
(paren
r_struct
id|iso_directory_record
op_star
)paren
id|pnt
)paren
suffix:semicolon
id|high_sierra
op_assign
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_high_sierra
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;i_ino
op_amp
(paren
id|ISOFS_BUFFER_SIZE
op_minus
l_int|1
)paren
)paren
op_plus
op_star
id|pnt
OG
id|ISOFS_BUFFER_SIZE
)paren
(brace
id|cpnt
op_assign
id|kmalloc
c_func
(paren
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cpnt
comma
id|bh-&gt;b_data
comma
id|ISOFS_BUFFER_SIZE
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
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
op_increment
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cpnt
op_plus
id|ISOFS_BUFFER_SIZE
comma
id|bh-&gt;b_data
comma
id|ISOFS_BUFFER_SIZE
)paren
suffix:semicolon
id|pnt
op_assign
(paren
(paren
r_char
op_star
)paren
id|cpnt
)paren
op_plus
(paren
id|inode-&gt;i_ino
op_amp
(paren
id|ISOFS_BUFFER_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|raw_inode
op_assign
(paren
(paren
r_struct
id|iso_directory_record
op_star
)paren
id|pnt
)paren
suffix:semicolon
)brace
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0444
suffix:semicolon
multiline_comment|/* Everybody gets to read the file. */
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|raw_inode-&gt;flags
(braket
op_minus
id|high_sierra
)braket
op_amp
l_int|2
)paren
(brace
id|inode-&gt;i_mode
op_assign
l_int|0555
op_or
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* There are always at least 2.  It is&n;&t;&t;&t;&t;       hard to figure out what is correct*/
)brace
r_else
(brace
id|inode-&gt;i_mode
op_assign
l_int|0444
suffix:semicolon
multiline_comment|/* Everybody gets to read the file. */
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mode
op_or_assign
id|S_IFREG
suffix:semicolon
multiline_comment|/* If there are no periods in the name, then set the execute permission bit */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|raw_inode-&gt;name_len
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|raw_inode-&gt;name
(braket
id|i
)braket
op_eq
l_char|&squot;.&squot;
op_logical_or
id|raw_inode-&gt;name
(braket
id|i
)braket
op_eq
l_char|&squot;;&squot;
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|raw_inode-&gt;name_len
(braket
l_int|0
)braket
op_logical_or
id|raw_inode-&gt;name
(braket
id|i
)braket
op_eq
l_char|&squot;;&squot;
)paren
(brace
id|inode-&gt;i_mode
op_or_assign
l_int|0111
suffix:semicolon
)brace
multiline_comment|/* execute permission */
)brace
suffix:semicolon
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|isonum_733
(paren
id|raw_inode-&gt;size
)paren
suffix:semicolon
multiline_comment|/* There are defective discs out there - we do this to protect&n;&t;   ourselves.  A cdrom will never contain more than 700Mb */
r_if
c_cond
(paren
id|inode-&gt;i_size
template_param
l_int|700000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: defective cdrom.  Enabling &bslash;&quot;cruft&bslash;&quot; mount option.&bslash;n&quot;
)paren
suffix:semicolon
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_cruft
op_assign
l_char|&squot;y&squot;
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Some dipshit decided to store some other bit of information in the high&n;   byte of the file length.  Catch this and holler.  WARNING: this will make&n;   it impossible for a file to be &gt; 16Mb on the CDROM!!!*/
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_cruft
op_eq
l_char|&squot;y&squot;
op_logical_and
id|inode-&gt;i_size
op_amp
l_int|0xff000000
)paren
(brace
multiline_comment|/*&t;  printk(&quot;Illegal format on cdrom.  Pester manufacturer.&bslash;n&quot;); */
id|inode-&gt;i_size
op_and_assign
l_int|0x00ffffff
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|isonum_723
(paren
id|raw_inode-&gt;volume_sequence_number
)paren
op_ne
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Multi volume CD somehow got mounted.&bslash;n&quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|raw_inode-&gt;interleave
(braket
l_int|0
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Interleaved files not (yet) supported.&bslash;n&quot;
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef DEBUG
multiline_comment|/* I have no idea what extended attributes are used for, so&n;&t;   we will flag it for now */
r_if
c_cond
(paren
id|raw_inode-&gt;ext_attr_length
(braket
l_int|0
)braket
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Extended attributes present for ISO file (%d).&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* I have no idea what file_unit_size is used for, so&n;&t;   we will flag it for now */
r_if
c_cond
(paren
id|raw_inode-&gt;file_unit_size
(braket
l_int|0
)braket
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File unit size != 0 for ISO file.(%d)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
multiline_comment|/* I have no idea what other flag bits are used for, so&n;&t;   we will flag it for now */
r_if
c_cond
(paren
(paren
id|raw_inode-&gt;flags
(braket
op_minus
id|high_sierra
)braket
op_amp
op_complement
l_int|2
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unusual flag settings for ISO file.(%d %x)&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|raw_inode-&gt;flags
(braket
op_minus
id|high_sierra
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Get inode %d: %d %d: %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|block
comma
(paren
(paren
r_int
)paren
id|pnt
)paren
op_amp
l_int|0x3ff
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
macro_line|#endif
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|iso_date
c_func
(paren
id|raw_inode-&gt;date
comma
id|high_sierra
)paren
suffix:semicolon
id|inode-&gt;u.isofs_i.i_first_extent
op_assign
id|isonum_733
(paren
id|raw_inode-&gt;extent
)paren
op_lshift
(paren
id|ISOFS_BLOCK_BITS
op_minus
id|ISOFS_BUFFER_BITS
)paren
suffix:semicolon
id|inode-&gt;u.isofs_i.i_backlink
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Will be used for previous directory */
r_switch
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_conversion
)paren
(brace
r_case
l_char|&squot;a&squot;
suffix:colon
id|inode-&gt;u.isofs_i.i_file_format
op_assign
id|ISOFS_FILE_UNKNOWN
suffix:semicolon
multiline_comment|/* File type */
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
id|inode-&gt;u.isofs_i.i_file_format
op_assign
id|ISOFS_FILE_BINARY
suffix:semicolon
multiline_comment|/* File type */
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
id|inode-&gt;u.isofs_i.i_file_format
op_assign
id|ISOFS_FILE_TEXT
suffix:semicolon
multiline_comment|/* File type */
r_break
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
id|inode-&gt;u.isofs_i.i_file_format
op_assign
id|ISOFS_FILE_TEXT_M
suffix:semicolon
multiline_comment|/* File type */
r_break
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Now test for possible Rock Ridge extensions which will override some of&n;   these numbers in the inode structure. */
r_if
c_cond
(paren
op_logical_neg
id|high_sierra
)paren
id|parse_rock_ridge_inode
c_func
(paren
id|raw_inode
comma
id|inode
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Inode: %x extent: %x&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;u.isofs_i.i_first_extent
)paren
suffix:semicolon
macro_line|#endif
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpnt
)paren
(brace
id|kfree_s
(paren
id|cpnt
comma
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
id|cpnt
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
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
id|isofs_file_inode_operations
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
id|isofs_dir_inode_operations
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
id|isofs_symlink_inode_operations
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
id|isofs_chrdev_inode_operations
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
id|isofs_blkdev_inode_operations
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
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|isofs_fifo_inode_operations
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
l_int|1
suffix:semicolon
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|NULL
suffix:semicolon
id|PIPE_HEAD
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_TAIL
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_READ_WAIT
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITE_WAIT
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|NULL
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* There are times when we need to know the inode number of a parent of&n;   a particular directory.  When control passes through a routine that&n;   has access to the parent information, it fills it into the inode structure,&n;   but sometimes the inode gets flushed out of the queue, and someone&n;   remmembers the number.  When they try to open up again, we have lost&n;   the information.  The &squot;..&squot; entry on the disc points to the data area&n;   for a particular inode, so we can follow these links back up, but since&n;   we do not know the inode number, we do not actually know how large the&n;   directory is.  The disc is almost always correct, and there is&n;   enough error checking on the drive itself, but an open ended search&n;   makes me a little nervous.&n;&n;   The bsd iso filesystem uses the extent number for an inode, and this&n;   would work really nicely for us except that the read_inode function&n;   would not have any clean way of finding the actual directory record&n;   that goes with the file.  If we had such info, then it would pay&n;   to change the inode numbers and eliminate this function.&n;*/
DECL|function|isofs_lookup_grandparent
r_int
id|isofs_lookup_grandparent
c_func
(paren
r_struct
id|inode
op_star
id|parent
comma
r_int
id|extent
)paren
(brace
r_int
r_int
id|block
comma
id|offset
suffix:semicolon
r_int
id|parent_dir
comma
id|inode_number
suffix:semicolon
r_int
id|old_offset
suffix:semicolon
r_char
op_star
id|cpnt
op_assign
l_int|0
suffix:semicolon
r_int
id|result
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|de
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|extent
op_lshift
(paren
id|ISOFS_BLOCK_BITS
op_minus
id|ISOFS_BUFFER_BITS
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
id|parent-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
op_eq
l_int|1
)paren
(brace
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|offset
op_plus
id|bh-&gt;b_data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
(paren
r_char
op_star
)paren
id|de
)paren
op_eq
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|offset
op_add_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|ISOFS_BUFFER_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;.. Directory not in first block of directory.&bslash;n&quot;
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;name_len
(braket
l_int|0
)braket
op_eq
l_int|1
op_logical_and
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|1
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|parent_dir
op_assign
id|find_rock_ridge_relocation
c_func
(paren
id|de
comma
id|parent
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Parent dir:%x&bslash;n&quot;
comma
id|parent_dir
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Now we know the extent where the parent dir starts on.  We have no&n;&t;   idea how long it is, so we just start reading until we either find it&n;&t;   or we find some kind of unreasonable circumstance. */
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|parent_dir
op_lshift
(paren
id|ISOFS_BLOCK_BITS
op_minus
id|ISOFS_BUFFER_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|parent-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
op_eq
l_int|1
)paren
(brace
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|offset
op_plus
id|bh-&gt;b_data
)paren
suffix:semicolon
id|inode_number
op_assign
(paren
id|block
op_lshift
id|ISOFS_BUFFER_BITS
)paren
op_plus
(paren
id|offset
op_amp
(paren
id|ISOFS_BUFFER_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* If the length byte is zero, we should move on to the next CDROM sector.&n;&t;&t;   If we are at the end of the directory, we kick out of the while loop. */
r_if
c_cond
(paren
op_star
(paren
(paren
r_char
op_star
)paren
id|de
)paren
op_eq
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|block
op_amp
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|block
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|parent-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Make sure that the entire directory record is in the current bh block.&n;&t;&t;   If not, we malloc a buffer, and put the two halves together, so that&n;&t;&t;   we can cleanly read the block */
id|old_offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|ISOFS_BUFFER_SIZE
)paren
(brace
id|cpnt
op_assign
id|kmalloc
c_func
(paren
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cpnt
comma
id|bh-&gt;b_data
comma
id|ISOFS_BUFFER_SIZE
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|old_offset
op_plus
id|cpnt
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|offset
op_sub_assign
id|ISOFS_BUFFER_SIZE
suffix:semicolon
id|block
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|block
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
r_return
op_minus
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
id|bread
c_func
(paren
id|parent-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|cpnt
op_plus
id|ISOFS_BUFFER_SIZE
comma
id|bh-&gt;b_data
comma
id|ISOFS_BUFFER_SIZE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|find_rock_ridge_relocation
c_func
(paren
id|de
comma
id|parent
)paren
op_eq
id|extent
)paren
(brace
id|result
op_assign
id|inode_number
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|cpnt
)paren
(brace
id|kfree_s
c_func
(paren
id|cpnt
comma
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
id|cpnt
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* We go here for any condition we cannot handle.  We also drop through&n;&t;   to here at the end of the directory. */
id|out
suffix:colon
r_if
c_cond
(paren
id|cpnt
)paren
(brace
id|kfree_s
c_func
(paren
id|cpnt
comma
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
id|cpnt
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Resultant Inode %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
r_return
id|result
suffix:semicolon
)brace
macro_line|#ifdef LEAK_CHECK
DECL|macro|malloc
macro_line|#undef malloc
DECL|macro|free_s
macro_line|#undef free_s
DECL|macro|bread
macro_line|#undef bread
DECL|macro|brelse
macro_line|#undef brelse
DECL|function|leak_check_malloc
r_void
op_star
(def_block
id|leak_check_malloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|tmp
suffix:semicolon
id|check_malloc
op_increment
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
)def_block
DECL|function|leak_check_free_s
r_void
(def_block
id|leak_check_free_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
(brace
id|check_malloc
op_decrement
suffix:semicolon
r_return
id|kfree_s
c_func
(paren
id|obj
comma
id|size
)paren
suffix:semicolon
)brace
)def_block
DECL|function|leak_check_bread
r_struct
id|buffer_head
op_star
(def_block
id|leak_check_bread
c_func
(paren
r_int
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
(brace
id|check_bread
op_increment
suffix:semicolon
r_return
id|bread
c_func
(paren
id|dev
comma
id|block
comma
id|size
)paren
suffix:semicolon
)brace
)def_block
DECL|function|leak_check_brelse
r_void
(def_block
id|leak_check_brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|check_bread
op_decrement
suffix:semicolon
r_return
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)def_block
macro_line|#endif
eof
