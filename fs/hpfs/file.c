multiline_comment|/*&n; *  linux/fs/hpfs/file.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  file VFS functions&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;hpfs_fn.h&quot;
DECL|function|hpfs_open
r_int
id|hpfs_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
id|hpfs_lock_inode
c_func
(paren
id|i
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/* make sure nobody is deleting the file */
r_if
c_cond
(paren
op_logical_neg
id|i-&gt;i_nlink
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_file_release
r_int
id|hpfs_file_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|hpfs_write_if_changed
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_file_fsync
r_int
id|hpfs_file_fsync
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
multiline_comment|/*return file_fsync(file, dentry);*/
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t fsync :-) */
)brace
multiline_comment|/*&n; * generic_file_read often calls bmap with non-existing sector,&n; * so we must ignore such errors.&n; */
DECL|function|hpfs_bmap
id|secno
id|hpfs_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|file_secno
)paren
(brace
r_int
id|n
comma
id|disk_secno
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|inode-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
op_le
id|file_secno
)paren
r_return
l_int|0
suffix:semicolon
id|n
op_assign
id|file_secno
op_minus
id|inode-&gt;i_hpfs_file_sec
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|inode-&gt;i_hpfs_n_secs
)paren
r_return
id|inode-&gt;i_hpfs_disk_sec
op_plus
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|disk_secno
op_assign
id|hpfs_bplus_lookup
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode
comma
op_amp
id|fnode-&gt;btree
comma
id|file_secno
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk_secno
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
id|hpfs_chk_sectors
c_func
(paren
id|inode-&gt;i_sb
comma
id|disk_secno
comma
l_int|1
comma
l_string|&quot;bmap&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|disk_secno
suffix:semicolon
)brace
DECL|function|hpfs_truncate
r_void
id|hpfs_truncate
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|i
)paren
)paren
r_return
multiline_comment|/*-EPERM*/
suffix:semicolon
id|i-&gt;i_hpfs_n_secs
op_assign
l_int|0
suffix:semicolon
id|i-&gt;i_blocks
op_assign
l_int|1
op_plus
(paren
(paren
id|i-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
id|hpfs_truncate_btree
c_func
(paren
id|i-&gt;i_sb
comma
id|i-&gt;i_ino
comma
l_int|1
comma
(paren
(paren
id|i-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
)paren
suffix:semicolon
id|hpfs_write_inode
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|function|hpfs_get_block
r_int
id|hpfs_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
id|secno
id|s
suffix:semicolon
r_if
c_cond
(paren
id|iblock
OL
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
(brace
id|s
op_assign
id|hpfs_bmap
c_func
(paren
id|inode
comma
id|iblock
)paren
suffix:semicolon
id|bh_result-&gt;b_dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|bh_result-&gt;b_blocknr
op_assign
id|s
suffix:semicolon
id|bh_result-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_Mapped
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
id|create
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iblock
OG
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
(brace
singleline_comment|//hpfs_error(inode-&gt;i_sb, &quot;hpfs_get_block beyond file end (requested %08x, inode size %08x&quot;, (int)iblock, (int)inode-&gt;i_blocks - 1);
id|printk
c_func
(paren
l_string|&quot;HPFS: could not write beyond file end. This is known bug.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EFSERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|s
op_assign
id|hpfs_add_sector_to_btree
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
l_int|1
comma
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|hpfs_truncate_btree
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
l_int|1
comma
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_increment
suffix:semicolon
id|bh_result-&gt;b_dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|bh_result-&gt;b_blocknr
op_assign
id|s
suffix:semicolon
id|bh_result-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
op_or
(paren
l_int|1UL
op_lshift
id|BH_New
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_write_partial_page
r_static
r_int
id|hpfs_write_partial_page
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|bytes
comma
r_const
r_char
op_star
id|buf
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|page
op_star
id|new_page
suffix:semicolon
r_int
r_int
id|pgpos
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pgpos
op_assign
(paren
(paren
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
op_star
l_int|512
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_while
c_loop
(paren
id|pgpos
OL
id|page-&gt;index
)paren
(brace
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|new_page
op_assign
id|grab_cache_page
c_func
(paren
op_amp
id|inode-&gt;i_data
comma
id|pgpos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_page
)paren
r_goto
id|out
suffix:semicolon
id|status
op_assign
id|block_write_cont_page
c_func
(paren
id|file
comma
id|new_page
comma
id|PAGE_SIZE
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|new_page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|new_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|pgpos
op_assign
(paren
(paren
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
op_star
l_int|512
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
)brace
id|status
op_assign
id|block_write_cont_page
c_func
(paren
id|file
comma
id|page
comma
id|offset
comma
id|bytes
comma
id|buf
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
DECL|function|hpfs_file_write
id|ssize_t
id|hpfs_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|ssize_t
id|retval
suffix:semicolon
id|retval
op_assign
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
comma
id|hpfs_write_partial_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_hpfs_dirty
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
