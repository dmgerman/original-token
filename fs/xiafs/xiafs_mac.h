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
multiline_comment|/* Use the most significant bytes of zone pointers to store block counter. */
multiline_comment|/* This is ugly, but it works. Note, We have another 7 bytes for &quot;expansion&quot;. */
DECL|macro|XIAFS_GET_BLOCKS
mdefine_line|#define XIAFS_GET_BLOCKS(row_ip, blocks)  &bslash;&n;  blocks=((((row_ip)-&gt;i_zone[0] &gt;&gt; 24) &amp; 0xff )|&bslash;&n;&t;  (((row_ip)-&gt;i_zone[1] &gt;&gt; 16) &amp; 0xff00 )|&bslash;&n;&t;  (((row_ip)-&gt;i_zone[2] &gt;&gt;  8) &amp; 0xff0000 ) )
multiline_comment|/* XIAFS_PUT_BLOCKS should be called before saving zone pointers */
DECL|macro|XIAFS_PUT_BLOCKS
mdefine_line|#define XIAFS_PUT_BLOCKS(row_ip, blocks)  &bslash;&n;  (row_ip)-&gt;i_zone[2]=((blocks)&lt;&lt; 8) &amp; 0xff000000;&bslash;&n;  (row_ip)-&gt;i_zone[1]=((blocks)&lt;&lt;16) &amp; 0xff000000;&bslash;&n;  (row_ip)-&gt;i_zone[0]=((blocks)&lt;&lt;24) &amp; 0xff000000
eof
