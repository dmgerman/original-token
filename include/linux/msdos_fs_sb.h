macro_line|#ifndef _MSDOS_FS_SB
DECL|macro|_MSDOS_FS_SB
mdefine_line|#define _MSDOS_FS_SB
multiline_comment|/*&n; * MS-DOS file system in-core superblock data&n; */
DECL|struct|fat_mount_options
r_struct
id|fat_mount_options
(brace
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
DECL|member|quiet
r_int
id|quiet
suffix:colon
l_int|1
comma
multiline_comment|/* set = fake successful chmods and chowns */
DECL|member|showexec
id|showexec
suffix:colon
l_int|1
comma
multiline_comment|/* set = only set x bit for com/exe/bat */
DECL|member|sys_immutable
id|sys_immutable
suffix:colon
l_int|1
comma
multiline_comment|/* set = system files are immutable */
DECL|member|dotsOK
id|dotsOK
suffix:colon
l_int|1
comma
multiline_comment|/* set = hidden and system files are named &squot;.filename&squot; */
DECL|member|isvfat
id|isvfat
suffix:colon
l_int|1
comma
multiline_comment|/* 0=no vfat long filename support, 1=vfat support */
DECL|member|unicode_xlate
id|unicode_xlate
suffix:colon
l_int|1
comma
multiline_comment|/* create escape sequences for unhandled Unicode */
DECL|member|posixfs
id|posixfs
suffix:colon
l_int|1
comma
multiline_comment|/* Allow names like makefile and Makefile to coexist */
DECL|member|numtail
id|numtail
suffix:colon
l_int|1
comma
multiline_comment|/* Does first alias have a numeric &squot;~1&squot; type tail? */
DECL|member|atari
id|atari
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Use Atari GEMDOS variation of MS-DOS fs */
)brace
suffix:semicolon
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
DECL|member|options
r_struct
id|fat_mount_options
id|options
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
