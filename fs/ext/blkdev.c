multiline_comment|/*&n; *  linux/fs/ext/blkdev.c&n; *&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *&n; *  from&n; *&n; *  linux/fs/minix/blkdev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/*&n; * Called every time an ext block special file is opened&n; */
DECL|function|blkdev_open
r_static
r_int
id|blkdev_open
c_func
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
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|MAX_BLKDEV
op_logical_or
op_logical_neg
id|blkdev_fops
(braket
id|i
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|blkdev_fops
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op-&gt;open
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Dummy default file-operations: the only thing this does&n; * is contain the open that then fills in the correct operations&n; * depending on the special file...&n; */
DECL|variable|def_blk_fops
r_static
r_struct
id|file_operations
id|def_blk_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|blkdev_open
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
)brace
suffix:semicolon
DECL|variable|ext_blkdev_inode_operations
r_struct
id|inode_operations
id|ext_blkdev_inode_operations
op_assign
(brace
op_amp
id|def_blk_fops
comma
multiline_comment|/* default file operations */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
eof
