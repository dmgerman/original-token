macro_line|#ifndef _NFS_FS_I
DECL|macro|_NFS_FS_I
mdefine_line|#define _NFS_FS_I
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
multiline_comment|/*&n; * nfs fs inode data in memory&n; */
DECL|struct|nfs_inode_info
r_struct
id|nfs_inode_info
(brace
DECL|member|pipeinfo
r_struct
id|pipe_inode_info
id|pipeinfo
suffix:semicolon
DECL|member|fhandle
r_struct
id|nfs_fh
id|fhandle
suffix:semicolon
multiline_comment|/*&n;&t; * read_cache_jiffies is when we started read-caching this inode,&n;&t; * and read_cache_mtime is the mtime of the inode at that time.&n;&t; *&n;&t; * We need to invalidate the cache for this inode if&n;&t; *&n;&t; *&t;jiffies - read_cache_jiffies &gt; 30*HZ&n;&t; * AND&n;&t; *&t;mtime != read_cache_mtime&n;&t; */
DECL|member|read_cache_jiffies
r_int
r_int
id|read_cache_jiffies
suffix:semicolon
DECL|member|read_cache_mtime
r_int
r_int
id|read_cache_mtime
suffix:semicolon
multiline_comment|/*&n;&t; * This is to support the clandestine rename on unlink.&n;&t; * Instead of the directory inode, we might as well keep its&n;&t; * NFS FH, but that requires a kmalloc.&n;&t; */
DECL|member|silly_rename_dir
r_struct
id|inode
op_star
id|silly_rename_dir
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
