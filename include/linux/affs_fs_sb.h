macro_line|#ifndef _AFFS_FS_SB
DECL|macro|_AFFS_FS_SB
mdefine_line|#define _AFFS_FS_SB
multiline_comment|/*&n; * super-block data in memory&n; *&n; * Block numbers are for FFS-sized (normally 512 bytes) blocks.&n; *&n; */
multiline_comment|/* Mount options */
DECL|struct|affs_options
r_struct
id|affs_options
(brace
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|root
r_int
id|root
suffix:semicolon
DECL|member|nocase
r_int
id|nocase
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Ignore case in filenames. */
DECL|member|conv_links
r_int
id|conv_links
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* convert pathnames symlinks point to */
)brace
suffix:semicolon
DECL|struct|affs_sb_info
r_struct
id|affs_sb_info
(brace
DECL|member|s_partition_offset
r_int
id|s_partition_offset
suffix:semicolon
multiline_comment|/* Offset to start in blocks. */
DECL|member|s_partition_size
r_int
id|s_partition_size
suffix:semicolon
multiline_comment|/* Partition size in blocks. */
DECL|member|s_root_block
r_int
id|s_root_block
suffix:semicolon
multiline_comment|/* Absolute FFS root block number. */
DECL|member|s_block_size
r_int
id|s_block_size
suffix:semicolon
multiline_comment|/* Block size in bytes. */
DECL|member|s_volume_name
r_char
id|s_volume_name
(braket
l_int|42
)braket
suffix:semicolon
DECL|member|s_options
r_struct
id|affs_options
id|s_options
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
