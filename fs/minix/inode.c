multiline_comment|/*&n; *  linux/fs/minix/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT
macro_line|#endif
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|function|minix_put_inode
r_void
id|minix_put_inode
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
id|minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|minix_free_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|minix_commit_super
r_static
r_void
id|minix_commit_super
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|minix_super_block
op_star
id|ms
)paren
(brace
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|minix_write_super
r_void
id|minix_write_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|minix_super_block
op_star
id|ms
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|ms
op_assign
id|sb-&gt;u.minix_sb.s_ms
suffix:semicolon
r_if
c_cond
(paren
id|ms-&gt;s_state
op_amp
id|MINIX_VALID_FS
)paren
id|ms-&gt;s_state
op_and_assign
op_complement
id|MINIX_VALID_FS
suffix:semicolon
id|minix_commit_super
(paren
id|sb
comma
id|ms
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|minix_put_super
r_void
id|minix_put_super
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|sb-&gt;u.minix_sb.s_ms-&gt;s_state
op_assign
id|sb-&gt;u.minix_sb.s_mount_state
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
comma
l_int|1
)paren
suffix:semicolon
)brace
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
id|MINIX_I_MAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|sb-&gt;u.minix_sb.s_imap
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
id|MINIX_Z_MAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|sb-&gt;u.minix_sb.s_zmap
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|sb-&gt;u.minix_sb.s_sbh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|minix_sops
r_static
r_struct
id|super_operations
id|minix_sops
op_assign
(brace
id|minix_read_inode
comma
l_int|NULL
comma
id|minix_write_inode
comma
id|minix_put_inode
comma
id|minix_put_super
comma
id|minix_write_super
comma
id|minix_statfs
comma
id|minix_remount
)brace
suffix:semicolon
DECL|function|minix_remount
r_int
id|minix_remount
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
r_struct
id|minix_super_block
op_star
id|ms
suffix:semicolon
id|ms
op_assign
id|sb-&gt;u.minix_sb.s_ms
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
op_eq
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
(brace
r_if
c_cond
(paren
id|ms-&gt;s_state
op_amp
id|MINIX_VALID_FS
op_logical_or
op_logical_neg
(paren
id|sb-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_VALID_FS
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Mounting a rw partition read-only. */
id|ms-&gt;s_state
op_assign
id|sb-&gt;u.minix_sb.s_mount_state
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|minix_commit_super
(paren
id|sb
comma
id|ms
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Mount a partition which is read-only, read-write. */
id|sb-&gt;u.minix_sb.s_mount_state
op_assign
id|ms-&gt;s_state
suffix:semicolon
id|ms-&gt;s_state
op_and_assign
op_complement
id|MINIX_VALID_FS
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sb-&gt;u.minix_sb.s_sbh
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_VALID_FS
)paren
)paren
id|printk
(paren
l_string|&quot;MINIX-fs warning: remounting unchecked fs, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|sb-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_ERROR_FS
)paren
)paren
id|printk
(paren
l_string|&quot;MINIX-fs warning: remounting fs with errors, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|minix_read_super
r_struct
id|super_block
op_star
id|minix_read_super
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
id|minix_super_block
op_star
id|ms
suffix:semicolon
r_int
id|i
comma
id|dev
op_assign
id|s-&gt;s_dev
comma
id|block
suffix:semicolon
r_if
c_cond
(paren
l_int|32
op_ne
r_sizeof
(paren
r_struct
id|minix_inode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;bad i-node size&quot;
)paren
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
l_int|1
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
l_string|&quot;MINIX-fs: unable to read superblock&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ms
op_assign
(paren
r_struct
id|minix_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|s-&gt;u.minix_sb.s_ms
op_assign
id|ms
suffix:semicolon
id|s-&gt;u.minix_sb.s_sbh
op_assign
id|bh
suffix:semicolon
id|s-&gt;u.minix_sb.s_mount_state
op_assign
id|ms-&gt;s_state
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;u.minix_sb.s_ninodes
op_assign
id|ms-&gt;s_ninodes
suffix:semicolon
id|s-&gt;u.minix_sb.s_nzones
op_assign
id|ms-&gt;s_nzones
suffix:semicolon
id|s-&gt;u.minix_sb.s_imap_blocks
op_assign
id|ms-&gt;s_imap_blocks
suffix:semicolon
id|s-&gt;u.minix_sb.s_zmap_blocks
op_assign
id|ms-&gt;s_zmap_blocks
suffix:semicolon
id|s-&gt;u.minix_sb.s_firstdatazone
op_assign
id|ms-&gt;s_firstdatazone
suffix:semicolon
id|s-&gt;u.minix_sb.s_log_zone_size
op_assign
id|ms-&gt;s_log_zone_size
suffix:semicolon
id|s-&gt;u.minix_sb.s_max_size
op_assign
id|ms-&gt;s_max_size
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|ms-&gt;s_magic
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC
)paren
(brace
id|s-&gt;u.minix_sb.s_dirsize
op_assign
l_int|16
suffix:semicolon
id|s-&gt;u.minix_sb.s_namelen
op_assign
l_int|14
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC2
)paren
(brace
id|s-&gt;u.minix_sb.s_dirsize
op_assign
l_int|32
suffix:semicolon
id|s-&gt;u.minix_sb.s_namelen
op_assign
l_int|30
suffix:semicolon
)brace
r_else
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
l_string|&quot;VFS: Can&squot;t find a minix filesystem on dev 0x%04x.&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|MINIX_I_MAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
id|s-&gt;u.minix_sb.s_imap
(braket
id|i
)braket
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
id|MINIX_Z_MAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
id|s-&gt;u.minix_sb.s_zmap
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|block
op_assign
l_int|2
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
id|s-&gt;u.minix_sb.s_imap_blocks
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|s-&gt;u.minix_sb.s_imap
(braket
id|i
)braket
op_assign
id|bread
c_func
(paren
id|dev
comma
id|block
comma
id|BLOCK_SIZE
)paren
)paren
op_ne
l_int|NULL
)paren
id|block
op_increment
suffix:semicolon
r_else
r_break
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
id|s-&gt;u.minix_sb.s_zmap_blocks
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|s-&gt;u.minix_sb.s_zmap
(braket
id|i
)braket
op_assign
id|bread
c_func
(paren
id|dev
comma
id|block
comma
id|BLOCK_SIZE
)paren
)paren
op_ne
l_int|NULL
)paren
id|block
op_increment
suffix:semicolon
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ne
l_int|2
op_plus
id|s-&gt;u.minix_sb.s_imap_blocks
op_plus
id|s-&gt;u.minix_sb.s_zmap_blocks
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
id|MINIX_I_MAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|s-&gt;u.minix_sb.s_imap
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
id|MINIX_Z_MAP_SLOTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|s-&gt;u.minix_sb.s_zmap
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
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MINIX-fs: bad superblock or unable to read bitmaps&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|set_bit
c_func
(paren
l_int|0
comma
id|s-&gt;u.minix_sb.s_imap
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
id|set_bit
c_func
(paren
l_int|0
comma
id|s-&gt;u.minix_sb.s_zmap
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
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
id|minix_sops
suffix:semicolon
id|s-&gt;s_mounted
op_assign
id|iget
c_func
(paren
id|s
comma
id|MINIX_ROOT_INO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_mounted
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
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
l_string|&quot;MINIX-fs: get root inode failed&bslash;n&quot;
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
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|ms-&gt;s_state
op_and_assign
op_complement
id|MINIX_VALID_FS
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_VALID_FS
)paren
)paren
id|printk
(paren
l_string|&quot;MINIX-fs: mounting unchecked file system, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;u.minix_sb.s_mount_state
op_amp
id|MINIX_ERROR_FS
)paren
id|printk
(paren
l_string|&quot;MINIX-fs: mounting file system with errors, &quot;
l_string|&quot;running fsck is recommended.&bslash;n&quot;
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|minix_statfs
r_void
id|minix_statfs
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
id|MINIX_SUPER_MAGIC
comma
op_amp
id|buf-&gt;f_type
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|1024
comma
op_amp
id|buf-&gt;f_bsize
)paren
suffix:semicolon
id|tmp
op_assign
id|sb-&gt;u.minix_sb.s_nzones
op_minus
id|sb-&gt;u.minix_sb.s_firstdatazone
suffix:semicolon
id|tmp
op_lshift_assign
id|sb-&gt;u.minix_sb.s_log_zone_size
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp
comma
op_amp
id|buf-&gt;f_blocks
)paren
suffix:semicolon
id|tmp
op_assign
id|minix_count_free_blocks
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
id|sb-&gt;u.minix_sb.s_ninodes
comma
op_amp
id|buf-&gt;f_files
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|minix_count_free_inodes
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
id|sb-&gt;u.minix_sb.s_namelen
comma
op_amp
id|buf-&gt;f_namelen
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t know what value to put in buf-&gt;f_fsid */
)brace
DECL|macro|inode_bmap
mdefine_line|#define inode_bmap(inode,nr) ((inode)-&gt;u.minix_i.i_data[(nr)])
DECL|function|block_bmap
r_static
r_int
id|block_bmap
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
r_int
r_int
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
DECL|function|minix_bmap
r_int
id|minix_bmap
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
r_int
id|i
suffix:semicolon
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
l_string|&quot;minix_bmap: block&lt;0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
op_ge
l_int|7
op_plus
l_int|512
op_plus
l_int|512
op_star
l_int|512
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_bmap: block&gt;big&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
OL
l_int|7
)paren
r_return
id|inode_bmap
c_func
(paren
id|inode
comma
id|block
)paren
suffix:semicolon
id|block
op_sub_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|512
)paren
(brace
id|i
op_assign
id|inode_bmap
c_func
(paren
id|inode
comma
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|block_bmap
c_func
(paren
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|BLOCK_SIZE
)paren
comma
id|block
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
l_int|512
suffix:semicolon
id|i
op_assign
id|inode_bmap
c_func
(paren
id|inode
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|block_bmap
c_func
(paren
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|BLOCK_SIZE
)paren
comma
id|block
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|block_bmap
c_func
(paren
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|BLOCK_SIZE
)paren
comma
id|block
op_amp
l_int|511
)paren
suffix:semicolon
)brace
DECL|function|inode_getblk
r_static
r_struct
id|buffer_head
op_star
id|inode_getblk
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nr
comma
r_int
id|create
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_int
r_int
op_star
id|p
suffix:semicolon
r_struct
id|buffer_head
op_star
id|result
suffix:semicolon
id|p
op_assign
id|inode-&gt;u.minix_i.i_data
op_plus
id|nr
suffix:semicolon
id|repeat
suffix:colon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|tmp
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
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
op_star
id|p
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
id|minix_new_block
c_func
(paren
id|inode-&gt;i_sb
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
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|minix_free_block
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
id|p
op_assign
id|tmp
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|block_getblk
r_static
r_struct
id|buffer_head
op_star
id|block_getblk
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
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_int
r_int
op_star
id|p
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
id|p
op_assign
id|nr
op_plus
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|repeat
suffix:colon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|tmp
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
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
op_star
id|p
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
id|minix_new_block
c_func
(paren
id|inode-&gt;i_sb
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
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|minix_free_block
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
id|p
op_assign
id|tmp
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
id|result
suffix:semicolon
)brace
DECL|function|minix_getblk
r_struct
id|buffer_head
op_star
id|minix_getblk
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
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
l_string|&quot;minix_getblk: block&lt;0&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
op_ge
l_int|7
op_plus
l_int|512
op_plus
l_int|512
op_star
l_int|512
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_getblk: block&gt;big&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
OL
l_int|7
)paren
r_return
id|inode_getblk
c_func
(paren
id|inode
comma
id|block
comma
id|create
)paren
suffix:semicolon
id|block
op_sub_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|512
)paren
(brace
id|bh
op_assign
id|inode_getblk
c_func
(paren
id|inode
comma
l_int|7
comma
id|create
)paren
suffix:semicolon
r_return
id|block_getblk
c_func
(paren
id|inode
comma
id|bh
comma
id|block
comma
id|create
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
l_int|512
suffix:semicolon
id|bh
op_assign
id|inode_getblk
c_func
(paren
id|inode
comma
l_int|8
comma
id|create
)paren
suffix:semicolon
id|bh
op_assign
id|block_getblk
c_func
(paren
id|inode
comma
id|bh
comma
id|block
op_rshift
l_int|9
comma
id|create
)paren
suffix:semicolon
r_return
id|block_getblk
c_func
(paren
id|inode
comma
id|bh
comma
id|block
op_amp
l_int|511
comma
id|create
)paren
suffix:semicolon
)brace
DECL|function|minix_bread
r_struct
id|buffer_head
op_star
id|minix_bread
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
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
id|minix_getblk
c_func
(paren
id|inode
comma
id|block
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
DECL|function|minix_read_inode
r_void
id|minix_read_inode
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
id|block
comma
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
op_ge
id|inode-&gt;i_sb-&gt;u.minix_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad inode number on dev 0x%04x: %d is out of range&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|block
op_assign
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
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Major problem: unable to read inode from dev 0x%04x&bslash;n&quot;
comma
id|inode-&gt;i_dev
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
id|minix_inode
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_mod
id|MINIX_INODES_PER_BLOCK
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
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|raw_inode-&gt;i_time
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
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
id|inode-&gt;i_rdev
op_assign
id|raw_inode-&gt;i_zone
(braket
l_int|0
)braket
suffix:semicolon
r_else
r_for
c_loop
(paren
id|block
op_assign
l_int|0
suffix:semicolon
id|block
OL
l_int|9
suffix:semicolon
id|block
op_increment
)paren
id|inode-&gt;u.minix_i.i_data
(braket
id|block
)braket
op_assign
id|raw_inode-&gt;i_zone
(braket
id|block
)braket
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
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|minix_file_inode_operations
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
id|minix_dir_inode_operations
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
id|minix_symlink_inode_operations
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
DECL|function|minix_update_inode
r_static
r_struct
id|buffer_head
op_star
id|minix_update_inode
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
op_ge
id|inode-&gt;i_sb-&gt;u.minix_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad inode number on dev 0x%04x: %d is out of range&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|ino
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
id|block
op_assign
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
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unable to read i-node block&bslash;n&quot;
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
id|minix_inode
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|ino
op_minus
l_int|1
)paren
op_mod
id|MINIX_INODES_PER_BLOCK
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
id|raw_inode-&gt;i_time
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
r_for
c_loop
(paren
id|block
op_assign
l_int|0
suffix:semicolon
id|block
OL
l_int|9
suffix:semicolon
id|block
op_increment
)paren
id|raw_inode-&gt;i_zone
(braket
id|block
)braket
op_assign
id|inode-&gt;u.minix_i.i_data
(braket
id|block
)braket
suffix:semicolon
id|inode-&gt;i_dirt
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
DECL|function|minix_write_inode
r_void
id|minix_write_inode
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
id|minix_update_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|minix_sync_inode
r_int
id|minix_sync_inode
c_func
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
id|minix_update_inode
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
l_string|&quot;IO error syncing minix inode [%04x:%08lx]&bslash;n&quot;
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
macro_line|#ifdef MODULE
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
DECL|variable|minix_fs_type
r_static
r_struct
id|file_system_type
id|minix_fs_type
op_assign
(brace
id|minix_read_super
comma
l_string|&quot;minix&quot;
comma
l_int|1
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|register_filesystem
c_func
(paren
op_amp
id|minix_fs_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MOD_IN_USE
)paren
id|printk
c_func
(paren
l_string|&quot;ne: device busy, remove delayed&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|minix_fs_type
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
