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
multiline_comment|/*&n;&t; * This is a place holder so named pipes on NFS filesystems&n;&t; * work (more or less correctly). This must be first in the&n;&t; * struct because the data is really accessed via inode-&gt;u.pipe_i.&n;&t; */
DECL|member|pipeinfo
r_struct
id|pipe_inode_info
id|pipeinfo
suffix:semicolon
multiline_comment|/*&n;&t; * The file handle&n;&t; */
DECL|member|fhandle
r_struct
id|nfs_fh
id|fhandle
suffix:semicolon
multiline_comment|/*&n;&t; * Various flags&n;&t; */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * read_cache_jiffies is when we started read-caching this inode,&n;&t; * and read_cache_mtime is the mtime of the inode at that time.&n;&t; * attrtimeo is for how long the cached information is assumed&n;&t; * to be valid. A successful attribute revalidation doubles&n;&t; * attrtimeo (up to acregmax/acdirmax), a failure resets it to&n;&t; * acregmin/acdirmin.&n;&t; *&n;&t; * We need to revalidate the cached attrs for this inode if&n;&t; *&n;&t; *&t;jiffies - read_cache_jiffies &gt; attrtimeo&n;&t; *&n;&t; * and invalidate any cached data/flush out any dirty pages if&n;&t; * we find that&n;&t; *&n;&t; *&t;mtime != read_cache_mtime&n;&t; */
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
DECL|member|attrtimeo
r_int
r_int
id|attrtimeo
suffix:semicolon
multiline_comment|/*&n;&t; * This is the list of dirty unwritten pages.&n;&t; * NFSv3 will want to add a list for written but uncommitted&n;&t; * pages.&n;&t; */
DECL|member|writeback
r_struct
id|nfs_wreq
op_star
id|writeback
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Legal inode flag values&n; */
DECL|macro|NFS_INO_REVALIDATE
mdefine_line|#define NFS_INO_REVALIDATE&t;0x0001&t;&t;/* revalidating attrs */
multiline_comment|/*&n; * NFS lock info&n; */
DECL|struct|nfs_lock_info
r_struct
id|nfs_lock_info
(brace
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Lock flag values&n; */
DECL|macro|NFS_LCK_GRANTED
mdefine_line|#define NFS_LCK_GRANTED&t;&t;0x0001&t;&t;/* lock has been granted */
macro_line|#endif
eof
