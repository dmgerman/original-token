multiline_comment|/*&n; *  linux/include/linux/ufs_fs_i.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_fs_i.h,v 1.1 1996/04/21 14:45:13 davem Exp $&n; *&n; */
macro_line|#ifndef _LINUX_UFS_FS_I_H
DECL|macro|_LINUX_UFS_FS_I_H
mdefine_line|#define _LINUX_UFS_FS_I_H
macro_line|#include &lt;linux/ufs_fs.h&gt;
DECL|struct|ufs_inode_info
r_struct
id|ufs_inode_info
(brace
DECL|member|ui_size
id|__u64
id|ui_size
suffix:semicolon
DECL|member|ui_flags
id|__u32
id|ui_flags
suffix:semicolon
DECL|member|ui_gen
id|__u32
id|ui_gen
suffix:semicolon
DECL|member|ui_shadow
id|__u32
id|ui_shadow
suffix:semicolon
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
DECL|member|ui_oeftflag
id|__u32
id|ui_oeftflag
suffix:semicolon
DECL|member|ui_db
id|__u32
id|ui_db
(braket
id|UFS_NDADDR
)braket
suffix:semicolon
DECL|member|ui_ib
id|__u32
id|ui_ib
(braket
id|UFS_NINDIR
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_UFS_FS_I_H */
eof
