macro_line|#ifndef _LINUX_HPFS_FS_H
DECL|macro|_LINUX_HPFS_FS_H
mdefine_line|#define _LINUX_HPFS_FS_H
multiline_comment|/* HPFS magic number (word 0 of block 16) */
DECL|macro|HPFS_SUPER_MAGIC
mdefine_line|#define HPFS_SUPER_MAGIC 0xf995e849
multiline_comment|/* The entry point for a VFS */
r_extern
r_struct
id|super_block
op_star
id|hpfs_read_super
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|init_hpfs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
