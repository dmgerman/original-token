multiline_comment|/*&n; *  linux/fs/minix/symlink.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  minix symlink handling code&n; *&n; *  Code removed. 1999, AV ;-)&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|minix_symlink_inode_operations
r_struct
id|inode_operations
id|minix_symlink_inode_operations
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
id|minix_get_block
comma
id|readpage
suffix:colon
id|block_read_full_page
)brace
suffix:semicolon
eof
