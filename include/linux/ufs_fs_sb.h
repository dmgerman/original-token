multiline_comment|/*&n; *  linux/include/linux/ufs_fs_sb.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_fs_sb.h,v 1.1 1996/04/21 14:45:15 davem Exp $&n; *&n; */
macro_line|#ifndef __LINUX_UFS_FS_SB_H
DECL|macro|__LINUX_UFS_FS_SB_H
mdefine_line|#define __LINUX_UFS_FS_SB_H
DECL|struct|ufs_sb_info
r_struct
id|ufs_sb_info
(brace
DECL|member|s_raw_sb
r_struct
id|ufs_superblock
op_star
id|s_raw_sb
suffix:semicolon
DECL|member|s_flags
id|__u32
id|s_flags
suffix:semicolon
multiline_comment|/* internal flags for UFS code */
DECL|member|s_ncg
id|__u32
id|s_ncg
suffix:semicolon
multiline_comment|/* used in ufs_read_inode */
DECL|member|s_ipg
id|__u32
id|s_ipg
suffix:semicolon
multiline_comment|/* used in ufs_read_inode */
DECL|member|s_fpg
id|__u32
id|s_fpg
suffix:semicolon
DECL|member|s_fsize
id|__u32
id|s_fsize
suffix:semicolon
DECL|member|s_bsize
id|__u32
id|s_bsize
suffix:semicolon
DECL|member|s_iblkno
id|__u32
id|s_iblkno
suffix:semicolon
DECL|member|s_dblkno
id|__u32
id|s_dblkno
suffix:semicolon
DECL|member|s_cgoffset
id|__u32
id|s_cgoffset
suffix:semicolon
DECL|member|s_cgmask
id|__u32
id|s_cgmask
suffix:semicolon
DECL|member|s_inopb
id|__u32
id|s_inopb
suffix:semicolon
DECL|member|s_fsfrag
id|__u32
id|s_fsfrag
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_UFS_FS_SB_H */
multiline_comment|/*&n; * Local Variables: ***&n; * c-indent-level: 8 ***&n; * c-continued-statement-offset: 8 ***&n; * c-brace-offset: -8 ***&n; * c-argdecl-indent: 0 ***&n; * c-label-offset: -8 ***&n; * End: ***&n; */
eof