multiline_comment|/*&n; *  linux/fs/ext/inode.c&n; *&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *&n; *  from&n; *&n; *  linux/fs/minix/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
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
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|function|ext_put_inode
r_void
id|ext_put_inode
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
id|ext_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ext_free_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ext_put_super
r_void
id|ext_put_super
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
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
id|brelse
(paren
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.ext_sb.s_firstfreeblock
)paren
id|brelse
(paren
id|sb-&gt;u.ext_sb.s_firstfreeblock
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
DECL|variable|ext_sops
r_static
r_struct
id|super_operations
id|ext_sops
op_assign
(brace
id|ext_read_inode
comma
l_int|NULL
comma
id|ext_write_inode
comma
id|ext_put_inode
comma
id|ext_put_super
comma
id|ext_write_super
comma
id|ext_statfs
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|ext_read_super
r_struct
id|super_block
op_star
id|ext_read_super
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
id|ext_super_block
op_star
id|es
suffix:semicolon
r_int
id|dev
op_assign
id|s-&gt;s_dev
comma
id|block
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
l_string|&quot;EXT-fs: unable to read superblock&bslash;n&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|es
op_assign
(paren
r_struct
id|ext_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;u.ext_sb.s_ninodes
op_assign
id|es-&gt;s_ninodes
suffix:semicolon
id|s-&gt;u.ext_sb.s_nzones
op_assign
id|es-&gt;s_nzones
suffix:semicolon
id|s-&gt;u.ext_sb.s_firstdatazone
op_assign
id|es-&gt;s_firstdatazone
suffix:semicolon
id|s-&gt;u.ext_sb.s_log_zone_size
op_assign
id|es-&gt;s_log_zone_size
suffix:semicolon
id|s-&gt;u.ext_sb.s_max_size
op_assign
id|es-&gt;s_max_size
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|es-&gt;s_magic
suffix:semicolon
id|s-&gt;u.ext_sb.s_firstfreeblocknumber
op_assign
id|es-&gt;s_firstfreeblock
suffix:semicolon
id|s-&gt;u.ext_sb.s_freeblockscount
op_assign
id|es-&gt;s_freeblockscount
suffix:semicolon
id|s-&gt;u.ext_sb.s_firstfreeinodenumber
op_assign
id|es-&gt;s_firstfreeinode
suffix:semicolon
id|s-&gt;u.ext_sb.s_freeinodescount
op_assign
id|es-&gt;s_freeinodescount
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
id|s-&gt;s_magic
op_ne
id|EXT_SUPER_MAGIC
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
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: Can&squot;t find an extfs filesystem on dev 0x%04x.&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;u.ext_sb.s_firstfreeblocknumber
)paren
id|s-&gt;u.ext_sb.s_firstfreeblock
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;u.ext_sb.s_firstfreeblock
op_assign
id|bread
c_func
(paren
id|dev
comma
id|s-&gt;u.ext_sb.s_firstfreeblocknumber
comma
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ext_read_super: unable to read first free block&bslash;n&quot;
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;u.ext_sb.s_firstfreeinodenumber
)paren
id|s-&gt;u.ext_sb.s_firstfreeinodeblock
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|block
op_assign
l_int|2
op_plus
(paren
id|s-&gt;u.ext_sb.s_firstfreeinodenumber
op_minus
l_int|1
)paren
op_div
id|EXT_INODES_PER_BLOCK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;u.ext_sb.s_firstfreeinodeblock
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
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ext_read_super: unable to read first free inode block&bslash;n&quot;
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|s-&gt;u.ext_sb.s_firstfreeblock
)paren
suffix:semicolon
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
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
id|ext_sops
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
id|EXT_ROOT_INO
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
l_string|&quot;EXT-fs: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|ext_write_super
r_void
id|ext_write_super
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
r_struct
id|ext_super_block
op_star
id|es
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
id|sb-&gt;s_dev
comma
l_int|1
comma
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;ext_write_super: bread failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|es
op_assign
(paren
r_struct
id|ext_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|es-&gt;s_firstfreeblock
op_assign
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
suffix:semicolon
id|es-&gt;s_freeblockscount
op_assign
id|sb-&gt;u.ext_sb.s_freeblockscount
suffix:semicolon
id|es-&gt;s_firstfreeinode
op_assign
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
suffix:semicolon
id|es-&gt;s_freeinodescount
op_assign
id|sb-&gt;u.ext_sb.s_freeinodescount
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
(paren
id|bh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|ext_statfs
r_void
id|ext_statfs
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
id|tmp.f_type
op_assign
id|EXT_SUPER_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
l_int|1024
suffix:semicolon
id|tmp.f_blocks
op_assign
id|sb-&gt;u.ext_sb.s_nzones
op_lshift
id|sb-&gt;u.ext_sb.s_log_zone_size
suffix:semicolon
id|tmp.f_bfree
op_assign
id|ext_count_free_blocks
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
id|sb-&gt;u.ext_sb.s_ninodes
suffix:semicolon
id|tmp.f_ffree
op_assign
id|ext_count_free_inodes
c_func
(paren
id|sb
)paren
suffix:semicolon
id|tmp.f_namelen
op_assign
id|EXT_NAME_LEN
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
op_amp
id|tmp
comma
id|bufsiz
)paren
suffix:semicolon
)brace
DECL|macro|inode_bmap
mdefine_line|#define inode_bmap(inode,nr) ((inode)-&gt;u.ext_i.i_data[(nr)])
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
DECL|function|ext_bmap
r_int
id|ext_bmap
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
l_string|&quot;ext_bmap: block&lt;0&quot;
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
l_int|9
op_plus
l_int|256
op_plus
l_int|256
op_star
l_int|256
op_plus
l_int|256
op_star
l_int|256
op_star
l_int|256
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ext_bmap: block&gt;big&quot;
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
l_int|9
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
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|256
)paren
(brace
id|i
op_assign
id|inode_bmap
c_func
(paren
id|inode
comma
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
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|256
op_star
l_int|256
)paren
(brace
id|i
op_assign
id|inode_bmap
c_func
(paren
id|inode
comma
l_int|10
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
l_int|255
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
l_int|256
op_star
l_int|256
suffix:semicolon
id|i
op_assign
id|inode_bmap
c_func
(paren
id|inode
comma
l_int|11
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
l_int|16
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
(paren
id|block
op_rshift
l_int|8
)paren
op_amp
l_int|255
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
l_int|255
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
id|inode-&gt;u.ext_i.i_data
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
id|ext_new_block
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
id|ext_free_block
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
id|ext_new_block
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
id|ext_free_block
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
DECL|function|ext_getblk
r_struct
id|buffer_head
op_star
id|ext_getblk
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
l_string|&quot;ext_getblk: block&lt;0&bslash;n&quot;
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
l_int|9
op_plus
l_int|256
op_plus
l_int|256
op_star
l_int|256
op_plus
l_int|256
op_star
l_int|256
op_star
l_int|256
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ext_getblk: block&gt;big&bslash;n&quot;
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
l_int|9
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
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|256
)paren
(brace
id|bh
op_assign
id|inode_getblk
c_func
(paren
id|inode
comma
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
comma
id|create
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|256
op_star
l_int|256
)paren
(brace
id|bh
op_assign
id|inode_getblk
c_func
(paren
id|inode
comma
l_int|10
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
l_int|8
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
l_int|255
comma
id|create
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
l_int|256
op_star
l_int|256
suffix:semicolon
id|bh
op_assign
id|inode_getblk
c_func
(paren
id|inode
comma
l_int|11
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
l_int|16
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
(paren
id|block
op_rshift
l_int|8
)paren
op_amp
l_int|255
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
l_int|255
comma
id|create
)paren
suffix:semicolon
)brace
DECL|function|ext_bread
r_struct
id|buffer_head
op_star
id|ext_bread
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
id|ext_getblk
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
DECL|function|ext_read_inode
r_void
id|ext_read_inode
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
id|ext_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|block
suffix:semicolon
id|block
op_assign
l_int|2
op_plus
(paren
id|inode-&gt;i_ino
op_minus
l_int|1
)paren
op_div
id|EXT_INODES_PER_BLOCK
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
id|panic
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
id|raw_inode
op_assign
(paren
(paren
r_struct
id|ext_inode
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|inode-&gt;i_ino
op_minus
l_int|1
)paren
op_mod
id|EXT_INODES_PER_BLOCK
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
l_int|12
suffix:semicolon
id|block
op_increment
)paren
id|inode-&gt;u.ext_i.i_data
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
id|ext_file_inode_operations
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
id|ext_dir_inode_operations
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
id|ext_symlink_inode_operations
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
DECL|function|ext_update_inode
r_static
r_struct
id|buffer_head
op_star
id|ext_update_inode
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
id|ext_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|block
suffix:semicolon
id|block
op_assign
l_int|2
op_plus
(paren
id|inode-&gt;i_ino
op_minus
l_int|1
)paren
op_div
id|EXT_INODES_PER_BLOCK
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
id|panic
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
id|raw_inode
op_assign
(paren
(paren
r_struct
id|ext_inode
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|inode-&gt;i_ino
op_minus
l_int|1
)paren
op_mod
id|EXT_INODES_PER_BLOCK
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
l_int|12
suffix:semicolon
id|block
op_increment
)paren
id|raw_inode-&gt;i_zone
(braket
id|block
)braket
op_assign
id|inode-&gt;u.ext_i.i_data
(braket
id|block
)braket
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|ext_write_inode
r_void
id|ext_write_inode
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
id|ext_update_inode
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
DECL|function|ext_sync_inode
r_int
id|ext_sync_inode
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
id|ext_update_inode
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
l_string|&quot;IO error syncing ext inode [%04x:%08lx]&bslash;n&quot;
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
DECL|variable|ext_fs_type
r_static
r_struct
id|file_system_type
id|ext_fs_type
op_assign
(brace
id|ext_read_super
comma
l_string|&quot;ext&quot;
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
id|ext_fs_type
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
id|unregister_filesystem
c_func
(paren
op_amp
id|ext_fs_type
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
