multiline_comment|/*&n; * linux/fs/minix/minix_op.c&n; *&n; * structures for the minix super_block/inode/file-operations&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
multiline_comment|/*&n; * These are the low-level inode operations for minix filesystem inodes.&n; */
DECL|variable|minix_inode_operations
r_struct
id|inode_operations
id|minix_inode_operations
op_assign
(brace
id|minix_create
comma
id|minix_lookup
comma
id|minix_link
comma
id|minix_unlink
comma
id|minix_symlink
comma
id|minix_mkdir
comma
id|minix_rmdir
comma
id|minix_mknod
comma
id|minix_rename
comma
id|minix_readlink
comma
id|minix_open
comma
id|minix_release
comma
id|minix_follow_link
)brace
suffix:semicolon
multiline_comment|/*&n; * We have just NULL&squot;s here: the current defaults are ok for&n; * the minix filesystem.&n; */
DECL|variable|minix_file_operations
r_struct
id|file_operations
id|minix_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
multiline_comment|/* write */
)brace
suffix:semicolon
eof
