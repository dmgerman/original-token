macro_line|#ifndef _HPFS_FS_I
DECL|macro|_HPFS_FS_I
mdefine_line|#define _HPFS_FS_I
DECL|struct|hpfs_inode_info
r_struct
id|hpfs_inode_info
(brace
DECL|member|i_parent_dir
id|ino_t
id|i_parent_dir
suffix:semicolon
multiline_comment|/* (directories) gives fnode of parent dir */
DECL|member|i_dno
r_int
id|i_dno
suffix:semicolon
multiline_comment|/* (directories) root dnode */
DECL|member|i_dpos
r_int
id|i_dpos
suffix:semicolon
multiline_comment|/* (directories) temp for readdir */
DECL|member|i_dsubdno
r_int
id|i_dsubdno
suffix:semicolon
multiline_comment|/* (directories) temp for readdir */
DECL|member|i_file_sec
r_int
id|i_file_sec
suffix:semicolon
multiline_comment|/* (files) minimalist cache of alloc info */
DECL|member|i_disk_sec
r_int
id|i_disk_sec
suffix:semicolon
multiline_comment|/* (files) minimalist cache of alloc info */
DECL|member|i_n_secs
r_int
id|i_n_secs
suffix:semicolon
multiline_comment|/* (files) minimalist cache of alloc info */
DECL|member|i_conv
r_int
id|i_conv
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* (files) crlf-&gt;newline hackery */
)brace
suffix:semicolon
DECL|macro|i_hpfs_dno
mdefine_line|#define i_hpfs_dno u.hpfs_i.i_dno
DECL|macro|i_hpfs_parent_dir
mdefine_line|#define i_hpfs_parent_dir u.hpfs_i.i_parent_dir
DECL|macro|i_hpfs_n_secs
mdefine_line|#define i_hpfs_n_secs u.hpfs_i.i_n_secs
DECL|macro|i_hpfs_file_sec
mdefine_line|#define i_hpfs_file_sec u.hpfs_i.i_file_sec
DECL|macro|i_hpfs_disk_sec
mdefine_line|#define i_hpfs_disk_sec u.hpfs_i.i_disk_sec
DECL|macro|i_hpfs_dpos
mdefine_line|#define i_hpfs_dpos u.hpfs_i.i_dpos
DECL|macro|i_hpfs_dsubdno
mdefine_line|#define i_hpfs_dsubdno u.hpfs_i.i_dsubdno
DECL|macro|i_hpfs_conv
mdefine_line|#define i_hpfs_conv u.hpfs_i.i_conv
macro_line|#endif
eof
