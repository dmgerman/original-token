multiline_comment|/*&n; *  linux/fs/isofs/symlink.c&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO 9660 filesystem.&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  isofs symlink handling code.  This is only used with the Rock Ridge&n; *  extensions to iso9660&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|isofs_symlink_inode_operations
r_struct
id|inode_operations
id|isofs_symlink_inode_operations
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
id|readpage
suffix:colon
id|rock_ridge_symlink_readpage
)brace
suffix:semicolon
eof
