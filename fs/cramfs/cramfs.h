macro_line|#ifndef __CRAMFS_H
DECL|macro|__CRAMFS_H
mdefine_line|#define __CRAMFS_H
DECL|macro|CRAMFS_MAGIC
mdefine_line|#define CRAMFS_MAGIC&t;&t;0x28cd3d45&t;/* some random number */
DECL|macro|CRAMFS_SIGNATURE
mdefine_line|#define CRAMFS_SIGNATURE&t;&quot;Compressed ROMFS&quot;
multiline_comment|/*&n; * Reasonably terse representation of the inode&n; * data.. When the mode of the inode indicates&n; * a special device node, the &quot;offset&quot; bits will&n; * encode i_rdev. In other cases, &quot;offset&quot; points&n; * to the ROM image for the actual file data&n; * (whether that data be directory or compressed&n; * file data depends on the inode type again)&n; */
DECL|struct|cramfs_inode
r_struct
id|cramfs_inode
(brace
DECL|member|mode
DECL|member|uid
id|u32
id|mode
suffix:colon
l_int|16
comma
id|uid
suffix:colon
l_int|16
suffix:semicolon
DECL|member|size
DECL|member|gid
id|u32
id|size
suffix:colon
l_int|24
comma
id|gid
suffix:colon
l_int|8
suffix:semicolon
DECL|member|namelen
DECL|member|offset
id|u32
id|namelen
suffix:colon
l_int|6
comma
id|offset
suffix:colon
l_int|26
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Superblock information at the beginning of the FS.&n; */
DECL|struct|cramfs_super
r_struct
id|cramfs_super
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* 0x28cd3d45 - random number */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* &gt; offset, &lt; 2**26 */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|future
id|u32
id|future
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|signature
id|u8
id|signature
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* &quot;Compressed ROMFS&quot; */
DECL|member|fsid
id|u8
id|fsid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* random number */
DECL|member|name
id|u8
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* user-defined name */
DECL|member|root
r_struct
id|cramfs_inode
id|root
suffix:semicolon
multiline_comment|/* Root inode data */
)brace
suffix:semicolon
multiline_comment|/* Uncompression interfaces to the underlying zlib */
r_int
id|cramfs_uncompress_block
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|dstlen
comma
r_void
op_star
id|src
comma
r_int
id|srclen
)paren
suffix:semicolon
r_int
id|cramfs_uncompress_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|cramfs_uncompress_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
