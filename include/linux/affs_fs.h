macro_line|#ifndef _AFFS_FS_H
DECL|macro|_AFFS_FS_H
mdefine_line|#define _AFFS_FS_H
multiline_comment|/*&n; * The affs filesystem constants/structures&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|AFFS_SUPER_MAGIC
mdefine_line|#define AFFS_SUPER_MAGIC 0xadff
multiline_comment|/* Get the filesystem block size given an inode. */
DECL|macro|AFFS_I2BSIZE
mdefine_line|#define AFFS_I2BSIZE(inode) ((inode)-&gt;i_sb-&gt;s_blocksize)
multiline_comment|/* Get the filesystem hash table size given an inode. */
DECL|macro|AFFS_I2HSIZE
mdefine_line|#define AFFS_I2HSIZE(inode) ((inode)-&gt;i_sb-&gt;u.affs_sb.s_hashsize)
multiline_comment|/* Get the block number bits given an inode */
DECL|macro|AFFS_I2BITS
mdefine_line|#define AFFS_I2BITS(inode) ((inode)-&gt;i_sb-&gt;s_blocksize_bits)
multiline_comment|/* Get the fs type given an inode */
DECL|macro|AFFS_I2FSTYPE
mdefine_line|#define AFFS_I2FSTYPE(inode) ((inode)-&gt;i_sb-&gt;u.affs_sb.s_flags &amp; SF_INTL)
DECL|struct|DateStamp
r_struct
id|DateStamp
(brace
DECL|member|ds_Days
id|u32
id|ds_Days
suffix:semicolon
DECL|member|ds_Minute
id|u32
id|ds_Minute
suffix:semicolon
DECL|member|ds_Tick
id|u32
id|ds_Tick
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --- Prototypes -----------------------------------------------------------------------------&t;*/
multiline_comment|/* amigaffs.c */
r_extern
r_int
id|affs_get_key_entry
c_func
(paren
r_int
id|bsize
comma
r_void
op_star
id|data
comma
r_int
id|entry_pos
)paren
suffix:semicolon
r_extern
r_int
id|affs_get_file_name
c_func
(paren
r_int
id|bsize
comma
r_void
op_star
id|fh_data
comma
r_int
r_char
op_star
op_star
id|name
)paren
suffix:semicolon
r_extern
id|u32
id|affs_checksum_block
c_func
(paren
r_int
id|bsize
comma
r_void
op_star
id|data
comma
id|s32
op_star
id|ptype
comma
id|s32
op_star
id|stype
)paren
suffix:semicolon
r_extern
r_void
id|affs_fix_checksum
c_func
(paren
r_int
id|bsize
comma
r_void
op_star
id|data
comma
r_int
id|cspos
)paren
suffix:semicolon
r_extern
r_void
id|secs_to_datestamp
c_func
(paren
id|time_t
id|secs
comma
r_struct
id|DateStamp
op_star
id|ds
)paren
suffix:semicolon
r_extern
r_int
id|prot_to_mode
c_func
(paren
r_int
r_int
id|prot
)paren
suffix:semicolon
r_extern
id|u32
id|mode_to_prot
c_func
(paren
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|affs_insert_hash
c_func
(paren
r_int
r_int
id|dir_ino
comma
r_struct
id|buffer_head
op_star
id|header
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|affs_remove_hash
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|affs_remove_link
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|affs_remove_header
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_error
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|affs_warning
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|affs_check_name
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|affs_copy_name
c_func
(paren
r_int
r_char
op_star
id|bstr
comma
r_const
r_int
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* bitmap. c */
r_extern
r_int
id|affs_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|affs_count_free_bits
c_func
(paren
r_int
id|blocksize
comma
r_const
r_char
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|affs_free_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|s32
id|block
)paren
suffix:semicolon
r_extern
id|s32
id|affs_new_header
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
id|s32
id|affs_new_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_make_zones
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_int
id|affs_hash_name
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|intl
comma
r_int
id|hashsize
)paren
suffix:semicolon
r_extern
r_int
id|affs_lookup
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
suffix:semicolon
r_extern
r_int
id|affs_unlink
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
suffix:semicolon
r_extern
r_int
id|affs_create
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
suffix:semicolon
r_extern
r_int
id|affs_mkdir
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
suffix:semicolon
r_extern
r_int
id|affs_rmdir
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
suffix:semicolon
r_extern
r_int
id|affs_link
c_func
(paren
r_struct
id|inode
op_star
id|oldinode
comma
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
suffix:semicolon
r_extern
r_int
id|affs_symlink
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
id|symname
)paren
suffix:semicolon
r_extern
r_int
id|affs_rename
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
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_struct
id|buffer_head
op_star
id|affs_bread
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|affs_brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_int
r_int
id|affs_parent_ino
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|affs_new_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_int
id|affs_notify_change
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_int
id|affs_add_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|link
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
id|s32
id|type
)paren
suffix:semicolon
r_extern
r_void
id|affs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_int
id|affs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_void
id|affs_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_void
id|affs_dir_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* jump tables */
r_extern
r_struct
id|inode_operations
id|affs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_file_inode_operations_ofs
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_chrdev_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_blkdev_inode_operations
suffix:semicolon
macro_line|#endif
eof
