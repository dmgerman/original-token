macro_line|#ifndef _HPFS_FS_SB
DECL|macro|_HPFS_FS_SB
mdefine_line|#define _HPFS_FS_SB
DECL|struct|hpfs_sb_info
r_struct
id|hpfs_sb_info
(brace
DECL|member|sb_root
id|ino_t
id|sb_root
suffix:semicolon
multiline_comment|/* inode number of root dir */
DECL|member|sb_fs_size
r_int
id|sb_fs_size
suffix:semicolon
multiline_comment|/* file system size, sectors */
DECL|member|sb_bitmaps
r_int
id|sb_bitmaps
suffix:semicolon
multiline_comment|/* sector number of bitmap list */
DECL|member|sb_dirband_size
r_int
id|sb_dirband_size
suffix:semicolon
multiline_comment|/* directory band size, dnodes */
DECL|member|sb_dmap
r_int
id|sb_dmap
suffix:semicolon
multiline_comment|/* sector number of dnode bit map */
DECL|member|sb_n_free
r_int
id|sb_n_free
suffix:semicolon
multiline_comment|/* free blocks for statfs, or -1 */
DECL|member|sb_n_free_dnodes
r_int
id|sb_n_free_dnodes
suffix:semicolon
multiline_comment|/* free dnodes for statfs, or -1 */
DECL|member|sb_uid
id|uid_t
id|sb_uid
suffix:semicolon
multiline_comment|/* uid from mount options */
DECL|member|sb_gid
id|gid_t
id|sb_gid
suffix:semicolon
multiline_comment|/* gid from mount options */
DECL|member|sb_mode
id|umode_t
id|sb_mode
suffix:semicolon
multiline_comment|/* mode from mount options */
DECL|member|sb_lowercase
r_int
id|sb_lowercase
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* downcase filenames hackery */
DECL|member|sb_conv
r_int
id|sb_conv
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* crlf-&gt;newline hackery */
)brace
suffix:semicolon
DECL|macro|s_hpfs_root
mdefine_line|#define s_hpfs_root u.hpfs_sb.sb_root
DECL|macro|s_hpfs_fs_size
mdefine_line|#define s_hpfs_fs_size u.hpfs_sb.sb_fs_size
DECL|macro|s_hpfs_bitmaps
mdefine_line|#define s_hpfs_bitmaps u.hpfs_sb.sb_bitmaps
DECL|macro|s_hpfs_dirband_size
mdefine_line|#define s_hpfs_dirband_size u.hpfs_sb.sb_dirband_size
DECL|macro|s_hpfs_dmap
mdefine_line|#define s_hpfs_dmap u.hpfs_sb.sb_dmap
DECL|macro|s_hpfs_uid
mdefine_line|#define s_hpfs_uid u.hpfs_sb.sb_uid
DECL|macro|s_hpfs_gid
mdefine_line|#define s_hpfs_gid u.hpfs_sb.sb_gid
DECL|macro|s_hpfs_mode
mdefine_line|#define s_hpfs_mode u.hpfs_sb.sb_mode
DECL|macro|s_hpfs_n_free
mdefine_line|#define s_hpfs_n_free u.hpfs_sb.sb_n_free
DECL|macro|s_hpfs_n_free_dnodes
mdefine_line|#define s_hpfs_n_free_dnodes u.hpfs_sb.sb_n_free_dnodes
DECL|macro|s_hpfs_lowercase
mdefine_line|#define s_hpfs_lowercase u.hpfs_sb.sb_lowercase
DECL|macro|s_hpfs_conv
mdefine_line|#define s_hpfs_conv u.hpfs_sb.sb_conv
macro_line|#endif
eof
