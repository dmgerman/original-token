macro_line|#ifndef _XIA_FS_SB_H
DECL|macro|_XIA_FS_SB_H
mdefine_line|#define _XIA_FS_SB_H
multiline_comment|/*&n; * include/linux/xia_fs_sb.h&n; *&n; * Copyright (C) Q. Frank Xia, 1993.&n; *&n; * Based on Linus&squot; minix_fs_sb.h.&n; * Copyright (C) Linus Torvalds, 1991, 1992.&n; */
DECL|macro|_XIAFS_IMAP_SLOTS
mdefine_line|#define _XIAFS_IMAP_SLOTS 8
DECL|macro|_XIAFS_ZMAP_SLOTS
mdefine_line|#define _XIAFS_ZMAP_SLOTS 32
DECL|struct|xiafs_sb_info
r_struct
id|xiafs_sb_info
(brace
DECL|member|s_nzones
id|u_long
id|s_nzones
suffix:semicolon
DECL|member|s_ninodes
id|u_long
id|s_ninodes
suffix:semicolon
DECL|member|s_ndatazones
id|u_long
id|s_ndatazones
suffix:semicolon
DECL|member|s_imap_zones
id|u_long
id|s_imap_zones
suffix:semicolon
DECL|member|s_zmap_zones
id|u_long
id|s_zmap_zones
suffix:semicolon
DECL|member|s_firstdatazone
id|u_long
id|s_firstdatazone
suffix:semicolon
DECL|member|s_zone_shift
id|u_long
id|s_zone_shift
suffix:semicolon
DECL|member|s_max_size
id|u_long
id|s_max_size
suffix:semicolon
multiline_comment|/*  32 bytes */
DECL|member|s_imap_buf
r_struct
id|buffer_head
op_star
id|s_imap_buf
(braket
id|_XIAFS_IMAP_SLOTS
)braket
suffix:semicolon
multiline_comment|/*  32 bytes */
DECL|member|s_zmap_buf
r_struct
id|buffer_head
op_star
id|s_zmap_buf
(braket
id|_XIAFS_ZMAP_SLOTS
)braket
suffix:semicolon
multiline_comment|/* 128 bytes */
DECL|member|s_imap_iznr
r_int
id|s_imap_iznr
(braket
id|_XIAFS_IMAP_SLOTS
)braket
suffix:semicolon
multiline_comment|/*  32 bytes */
DECL|member|s_zmap_zznr
r_int
id|s_zmap_zznr
(braket
id|_XIAFS_ZMAP_SLOTS
)braket
suffix:semicolon
multiline_comment|/* 128 bytes */
DECL|member|s_imap_cached
id|u_char
id|s_imap_cached
suffix:semicolon
multiline_comment|/* flag for cached imap */
DECL|member|s_zmap_cached
id|u_char
id|s_zmap_cached
suffix:semicolon
multiline_comment|/* flag for cached imap */
)brace
suffix:semicolon
macro_line|#endif /* _XIA_FS_SB_H */
eof
