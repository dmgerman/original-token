macro_line|#ifndef _MSDOS_FS_SB
DECL|macro|_MSDOS_FS_SB
mdefine_line|#define _MSDOS_FS_SB
DECL|struct|msdos_sb_info
r_struct
id|msdos_sb_info
(brace
multiline_comment|/* space in struct super_block is 28 bytes */
DECL|member|cluster_size
r_int
r_int
id|cluster_size
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|fats
DECL|member|fat_bits
r_int
r_char
id|fats
comma
id|fat_bits
suffix:semicolon
multiline_comment|/* number of FATs, FAT bits (12 or 16) */
DECL|member|fat_start
DECL|member|fat_length
r_int
r_int
id|fat_start
comma
id|fat_length
suffix:semicolon
multiline_comment|/* FAT start &amp; length (sec.) */
DECL|member|dir_start
DECL|member|dir_entries
r_int
r_int
id|dir_start
comma
id|dir_entries
suffix:semicolon
multiline_comment|/* root dir start &amp; entries */
DECL|member|data_start
r_int
r_int
id|data_start
suffix:semicolon
multiline_comment|/* first data sector */
DECL|member|clusters
r_int
r_int
id|clusters
suffix:semicolon
multiline_comment|/* number of clusters */
DECL|member|fs_uid
id|uid_t
id|fs_uid
suffix:semicolon
DECL|member|fs_gid
id|gid_t
id|fs_gid
suffix:semicolon
DECL|member|fs_umask
r_int
r_int
id|fs_umask
suffix:semicolon
DECL|member|name_check
r_int
r_char
id|name_check
suffix:semicolon
multiline_comment|/* r = relaxed, n = normal, s = strict */
DECL|member|conversion
r_int
r_char
id|conversion
suffix:semicolon
multiline_comment|/* b = binary, t = text, a = auto */
)brace
suffix:semicolon
macro_line|#endif
eof
