multiline_comment|/*&n; *  linux/fs/xiafs/xiafs_mac.h&n; *&n; *  Copyright (C) Q. Frank Xia, 1993.&n; */
r_extern
r_char
id|internal_error_message
(braket
)braket
suffix:semicolon
DECL|macro|INTERN_ERR
mdefine_line|#define INTERN_ERR&t;&t;internal_error_message, __FILE__, __LINE__
DECL|macro|WHERE_ERR
mdefine_line|#define WHERE_ERR&t;&t;__FILE__, __LINE__
DECL|macro|XIAFS_ZSHIFT
mdefine_line|#define XIAFS_ZSHIFT(sp)&t;&t;((sp)-&gt;u.xiafs_sb.s_zone_shift)
DECL|macro|XIAFS_ZSIZE
mdefine_line|#define XIAFS_ZSIZE(sp)&t;&t;(BLOCK_SIZE &lt;&lt; XIAFS_ZSHIFT(sp))
DECL|macro|XIAFS_ZSIZE_BITS
mdefine_line|#define XIAFS_ZSIZE_BITS(sp)&t;(BLOCK_SIZE_BITS + XIAFS_ZSHIFT(sp))
DECL|macro|XIAFS_ADDRS_PER_Z
mdefine_line|#define XIAFS_ADDRS_PER_Z(sp)   &t;(BLOCK_SIZE &gt;&gt; (2 - XIAFS_ZSHIFT(sp)))
DECL|macro|XIAFS_ADDRS_PER_Z_BITS
mdefine_line|#define XIAFS_ADDRS_PER_Z_BITS(sp) &t;(BLOCK_SIZE_BITS - 2 + XIAFS_ZSHIFT(sp))
DECL|macro|XIAFS_BITS_PER_Z
mdefine_line|#define XIAFS_BITS_PER_Z(sp)&t;(BLOCK_SIZE  &lt;&lt; (3 + XIAFS_ZSHIFT(sp)))
DECL|macro|XIAFS_BITS_PER_Z_BITS
mdefine_line|#define XIAFS_BITS_PER_Z_BITS(sp)&t;(BLOCK_SIZE_BITS + 3 + XIAFS_ZSHIFT(sp))
DECL|macro|XIAFS_INODES_PER_Z
mdefine_line|#define XIAFS_INODES_PER_Z(sp)&t;(_XIAFS_INODES_PER_BLOCK &lt;&lt; XIAFS_ZSHIFT(sp))
eof
