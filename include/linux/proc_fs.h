macro_line|#ifndef _LINUX_PROC_FS_H
DECL|macro|_LINUX_PROC_FS_H
mdefine_line|#define _LINUX_PROC_FS_H
multiline_comment|/*&n; * The proc filesystem constants/structures&n; */
DECL|macro|PROC_ROOT_INO
mdefine_line|#define PROC_ROOT_INO 1
DECL|macro|PROC_SUPER_MAGIC
mdefine_line|#define PROC_SUPER_MAGIC 0x9fa0
DECL|struct|proc_dir_entry
r_struct
id|proc_dir_entry
(brace
DECL|member|low_ino
r_int
r_int
id|low_ino
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|super_block
op_star
id|proc_read_super
c_func
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_write_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_match
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_root_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_base_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_mem_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_array_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_link_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_fd_inode_operations
suffix:semicolon
macro_line|#endif
eof
