multiline_comment|/*&n; *  linux/fs/sysv/symlink.c&n; *&n; *  minix/symlink.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/symlink.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/symlink.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent symlink handling code&n; */
macro_line|#include &lt;linux/sysv_fs.h&gt;
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|sysv_symlink_inode_operations
r_struct
id|inode_operations
id|sysv_symlink_inode_operations
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
id|sysv_get_block
comma
id|readpage
suffix:colon
id|block_read_full_page
)brace
suffix:semicolon
eof
