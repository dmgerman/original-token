macro_line|#ifndef _MINIX_FS_SB
DECL|macro|_MINIX_FS_SB
mdefine_line|#define _MINIX_FS_SB
multiline_comment|/*&n; * minix super-block data in memory&n; */
DECL|struct|minix_sb_info
r_struct
id|minix_sb_info
(brace
DECL|member|s_ninodes
r_int
r_int
id|s_ninodes
suffix:semicolon
DECL|member|s_nzones
r_int
r_int
id|s_nzones
suffix:semicolon
DECL|member|s_imap_blocks
r_int
r_int
id|s_imap_blocks
suffix:semicolon
DECL|member|s_zmap_blocks
r_int
r_int
id|s_zmap_blocks
suffix:semicolon
DECL|member|s_firstdatazone
r_int
r_int
id|s_firstdatazone
suffix:semicolon
DECL|member|s_log_zone_size
r_int
r_int
id|s_log_zone_size
suffix:semicolon
DECL|member|s_max_size
r_int
r_int
id|s_max_size
suffix:semicolon
DECL|member|s_imap
r_struct
id|buffer_head
op_star
id|s_imap
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|s_zmap
r_struct
id|buffer_head
op_star
id|s_zmap
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
