macro_line|#ifndef _XIA_FS_I_H
DECL|macro|_XIA_FS_I_H
mdefine_line|#define _XIA_FS_I_H
multiline_comment|/*&n; * include/linux/xia_fs_i.h&n; *&n; * Copyright (C) Q. Frank Xia, 1993.&n; * &n; * Based on Linus&squot; minix_fs_i.h.&n; * Copyright (C) Linus Torvalds, 1991, 1992.&n; */
DECL|struct|xiafs_inode_info
r_struct
id|xiafs_inode_info
(brace
multiline_comment|/* for data zone pointers */
DECL|member|i_zone
r_int
r_int
id|i_zone
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|i_ind_zone
r_int
r_int
id|i_ind_zone
suffix:semicolon
DECL|member|i_dind_zone
r_int
r_int
id|i_dind_zone
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif  /* _XIA_FS_I_H */
eof
