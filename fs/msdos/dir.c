multiline_comment|/*&n; *  linux/fs/msdos/dir.c&n; *&n; *  Written 1992 by Werner Almesberger&n; *&n; *  MS-DOS directory handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|function|msdos_dir_read
r_static
r_int
id|msdos_dir_read
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
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_return
op_minus
id|EISDIR
suffix:semicolon
)brace
r_static
r_int
id|msdos_readdir
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
comma
r_struct
id|dirent
op_star
id|dirent
comma
r_int
id|count
)paren
suffix:semicolon
DECL|variable|msdos_dir_operations
r_static
r_struct
id|file_operations
id|msdos_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|msdos_dir_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|msdos_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
DECL|variable|msdos_dir_inode_operations
r_struct
id|inode_operations
id|msdos_dir_inode_operations
op_assign
(brace
op_amp
id|msdos_dir_operations
comma
multiline_comment|/* default directory file-ops */
id|msdos_create
comma
multiline_comment|/* create */
id|msdos_lookup
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
id|msdos_unlink
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
id|msdos_mkdir
comma
multiline_comment|/* mkdir */
id|msdos_rmdir
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
id|msdos_rename
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
id|msdos_bmap
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
DECL|function|msdos_readdir
r_static
r_int
id|msdos_readdir
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
comma
r_struct
id|dirent
op_star
id|dirent
comma
r_int
id|count
)paren
(brace
r_int
id|ino
comma
id|i
comma
id|i2
comma
id|last
suffix:semicolon
r_char
id|c
comma
op_star
id|walk
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
(brace
multiline_comment|/* Fake . and .. for the root directory. */
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|2
)paren
id|filp-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|filp-&gt;f_pos
OL
l_int|2
)paren
(brace
id|walk
op_assign
id|filp-&gt;f_pos
op_increment
ques
c_cond
l_string|&quot;..&quot;
suffix:colon
l_string|&quot;.&quot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|walk
suffix:semicolon
id|walk
op_increment
)paren
id|put_fs_byte
c_func
(paren
op_star
id|walk
comma
id|dirent-&gt;d_name
op_plus
id|i
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|MSDOS_ROOT_INO
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|dirent-&gt;d_name
op_plus
id|i
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_amp
(paren
r_sizeof
(paren
r_struct
id|msdos_dir_entry
)paren
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ino
op_assign
id|msdos_get_entry
c_func
(paren
id|inode
comma
op_amp
id|filp-&gt;f_pos
comma
op_amp
id|bh
comma
op_amp
id|de
)paren
)paren
OG
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_logical_and
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|de-&gt;name
)paren
)paren
(braket
l_int|0
)braket
op_ne
id|DELETED_FLAG
op_logical_and
op_logical_neg
(paren
id|de-&gt;attr
op_amp
id|ATTR_VOLUME
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|last
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|c
op_assign
id|de-&gt;name
(braket
id|i
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
id|c
op_add_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot; &squot;
)paren
id|last
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|c
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
)brace
id|i
op_assign
id|last
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;ext
(braket
l_int|0
)braket
op_logical_and
id|de-&gt;ext
(braket
l_int|0
)braket
op_ne
l_char|&squot; &squot;
)paren
(brace
id|put_fs_byte
c_func
(paren
l_char|&squot;.&squot;
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|i2
op_assign
l_int|0
suffix:semicolon
id|i2
OL
l_int|3
suffix:semicolon
id|i2
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|c
op_assign
id|de-&gt;ext
(braket
id|i2
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
id|c
op_add_assign
l_int|32
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|c
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot; &squot;
)paren
id|last
op_assign
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_assign
id|last
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|de-&gt;name
comma
id|MSDOS_DOT
)paren
)paren
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|de-&gt;name
comma
id|MSDOS_DOTDOT
)paren
)paren
id|ino
op_assign
id|msdos_parent_ino
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ino
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
