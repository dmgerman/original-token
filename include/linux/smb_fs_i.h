multiline_comment|/*&n; *  smb_fs_i.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_FS_I
DECL|macro|_LINUX_SMB_FS_I
mdefine_line|#define _LINUX_SMB_FS_I
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/smb.h&gt;
DECL|enum|smb_inode_state
r_enum
id|smb_inode_state
(brace
DECL|enumerator|INODE_VALID
id|INODE_VALID
op_assign
l_int|19
comma
multiline_comment|/* Inode currently in use */
DECL|enumerator|INODE_LOOKED_UP
id|INODE_LOOKED_UP
comma
multiline_comment|/* directly before iget */
DECL|enumerator|INODE_CACHED
id|INODE_CACHED
comma
multiline_comment|/* in a path to an inode which is in use */
DECL|enumerator|INODE_INVALID
id|INODE_INVALID
)brace
suffix:semicolon
multiline_comment|/*&n; * smb fs inode data (in memory only)&n; */
DECL|struct|smb_inode_info
r_struct
id|smb_inode_info
(brace
DECL|member|state
r_enum
id|smb_inode_state
id|state
suffix:semicolon
DECL|member|nused
r_int
id|nused
suffix:semicolon
multiline_comment|/* for directories:&n;                                   number of references in memory */
DECL|member|dir
r_struct
id|smb_inode_info
op_star
id|dir
suffix:semicolon
DECL|member|next
DECL|member|prev
r_struct
id|smb_inode_info
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|finfo
r_struct
id|smb_dirent
id|finfo
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
