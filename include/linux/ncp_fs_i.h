multiline_comment|/*&n; *  ncp_fs_i.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_NCP_FS_I
DECL|macro|_LINUX_NCP_FS_I
mdefine_line|#define _LINUX_NCP_FS_I
macro_line|#include &lt;linux/ncp.h&gt;
macro_line|#ifdef __KERNEL__
DECL|enum|ncp_inode_state
r_enum
id|ncp_inode_state
(brace
DECL|enumerator|NCP_INODE_VALID
id|NCP_INODE_VALID
op_assign
l_int|19
comma
multiline_comment|/* Inode currently in use */
DECL|enumerator|NCP_INODE_LOOKED_UP
id|NCP_INODE_LOOKED_UP
comma
multiline_comment|/* directly before iget */
DECL|enumerator|NCP_INODE_CACHED
id|NCP_INODE_CACHED
comma
multiline_comment|/* in a path to an inode which is in use */
DECL|enumerator|NCP_INODE_INVALID
id|NCP_INODE_INVALID
)brace
suffix:semicolon
multiline_comment|/*&n; * ncp fs inode data (in memory only)&n; */
DECL|struct|ncp_inode_info
r_struct
id|ncp_inode_info
(brace
DECL|member|state
r_enum
id|ncp_inode_state
id|state
suffix:semicolon
DECL|member|nused
r_int
id|nused
suffix:semicolon
multiline_comment|/* for directories:&n;                                   number of references in memory */
DECL|member|dir
r_struct
id|ncp_inode_info
op_star
id|dir
suffix:semicolon
DECL|member|next
DECL|member|prev
r_struct
id|ncp_inode_info
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|finfo
r_struct
id|nw_file_info
id|finfo
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
