multiline_comment|/*&n; *  linux/fs/affs/dir.c&n; *&n; *  (c) 1996  Hans-Joachim Widmaier - Rewritten&n; *&n; *  (C) 1993  Ray Burr - Modified for Amiga FFS filesystem.&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; *&n; *  affs directory handling functions&n; *&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
r_static
r_int
id|affs_readdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_int
id|affs_dir_read
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
r_int
id|count
)paren
suffix:semicolon
DECL|variable|affs_dir_operations
r_static
r_struct
id|file_operations
id|affs_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|affs_dir_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|affs_readdir
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
comma
multiline_comment|/* no special release code */
id|file_fsync
multiline_comment|/* default fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|affs_dir_inode_operations
r_struct
id|inode_operations
id|affs_dir_inode_operations
op_assign
(brace
op_amp
id|affs_dir_operations
comma
multiline_comment|/* default directory file-ops */
id|affs_create
comma
multiline_comment|/* create */
id|affs_lookup
comma
multiline_comment|/* lookup */
id|affs_link
comma
multiline_comment|/* link */
id|affs_unlink
comma
multiline_comment|/* unlink */
id|affs_symlink
comma
multiline_comment|/* symlink */
id|affs_mkdir
comma
multiline_comment|/* mkdir */
id|affs_rmdir
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
id|affs_rename
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
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permissions */
)brace
suffix:semicolon
r_static
r_int
DECL|function|affs_dir_read
id|affs_dir_read
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
DECL|function|affs_readdir
id|affs_readdir
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
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|j
comma
id|namelen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|hash_pos
suffix:semicolon
r_int
id|chain_pos
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_int
r_int
id|old
suffix:semicolon
r_int
id|stored
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dir_bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|fh_bh
suffix:semicolon
r_struct
id|inode
op_star
id|dir
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: readdir(ino=%ld,f_pos=%lu)&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|filp-&gt;f_pos
)paren
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
id|stored
op_assign
l_int|0
suffix:semicolon
id|dir_bh
op_assign
l_int|NULL
suffix:semicolon
id|fh_bh
op_assign
l_int|NULL
suffix:semicolon
id|dir
op_assign
l_int|NULL
suffix:semicolon
id|old
op_assign
id|filp-&gt;f_pos
op_amp
l_int|0x80000000
suffix:semicolon
id|filp-&gt;f_pos
op_and_assign
l_int|0x7FFFFFFF
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|0
)paren
(brace
id|filp-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|filp-&gt;f_pos
comma
id|inode-&gt;i_ino
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
op_increment
id|filp-&gt;f_pos
suffix:semicolon
id|stored
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|filp-&gt;f_pos
comma
id|affs_parent_ino
c_func
(paren
id|inode
)paren
)paren
OL
l_int|0
)paren
(brace
id|filp-&gt;f_pos
op_or_assign
l_int|0x80000000
suffix:semicolon
r_return
id|stored
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_assign
l_int|2
suffix:semicolon
id|stored
op_increment
suffix:semicolon
)brace
multiline_comment|/* Read original if this is a link */
id|ino
op_assign
id|inode-&gt;u.affs_i.i_original
ques
c_cond
id|inode-&gt;u.affs_i.i_original
suffix:colon
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
op_assign
id|iget
c_func
(paren
id|inode-&gt;i_sb
comma
id|ino
)paren
)paren
)paren
r_return
id|stored
suffix:semicolon
id|chain_pos
op_assign
(paren
id|filp-&gt;f_pos
op_minus
l_int|2
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|hash_pos
op_assign
(paren
id|filp-&gt;f_pos
op_minus
l_int|2
)paren
op_rshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|chain_pos
op_eq
l_int|0xffff
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AFFS: more than 65535 entries in chain&bslash;n&quot;
)paren
suffix:semicolon
id|chain_pos
op_assign
l_int|0
suffix:semicolon
id|hash_pos
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_assign
(paren
(paren
id|hash_pos
op_lshift
l_int|16
)paren
op_or
id|chain_pos
)paren
op_plus
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir_bh
op_assign
id|affs_bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|ino
comma
id|AFFS_I2BSIZE
c_func
(paren
id|inode
)paren
)paren
)paren
)paren
r_goto
id|readdir_done
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|stored
op_logical_or
op_logical_neg
id|old
)paren
(brace
r_while
c_loop
(paren
id|hash_pos
OL
id|AFFS_I2HSIZE
c_func
(paren
id|inode
)paren
op_logical_and
op_logical_neg
(paren
(paren
r_struct
id|dir_front
op_star
)paren
id|dir_bh-&gt;b_data
)paren
op_member_access_from_pointer
id|hashtable
(braket
id|hash_pos
)braket
)paren
id|hash_pos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hash_pos
op_ge
id|AFFS_I2HSIZE
c_func
(paren
id|inode
)paren
)paren
r_goto
id|readdir_done
suffix:semicolon
id|i
op_assign
id|htonl
c_func
(paren
(paren
(paren
r_struct
id|dir_front
op_star
)paren
id|dir_bh-&gt;b_data
)paren
op_member_access_from_pointer
id|hashtable
(braket
id|hash_pos
)braket
)paren
suffix:semicolon
id|j
op_assign
id|chain_pos
suffix:semicolon
multiline_comment|/* If the directory hasn&squot;t changed since the last call to readdir(),&n;&t;&t; * we can jump directly to where we left off.&n;&t;&t; */
r_if
c_cond
(paren
id|filp-&gt;private_data
op_logical_and
id|filp-&gt;f_version
op_eq
id|dir-&gt;i_version
)paren
(brace
id|i
op_assign
(paren
r_int
)paren
id|filp-&gt;private_data
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: readdir() left off=%d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|filp-&gt;f_version
op_assign
id|dir-&gt;i_version
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: hash_pos=%lu chain_pos=%lu&bslash;n&quot;
comma
id|hash_pos
comma
id|chain_pos
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fh_bh
op_assign
id|affs_bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|i
comma
id|AFFS_I2BSIZE
c_func
(paren
id|inode
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AFFS: readdir: Can&squot;t get block %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_goto
id|readdir_done
suffix:semicolon
)brace
id|ino
op_assign
id|i
suffix:semicolon
id|i
op_assign
id|htonl
c_func
(paren
id|FILE_END
c_func
(paren
id|fh_bh-&gt;b_data
comma
id|inode
)paren
op_member_access_from_pointer
id|hash_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|affs_brelse
c_func
(paren
id|fh_bh
)paren
suffix:semicolon
id|fh_bh
op_assign
l_int|NULL
suffix:semicolon
id|j
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fh_bh
)paren
(brace
id|namelen
op_assign
id|affs_get_file_name
c_func
(paren
id|AFFS_I2BSIZE
c_func
(paren
id|inode
)paren
comma
id|fh_bh-&gt;b_data
comma
op_amp
id|name
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: readdir(): filldir(..,&bslash;&quot;%.*s&bslash;&quot;,ino=%lu), i=%lu&bslash;n&quot;
comma
id|namelen
comma
id|name
comma
id|ino
comma
id|i
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|name
comma
id|namelen
comma
id|filp-&gt;f_pos
comma
id|ino
)paren
OL
l_int|0
)paren
r_goto
id|readdir_done
suffix:semicolon
id|filp-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|i
suffix:semicolon
id|affs_brelse
c_func
(paren
id|fh_bh
)paren
suffix:semicolon
id|fh_bh
op_assign
l_int|NULL
suffix:semicolon
id|stored
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|hash_pos
op_increment
suffix:semicolon
id|chain_pos
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|chain_pos
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_assign
(paren
(paren
id|hash_pos
op_lshift
l_int|16
)paren
op_or
id|chain_pos
)paren
op_plus
l_int|2
suffix:semicolon
)brace
id|readdir_done
suffix:colon
id|filp-&gt;f_pos
op_or_assign
id|old
suffix:semicolon
id|affs_brelse
c_func
(paren
id|dir_bh
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|fh_bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: readdir()=%d&bslash;n&quot;
comma
id|stored
)paren
suffix:semicolon
r_return
id|stored
suffix:semicolon
)brace
eof
