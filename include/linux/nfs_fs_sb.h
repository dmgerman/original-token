macro_line|#ifndef _NFS_FS_SB
DECL|macro|_NFS_FS_SB
mdefine_line|#define _NFS_FS_SB
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/in.h&gt;
multiline_comment|/*&n; * NFS client parameters&n; * Part of this is duplicated in rpc_clnt and is therefore obsolete.&n; */
DECL|struct|nfs_server
r_struct
id|nfs_server
(brace
DECL|member|client
r_struct
id|rpc_clnt
op_star
id|client
suffix:semicolon
multiline_comment|/* RPC client handle */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|rsize
r_int
id|rsize
suffix:semicolon
multiline_comment|/* read size */
DECL|member|wsize
r_int
id|wsize
suffix:semicolon
multiline_comment|/* write size */
DECL|member|bsize
r_int
r_int
id|bsize
suffix:semicolon
multiline_comment|/* server block size */
DECL|member|acregmin
r_int
r_int
id|acregmin
suffix:semicolon
multiline_comment|/* attr cache timeouts */
DECL|member|acregmax
r_int
r_int
id|acregmax
suffix:semicolon
DECL|member|acdirmin
r_int
r_int
id|acdirmin
suffix:semicolon
DECL|member|acdirmax
r_int
r_int
id|acdirmax
suffix:semicolon
DECL|member|hostname
r_char
id|hostname
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* remote hostname */
)brace
suffix:semicolon
multiline_comment|/*&n; * nfs super-block data in memory&n; */
DECL|struct|nfs_sb_info
r_struct
id|nfs_sb_info
(brace
DECL|member|s_server
r_struct
id|nfs_server
id|s_server
suffix:semicolon
DECL|member|s_root
r_struct
id|nfs_fh
id|s_root
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
