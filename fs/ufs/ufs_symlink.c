multiline_comment|/*&n; *  linux/fs/ufs/ufs_symlink.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * Ported to 2.1.62 by Francois-Rene Rideau &lt;rideau@ens.fr&gt; 19971109&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
id|ufs_bmap
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
DECL|function|ufs_readlink
id|ufs_readlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_int
r_int
r_int
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
(paren
id|UFS_DEBUG
op_or
id|UFS_DEBUG_LINKS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_readlink: called on ino %lu dev %u/%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|MINOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buflen
OG
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
)paren
id|buflen
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_blocks
)paren
(brace
multiline_comment|/* XXX - error checking */
id|block
op_assign
id|ufs_bmap
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
(paren
id|UFS_DEBUG
op_or
id|UFS_DEBUG_LINKS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_readlink: bmap got %lu for ino %lu&bslash;n&quot;
comma
id|block
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
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
l_string|&quot;ufs_readlink: can&squot;t read block 0 for ino %lu on dev %u/%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|MINOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|link
op_assign
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* no need to bswap */
)brace
r_else
(brace
id|link
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|inode-&gt;u.ufs_i.i_data
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|buflen
op_logical_and
(paren
id|c
op_assign
id|link
(braket
id|i
)braket
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
id|put_user
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
)brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX - blatantly stolen from minix fs&n; */
r_static
r_struct
id|dentry
op_star
DECL|function|ufs_follow_link
id|ufs_follow_link
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|base
)paren
(brace
r_int
r_int
r_int
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
(paren
id|UFS_DEBUG
op_or
id|UFS_DEBUG_LINKS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_follow_link: called on ino %lu dev %u/%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|MINOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_blocks
)paren
(brace
multiline_comment|/* read the link from disk */
multiline_comment|/* XXX - error checking */
id|block
op_assign
id|ufs_bmap
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
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
l_string|&quot;ufs_follow_link: can&squot;t read block 0 for ino %lu on dev %u/%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|MINOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
suffix:semicolon
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
id|link
op_assign
id|bh-&gt;b_data
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* fast symlink */
id|link
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|inode-&gt;u.ufs_i.i_data
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|base
op_assign
id|lookup_dentry
c_func
(paren
id|link
comma
id|base
comma
l_int|1
)paren
suffix:semicolon
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
DECL|variable|ufs_symlink_operations
r_static
r_struct
id|file_operations
id|ufs_symlink_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
l_int|NULL
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
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
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
DECL|variable|ufs_symlink_inode_operations
r_struct
id|inode_operations
id|ufs_symlink_inode_operations
op_assign
(brace
op_amp
id|ufs_symlink_operations
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
op_amp
id|ufs_readlink
comma
multiline_comment|/* readlink */
op_amp
id|ufs_follow_link
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
)brace
suffix:semicolon
eof
