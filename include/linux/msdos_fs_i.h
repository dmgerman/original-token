macro_line|#ifndef _MSDOS_FS_I
DECL|macro|_MSDOS_FS_I
mdefine_line|#define _MSDOS_FS_I
multiline_comment|/*&n; * msdos file system inode data in memory&n; */
DECL|struct|msdos_inode_info
r_struct
id|msdos_inode_info
(brace
DECL|member|i_start
r_int
id|i_start
suffix:semicolon
multiline_comment|/* first cluster or 0 */
DECL|member|i_attrs
r_int
id|i_attrs
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_busy
r_int
id|i_busy
suffix:semicolon
multiline_comment|/* file is either deleted but still open, or&n;&t;&t;&t;   inconsistent (mkdir) */
DECL|member|i_depend
r_struct
id|inode
op_star
id|i_depend
suffix:semicolon
multiline_comment|/* pointer to inode that depends on the&n;&t;&t;&t;&t;   current inode */
DECL|member|i_old
r_struct
id|inode
op_star
id|i_old
suffix:semicolon
multiline_comment|/* pointer to the old inode this inode&n;&t;&t;&t;&t;   depends on */
DECL|member|i_binary
r_int
id|i_binary
suffix:semicolon
multiline_comment|/* file contains non-text data */
)brace
suffix:semicolon
macro_line|#endif
eof
