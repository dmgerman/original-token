multiline_comment|/*&n; *  linux/fs/hpfs/namei.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  adding &amp; removing files &amp; directories&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;hpfs_fn.h&quot;
DECL|function|hpfs_mkdir
r_int
id|hpfs_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|quad_buffer_head
id|qbh0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|de
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
r_struct
id|dnode
op_star
id|dnode
suffix:semicolon
r_struct
id|inode
op_star
id|result
suffix:semicolon
id|fnode_secno
id|fno
suffix:semicolon
id|dnode_secno
id|dno
suffix:semicolon
r_int
id|r
suffix:semicolon
r_struct
id|hpfs_dirent
id|dee
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hpfs_chk_name
c_func
(paren
(paren
r_char
op_star
)paren
id|name
comma
op_amp
id|len
)paren
)paren
)paren
r_return
id|err
op_eq
op_minus
id|ENOENT
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_alloc_fnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|dir-&gt;i_hpfs_dno
comma
op_amp
id|fno
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|bail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dnode
op_assign
id|hpfs_alloc_dnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
op_amp
id|dno
comma
op_amp
id|qbh0
comma
l_int|1
)paren
)paren
)paren
r_goto
id|bail1
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dee
comma
l_int|0
comma
r_sizeof
id|dee
)paren
suffix:semicolon
id|dee.directory
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
l_int|0222
)paren
)paren
id|dee.read_only
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*dee.archive = 0;*/
id|dee.hidden
op_assign
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
suffix:semicolon
id|dee.fnode
op_assign
id|fno
suffix:semicolon
id|dee.creation_date
op_assign
id|dee.write_date
op_assign
id|dee.read_date
op_assign
id|gmt_to_local
c_func
(paren
id|dir-&gt;i_sb
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|hpfs_lock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|r
op_assign
id|hpfs_add_dirent
c_func
(paren
id|dir
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
comma
op_amp
id|dee
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|1
)paren
r_goto
id|bail2
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_minus
l_int|1
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh0
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_free_dnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|dno
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|fnode-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|fnode-&gt;name
comma
id|name
comma
id|len
OG
l_int|15
ques
c_cond
l_int|15
suffix:colon
id|len
)paren
suffix:semicolon
id|fnode-&gt;up
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|fnode-&gt;dirflag
op_assign
l_int|1
suffix:semicolon
id|fnode-&gt;btree.n_free_nodes
op_assign
l_int|7
suffix:semicolon
id|fnode-&gt;btree.n_used_nodes
op_assign
l_int|1
suffix:semicolon
id|fnode-&gt;btree.first_free
op_assign
l_int|0x14
suffix:semicolon
id|fnode-&gt;u.external
(braket
l_int|0
)braket
dot
id|disk_secno
op_assign
id|dno
suffix:semicolon
id|fnode-&gt;u.external
(braket
l_int|0
)braket
dot
id|file_secno
op_assign
op_minus
l_int|1
suffix:semicolon
id|dnode-&gt;root_dnode
op_assign
l_int|1
suffix:semicolon
id|dnode-&gt;up
op_assign
id|fno
suffix:semicolon
id|de
op_assign
id|hpfs_add_de
c_func
(paren
id|dir-&gt;i_sb
comma
id|dnode
comma
l_string|&quot;&bslash;001&bslash;001&quot;
comma
l_int|2
comma
l_int|0
)paren
suffix:semicolon
id|de-&gt;creation_date
op_assign
id|de-&gt;write_date
op_assign
id|de-&gt;read_date
op_assign
id|gmt_to_local
c_func
(paren
id|dir-&gt;i_sb
comma
id|CURRENT_TIME
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
l_int|0222
)paren
)paren
id|de-&gt;read_only
op_assign
l_int|1
suffix:semicolon
id|de-&gt;first
op_assign
id|de-&gt;directory
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*de-&gt;hidden = de-&gt;system = 0;*/
id|de-&gt;fnode
op_assign
id|fno
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
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh0
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh0
)paren
suffix:semicolon
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
id|hpfs_lock_iget
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
)paren
)paren
)paren
(brace
id|result-&gt;i_hpfs_parent_dir
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|result-&gt;i_ctime
op_assign
id|result-&gt;i_mtime
op_assign
id|result-&gt;i_atime
op_assign
id|local_to_gmt
c_func
(paren
id|dir-&gt;i_sb
comma
id|dee.creation_date
)paren
suffix:semicolon
id|result-&gt;i_hpfs_ea_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dee.read_only
)paren
id|result-&gt;i_mode
op_and_assign
op_complement
l_int|0222
suffix:semicolon
r_if
c_cond
(paren
id|result-&gt;i_uid
op_ne
id|current-&gt;fsuid
op_logical_or
id|result-&gt;i_gid
op_ne
id|current-&gt;fsgid
op_logical_or
id|result-&gt;i_mode
op_ne
(paren
id|mode
op_or
id|S_IFDIR
)paren
)paren
(brace
id|result-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|result-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|result-&gt;i_mode
op_assign
id|mode
op_or
id|S_IFDIR
suffix:semicolon
id|hpfs_write_inode_nolock
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
id|d_instantiate
c_func
(paren
id|dentry
comma
id|result
)paren
suffix:semicolon
)brace
id|hpfs_unlock_iget
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bail2
suffix:colon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh0
)paren
suffix:semicolon
id|hpfs_free_dnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|dno
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|bail1
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|bail
suffix:colon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|hpfs_create
r_int
id|hpfs_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|inode
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
id|fnode_secno
id|fno
suffix:semicolon
r_int
id|r
suffix:semicolon
r_struct
id|hpfs_dirent
id|dee
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hpfs_chk_name
c_func
(paren
(paren
r_char
op_star
)paren
id|name
comma
op_amp
id|len
)paren
)paren
)paren
r_return
id|err
op_eq
op_minus
id|ENOENT
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_alloc_fnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|dir-&gt;i_hpfs_dno
comma
op_amp
id|fno
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|bail
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dee
comma
l_int|0
comma
r_sizeof
id|dee
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
l_int|0222
)paren
)paren
id|dee.read_only
op_assign
l_int|1
suffix:semicolon
id|dee.archive
op_assign
l_int|1
suffix:semicolon
id|dee.hidden
op_assign
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
suffix:semicolon
id|dee.fnode
op_assign
id|fno
suffix:semicolon
id|dee.creation_date
op_assign
id|dee.write_date
op_assign
id|dee.read_date
op_assign
id|gmt_to_local
c_func
(paren
id|dir-&gt;i_sb
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|hpfs_lock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|r
op_assign
id|hpfs_add_dirent
c_func
(paren
id|dir
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
comma
op_amp
id|dee
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|1
)paren
r_goto
id|bail1
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_minus
l_int|1
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|fnode-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|fnode-&gt;name
comma
id|name
comma
id|len
OG
l_int|15
ques
c_cond
l_int|15
suffix:colon
id|len
)paren
suffix:semicolon
id|fnode-&gt;up
op_assign
id|dir-&gt;i_ino
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
id|hpfs_lock_iget
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
)paren
)paren
)paren
(brace
id|hpfs_decide_conv
c_func
(paren
id|result
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
)paren
suffix:semicolon
id|result-&gt;i_hpfs_parent_dir
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|result-&gt;i_ctime
op_assign
id|result-&gt;i_mtime
op_assign
id|result-&gt;i_atime
op_assign
id|local_to_gmt
c_func
(paren
id|dir-&gt;i_sb
comma
id|dee.creation_date
)paren
suffix:semicolon
id|result-&gt;i_hpfs_ea_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dee.read_only
)paren
id|result-&gt;i_mode
op_and_assign
op_complement
l_int|0222
suffix:semicolon
r_if
c_cond
(paren
id|result-&gt;i_blocks
op_eq
op_minus
l_int|1
)paren
id|result-&gt;i_blocks
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|result-&gt;i_size
op_eq
op_minus
l_int|1
)paren
(brace
id|result-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|result-&gt;i_data.a_ops
op_assign
op_amp
id|hpfs_aops
suffix:semicolon
id|result-&gt;u.hpfs_i.mmu_private
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result-&gt;i_uid
op_ne
id|current-&gt;fsuid
op_logical_or
id|result-&gt;i_gid
op_ne
id|current-&gt;fsgid
op_logical_or
id|result-&gt;i_mode
op_ne
(paren
id|mode
op_or
id|S_IFREG
)paren
)paren
(brace
id|result-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|result-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|result-&gt;i_mode
op_assign
id|mode
op_or
id|S_IFREG
suffix:semicolon
id|hpfs_write_inode_nolock
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
id|d_instantiate
c_func
(paren
id|dentry
comma
id|result
)paren
suffix:semicolon
)brace
id|hpfs_unlock_iget
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bail1
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|bail
suffix:colon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|hpfs_mknod
r_int
id|hpfs_mknod
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
r_int
id|rdev
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
id|fnode_secno
id|fno
suffix:semicolon
r_int
id|r
suffix:semicolon
r_struct
id|hpfs_dirent
id|dee
suffix:semicolon
r_struct
id|inode
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hpfs_chk_name
c_func
(paren
(paren
r_char
op_star
)paren
id|name
comma
op_amp
id|len
)paren
)paren
)paren
r_return
id|err
op_eq
op_minus
id|ENOENT
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|err
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;s_hpfs_eas
OL
l_int|2
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_alloc_fnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|dir-&gt;i_hpfs_dno
comma
op_amp
id|fno
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|bail
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dee
comma
l_int|0
comma
r_sizeof
id|dee
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
l_int|0222
)paren
)paren
id|dee.read_only
op_assign
l_int|1
suffix:semicolon
id|dee.archive
op_assign
l_int|1
suffix:semicolon
id|dee.hidden
op_assign
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
suffix:semicolon
id|dee.fnode
op_assign
id|fno
suffix:semicolon
id|dee.creation_date
op_assign
id|dee.write_date
op_assign
id|dee.read_date
op_assign
id|gmt_to_local
c_func
(paren
id|dir-&gt;i_sb
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|hpfs_lock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|r
op_assign
id|hpfs_add_dirent
c_func
(paren
id|dir
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
comma
op_amp
id|dee
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|1
)paren
r_goto
id|bail1
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_minus
l_int|1
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|fnode-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|fnode-&gt;name
comma
id|name
comma
id|len
OG
l_int|15
ques
c_cond
l_int|15
suffix:colon
id|len
)paren
suffix:semicolon
id|fnode-&gt;up
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_lock_iget
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
)paren
)paren
)paren
(brace
id|result-&gt;i_hpfs_parent_dir
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|result-&gt;i_ctime
op_assign
id|result-&gt;i_mtime
op_assign
id|result-&gt;i_atime
op_assign
id|local_to_gmt
c_func
(paren
id|dir-&gt;i_sb
comma
id|dee.creation_date
)paren
suffix:semicolon
id|result-&gt;i_hpfs_ea_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*if (result-&gt;i_blocks == -1) result-&gt;i_blocks = 1;&n;&t;&t;if (result-&gt;i_size == -1) result-&gt;i_size = 0;*/
id|result-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|result-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|result-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|result-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|result-&gt;i_blocks
op_assign
l_int|1
suffix:semicolon
id|init_special_inode
c_func
(paren
id|result
comma
id|mode
comma
id|rdev
)paren
suffix:semicolon
id|hpfs_write_inode_nolock
c_func
(paren
id|result
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|result
)paren
suffix:semicolon
)brace
id|hpfs_unlock_iget
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bail1
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|bail
suffix:colon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_extern
r_struct
id|address_space_operations
id|hpfs_symlink_aops
suffix:semicolon
DECL|function|hpfs_symlink
r_int
id|hpfs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symlink
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
id|fnode_secno
id|fno
suffix:semicolon
r_int
id|r
suffix:semicolon
r_struct
id|hpfs_dirent
id|dee
suffix:semicolon
r_struct
id|inode
op_star
id|result
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hpfs_chk_name
c_func
(paren
(paren
r_char
op_star
)paren
id|name
comma
op_amp
id|len
)paren
)paren
)paren
r_return
id|err
op_eq
op_minus
id|ENOENT
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|err
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;s_hpfs_eas
OL
l_int|2
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_alloc_fnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|dir-&gt;i_hpfs_dno
comma
op_amp
id|fno
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|bail
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dee
comma
l_int|0
comma
r_sizeof
id|dee
)paren
suffix:semicolon
id|dee.archive
op_assign
l_int|1
suffix:semicolon
id|dee.hidden
op_assign
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
suffix:semicolon
id|dee.fnode
op_assign
id|fno
suffix:semicolon
id|dee.creation_date
op_assign
id|dee.write_date
op_assign
id|dee.read_date
op_assign
id|gmt_to_local
c_func
(paren
id|dir-&gt;i_sb
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|hpfs_lock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|r
op_assign
id|hpfs_add_dirent
c_func
(paren
id|dir
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
comma
op_amp
id|dee
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|1
)paren
r_goto
id|bail1
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_minus
l_int|1
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|fnode-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|fnode-&gt;name
comma
id|name
comma
id|len
OG
l_int|15
ques
c_cond
l_int|15
suffix:colon
id|len
)paren
suffix:semicolon
id|fnode-&gt;up
op_assign
id|dir-&gt;i_ino
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
id|hpfs_lock_iget
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
)paren
)paren
)paren
(brace
id|result-&gt;i_hpfs_parent_dir
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|result-&gt;i_ctime
op_assign
id|result-&gt;i_mtime
op_assign
id|result-&gt;i_atime
op_assign
id|local_to_gmt
c_func
(paren
id|dir-&gt;i_sb
comma
id|dee.creation_date
)paren
suffix:semicolon
id|result-&gt;i_hpfs_ea_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*if (result-&gt;i_blocks == -1) result-&gt;i_blocks = 1;&n;&t;&t;if (result-&gt;i_size == -1) result-&gt;i_size = 0;*/
id|result-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0777
suffix:semicolon
id|result-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|result-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|result-&gt;i_blocks
op_assign
l_int|1
suffix:semicolon
id|result-&gt;i_size
op_assign
id|strlen
c_func
(paren
id|symlink
)paren
suffix:semicolon
id|result-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|result-&gt;i_data.a_ops
op_assign
op_amp
id|hpfs_symlink_aops
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|hpfs_set_ea
c_func
(paren
id|result
comma
id|fnode
comma
l_string|&quot;SYMLINK&quot;
comma
(paren
r_char
op_star
)paren
id|symlink
comma
id|strlen
c_func
(paren
id|symlink
)paren
)paren
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
id|hpfs_write_inode_nolock
c_func
(paren
id|result
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|result
)paren
suffix:semicolon
)brace
id|hpfs_unlock_iget
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bail1
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|hpfs_free_sectors
c_func
(paren
id|dir-&gt;i_sb
comma
id|fno
comma
l_int|1
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
id|bail
suffix:colon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|hpfs_unlink
r_int
id|hpfs_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|dnode_secno
id|dno
suffix:semicolon
id|fnode_secno
id|fno
suffix:semicolon
r_int
id|r
suffix:semicolon
r_int
id|rep
op_assign
l_int|0
suffix:semicolon
id|hpfs_adjust_length
c_func
(paren
(paren
r_char
op_star
)paren
id|name
comma
op_amp
id|len
)paren
suffix:semicolon
id|again
suffix:colon
id|hpfs_lock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|de
op_assign
id|map_dirent
c_func
(paren
id|dir
comma
id|dir-&gt;i_hpfs_dno
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
comma
op_amp
id|dno
comma
op_amp
id|qbh
)paren
)paren
)paren
(brace
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;first
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;directory
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EISDIR
suffix:semicolon
)brace
id|fno
op_assign
id|de-&gt;fnode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|hpfs_remove_dirent
c_func
(paren
id|dir
comma
id|dno
comma
id|de
comma
op_amp
id|qbh
comma
l_int|1
)paren
)paren
op_eq
l_int|1
)paren
id|hpfs_error
c_func
(paren
id|dir-&gt;i_sb
comma
l_string|&quot;there was error when removing dirent&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
l_int|2
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* no space for deleting, try to truncate file */
r_struct
id|iattr
id|newattrs
suffix:semicolon
r_int
id|err
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rep
op_logical_or
id|dentry-&gt;d_count
OG
l_int|1
op_logical_or
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_logical_or
id|get_write_access
c_func
(paren
id|inode
)paren
)paren
r_goto
id|ret
suffix:semicolon
multiline_comment|/*printk(&quot;HPFS: truncating file before delete.&bslash;n&quot;);*/
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|newattrs.ia_size
op_assign
l_int|0
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_SIZE
op_or
id|ATTR_CTIME
suffix:semicolon
id|err
op_assign
id|notify_change
c_func
(paren
id|dentry
comma
op_amp
id|newattrs
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|put_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|ret
suffix:semicolon
id|rep
op_assign
l_int|1
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
id|ret
suffix:colon
r_return
id|r
op_eq
l_int|2
ques
c_cond
op_minus
id|ENOSPC
suffix:colon
id|r
op_eq
l_int|1
ques
c_cond
op_minus
id|EFSERROR
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_rmdir
r_int
id|hpfs_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|dnode_secno
id|dno
suffix:semicolon
id|fnode_secno
id|fno
suffix:semicolon
r_int
id|n_items
op_assign
l_int|0
suffix:semicolon
r_int
id|r
suffix:semicolon
id|hpfs_adjust_length
c_func
(paren
(paren
r_char
op_star
)paren
id|name
comma
op_amp
id|len
)paren
suffix:semicolon
id|hpfs_lock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|de
op_assign
id|map_dirent
c_func
(paren
id|dir
comma
id|dir-&gt;i_hpfs_dno
comma
(paren
r_char
op_star
)paren
id|name
comma
id|len
comma
op_amp
id|dno
comma
op_amp
id|qbh
)paren
)paren
)paren
(brace
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;first
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;directory
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOTDIR
suffix:semicolon
)brace
id|hpfs_count_dnodes
c_func
(paren
id|dir-&gt;i_sb
comma
id|inode-&gt;i_hpfs_dno
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|n_items
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_items
)paren
(brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOTEMPTY
suffix:semicolon
)brace
id|fno
op_assign
id|de-&gt;fnode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|hpfs_remove_dirent
c_func
(paren
id|dir
comma
id|dno
comma
id|de
comma
op_amp
id|qbh
comma
l_int|1
)paren
)paren
op_eq
l_int|1
)paren
id|hpfs_error
c_func
(paren
id|dir-&gt;i_sb
comma
l_string|&quot;there was error when removing dirent&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
l_int|2
)paren
(brace
id|dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
)brace
r_else
id|hpfs_unlock_2inodes
c_func
(paren
id|dir
comma
id|inode
)paren
suffix:semicolon
r_return
id|r
op_eq
l_int|2
ques
c_cond
op_minus
id|ENOSPC
suffix:colon
id|r
op_eq
l_int|1
ques
c_cond
op_minus
id|EFSERROR
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_symlink_readpage
r_int
id|hpfs_symlink_readpage
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
)paren
(brace
r_char
op_star
id|link
op_assign
(paren
r_char
op_star
)paren
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|i
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|page-&gt;mapping-&gt;host
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
r_int
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
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
id|i-&gt;i_sb
comma
id|i-&gt;i_ino
comma
op_amp
id|bh
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|err
op_assign
id|hpfs_read_ea
c_func
(paren
id|i-&gt;i_sb
comma
id|fnode
comma
l_string|&quot;SYMLINK&quot;
comma
id|link
comma
id|PAGE_SIZE
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
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hpfs_rename
r_int
id|hpfs_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_char
op_star
id|old_name
op_assign
(paren
r_char
op_star
)paren
id|old_dentry-&gt;d_name.name
suffix:semicolon
r_int
id|old_len
op_assign
id|old_dentry-&gt;d_name.len
suffix:semicolon
r_char
op_star
id|new_name
op_assign
(paren
r_char
op_star
)paren
id|new_dentry-&gt;d_name.name
suffix:semicolon
r_int
id|new_len
op_assign
id|new_dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|inode
op_star
id|i
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|quad_buffer_head
id|qbh
comma
id|qbh1
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|dep
comma
op_star
id|nde
suffix:semicolon
r_struct
id|hpfs_dirent
id|de
suffix:semicolon
id|dnode_secno
id|dno
suffix:semicolon
r_int
id|r
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hpfs_chk_name
c_func
(paren
(paren
r_char
op_star
)paren
id|new_name
comma
op_amp
id|new_len
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|hpfs_adjust_length
c_func
(paren
(paren
r_char
op_star
)paren
id|old_name
comma
op_amp
id|old_len
)paren
suffix:semicolon
id|hpfs_lock_3inodes
c_func
(paren
id|old_dir
comma
id|new_dir
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* Erm? Moving over the empty non-busy directory is perfectly legal */
r_if
c_cond
(paren
id|new_inode
op_logical_and
id|S_ISDIR
c_func
(paren
id|new_inode-&gt;i_mode
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dep
op_assign
id|map_dirent
c_func
(paren
id|old_dir
comma
id|old_dir-&gt;i_hpfs_dno
comma
(paren
r_char
op_star
)paren
id|old_name
comma
id|old_len
comma
op_amp
id|dno
comma
op_amp
id|qbh
)paren
)paren
)paren
(brace
id|hpfs_error
c_func
(paren
id|i-&gt;i_sb
comma
l_string|&quot;lookup succeeded but map dirent failed&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
id|copy_de
c_func
(paren
op_amp
id|de
comma
id|dep
)paren
suffix:semicolon
id|de.hidden
op_assign
id|new_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|hpfs_remove_dirent
c_func
(paren
id|old_dir
comma
id|dno
comma
id|dep
comma
op_amp
id|qbh
comma
l_int|1
)paren
)paren
op_ne
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|nde
op_assign
id|map_dirent
c_func
(paren
id|new_dir
comma
id|new_dir-&gt;i_hpfs_dno
comma
(paren
r_char
op_star
)paren
id|new_name
comma
id|new_len
comma
l_int|NULL
comma
op_amp
id|qbh1
)paren
)paren
)paren
(brace
id|new_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|copy_de
c_func
(paren
id|nde
comma
op_amp
id|de
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|nde-&gt;name
comma
id|new_name
comma
id|new_len
)paren
suffix:semicolon
id|hpfs_mark_4buffers_dirty
c_func
(paren
op_amp
id|qbh1
)paren
suffix:semicolon
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh1
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|hpfs_error
c_func
(paren
id|new_dir-&gt;i_sb
comma
l_string|&quot;hpfs_rename: could not find dirent&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EFSERROR
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
id|err
op_assign
id|r
op_eq
l_int|2
ques
c_cond
op_minus
id|ENOSPC
suffix:colon
id|r
op_eq
l_int|1
ques
c_cond
op_minus
id|EFSERROR
suffix:colon
l_int|0
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_dir
op_eq
id|old_dir
)paren
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
id|hpfs_lock_creation
c_func
(paren
id|i-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|hpfs_add_dirent
c_func
(paren
id|new_dir
comma
id|new_name
comma
id|new_len
comma
op_amp
id|de
comma
l_int|1
)paren
)paren
)paren
(brace
id|hpfs_unlock_creation
c_func
(paren
id|i-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_minus
l_int|1
)paren
id|hpfs_error
c_func
(paren
id|new_dir-&gt;i_sb
comma
l_string|&quot;hpfs_rename: dirent already exists!&quot;
)paren
suffix:semicolon
id|err
op_assign
id|r
op_eq
l_int|1
ques
c_cond
op_minus
id|ENOSPC
suffix:colon
op_minus
id|EFSERROR
suffix:semicolon
r_if
c_cond
(paren
id|new_dir
op_ne
id|old_dir
)paren
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_dir
op_eq
id|old_dir
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|dep
op_assign
id|map_dirent
c_func
(paren
id|old_dir
comma
id|old_dir-&gt;i_hpfs_dno
comma
(paren
r_char
op_star
)paren
id|old_name
comma
id|old_len
comma
op_amp
id|dno
comma
op_amp
id|qbh
)paren
)paren
)paren
(brace
id|hpfs_unlock_creation
c_func
(paren
id|i-&gt;i_sb
)paren
suffix:semicolon
id|hpfs_error
c_func
(paren
id|i-&gt;i_sb
comma
l_string|&quot;lookup succeeded but map dirent failed at #2&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|r
op_assign
id|hpfs_remove_dirent
c_func
(paren
id|old_dir
comma
id|dno
comma
id|dep
comma
op_amp
id|qbh
comma
l_int|0
)paren
)paren
)paren
(brace
id|hpfs_unlock_creation
c_func
(paren
id|i-&gt;i_sb
)paren
suffix:semicolon
id|hpfs_error
c_func
(paren
id|i-&gt;i_sb
comma
l_string|&quot;hpfs_rename: could not remove dirent&quot;
)paren
suffix:semicolon
id|err
op_assign
id|r
op_eq
l_int|2
ques
c_cond
op_minus
id|ENOSPC
suffix:colon
op_minus
id|EFSERROR
suffix:semicolon
r_goto
id|end1
suffix:semicolon
)brace
id|hpfs_unlock_creation
c_func
(paren
id|i-&gt;i_sb
)paren
suffix:semicolon
id|end
suffix:colon
id|i-&gt;i_hpfs_parent_dir
op_assign
id|new_dir-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|i-&gt;i_mode
)paren
)paren
(brace
id|new_dir-&gt;i_nlink
op_increment
suffix:semicolon
id|old_dir-&gt;i_nlink
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|i-&gt;i_sb
comma
id|i-&gt;i_ino
comma
op_amp
id|bh
)paren
)paren
)paren
(brace
id|fnode-&gt;up
op_assign
id|new_dir-&gt;i_ino
suffix:semicolon
id|fnode-&gt;len
op_assign
id|new_len
suffix:semicolon
id|memcpy
c_func
(paren
id|fnode-&gt;name
comma
id|new_name
comma
id|new_len
OG
l_int|15
ques
c_cond
l_int|15
suffix:colon
id|new_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_len
OL
l_int|15
)paren
id|memset
c_func
(paren
op_amp
id|fnode-&gt;name
(braket
id|new_len
)braket
comma
l_int|0
comma
l_int|15
op_minus
id|new_len
)paren
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
id|i-&gt;i_hpfs_conv
op_assign
id|i-&gt;i_sb-&gt;s_hpfs_conv
suffix:semicolon
id|hpfs_decide_conv
c_func
(paren
id|i
comma
(paren
r_char
op_star
)paren
id|new_name
comma
id|new_len
)paren
suffix:semicolon
id|end1
suffix:colon
id|hpfs_unlock_3inodes
c_func
(paren
id|old_dir
comma
id|new_dir
comma
id|i
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
