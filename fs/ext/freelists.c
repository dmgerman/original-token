multiline_comment|/*&n; *  linux/fs/ext/freelists.c&n; *&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *&n; */
multiline_comment|/* freelists.c contains the code that handles the inode and block free lists */
multiline_comment|/*&n;&n;   The free blocks are managed by a linked list. The super block contains the&n;   number of the first free block. This block contains 254 numbers of other&n;   free blocks and the number of the next block in the list.&n;&n;   When an ext fs is mounted, the number of the first free block is stored&n;   in s-&gt;u.ext_sb.s_firstfreeblocknumber and the block header is stored in&n;   s-&gt;u.ext_sb.s_firstfreeblock. u.ext_sb.s_freeblockscount contains the count&n;   of free blocks.&n;&n;   The free inodes are also managed by a linked list in a similar way. The&n;   super block contains the number of the first free inode. This inode contains&n;   14 numbers of other free inodes and the number of the next inode in the list.&n;   &n;   The number of the first free inode is stored in&n;   s-&gt;u.ext_sb.s_firstfreeinodenumber and the header of the block containing&n;   the inode is stored in s-&gt;u.ext_sb.s_firstfreeinodeblock.&n;   u.ext_sb.s_freeinodescount contains the count of free inodes.&n;&n;*/
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
DECL|macro|clear_block
mdefine_line|#define clear_block(addr) &bslash;&n;__asm__(&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;        &quot;rep&bslash;n&bslash;t&quot; &bslash;&n;        &quot;stosl&quot; &bslash;&n;        ::&quot;a&quot; (0),&quot;c&quot; (BLOCK_SIZE/4),&quot;D&quot; ((long) (addr)):&quot;cx&quot;,&quot;di&quot;)
DECL|function|ext_free_block
r_void
id|ext_free_block
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
r_struct
id|ext_free_block
op_star
id|efb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
id|panic
c_func
(paren
l_string|&quot;trying to free block on nonexistent device&quot;
)paren
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
id|sb-&gt;u.ext_sb.s_firstdatazone
op_logical_or
id|block
op_ge
id|sb-&gt;u.ext_sb.s_nzones
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
id|sb-&gt;s_blocksize
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
r_if
c_cond
(paren
id|sb-&gt;u.ext_sb.s_firstfreeblock
)paren
id|efb
op_assign
(paren
r_struct
id|ext_free_block
op_star
)paren
id|sb-&gt;u.ext_sb.s_firstfreeblock-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeblock
op_logical_or
id|efb-&gt;count
op_eq
l_int|254
)paren
(brace
macro_line|#ifdef EXTFS_DEBUG
id|printk
c_func
(paren
l_string|&quot;ext_free_block: block full, skipping to %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;u.ext_sb.s_firstfreeblock
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
id|panic
(paren
l_string|&quot;ext_free_block: unable to read block to free&bslash;n&quot;
)paren
suffix:semicolon
id|efb
op_assign
(paren
r_struct
id|ext_free_block
op_star
)paren
id|sb-&gt;u.ext_sb.s_firstfreeblock-&gt;b_data
suffix:semicolon
id|efb-&gt;next
op_assign
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
suffix:semicolon
id|efb-&gt;count
op_assign
l_int|0
suffix:semicolon
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
op_assign
id|block
suffix:semicolon
)brace
r_else
(brace
id|efb-&gt;free
(braket
id|efb-&gt;count
op_increment
)braket
op_assign
id|block
suffix:semicolon
)brace
id|sb-&gt;u.ext_sb.s_freeblockscount
op_increment
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|sb-&gt;u.ext_sb.s_firstfreeblock-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|ext_new_block
r_int
id|ext_new_block
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
r_struct
id|ext_free_block
op_star
id|efb
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
id|panic
c_func
(paren
l_string|&quot;trying to get new block from nonexistant device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeblock
)paren
r_return
l_int|0
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|efb
op_assign
(paren
r_struct
id|ext_free_block
op_star
)paren
id|sb-&gt;u.ext_sb.s_firstfreeblock-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|efb-&gt;count
)paren
(brace
id|j
op_assign
id|efb-&gt;free
(braket
op_decrement
id|efb-&gt;count
)braket
suffix:semicolon
id|sb-&gt;u.ext_sb.s_firstfreeblock-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef EXTFS_DEBUG
id|printk
c_func
(paren
l_string|&quot;ext_new_block: block empty, skipping to %d&bslash;n&quot;
comma
id|efb-&gt;next
)paren
suffix:semicolon
macro_line|#endif
id|j
op_assign
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
suffix:semicolon
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
op_assign
id|efb-&gt;next
suffix:semicolon
id|brelse
(paren
id|sb-&gt;u.ext_sb.s_firstfreeblock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
)paren
(brace
id|sb-&gt;u.ext_sb.s_firstfreeblock
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;u.ext_sb.s_firstfreeblock
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|sb-&gt;u.ext_sb.s_firstfreeblocknumber
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
id|panic
(paren
l_string|&quot;ext_new_block: unable to read next free block&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|j
template_param
id|sb-&gt;u.ext_sb.s_nzones
)paren
(brace
id|printk
(paren
l_string|&quot;ext_new_block: blk = %d&bslash;n&quot;
comma
id|j
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;allocating block not in data zone&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|sb-&gt;u.ext_sb.s_freeblockscount
op_decrement
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
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
id|j
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;new_block: cannot get block&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_count
op_ne
l_int|1
)paren
id|panic
c_func
(paren
l_string|&quot;new block: count is != 1&quot;
)paren
suffix:semicolon
id|clear_block
c_func
(paren
id|bh-&gt;b_data
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
macro_line|#ifdef EXTFS_DEBUG
id|printk
c_func
(paren
l_string|&quot;ext_new_block: allocating block %d&bslash;n&quot;
comma
id|j
)paren
suffix:semicolon
macro_line|#endif
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|j
suffix:semicolon
)brace
DECL|function|ext_count_free_blocks
r_int
r_int
id|ext_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
macro_line|#ifdef EXTFS_DEBUG
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ext_free_block
op_star
id|efb
suffix:semicolon
r_int
r_int
id|count
comma
id|block
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeblock
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|efb
op_assign
(paren
r_struct
id|ext_free_block
op_star
)paren
id|sb-&gt;u.ext_sb.s_firstfreeblock-&gt;b_data
suffix:semicolon
id|count
op_assign
id|efb-&gt;count
op_plus
l_int|1
suffix:semicolon
id|block
op_assign
id|efb-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|block
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
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;ext_count_free: error while reading free blocks list&bslash;n&quot;
)paren
suffix:semicolon
id|block
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|efb
op_assign
(paren
r_struct
id|ext_free_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|count
op_add_assign
id|efb-&gt;count
op_plus
l_int|1
suffix:semicolon
id|block
op_assign
id|efb-&gt;next
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;ext_count_free_blocks: stored = %d, computed = %d&bslash;n&quot;
comma
id|sb-&gt;u.ext_sb.s_freeblockscount
comma
id|count
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
macro_line|#else
r_return
id|sb-&gt;u.ext_sb.s_freeblockscount
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ext_free_inode
r_void
id|ext_free_inode
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
id|ext_free_inode
op_star
id|efi
suffix:semicolon
r_int
r_int
id|block
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
id|memset
c_func
(paren
id|inode
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|inode
)paren
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
id|lock_super
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
template_param
id|inode-&gt;i_sb-&gt;u.ext_sb.s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;free_inode: inode 0 or nonexistent inode&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
id|efi
op_assign
(paren
(paren
r_struct
id|ext_free_inode
op_star
)paren
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock-&gt;b_data
)paren
op_plus
(paren
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodenumber
op_minus
l_int|1
)paren
op_mod
id|EXT_INODES_PER_BLOCK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock
op_logical_or
id|efi-&gt;count
op_eq
l_int|14
)paren
(brace
macro_line|#ifdef EXTFS_DEBUG
id|printk
c_func
(paren
l_string|&quot;ext_free_inode: inode full, skipping to %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
id|brelse
(paren
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
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
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;ext_free_inode: unable to read inode block&bslash;n&quot;
)paren
suffix:semicolon
id|efi
op_assign
(paren
(paren
r_struct
id|ext_free_inode
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
id|efi-&gt;next
op_assign
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodenumber
suffix:semicolon
id|efi-&gt;count
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodenumber
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
id|efi-&gt;free
(braket
id|efi-&gt;count
op_increment
)braket
op_assign
id|inode-&gt;i_ino
suffix:semicolon
)brace
id|inode-&gt;i_sb-&gt;u.ext_sb.s_freeinodescount
op_increment
suffix:semicolon
id|inode-&gt;i_sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_sb-&gt;u.ext_sb.s_firstfreeinodeblock-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|unlock_super
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|memset
c_func
(paren
id|inode
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|function|ext_new_inode
r_struct
id|inode
op_star
id|ext_new_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|ext_free_inode
op_star
id|efi
suffix:semicolon
r_int
r_int
id|block
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
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
id|sb-&gt;s_flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
r_return
l_int|0
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|efi
op_assign
(paren
(paren
r_struct
id|ext_free_inode
op_star
)paren
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock-&gt;b_data
)paren
op_plus
(paren
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
op_minus
l_int|1
)paren
op_mod
id|EXT_INODES_PER_BLOCK
suffix:semicolon
r_if
c_cond
(paren
id|efi-&gt;count
)paren
(brace
id|j
op_assign
id|efi-&gt;free
(braket
op_decrement
id|efi-&gt;count
)braket
suffix:semicolon
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef EXTFS_DEBUG
id|printk
c_func
(paren
l_string|&quot;ext_free_inode: inode empty, skipping to %d&bslash;n&quot;
comma
id|efi-&gt;next
)paren
suffix:semicolon
macro_line|#endif
id|j
op_assign
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
suffix:semicolon
r_if
c_cond
(paren
id|efi-&gt;next
OG
id|sb-&gt;u.ext_sb.s_ninodes
)paren
(brace
id|printk
(paren
l_string|&quot;efi-&gt;next = %d&bslash;n&quot;
comma
id|efi-&gt;next
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;ext_new_inode: bad inode number in free list&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
op_assign
id|efi-&gt;next
suffix:semicolon
id|block
op_assign
l_int|2
op_plus
(paren
(paren
(paren
r_int
r_int
)paren
id|efi-&gt;next
)paren
op_minus
l_int|1
)paren
op_div
id|EXT_INODES_PER_BLOCK
suffix:semicolon
id|brelse
(paren
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
)paren
(brace
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
id|panic
(paren
l_string|&quot;ext_new_inode: unable to read next free inode block&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|sb-&gt;u.ext_sb.s_freeinodescount
op_decrement
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
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
id|current-&gt;egid
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
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
macro_line|#ifdef EXTFS_DEBUG
id|printk
c_func
(paren
l_string|&quot;ext_new_inode : allocating inode %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
macro_line|#endif
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|ext_count_free_inodes
r_int
r_int
id|ext_count_free_inodes
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
macro_line|#ifdef EXTFS_DEBUG
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ext_free_inode
op_star
id|efi
suffix:semicolon
r_int
r_int
id|count
comma
id|block
comma
id|ino
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|efi
op_assign
(paren
(paren
r_struct
id|ext_free_inode
op_star
)paren
id|sb-&gt;u.ext_sb.s_firstfreeinodeblock-&gt;b_data
)paren
op_plus
(paren
(paren
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
op_minus
l_int|1
)paren
op_mod
id|EXT_INODES_PER_BLOCK
)paren
suffix:semicolon
id|count
op_assign
id|efi-&gt;count
op_plus
l_int|1
suffix:semicolon
id|ino
op_assign
id|efi-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|ino
)paren
(brace
r_if
c_cond
(paren
id|ino
template_param
id|sb-&gt;u.ext_sb.s_ninodes
)paren
(brace
id|printk
(paren
l_string|&quot;u.ext_sb.s_firstfreeinodenumber = %d, ino = %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|sb-&gt;u.ext_sb.s_firstfreeinodenumber
comma
id|ino
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;ext_count_fre_inodes: bad inode number in free list&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|block
op_assign
l_int|2
op_plus
(paren
(paren
id|ino
op_minus
l_int|1
)paren
op_div
id|EXT_INODES_PER_BLOCK
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
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;ext_count_free_inodes: error while reading free inodes list&bslash;n&quot;
)paren
suffix:semicolon
id|block
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|efi
op_assign
(paren
(paren
r_struct
id|ext_free_inode
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
op_mod
id|EXT_INODES_PER_BLOCK
)paren
suffix:semicolon
id|count
op_add_assign
id|efi-&gt;count
op_plus
l_int|1
suffix:semicolon
id|ino
op_assign
id|efi-&gt;next
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;ext_count_free_inodes: stored = %d, computed = %d&bslash;n&quot;
comma
id|sb-&gt;u.ext_sb.s_freeinodescount
comma
id|count
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
macro_line|#else
r_return
id|sb-&gt;u.ext_sb.s_freeinodescount
suffix:semicolon
macro_line|#endif
)brace
eof
