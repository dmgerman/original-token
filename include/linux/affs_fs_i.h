macro_line|#ifndef _AFFS_FS_I
DECL|macro|_AFFS_FS_I
mdefine_line|#define _AFFS_FS_I
DECL|macro|EXT_CACHE_SIZE
mdefine_line|#define EXT_CACHE_SIZE&t;16
DECL|macro|MAX_PREALLOC
mdefine_line|#define MAX_PREALLOC&t;8&t;/* MUST be a power of 2 */
multiline_comment|/*&n; * affs fs inode data in memory&n; */
DECL|struct|affs_inode_info
r_struct
id|affs_inode_info
(brace
DECL|member|i_protect
r_int
id|i_protect
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_parent
r_int
id|i_parent
suffix:semicolon
multiline_comment|/* parent ino */
DECL|member|i_original
r_int
id|i_original
suffix:semicolon
multiline_comment|/* if != 0, this is the key of the original */
DECL|member|i_ext
id|__u32
id|i_ext
(braket
id|EXT_CACHE_SIZE
)braket
suffix:semicolon
multiline_comment|/* extension block numbers */
DECL|member|i_data
id|__u32
id|i_data
(braket
id|MAX_PREALLOC
)braket
suffix:semicolon
multiline_comment|/* preallocated blocks */
DECL|member|i_max_ext
r_int
id|i_max_ext
suffix:semicolon
multiline_comment|/* last known extension block */
DECL|member|i_pa_cnt
r_int
id|i_pa_cnt
suffix:semicolon
multiline_comment|/* number of preallocated blocks */
DECL|member|i_pa_next
r_int
id|i_pa_next
suffix:semicolon
multiline_comment|/* Index of next block in i_data[] */
DECL|member|i_pa_last
r_int
id|i_pa_last
suffix:semicolon
multiline_comment|/* Index of next free slot in i_data[] */
DECL|member|i_zone
r_int
id|i_zone
suffix:semicolon
multiline_comment|/* write zone */
DECL|member|i_hlink
r_int
r_char
id|i_hlink
suffix:semicolon
multiline_comment|/* This is a fake */
DECL|member|i_pad
r_int
r_char
id|i_pad
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
