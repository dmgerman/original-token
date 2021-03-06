multiline_comment|/*&n; *  inode.h&n; *  Header file for inode.c&n; *&n; *  Copyright (C) 1997 R&#xfffd;gis Duchesne&n; *  Copyright (C) 1998 Martin von L&#xfffd;wis&n; */
id|ntfs_attribute
op_star
id|ntfs_find_attr
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_int
id|type
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|ntfs_read_attr
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_int
id|type
comma
r_char
op_star
id|name
comma
r_int
id|offset
comma
id|ntfs_io
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ntfs_write_attr
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_int
id|type
comma
r_char
op_star
id|name
comma
r_int
id|offset
comma
id|ntfs_io
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ntfs_init_inode
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
id|ntfs_volume
op_star
id|vol
comma
r_int
id|inum
)paren
suffix:semicolon
r_void
id|ntfs_clear_inode
c_func
(paren
id|ntfs_inode
op_star
id|ino
)paren
suffix:semicolon
r_int
id|ntfs_check_mft_record
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_char
op_star
id|record
)paren
suffix:semicolon
r_int
id|ntfs_alloc_inode
(paren
id|ntfs_inode
op_star
id|dir
comma
id|ntfs_inode
op_star
id|result
comma
r_const
r_char
op_star
id|filename
comma
r_int
id|namelen
comma
id|ntfs_u32
)paren
suffix:semicolon
r_int
id|ntfs_alloc_file
(paren
id|ntfs_inode
op_star
id|dir
comma
id|ntfs_inode
op_star
id|result
comma
r_char
op_star
id|filename
comma
r_int
id|namelen
)paren
suffix:semicolon
r_int
id|ntfs_update_inode
c_func
(paren
id|ntfs_inode
op_star
id|ino
)paren
suffix:semicolon
r_int
id|ntfs_vcn_to_lcn
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_int
id|vcn
)paren
suffix:semicolon
r_int
id|ntfs_readwrite_attr
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
id|ntfs_attribute
op_star
id|attr
comma
r_int
id|offset
comma
id|ntfs_io
op_star
id|dest
)paren
suffix:semicolon
r_int
id|ntfs_allocate_attr_number
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_int
op_star
id|result
)paren
suffix:semicolon
r_int
id|ntfs_decompress_run
c_func
(paren
r_int
r_char
op_star
op_star
id|data
comma
r_int
op_star
id|length
comma
id|ntfs_cluster_t
op_star
id|cluster
comma
r_int
op_star
id|ctype
)paren
suffix:semicolon
r_void
id|ntfs_decompress
c_func
(paren
r_int
r_char
op_star
id|dest
comma
r_int
r_char
op_star
id|src
comma
id|ntfs_size_t
id|l
)paren
suffix:semicolon
r_void
id|ntfs_fill_mft_header
c_func
(paren
id|ntfs_u8
op_star
id|mft
comma
r_int
id|recordsize
comma
r_int
id|blocksize
comma
r_int
id|sequence_number
)paren
suffix:semicolon
eof
