multiline_comment|/*&n; *  linux/fs/ufs/ufs_file.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_file.c,v 1.1 1996/04/21 14:41:08 davem Exp $&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/*&n; * Return values:&n; *   0:  bmap failed&n; *  nonzero: absolute &quot;block&quot; number&n; */
DECL|function|ufs_bmap
r_int
id|ufs_bmap
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
r_int
r_int
id|fsblkno
comma
id|phys_block
comma
id|lfsblkno
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
multiline_comment|/*&n;&t; * Note that contrary to what the BSD source calls these things,&n;&t; * blkno and lblkno are *frags* (1024), not UFS blocks (8192).&n;&t; * XXX - maybe I&squot;m wrong, and ui_blocks is really 512-blocks...&n;&t; */
multiline_comment|/*&n;&t; * Ok, I think I figured out what is going on.  ui_blocks is the&n;&t; * number of 512-byte blocks that are allocated to the file.  The&n;&t; * elements in ui_db[UFS_NDADDR] are pointers to 1024-byte aligned&n;&t; * 8192 byte objects.  The entire 8192 bytes (16 512-blocks) may&n;&t; * not be allocated to the file in question - use ui_blocks to see&n;&t; * how many of the blocks are allocated.  Also, use ui_size to see&n;&t; * what fraction of the last block is allocated to the file, and&n;&t; * what fraction is unused.  I have not yet seen a file with a&n;&t; * hole in it, but I&squot;d guess that a hole must be at least 8192&n;&t; * bytes of zeros, and it&squot;s represented by a zero in ui_db[X].&n;&t; *&n;&t; * Yes, this means that there is more than one way to name a given&n;&t; * 512-byte block on the disk. Because of the 1024-byte alignment&n;&t; * of 8192-byte filesystem blocks, a given 512-byte disk block&n;&t; * could be referred to in eight different ways.&n;&t; */
multiline_comment|/*&n;&t; * block is the logical 1024-block in the file&n;&t; * lfsblkno is the logical 8192-block in the file&n;&t; * fsblkno is the physical 8192-block&n;&t; * phys_block is the 1024-block&n;&t; */
id|lfsblkno
op_assign
id|block
op_rshift
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
id|UFS_NDADDR
)paren
(brace
multiline_comment|/* It&squot;s a direct block */
id|fsblkno
op_assign
id|inode-&gt;u.ufs_i.ui_db
(braket
id|lfsblkno
)braket
suffix:semicolon
multiline_comment|/* XXX */
macro_line|#if 0
id|phys_block
op_assign
id|ufs_cgdmin
c_func
(paren
id|inode-&gt;i_sb
comma
id|ufs_ino2cg
c_func
(paren
id|inode
)paren
)paren
op_plus
id|blkno
op_mod
(paren
id|inode-&gt;i_sb-&gt;u.ufs_sb.s_fpg
)paren
suffix:semicolon
macro_line|#endif
id|phys_block
op_assign
id|fsblkno
op_plus
(paren
(paren
id|block
op_amp
l_int|0x7
)paren
op_lshift
l_int|10
)paren
suffix:semicolon
multiline_comment|/* XXX */
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_bmap: mapped ino %lu  logical %u to %lu (phys %lu)&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|block
comma
id|fsblkno
comma
id|phys_block
)paren
suffix:semicolon
)brace
r_return
id|phys_block
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Need to use indirect blocks */
multiline_comment|/* XXX - bmap through indirect blocks not implemented */
id|block
op_sub_assign
id|UFS_NDADDR
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
(paren
id|inode-&gt;i_sb-&gt;s_blocksize
op_div
r_sizeof
(paren
id|__u32
)paren
)paren
)paren
(brace
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;u.ufs_i.ui_ib
(braket
l_int|0
)braket
comma
id|BLOCK_SIZE
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
id|printk
c_func
(paren
l_string|&quot;ufs_bmap: can&squot;t map block %lu, ino %lu&bslash;n&quot;
comma
id|block
op_plus
id|UFS_NDADDR
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|phys_block
op_assign
(paren
(paren
id|__u32
op_star
)paren
id|bh-&gt;b_data
)paren
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
id|printk
c_func
(paren
l_string|&quot;ufs_bmap: imap ino %lu block %lu phys %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|block
op_plus
id|UFS_NDADDR
comma
id|phys_block
)paren
suffix:semicolon
r_return
id|phys_block
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_bmap: ino %lu: indirect blocks not implemented&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ufs_file_operations
r_static
r_struct
id|file_operations
id|ufs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
op_amp
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
multiline_comment|/* select */
l_int|NULL
comma
multiline_comment|/* ioctl */
op_amp
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
op_amp
id|file_fsync
comma
multiline_comment|/* fsync */
multiline_comment|/* XXX - is this ok? */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|ufs_file_inode_operations
r_struct
id|inode_operations
id|ufs_file_inode_operations
op_assign
(brace
op_amp
id|ufs_file_operations
comma
multiline_comment|/* default directory file operations */
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
op_amp
id|generic_readpage
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
op_amp
id|ufs_bmap
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
)brace
suffix:semicolon
multiline_comment|/*&n; * Local Variables: ***&n; * c-indent-level: 8 ***&n; * c-continued-statement-offset: 8 ***&n; * c-brace-offset: -8 ***&n; * c-argdecl-indent: 0 ***&n; * c-label-offset: -8 ***&n; * End: ***&n; */
eof
