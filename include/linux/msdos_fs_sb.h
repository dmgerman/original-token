macro_line|#ifndef _MSDOS_FS_SB
DECL|macro|_MSDOS_FS_SB
mdefine_line|#define _MSDOS_FS_SB
multiline_comment|/*&n; * MS-DOS file system in-core superblock data&n; */
DECL|struct|msdos_sb_info
r_struct
id|msdos_sb_info
(brace
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
DECL|member|quiet
r_int
id|quiet
suffix:semicolon
multiline_comment|/* fake successful chmods and chowns */
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
DECL|member|fat_wait
r_struct
id|wait_queue
op_star
id|fat_wait
suffix:semicolon
DECL|member|fat_lock
r_int
id|fat_lock
suffix:semicolon
DECL|member|prev_free
r_int
id|prev_free
suffix:semicolon
multiline_comment|/* previously returned free cluster number */
DECL|member|free_clusters
r_int
id|free_clusters
suffix:semicolon
multiline_comment|/* -1 if undefined */
DECL|member|dotsOK
r_char
id|dotsOK
suffix:semicolon
DECL|member|showexec
r_char
id|showexec
suffix:semicolon
multiline_comment|/* 1 = only set x bit for com/exe/bat */
DECL|member|sys_immutable
r_char
id|sys_immutable
suffix:semicolon
multiline_comment|/* system files are immutable */
DECL|member|vfat
r_int
id|vfat
suffix:semicolon
multiline_comment|/* 0=no vfat long filename support, 1=vfat support */
DECL|member|umsdos
r_int
id|umsdos
suffix:semicolon
multiline_comment|/* 1 if mounted by umsdos, 0 if not */
)brace
suffix:semicolon
macro_line|#endif
eof
