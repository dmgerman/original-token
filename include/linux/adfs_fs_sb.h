multiline_comment|/*&n; *  linux/include/linux/adfs_fs_sb.h&n; *&n; * Copyright (C) 1997 Russell King&n; */
macro_line|#ifndef _ADFS_FS_SB
DECL|macro|_ADFS_FS_SB
mdefine_line|#define _ADFS_FS_SB
macro_line|#include &lt;linux/adfs_fs.h&gt;
multiline_comment|/*&n; * adfs file system superblock data in memory&n; */
DECL|struct|adfs_sb_info
r_struct
id|adfs_sb_info
(brace
DECL|member|s_sbh
r_struct
id|buffer_head
op_star
id|s_sbh
suffix:semicolon
multiline_comment|/* buffer head containing disc record&t; */
DECL|member|s_dr
r_struct
id|adfs_discrecord
op_star
id|s_dr
suffix:semicolon
multiline_comment|/* pointer to disc record in s_sbh&t; */
DECL|member|s_zone_size
id|__u16
id|s_zone_size
suffix:semicolon
multiline_comment|/* size of a map zone in bits&t;&t; */
DECL|member|s_ids_per_zone
id|__u16
id|s_ids_per_zone
suffix:semicolon
multiline_comment|/* max. no ids in one zone&t;&t; */
DECL|member|s_idlen
id|__u32
id|s_idlen
suffix:semicolon
multiline_comment|/* length of ID in map&t;&t;&t; */
DECL|member|s_map_size
id|__u32
id|s_map_size
suffix:semicolon
multiline_comment|/* size of a map&t;&t;&t; */
DECL|member|s_zonesize
id|__u32
id|s_zonesize
suffix:semicolon
multiline_comment|/* zone size (in map bits)&t;&t; */
DECL|member|s_map_block
id|__u32
id|s_map_block
suffix:semicolon
multiline_comment|/* block address of map&t;&t;&t; */
DECL|member|s_map
r_struct
id|buffer_head
op_star
op_star
id|s_map
suffix:semicolon
multiline_comment|/* bh list containing map&t;&t; */
DECL|member|s_root
id|__u32
id|s_root
suffix:semicolon
multiline_comment|/* root disc address&t;&t;&t; */
DECL|member|s_map2blk
id|__s8
id|s_map2blk
suffix:semicolon
multiline_comment|/* shift left by this for map-&gt;sector&t; */
)brace
suffix:semicolon
macro_line|#endif
eof
