multiline_comment|/*&n; * linux/fs/minix/minix_op.c&n; *&n; * structures for the minix super_block/inode/file-operations&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
DECL|function|minix_put_inode
r_void
id|minix_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|minix_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|minix_free_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
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
comma
id|minix_bmap
comma
id|minix_truncate
comma
id|minix_write_inode
comma
id|minix_put_inode
)brace
suffix:semicolon
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the minix filesystem.&n; */
DECL|variable|minix_file_operations
r_struct
id|file_operations
id|minix_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|minix_file_read
comma
multiline_comment|/* read */
id|minix_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* close - default */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
multiline_comment|/* ioctl - default */
)brace
suffix:semicolon
DECL|variable|minix_dir_operations
r_struct
id|file_operations
id|minix_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|minix_file_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|minix_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* close - default */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
multiline_comment|/* ioctl - default */
)brace
suffix:semicolon
eof
