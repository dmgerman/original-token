multiline_comment|/*&n; *  linux/fs/sysv/dir.c&n; *&n; *  minix/dir.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/dir.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/dir.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent directory handling functions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|sysv_dir_read
r_static
r_int
id|sysv_dir_read
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
id|sysv_readdir
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
DECL|variable|sysv_dir_operations
r_static
r_struct
id|file_operations
id|sysv_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|sysv_dir_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|sysv_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll - default */
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
DECL|variable|sysv_dir_inode_operations
r_struct
id|inode_operations
id|sysv_dir_inode_operations
op_assign
(brace
op_amp
id|sysv_dir_operations
comma
multiline_comment|/* default directory file-ops */
id|sysv_create
comma
multiline_comment|/* create */
id|sysv_lookup
comma
multiline_comment|/* lookup */
id|sysv_link
comma
multiline_comment|/* link */
id|sysv_unlink
comma
multiline_comment|/* unlink */
id|sysv_symlink
comma
multiline_comment|/* symlink */
id|sysv_mkdir
comma
multiline_comment|/* mkdir */
id|sysv_rmdir
comma
multiline_comment|/* rmdir */
id|sysv_mknod
comma
multiline_comment|/* mknod */
id|sysv_rename
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
id|sysv_truncate
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|sysv_readdir
r_static
r_int
id|sysv_readdir
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
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
r_int
id|offset
comma
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|bh_data
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
comma
id|sde
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
(paren
id|sb
op_assign
id|inode-&gt;i_sb
)paren
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
(paren
r_int
r_int
)paren
(paren
id|filp-&gt;f_pos
)paren
op_mod
id|SYSV_DIRSIZE
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_while
c_loop
(paren
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
id|sb-&gt;sv_block_size_1
suffix:semicolon
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|inode
comma
id|filp-&gt;f_pos
op_rshift
id|sb-&gt;sv_block_size_bits
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|filp-&gt;f_pos
op_add_assign
id|sb-&gt;sv_block_size
op_minus
id|offset
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|bh_data
op_assign
id|bh-&gt;b_data
suffix:semicolon
r_while
c_loop
(paren
id|offset
OL
id|sb-&gt;sv_block_size
op_logical_and
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|offset
op_plus
id|bh_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
multiline_comment|/* Copy the directory entry first, because the directory&n;&t;&t;&t;&t; * might be modified while we sleep in filldir()...&n;&t;&t;&t;&t; */
id|memcpy
c_func
(paren
op_amp
id|sde
comma
id|de
comma
r_sizeof
(paren
r_struct
id|sysv_dir_entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sde.inode
OG
id|inode-&gt;i_sb-&gt;sv_ninodes
)paren
id|printk
c_func
(paren
l_string|&quot;sysv_readdir: Bad inode number on dev &quot;
l_string|&quot;%s, ino %ld, offset 0x%04lx: %d is out of range&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|inode-&gt;i_ino
comma
(paren
id|off_t
)paren
id|filp-&gt;f_pos
comma
id|sde.inode
)paren
suffix:semicolon
id|i
op_assign
id|strnlen
c_func
(paren
id|sde.name
comma
id|SYSV_NAMELEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|sde.name
comma
id|i
comma
id|filp-&gt;f_pos
comma
id|sde.inode
)paren
OL
l_int|0
)paren
(brace
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
)brace
id|offset
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
