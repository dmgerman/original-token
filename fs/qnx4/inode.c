multiline_comment|/* &n; * QNX4 file system, Linux implementation.&n; * &n; * Version : 0.1&n; * &n; * Using parts of the xiafs filesystem.&n; * &n; * History :&n; * &n; * 01-06-1998 by Richard Frowijn : first release.&n; * 20-06-1998 by Frank Denis : Linux 2.1.99+ support, boot signature, misc.&n; * 30-06-1998 by Frank Denis : first step to write inodes.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|QNX4_VERSION
mdefine_line|#define QNX4_VERSION  4
DECL|macro|QNX4_BMNAME
mdefine_line|#define QNX4_BMNAME   &quot;.bitmap&quot;
DECL|variable|qnx4_sops
r_static
r_struct
id|super_operations
id|qnx4_sops
suffix:semicolon
macro_line|#ifdef CONFIG_QNX4FS_RW
DECL|function|qnx4_sync_inode
r_int
id|qnx4_sync_inode
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
macro_line|# if 0
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|qnx4_update_inode
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
id|buffer_dirty
c_func
(paren
id|bh
)paren
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
id|buffer_req
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;IO error syncing qnx4 inode [%s:%08lx]&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
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
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|# endif
r_return
id|err
suffix:semicolon
)brace
DECL|function|qnx4_delete_inode
r_static
r_void
id|qnx4_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: deleting inode [%lu]&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|qnx4_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|qnx4_free_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|qnx4_write_super
r_static
r_void
id|qnx4_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: write_super&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|qnx4_write_inode
r_static
r_void
id|qnx4_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|qnx4_inode_entry
op_star
id|raw_inode
suffix:semicolon
r_int
id|block
comma
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: write inode 1.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: bad inode number on dev %s: %d is out of range&bslash;n&quot;
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
suffix:semicolon
)brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;qnx4: write inode 2.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|block
op_assign
id|ino
op_div
id|QNX4_INODES_PER_BLOCK
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
id|QNX4_BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: major problem: unable to read inode from dev &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
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
id|qnx4_inode_entry
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|ino
op_mod
id|QNX4_INODES_PER_BLOCK
)paren
suffix:semicolon
id|raw_inode-&gt;di_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|raw_inode-&gt;di_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|raw_inode-&gt;di_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|raw_inode-&gt;di_nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|raw_inode-&gt;di_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|raw_inode-&gt;di_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|raw_inode-&gt;di_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|raw_inode-&gt;di_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|raw_inode-&gt;di_first_xtnt.xtnt_size
op_assign
id|inode-&gt;i_blocks
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
)brace
macro_line|#endif
r_static
r_struct
id|super_block
op_star
id|qnx4_read_super
c_func
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|qnx4_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_void
id|qnx4_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_int
id|qnx4_remount
c_func
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
suffix:semicolon
r_static
r_int
id|qnx4_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|qnx4_sops
r_static
r_struct
id|super_operations
id|qnx4_sops
op_assign
(brace
id|qnx4_read_inode
comma
macro_line|#ifdef CONFIG_QNX4FS_RW
id|qnx4_write_inode
comma
macro_line|#else
l_int|NULL
comma
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* put_inode */
macro_line|#ifdef CONFIG_QNX4FS_RW
id|qnx4_delete_inode
comma
macro_line|#else
l_int|NULL
comma
multiline_comment|/* delete_inode */
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* notify_change */
id|qnx4_put_super
comma
macro_line|#ifdef CONFIG_QNX4FS_RW
id|qnx4_write_super
comma
macro_line|#else
l_int|NULL
comma
macro_line|#endif
id|qnx4_statfs
comma
id|qnx4_remount
comma
l_int|NULL
multiline_comment|/* clear_inode */
)brace
suffix:semicolon
DECL|function|qnx4_remount
r_static
r_int
id|qnx4_remount
c_func
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
id|qnx4_sb_info
op_star
id|qs
suffix:semicolon
id|qs
op_assign
op_amp
id|sb-&gt;u.qnx4_sb
suffix:semicolon
id|qs-&gt;Version
op_assign
id|QNX4_VERSION
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
r_return
l_int|0
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|qs-&gt;sb_buf
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inode_getblk
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
id|tst
suffix:semicolon
r_struct
id|buffer_head
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
id|tst
op_assign
id|nr
suffix:semicolon
id|repeat
suffix:colon
id|tmp
op_assign
id|tst
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
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
id|tst
)paren
(brace
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
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#if 0
id|tmp
op_assign
id|qnx4_new_block
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
r_return
l_int|NULL
suffix:semicolon
)brace
id|result
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|tmp
comma
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tst
)paren
(brace
id|qnx4_free_block
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
id|tst
op_assign
id|tmp
suffix:semicolon
macro_line|#endif
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|qnx4_bread
r_struct
id|buffer_head
op_star
id|qnx4_bread
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
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
r_return
id|bh
suffix:semicolon
)brace
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
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
r_return
id|bh
suffix:semicolon
)brace
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
DECL|function|qnx4_statfs
r_static
r_int
id|qnx4_statfs
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
comma
r_int
id|bufsize
)paren
(brace
r_struct
id|statfs
id|tmp
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
id|tmp
)paren
suffix:semicolon
id|tmp.f_type
op_assign
id|sb-&gt;s_magic
suffix:semicolon
id|tmp.f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|tmp.f_blocks
op_assign
id|le32_to_cpu
c_func
(paren
id|sb-&gt;u.qnx4_sb.BitMap-&gt;di_size
)paren
op_star
l_int|8
suffix:semicolon
id|tmp.f_bfree
op_assign
id|qnx4_count_free_blocks
c_func
(paren
id|sb
)paren
suffix:semicolon
id|tmp.f_bavail
op_assign
id|tmp.f_bfree
suffix:semicolon
id|tmp.f_files
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* change this !!! */
id|tmp.f_ffree
op_assign
id|qnx4_count_free_inodes
c_func
(paren
id|sb
)paren
suffix:semicolon
id|tmp.f_namelen
op_assign
id|QNX4_NAME_MAX
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tmp
comma
id|bufsize
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the root directory of the filesystem to make sure&n; * it really _is_ a qnx4 filesystem, and to check the size&n; * of the directory entry.&n; */
DECL|function|qnx4_checkroot
r_static
r_const
r_char
op_star
id|qnx4_checkroot
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|qnx4_inode_entry
op_star
id|rootdir
suffix:semicolon
r_int
id|rd
comma
id|rl
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|s-&gt;u.qnx4_sb.sb-&gt;RootDir.di_fname
)paren
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_return
l_string|&quot;no qnx4 filesystem (no root dir).&quot;
suffix:semicolon
)brace
r_else
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;QNX4 filesystem found on dev %s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|s-&gt;s_dev
)paren
)paren
)paren
suffix:semicolon
id|rd
op_assign
id|s-&gt;u.qnx4_sb.sb-&gt;RootDir.di_first_xtnt.xtnt_blk
op_minus
l_int|1
suffix:semicolon
id|rl
op_assign
id|s-&gt;u.qnx4_sb.sb-&gt;RootDir.di_first_xtnt.xtnt_size
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
id|rl
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bh
op_assign
id|bread
c_func
(paren
id|s-&gt;s_dev
comma
id|rd
op_plus
id|j
comma
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
multiline_comment|/* root dir, first block */
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
r_return
l_string|&quot;unable to read root entry.&quot;
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
id|QNX4_INODES_PER_BLOCK
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rootdir
op_assign
(paren
r_struct
id|qnx4_inode_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|i
op_star
id|QNX4_DIR_ENTRY_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rootdir-&gt;di_fname
op_ne
l_int|NULL
)paren
(brace
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;Rootdir entry found : [%s]&bslash;n&quot;
comma
id|rootdir-&gt;di_fname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|rootdir-&gt;di_fname
comma
id|QNX4_BMNAME
comma
r_sizeof
id|QNX4_BMNAME
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|s-&gt;u.qnx4_sb.BitMap
op_assign
id|rootdir
suffix:semicolon
multiline_comment|/* keep bitmap inode known */
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* WAIT! s-&gt;u.qnx4_sb.BitMap points into bh-&gt;b_data&n;&t;&t;&t;   and now we release bh?? */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|0
)paren
(brace
r_return
l_string|&quot;bitmap file not found.&quot;
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|qnx4_read_super
r_static
r_struct
id|super_block
op_star
id|qnx4_read_super
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
id|kdev_t
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
r_struct
id|inode
op_star
id|root
suffix:semicolon
r_char
op_star
id|tmpc
suffix:semicolon
r_const
r_char
op_star
id|errmsg
suffix:semicolon
id|MOD_INC_USE_COUNT
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
id|QNX4_BLOCK_SIZE
)paren
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
id|QNX4_BLOCK_SIZE
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|9
suffix:semicolon
id|s-&gt;s_dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Check the boot signature. Since the qnx4 code is&n;&t;   dangerous, we should leave as quickly as possible&n;&t;   if we don&squot;t belong here... */
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
id|QNX4_BLOCK_SIZE
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
l_string|&quot;qnx4: unable to read the boot sector&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|outnobh
suffix:semicolon
)brace
id|tmpc
op_assign
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|tmpc
(braket
l_int|4
)braket
op_ne
l_char|&squot;Q&squot;
op_logical_or
id|tmpc
(braket
l_int|5
)braket
op_ne
l_char|&squot;N&squot;
op_logical_or
id|tmpc
(braket
l_int|6
)braket
op_ne
l_char|&squot;X&squot;
op_logical_or
id|tmpc
(braket
l_int|7
)braket
op_ne
l_char|&squot;4&squot;
op_logical_or
id|tmpc
(braket
l_int|8
)braket
op_ne
l_char|&squot;F&squot;
op_logical_or
id|tmpc
(braket
l_int|9
)braket
op_ne
l_char|&squot;S&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;qnx4: wrong fsid in boot sector.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|1
comma
id|QNX4_BLOCK_SIZE
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
l_string|&quot;qnx4: unable to read the superblock&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|outnobh
suffix:semicolon
)brace
id|s-&gt;s_op
op_assign
op_amp
id|qnx4_sops
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|QNX4_SUPER_MAGIC
suffix:semicolon
macro_line|#ifndef CONFIG_QNX4FS_RW
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
multiline_comment|/* Yup, read-only yet */
macro_line|#endif
id|s-&gt;u.qnx4_sb.sb_buf
op_assign
id|bh
suffix:semicolon
id|s-&gt;u.qnx4_sb.sb
op_assign
(paren
r_struct
id|qnx4_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* check before allocating dentries, inodes, .. */
id|errmsg
op_assign
id|qnx4_checkroot
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errmsg
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;qnx4: %s&bslash;n&quot;
comma
id|errmsg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* does root not have inode number QNX4_ROOT_INO ?? */
id|root
op_assign
id|iget
c_func
(paren
id|s
comma
id|QNX4_ROOT_INO
op_star
id|QNX4_INODES_PER_BLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: get inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
op_eq
l_int|NULL
)paren
r_goto
id|outi
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|s
suffix:semicolon
id|outi
suffix:colon
id|iput
c_func
(paren
id|root
)paren
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|outnobh
suffix:colon
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|qnx4_put_super
r_static
r_void
id|qnx4_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|qnx4_read_inode
r_static
r_void
id|qnx4_read_inode
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
id|qnx4_inode_entry
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
id|QNX4DEBUG
c_func
(paren
(paren
l_string|&quot;Reading inode : [%d]&bslash;n&quot;
comma
id|ino
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: bad inode number on dev %s: %d is out of range&bslash;n&quot;
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
suffix:semicolon
)brace
id|block
op_assign
id|ino
op_div
id|QNX4_INODES_PER_BLOCK
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
id|QNX4_BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;qnx4: major problem: unable to read inode from dev &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
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
id|qnx4_inode_entry
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|ino
op_mod
id|QNX4_INODES_PER_BLOCK
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|raw_inode-&gt;di_mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|raw_inode-&gt;di_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|raw_inode-&gt;di_gid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|raw_inode-&gt;di_nlink
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|raw_inode-&gt;di_size
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|raw_inode-&gt;di_mtime
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|raw_inode-&gt;di_atime
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|raw_inode-&gt;di_ctime
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|raw_inode-&gt;di_first_xtnt.xtnt_size
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|QNX4_DIR_ENTRY_SIZE
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|inode-&gt;u.qnx4_i
comma
(paren
r_struct
id|qnx4_inode_info
op_star
)paren
id|raw_inode
comma
id|QNX4_DIR_ENTRY_SIZE
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|qnx4_file_inode_operations
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
id|qnx4_file_inode_operations
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
id|qnx4_dir_inode_operations
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
id|qnx4_symlink_inode_operations
suffix:semicolon
r_else
multiline_comment|/* HUH??? Where is device number? Oh, well... */
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
l_int|0
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|variable|qnx4_fs_type
r_static
r_struct
id|file_system_type
id|qnx4_fs_type
op_assign
(brace
l_string|&quot;qnx4&quot;
comma
id|FS_REQUIRES_DEV
comma
id|qnx4_read_super
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_qnx4_fs
r_int
id|__init
id|init_qnx4_fs
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;QNX4 filesystem v0.2 registered.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|register_filesystem
c_func
(paren
op_amp
id|qnx4_fs_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|init_qnx4_fs
c_func
(paren
)paren
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
id|unregister_filesystem
c_func
(paren
op_amp
id|qnx4_fs_type
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
