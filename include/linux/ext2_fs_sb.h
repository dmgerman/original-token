macro_line|#ifndef _EXT2_FS_SB
DECL|macro|_EXT2_FS_SB
mdefine_line|#define _EXT2_FS_SB
DECL|macro|EXT2_MAX_GROUP_DESC
mdefine_line|#define EXT2_MAX_GROUP_DESC&t;4
DECL|macro|EXT2_MAX_GROUP_LOADED
mdefine_line|#define EXT2_MAX_GROUP_LOADED&t;8
multiline_comment|/*&n; * second extended-fs super-block data in memory&n; */
DECL|struct|ext2_sb_info
r_struct
id|ext2_sb_info
(brace
DECL|member|s_inodes_count
r_int
r_int
id|s_inodes_count
suffix:semicolon
multiline_comment|/* Inodes count */
DECL|member|s_blocks_count
r_int
r_int
id|s_blocks_count
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|s_r_blocks_count
r_int
r_int
id|s_r_blocks_count
suffix:semicolon
multiline_comment|/* Reserved blocks count */
DECL|member|s_first_data_block
r_int
r_int
id|s_first_data_block
suffix:semicolon
multiline_comment|/* First data block */
DECL|member|s_log_block_size
r_int
r_int
id|s_log_block_size
suffix:semicolon
multiline_comment|/* Log of block size */
DECL|member|s_log_frag_size
r_int
id|s_log_frag_size
suffix:semicolon
multiline_comment|/* Log of fragment size */
DECL|member|s_frag_size
r_int
r_int
id|s_frag_size
suffix:semicolon
multiline_comment|/* Size of a fragment in bytes */
DECL|member|s_frags_per_block
r_int
r_int
id|s_frags_per_block
suffix:semicolon
multiline_comment|/* Number of fragments per block */
DECL|member|s_inodes_per_block
r_int
r_int
id|s_inodes_per_block
suffix:semicolon
multiline_comment|/* Number of inodes per block */
DECL|member|s_frags_per_group
r_int
r_int
id|s_frags_per_group
suffix:semicolon
multiline_comment|/* Number of fragments in a group */
DECL|member|s_blocks_per_group
r_int
r_int
id|s_blocks_per_group
suffix:semicolon
multiline_comment|/* Number of blocks in a group */
DECL|member|s_inodes_per_group
r_int
r_int
id|s_inodes_per_group
suffix:semicolon
multiline_comment|/* Number of inodes in a group */
DECL|member|s_desc_per_block
r_int
r_int
id|s_desc_per_block
suffix:semicolon
multiline_comment|/* Number of group descriptors per block */
DECL|member|s_groups_count
r_int
r_int
id|s_groups_count
suffix:semicolon
multiline_comment|/* Number of groups in the fs */
DECL|member|s_sbh
r_struct
id|buffer_head
op_star
id|s_sbh
suffix:semicolon
multiline_comment|/* Buffer containing the super block */
DECL|member|s_group_desc
r_struct
id|buffer_head
op_star
id|s_group_desc
(braket
id|EXT2_MAX_GROUP_DESC
)braket
suffix:semicolon
DECL|member|s_loaded_inode_bitmaps
r_int
r_int
id|s_loaded_inode_bitmaps
suffix:semicolon
DECL|member|s_loaded_block_bitmaps
r_int
r_int
id|s_loaded_block_bitmaps
suffix:semicolon
DECL|member|s_inode_bitmap_number
r_int
r_int
id|s_inode_bitmap_number
(braket
id|EXT2_MAX_GROUP_LOADED
)braket
suffix:semicolon
DECL|member|s_inode_bitmap
r_struct
id|buffer_head
op_star
id|s_inode_bitmap
(braket
id|EXT2_MAX_GROUP_LOADED
)braket
suffix:semicolon
DECL|member|s_block_bitmap_number
r_int
r_int
id|s_block_bitmap_number
(braket
id|EXT2_MAX_GROUP_LOADED
)braket
suffix:semicolon
DECL|member|s_block_bitmap
r_struct
id|buffer_head
op_star
id|s_block_bitmap
(braket
id|EXT2_MAX_GROUP_LOADED
)braket
suffix:semicolon
DECL|member|s_rename_lock
r_int
id|s_rename_lock
suffix:semicolon
DECL|member|s_was_mounted_valid
r_int
id|s_was_mounted_valid
suffix:semicolon
DECL|member|s_rename_wait
r_struct
id|wait_queue
op_star
id|s_rename_wait
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
