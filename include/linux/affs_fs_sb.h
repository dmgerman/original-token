macro_line|#ifndef _AFFS_FS_SB
DECL|macro|_AFFS_FS_SB
mdefine_line|#define _AFFS_FS_SB
multiline_comment|/*&n; * super-block data in memory&n; *&n; * Block numbers are adjusted for their actual size&n; *&n; */
macro_line|#include &lt;linux/amigaffs.h&gt;
DECL|macro|MAX_ZONES
mdefine_line|#define MAX_ZONES&t;&t;8
DECL|macro|AFFS_DATA_MIN_FREE
mdefine_line|#define AFFS_DATA_MIN_FREE&t;30&t;/* Percentage of free blocks needed for a data zone */
DECL|macro|AFFS_HDR_MIN_FREE
mdefine_line|#define AFFS_HDR_MIN_FREE&t;10&t;/* Same for header blocks */
DECL|struct|affs_bm_info
r_struct
id|affs_bm_info
(brace
DECL|member|bm_bh
r_struct
id|buffer_head
op_star
id|bm_bh
suffix:semicolon
multiline_comment|/* Buffer for bitmap. */
DECL|member|bm_free
r_int
id|bm_free
suffix:semicolon
multiline_comment|/* Free blocks. */
DECL|member|bm_size
r_int
id|bm_size
suffix:semicolon
multiline_comment|/* Size in bits, rounded to multiple of 32. */
DECL|member|bm_firstblk
r_int
id|bm_firstblk
suffix:semicolon
multiline_comment|/* Block number of first bit in this map */
)brace
suffix:semicolon
DECL|struct|affs_zone
r_struct
id|affs_zone
(brace
DECL|member|z_ino
r_int
r_int
id|z_ino
suffix:semicolon
multiline_comment|/* Associated inode number */
DECL|member|z_bm
r_struct
id|affs_bm_info
op_star
id|z_bm
suffix:semicolon
multiline_comment|/* Zone lies in this bitmap */
DECL|member|z_start
r_int
id|z_start
suffix:semicolon
multiline_comment|/* Index of first word in bitmap */
DECL|member|z_zone_no
r_int
id|z_zone_no
suffix:semicolon
multiline_comment|/* Zone number */
DECL|member|z_lru_time
r_int
r_int
id|z_lru_time
suffix:semicolon
multiline_comment|/* Time of last usage */
)brace
suffix:semicolon
DECL|struct|affs_sb_info
r_struct
id|affs_sb_info
(brace
DECL|member|s_partition_size
r_int
id|s_partition_size
suffix:semicolon
multiline_comment|/* Partition size in blocks. */
DECL|member|s_root_block
r_int
id|s_root_block
suffix:semicolon
multiline_comment|/* FFS root block number. */
DECL|member|s_hashsize
r_int
id|s_hashsize
suffix:semicolon
multiline_comment|/* Size of hash table. */
DECL|member|s_flags
r_int
r_int
id|s_flags
suffix:semicolon
multiline_comment|/* See below. */
DECL|member|s_uid
r_int
id|s_uid
suffix:semicolon
multiline_comment|/* uid to override */
DECL|member|s_gid
r_int
id|s_gid
suffix:semicolon
multiline_comment|/* gid to override */
DECL|member|s_mode
id|umode_t
id|s_mode
suffix:semicolon
multiline_comment|/* mode to override */
DECL|member|s_reserved
r_int
id|s_reserved
suffix:semicolon
multiline_comment|/* Number of reserved blocks. */
DECL|member|s_root_bh
r_struct
id|buffer_head
op_star
id|s_root_bh
suffix:semicolon
multiline_comment|/* Cached root block. */
DECL|member|s_bitmap
r_struct
id|affs_bm_info
op_star
id|s_bitmap
suffix:semicolon
multiline_comment|/* Bitmap infos. */
DECL|member|s_bm_count
r_int
id|s_bm_count
suffix:semicolon
multiline_comment|/* Number of bitmap blocks. */
DECL|member|s_nextzone
r_int
id|s_nextzone
suffix:semicolon
multiline_comment|/* Next zone to look for free blocks. */
DECL|member|s_num_zones
r_int
id|s_num_zones
suffix:semicolon
multiline_comment|/* Total number of zones. */
DECL|member|s_zones
r_struct
id|affs_zone
op_star
id|s_zones
suffix:semicolon
multiline_comment|/* The zones themselfes. */
DECL|member|s_zonemap
r_char
op_star
id|s_zonemap
suffix:semicolon
multiline_comment|/* Bitmap for zones. */
DECL|member|s_prefix
r_char
op_star
id|s_prefix
suffix:semicolon
multiline_comment|/* Prefix for volumes and assignes. */
DECL|member|s_prefix_len
r_int
id|s_prefix_len
suffix:semicolon
multiline_comment|/* Length of prefix. */
DECL|member|s_volume
r_char
id|s_volume
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Volume prefix for absolute symlinks. */
)brace
suffix:semicolon
DECL|macro|SF_INTL
mdefine_line|#define SF_INTL&t;&t;0x0001&t;&t;/* International filesystem. */
DECL|macro|SF_BM_VALID
mdefine_line|#define SF_BM_VALID&t;0x0002&t;&t;/* Bitmap is valid. */
DECL|macro|SF_IMMUTABLE
mdefine_line|#define SF_IMMUTABLE&t;0x0004&t;&t;/* Protection bits cannot be changed */
DECL|macro|SF_QUIET
mdefine_line|#define SF_QUIET&t;0x0008&t;&t;/* chmod errors will be not reported */
DECL|macro|SF_SETUID
mdefine_line|#define SF_SETUID&t;0x0010&t;&t;/* Ignore Amiga uid */
DECL|macro|SF_SETGID
mdefine_line|#define SF_SETGID&t;0x0020&t;&t;/* Ignore Amiga gid */
DECL|macro|SF_SETMODE
mdefine_line|#define SF_SETMODE&t;0x0040&t;&t;/* Ignore Amiga protection bits */
DECL|macro|SF_USE_MP
mdefine_line|#define SF_USE_MP&t;0x0080&t;&t;/* Use uid and gid from mount point */
DECL|macro|SF_MUFS
mdefine_line|#define SF_MUFS&t;&t;0x0100&t;&t;/* Use MUFS uid/gid mapping */
DECL|macro|SF_OFS
mdefine_line|#define SF_OFS&t;&t;0x0200&t;&t;/* Old filesystem */
DECL|macro|SF_PREFIX
mdefine_line|#define SF_PREFIX&t;0x0400&t;&t;/* Buffer for prefix is allocated */
DECL|macro|SF_VERBOSE
mdefine_line|#define SF_VERBOSE&t;0x0800&t;&t;/* Talk about fs when mounting */
macro_line|#endif
eof
