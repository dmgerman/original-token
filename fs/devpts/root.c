multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/devpts/root.c&n; *&n; *  Copyright 1998 H. Peter Anvin -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &quot;devpts_i.h&quot;
r_static
r_int
id|devpts_root_readdir
c_func
(paren
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
id|devpts_root_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|devpts_revalidate
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|variable|devpts_root_operations
r_static
r_struct
id|file_operations
id|devpts_root_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* llseek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
id|devpts_root_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
l_int|NULL
multiline_comment|/* lock */
)brace
suffix:semicolon
DECL|variable|devpts_root_inode_operations
r_struct
id|inode_operations
id|devpts_root_inode_operations
op_assign
(brace
op_amp
id|devpts_root_operations
comma
multiline_comment|/* file operations */
l_int|NULL
comma
multiline_comment|/* create */
id|devpts_root_lookup
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
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* updatepage */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|devpts_dentry_operations
r_static
r_struct
id|dentry_operations
id|devpts_dentry_operations
op_assign
(brace
id|devpts_revalidate
comma
multiline_comment|/* d_revalidate */
l_int|NULL
comma
multiline_comment|/* d_hash */
l_int|NULL
comma
multiline_comment|/* d_compare */
)brace
suffix:semicolon
multiline_comment|/*&n; * The normal naming convention is simply /dev/pts/&lt;number&gt;; this conforms&n; * to the System V naming convention&n; */
DECL|macro|genptsname
mdefine_line|#define genptsname(buf,num) sprintf(buf, &quot;%d&quot;, num)
DECL|function|devpts_root_readdir
r_static
r_int
id|devpts_root_readdir
c_func
(paren
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
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|devpts_sb_info
op_star
id|sbi
op_assign
id|SBI
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_sb
)paren
suffix:semicolon
id|off_t
id|nr
suffix:semicolon
r_char
id|numbuf
(braket
l_int|16
)braket
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
id|ENOTDIR
suffix:semicolon
id|nr
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_switch
c_cond
(paren
id|nr
)paren
(brace
r_case
l_int|0
suffix:colon
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
id|nr
comma
id|inode-&gt;i_ino
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_assign
op_increment
id|nr
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|1
suffix:colon
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
id|nr
comma
id|inode-&gt;i_ino
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_assign
op_increment
id|nr
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
(brace
)brace
r_while
c_loop
(paren
id|nr
OL
id|NR_PTYS
op_plus
l_int|2
)paren
(brace
r_int
id|ptynr
op_assign
id|nr
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;inodes
(braket
id|ptynr
)braket
)paren
(brace
id|genptsname
c_func
(paren
id|numbuf
comma
id|ptynr
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
id|numbuf
comma
id|strlen
c_func
(paren
id|numbuf
)paren
comma
id|nr
comma
id|nr
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_assign
op_increment
id|nr
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Revalidate is called on every cache lookup.  We use it to check that&n; * the pty really does still exist.  Never revalidate negative dentries;&n; * for simplicity (fix later?)&n; */
DECL|function|devpts_revalidate
r_static
r_int
id|devpts_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|devpts_sb_info
op_star
id|sbi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
r_return
l_int|0
suffix:semicolon
id|sbi
op_assign
id|SBI
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_sb
)paren
suffix:semicolon
r_return
(paren
id|sbi-&gt;inodes
(braket
id|dentry-&gt;d_inode-&gt;i_ino
op_minus
l_int|2
)braket
op_eq
id|dentry-&gt;d_inode
)paren
suffix:semicolon
)brace
DECL|function|devpts_root_lookup
r_static
r_int
id|devpts_root_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|devpts_sb_info
op_star
id|sbi
op_assign
id|SBI
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_int
id|entry
comma
id|i
suffix:semicolon
r_const
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
r_return
op_minus
id|ENOTDIR
suffix:semicolon
id|dentry-&gt;d_inode
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Assume failure */
id|dentry-&gt;d_op
op_assign
op_amp
id|devpts_dentry_operations
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
op_eq
l_int|1
op_logical_and
id|dentry-&gt;d_name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|entry
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OL
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
template_param
l_char|&squot;9&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|entry
op_assign
op_star
id|p
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dentry-&gt;d_name.len
op_minus
l_int|1
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
template_param
l_char|&squot;9&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|entry
op_mul_assign
l_int|10
suffix:semicolon
id|entry
op_add_assign
(paren
op_star
id|p
op_increment
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
)brace
id|dentry-&gt;d_inode
op_assign
id|sbi-&gt;inodes
(braket
id|entry
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
id|dentry-&gt;d_inode-&gt;i_count
op_increment
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
