multiline_comment|/*&n; * file.c&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from work (c) 1995,1996 Christian Vogelgsang.&n; */
macro_line|#include &lt;linux/efs_fs.h&gt;
DECL|function|efs_get_block
r_int
id|efs_get_block
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
r_int
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
r_int
id|phys
suffix:semicolon
r_if
c_cond
(paren
id|create
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|iblock
op_ge
id|inode-&gt;i_blocks
)paren
(brace
macro_line|#ifdef DEBUG
multiline_comment|/*&n;&t;&t; * i have no idea why this happens as often as it does&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: bmap(): block %d &gt;= %ld (filesize %ld)&bslash;n&quot;
comma
id|block
comma
id|inode-&gt;i_blocks
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|phys
op_assign
id|efs_map_block
c_func
(paren
id|inode
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys
)paren
(brace
id|bh_result-&gt;b_dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|bh_result-&gt;b_blocknr
op_assign
id|phys
suffix:semicolon
id|bh_result-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|efs_bmap
r_int
id|efs_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|efs_block_t
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
id|KERN_WARNING
l_string|&quot;EFS: bmap(): block &lt; 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* are we about to read past the end of a file ? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
OL
id|inode-&gt;i_blocks
)paren
)paren
(brace
macro_line|#ifdef DEBUG
multiline_comment|/*&n;&t;&t; * i have no idea why this happens as often as it does&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: bmap(): block %d &gt;= %ld (filesize %ld)&bslash;n&quot;
comma
id|block
comma
id|inode-&gt;i_blocks
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|efs_map_block
c_func
(paren
id|inode
comma
id|block
)paren
suffix:semicolon
)brace
DECL|variable|efs_file_operations
r_static
r_struct
id|file_operations
id|efs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
id|generic_file_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
)brace
suffix:semicolon
DECL|variable|efs_file_inode_operations
r_struct
id|inode_operations
id|efs_file_inode_operations
op_assign
(brace
op_amp
id|efs_file_operations
comma
multiline_comment|/* default file operations */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
id|efs_get_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
