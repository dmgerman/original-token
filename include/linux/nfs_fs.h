macro_line|#ifndef _LINUX_NFS_FS_H
DECL|macro|_LINUX_NFS_FS_H
mdefine_line|#define _LINUX_NFS_FS_H
multiline_comment|/*&n; *  linux/include/linux/nfs_fs.h&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  OS-specific nfs filesystem definitions and declarations&n; */
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
multiline_comment|/*&n; * The readdir cache size controls how many directory entries are cached.&n; * Its size is limited by the number of nfs_entry structures that can fit&n; * in one 4096-byte page, currently 256.&n; */
DECL|macro|NFS_READDIR_CACHE_SIZE
mdefine_line|#define NFS_READDIR_CACHE_SIZE&t;&t;64
DECL|macro|NFS_MAX_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_MAX_FILE_IO_BUFFER_SIZE&t;16384
DECL|macro|NFS_DEF_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_DEF_FILE_IO_BUFFER_SIZE&t;1024
multiline_comment|/*&n; * The upper limit on timeouts for the exponential backoff algorithm&n; * in tenths of a second.&n; */
DECL|macro|NFS_MAX_RPC_TIMEOUT
mdefine_line|#define NFS_MAX_RPC_TIMEOUT&t;&t;600
multiline_comment|/*&n; * Size of the lookup cache in units of number of entries cached.&n; * It is better not to make this too large although the optimimum&n; * depends on a usage and environment.&n; */
DECL|macro|NFS_LOOKUP_CACHE_SIZE
mdefine_line|#define NFS_LOOKUP_CACHE_SIZE&t;&t;64
DECL|macro|NFS_SUPER_MAGIC
mdefine_line|#define NFS_SUPER_MAGIC&t;&t;&t;0x6969
DECL|macro|NFS_SERVER
mdefine_line|#define NFS_SERVER(inode)&t;&t;(&amp;(inode)-&gt;i_sb-&gt;u.nfs_sb.s_server)
DECL|macro|NFS_FH
mdefine_line|#define NFS_FH(inode)&t;&t;&t;(&amp;(inode)-&gt;u.nfs_i.fhandle)
macro_line|#ifdef __KERNEL__
multiline_comment|/* linux/fs/nfs/proc.c */
r_extern
r_int
id|nfs_proc_getattr
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_setattr
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_sattr
op_star
id|sattr
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_lookup
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_readlink
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_char
op_star
id|res
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_read
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_int
id|offset
comma
r_int
id|count
comma
r_char
op_star
id|data
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_write
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_int
id|offset
comma
r_int
id|count
comma
r_char
op_star
id|data
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_create
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|nfs_sattr
op_star
id|sattr
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_remove
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_rename
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|old_dir
comma
r_const
r_char
op_star
id|old_name
comma
r_struct
id|nfs_fh
op_star
id|new_dir
comma
r_const
r_char
op_star
id|new_name
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_link
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_symlink
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|path
comma
r_struct
id|nfs_sattr
op_star
id|sattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_mkdir
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|nfs_sattr
op_star
id|sattr
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_rmdir
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_readdir
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_int
id|cookie
comma
r_int
id|count
comma
r_struct
id|nfs_entry
op_star
id|entry
)paren
suffix:semicolon
r_extern
r_int
id|nfs_proc_statfs
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fsinfo
op_star
id|res
)paren
suffix:semicolon
multiline_comment|/* linux/fs/nfs/sock.c */
r_extern
r_int
id|nfs_rpc_call
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_int
op_star
id|start
comma
r_int
op_star
id|end
)paren
suffix:semicolon
multiline_comment|/* linux/fs/nfs/inode.c */
r_extern
r_struct
id|super_block
op_star
id|nfs_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|nfs_fhget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_void
id|nfs_refresh_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
suffix:semicolon
multiline_comment|/* linux/fs/nfs/file.c */
r_extern
r_struct
id|inode_operations
id|nfs_file_inode_operations
suffix:semicolon
multiline_comment|/* linux/fs/nfs/dir.c */
r_extern
r_struct
id|inode_operations
id|nfs_dir_inode_operations
suffix:semicolon
multiline_comment|/* linux/fs/nfs/symlink.c */
r_extern
r_struct
id|inode_operations
id|nfs_symlink_inode_operations
suffix:semicolon
multiline_comment|/* linux/fs/nfs/mmap.c */
r_extern
r_int
id|nfs_mmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
