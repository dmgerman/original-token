multiline_comment|/*&n; *  linux/fs/ufs/ufs_inode.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_inode.c,v 1.3 1996/04/25 09:12:05 davem Exp $&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
r_extern
r_struct
id|inode_operations
id|ufs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ufs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ufs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_dir_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_symlink_operations
suffix:semicolon
DECL|function|ufs_print_inode
r_void
id|ufs_print_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ino %lu  mode 0%6.6o  lk %d  uid %d  gid %d  sz %lu  blks %lu  cnt %u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_mode
comma
id|inode-&gt;i_nlink
comma
id|inode-&gt;i_uid
comma
id|inode-&gt;i_gid
comma
id|inode-&gt;i_size
comma
id|inode-&gt;i_blocks
comma
id|inode-&gt;i_count
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  db &lt;0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x&gt;&bslash;n&quot;
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|0
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|1
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|2
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|3
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|4
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|5
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|6
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|7
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|8
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|9
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|10
)braket
comma
id|inode-&gt;u.ufs_i.ui_db
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  gen 0x%8.8x ib &lt;0x%x 0x%x 0x%x&gt;&bslash;n&quot;
comma
id|inode-&gt;u.ufs_i.ui_gen
comma
id|inode-&gt;u.ufs_i.ui_ib
(braket
l_int|0
)braket
comma
id|inode-&gt;u.ufs_i.ui_ib
(braket
l_int|1
)braket
comma
id|inode-&gt;u.ufs_i.ui_ib
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX - ufs_read_inode is a mess */
DECL|function|ufs_read_inode
r_void
id|ufs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|ufs_inode
op_star
id|ufsip
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|ufs_ino_ok
c_func
(paren
id|inode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: bad inum %lu&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: ino %lu  cg %u  cgino %u  ipg %u  inopb %u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|ufs_ino2cg
c_func
(paren
id|inode
)paren
comma
(paren
id|inode-&gt;i_ino
op_mod
id|sb-&gt;u.ufs_sb.s_inopb
)paren
comma
id|sb-&gt;u.ufs_sb.s_ipg
comma
id|sb-&gt;u.ufs_sb.s_inopb
)paren
suffix:semicolon
macro_line|#endif
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|ufs_cgimin
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
(paren
id|inode-&gt;i_ino
op_mod
id|sb-&gt;u.ufs_sb.s_ipg
)paren
op_div
(paren
id|sb-&gt;u.ufs_sb.s_inopb
op_div
id|sb-&gt;u.ufs_sb.s_fsfrag
)paren
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
l_string|&quot;ufs_read_inode: can&squot;t read inode %lu from dev %d/%d&quot;
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
suffix:semicolon
)brace
id|ufsip
op_assign
(paren
r_struct
id|ufs_inode
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|ufsip
op_add_assign
(paren
id|inode-&gt;i_ino
op_mod
(paren
id|sb-&gt;u.ufs_sb.s_inopb
op_div
id|sb-&gt;u.ufs_sb.s_fsfrag
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Copy data to the in-core inode.&n;&t; */
id|inode-&gt;i_mode
op_assign
id|ufsip-&gt;ui_mode
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|ufsip-&gt;ui_nlink
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
(brace
multiline_comment|/* XXX */
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: zero nlink ino %lu  dev %u/%u&bslash;n&quot;
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
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: fishy ino %lu pblk %lu dev %u/%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|ufs_cgimin
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
(paren
id|inode-&gt;i_ino
op_mod
id|sb-&gt;u.ufs_sb.s_ipg
)paren
op_div
id|sb-&gt;u.ufs_sb.s_inopb
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
multiline_comment|/* XXX - debugging */
r_if
c_cond
(paren
id|ufsip-&gt;ui_gen
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: zero gen ino %lu pblk %lu dev %u/%u&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|ufs_cgimin
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
(paren
id|inode-&gt;i_ino
op_mod
id|sb-&gt;u.ufs_sb.s_ipg
)paren
op_div
id|sb-&gt;u.ufs_sb.s_inopb
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
multiline_comment|/*&n;&t; * Since Linux currently only has 16-bit uid_t and gid_t, we can&squot;t&n;&t; * really support EFTs.  For the moment, we use 0 as the uid and gid&n;&t; * if an inode has a uid or gid that won&squot;t fit in 16 bits.  This way&n;&t; * random users can&squot;t get at these files, since they get dynamically&n;&t; * &quot;chown()ed&quot; to root.&n;&t; */
r_if
c_cond
(paren
id|ufsip-&gt;ui_suid
op_eq
id|UFS_USEEFT
)paren
(brace
multiline_comment|/* EFT */
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: EFT uid %u ino %lu dev %u/%u, using %u&bslash;n&quot;
comma
id|ufsip-&gt;ui_uid
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
comma
id|inode-&gt;i_uid
)paren
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_uid
op_assign
id|ufsip-&gt;ui_suid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ufsip-&gt;ui_suid
op_eq
id|UFS_USEEFT
)paren
(brace
multiline_comment|/* EFT */
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: EFT gid %u ino %lu dev %u/%u, using %u&bslash;n&quot;
comma
id|ufsip-&gt;ui_gid
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
comma
id|inode-&gt;i_gid
)paren
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_gid
op_assign
id|ufsip-&gt;ui_sgid
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Linux i_size is 32 bits, so some files on a UFS filesystem may not&n;&t; * be readable.  I let people access the first 32 bits worth of them.&n;&t; * for the rw code, we may want to mark these inodes as read-only.&n;&t; * XXX - bug Linus to make i_size a __u64 instead of a __u32.&n;&t; */
id|inode-&gt;u.ufs_i.ui_size
op_assign
(paren
(paren
id|__u64
)paren
(paren
id|ufsip-&gt;ui_size.val
(braket
l_int|0
)braket
)paren
op_lshift
l_int|32
)paren
op_or
(paren
id|__u64
)paren
(paren
id|ufsip-&gt;ui_size.val
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|ufsip-&gt;ui_size.val
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* XXX - endianity */
r_if
c_cond
(paren
id|ufsip-&gt;ui_size.val
(braket
l_int|0
)braket
op_ne
l_int|0
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0xffffffff
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: file too big ino %lu dev %u/%u, faking size&bslash;n&quot;
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
multiline_comment|/*&n;&t; * Linux doesn&squot;t keep tv_usec around in the kernel, so we discard it.&n;&t; * XXX - I&squot;m not sure what I should do about writing things.  I may&n;&t; * want to keep this data, but for the moment I think I&squot;ll just write&n;&t; * zeros for these fields when writing out inodes.&n;&t; */
id|inode-&gt;i_atime
op_assign
id|ufsip-&gt;ui_atime.tv_sec
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|ufsip-&gt;ui_mtime.tv_sec
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|ufsip-&gt;ui_ctime.tv_sec
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|sb-&gt;u.ufs_sb.s_fsize
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|ufsip-&gt;ui_blocks
suffix:semicolon
id|inode-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
multiline_comment|/* see linux/kernel/sched.c */
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_file_inode_operations
suffix:semicolon
)brace
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
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_dir_inode_operations
suffix:semicolon
)brace
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
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_symlink_inode_operations
suffix:semicolon
)brace
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
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|chrdev_inode_operations
suffix:semicolon
)brace
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
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|blkdev_inode_operations
suffix:semicolon
)brace
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
id|init_fifo
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_read_inode: unknown file type 0%o ino %lu dev %d/%d&bslash;n&quot;
comma
id|inode-&gt;i_mode
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
multiline_comment|/* XXX - debugging */
id|ufs_print_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_file_inode_operations
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * ufs_read_super makes sure that UFS_NDADDR and UFS_NINDIR are sane.&n;&t; */
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_int
id|i
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
id|UFS_NDADDR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|inode-&gt;u.ufs_i.ui_db
(braket
id|i
)braket
op_assign
id|ufsip-&gt;ui_db
(braket
id|i
)braket
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
id|UFS_NINDIR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|inode-&gt;u.ufs_i.ui_ib
(braket
id|i
)braket
op_assign
id|ufsip-&gt;ui_ib
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
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
(brace
multiline_comment|/* XXX - should be ui_db[1] on little endian ufs filesystems */
id|inode-&gt;i_rdev
op_assign
id|to_kdev_t
c_func
(paren
id|ufsip-&gt;ui_db
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX - implement fast and slow symlinks */
id|inode-&gt;u.ufs_i.ui_flags
op_assign
id|ufsip-&gt;ui_flags
suffix:semicolon
id|inode-&gt;u.ufs_i.ui_gen
op_assign
id|ufsip-&gt;ui_gen
suffix:semicolon
multiline_comment|/* XXX - is this i_version? */
id|inode-&gt;u.ufs_i.ui_shadow
op_assign
id|ufsip-&gt;ui_shadow
suffix:semicolon
multiline_comment|/* XXX */
id|inode-&gt;u.ufs_i.ui_uid
op_assign
id|ufsip-&gt;ui_uid
suffix:semicolon
id|inode-&gt;u.ufs_i.ui_gid
op_assign
id|ufsip-&gt;ui_gid
suffix:semicolon
id|inode-&gt;u.ufs_i.ui_oeftflag
op_assign
id|ufsip-&gt;ui_oeftflag
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
id|inode-&gt;i_sb-&gt;u.ufs_sb.s_flags
op_amp
(paren
id|UFS_DEBUG
op_or
id|UFS_DEBUG_INODE
)paren
)paren
(brace
id|ufs_print_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|ufs_put_inode
r_void
id|ufs_put_inode
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
id|printk
c_func
(paren
l_string|&quot;ufs_put_inode: nlink == 0 for inum %lu on dev %d/%d&bslash;n&quot;
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
id|ufs_print_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;ufs_put_inode: fs is read only, and nlink == 0&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX - this code goes here eventually&n;&t;inode-&gt;i_size = 0;&n;&t;if (inode-&gt;i_blocks)&n;&t;        ufs_truncate(inode);&n;&t;ufs_free_inode(inode);&n;&t;*/
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Local Variables: ***&n; * c-indent-level: 8 ***&n; * c-continued-statement-offset: 8 ***&n; * c-brace-offset: -8 ***&n; * c-argdecl-indent: 0 ***&n; * c-label-offset: -8 ***&n; * End: ***&n; */
eof