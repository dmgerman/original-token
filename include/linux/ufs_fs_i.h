multiline_comment|/*&n; *  linux/include/linux/ufs_fs_i.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_fs_i.h,v 1.2 1996/05/03 04:02:25 davem Exp $&n; *&n; */
macro_line|#ifndef _LINUX_UFS_FS_I_H
DECL|macro|_LINUX_UFS_FS_I_H
mdefine_line|#define _LINUX_UFS_FS_I_H
DECL|struct|ufs_inode_info
r_struct
id|ufs_inode_info
(brace
DECL|member|i_data
id|__u32
id|i_data
(braket
l_int|15
)braket
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
DECL|member|i_uid
id|__u32
id|i_uid
suffix:semicolon
DECL|member|i_gid
id|__u32
id|i_gid
suffix:semicolon
DECL|member|i_oeftflag
id|__u32
id|i_oeftflag
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_UFS_FS_I_H */
eof
