macro_line|#ifndef _FAT_CVF
DECL|macro|_FAT_CVF
mdefine_line|#define _FAT_CVF
DECL|macro|CVF_USE_READPAGE
mdefine_line|#define CVF_USE_READPAGE  0x0001
DECL|struct|cvf_format
r_struct
id|cvf_format
DECL|member|cvf_version
(brace
r_int
id|cvf_version
suffix:semicolon
DECL|member|cvf_version_text
r_char
op_star
id|cvf_version_text
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|detect_cvf
r_int
(paren
op_star
id|detect_cvf
)paren
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
DECL|member|mount_cvf
r_int
(paren
op_star
id|mount_cvf
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|options
)paren
suffix:semicolon
DECL|member|unmount_cvf
r_int
(paren
op_star
id|unmount_cvf
)paren
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
DECL|member|cvf_bread
r_struct
id|buffer_head
op_star
(paren
op_star
id|cvf_bread
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
suffix:semicolon
DECL|member|cvf_getblk
r_struct
id|buffer_head
op_star
(paren
op_star
id|cvf_getblk
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
suffix:semicolon
DECL|member|cvf_brelse
r_void
(paren
op_star
id|cvf_brelse
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|member|cvf_mark_buffer_dirty
r_void
(paren
op_star
id|cvf_mark_buffer_dirty
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|dirty_val
)paren
suffix:semicolon
DECL|member|cvf_set_uptodate
r_void
(paren
op_star
id|cvf_set_uptodate
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|val
)paren
suffix:semicolon
DECL|member|cvf_is_uptodate
r_int
(paren
op_star
id|cvf_is_uptodate
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|member|cvf_ll_rw_block
r_void
(paren
op_star
id|cvf_ll_rw_block
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|opr
comma
r_int
id|nbreq
comma
r_struct
id|buffer_head
op_star
id|bh
(braket
l_int|32
)braket
)paren
suffix:semicolon
DECL|member|fat_access
r_int
(paren
op_star
id|fat_access
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
comma
r_int
id|new_value
)paren
suffix:semicolon
DECL|member|cvf_statfs
r_int
(paren
op_star
id|cvf_statfs
)paren
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
suffix:semicolon
DECL|member|cvf_bmap
r_int
(paren
op_star
id|cvf_bmap
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
suffix:semicolon
DECL|member|cvf_smap
r_int
(paren
op_star
id|cvf_smap
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sector
)paren
suffix:semicolon
DECL|member|cvf_file_read
id|ssize_t
(paren
op_star
id|cvf_file_read
)paren
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
DECL|member|cvf_file_write
id|ssize_t
(paren
op_star
id|cvf_file_write
)paren
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
DECL|member|cvf_mmap
r_int
(paren
op_star
id|cvf_mmap
)paren
(paren
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
DECL|member|cvf_readpage
r_int
(paren
op_star
id|cvf_readpage
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
DECL|member|cvf_writepage
r_int
(paren
op_star
id|cvf_writepage
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
DECL|member|cvf_dir_ioctl
r_int
(paren
op_star
id|cvf_dir_ioctl
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|zero_out_cluster
r_void
(paren
op_star
id|zero_out_cluster
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
id|clusternr
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|register_cvf_format
c_func
(paren
r_struct
id|cvf_format
op_star
id|cvf_format
)paren
suffix:semicolon
r_int
id|unregister_cvf_format
c_func
(paren
r_struct
id|cvf_format
op_star
id|cvf_format
)paren
suffix:semicolon
r_void
id|dec_cvf_format_use_count_by_version
c_func
(paren
r_int
id|version
)paren
suffix:semicolon
r_int
id|detect_cvf
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|force
)paren
suffix:semicolon
r_extern
r_struct
id|cvf_format
op_star
id|cvf_formats
(braket
)braket
suffix:semicolon
r_extern
r_int
id|cvf_format_use_count
(braket
)braket
suffix:semicolon
macro_line|#endif
eof
