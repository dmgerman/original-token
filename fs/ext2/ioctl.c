multiline_comment|/*&n; * linux/fs/ext2/ioctl.c&n; *&n; * Copyright (C) 1993  Remy Card (card@masi.ibp.fr)&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
DECL|function|ext2_ioctl
r_int
id|ext2_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
macro_line|#ifdef EXT2FS_DEBUG
id|printk
(paren
l_string|&quot;ext2_ioctl: cmd = %d, arg = %d&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
