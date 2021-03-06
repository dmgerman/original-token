multiline_comment|/*&n; *  linux/include/linux/ufs_fs_i.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * NeXTstep support added on February 5th 1998 by&n; * Niels Kristian Bech Jensen &lt;nkbj@image.dk&gt;.&n; */
macro_line|#ifndef _LINUX_UFS_FS_I_H
DECL|macro|_LINUX_UFS_FS_I_H
mdefine_line|#define _LINUX_UFS_FS_I_H
DECL|struct|ufs_inode_info
r_struct
id|ufs_inode_info
(brace
r_union
(brace
DECL|member|i_data
id|__u32
id|i_data
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|i_symlink
id|__u8
id|i_symlink
(braket
l_int|4
op_star
l_int|15
)braket
suffix:semicolon
DECL|member|i_u1
)brace
id|i_u1
suffix:semicolon
DECL|member|i_size
id|__u64
id|i_size
suffix:semicolon
DECL|member|i_flags
id|__u32
id|i_flags
suffix:semicolon
DECL|member|i_gen
id|__u32
id|i_gen
suffix:semicolon
DECL|member|i_shadow
id|__u32
id|i_shadow
suffix:semicolon
DECL|member|i_unused1
id|__u32
id|i_unused1
suffix:semicolon
DECL|member|i_unused2
id|__u32
id|i_unused2
suffix:semicolon
DECL|member|i_oeftflag
id|__u32
id|i_oeftflag
suffix:semicolon
DECL|member|i_osync
id|__u16
id|i_osync
suffix:semicolon
DECL|member|i_lastfrag
id|__u32
id|i_lastfrag
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_UFS_FS_I_H */
eof
