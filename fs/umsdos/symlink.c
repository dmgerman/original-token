multiline_comment|/*&n; *  linux/fs/umsdos/file.c&n; *&n; *  Written 1992 by Jacques Gelinas&n; *      inspired from linux/fs/msdos/file.c Werner Almesberger&n; *&n; *  Extended MS-DOS regular file handling primitives&n; *&n; *  Wow. It looks like we could support them on FAT with little (if any)&n; *  problems. Oh, well...&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
DECL|variable|umsdos_symlink_inode_operations
r_struct
id|inode_operations
id|umsdos_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|page_readlink
comma
id|follow_link
suffix:colon
id|page_follow_link
comma
id|get_block
suffix:colon
id|fat_get_block
comma
id|readpage
suffix:colon
id|block_read_full_page
)brace
suffix:semicolon
eof
